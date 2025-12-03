#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Image
from std_msgs.msg import Float32
import numpy as np
import cv2
import onnxruntime as ort
from cv_bridge import CvBridge, CvBridgeError
import os
from ament_index_python.packages import get_package_share_directory

from rclpy.qos import QoSProfile, ReliabilityPolicy, HistoryPolicy

# onnx-native inference script 

from uc1_tactile_images.msg import ImageArrayLink 

class TactileInferenceNode(Node):
    def __init__(self):
        super().__init__('tactile_inference_node')

        qos_profile = QoSProfile(
            reliability=ReliabilityPolicy.BEST_EFFORT,  # or RELIABLE
            history=HistoryPolicy.KEEP_LAST,
            depth=10
        )


        # load ONNX model
        package_name = 'uc1_tactile_images'
        model_dir = os.path.join(get_package_share_directory(package_name), 'models_onnx')
        model_path = os.path.join(model_dir, 'HandsNet_handles_finetuned.onnx')
        self.get_logger().info(f"Loading model from: {model_path}")
        
        # run onnx-runtime session
        self.session = ort.InferenceSession(model_path)
        self.input_name = self.session.get_inputs()[0].name
        self.output_name = self.session.get_outputs()[0].name
        self.get_logger().info("ONNX model loaded successfully.")

        self.subscription = self.create_subscription(
            ImageArrayLink,
            "uc1_tactile_images/link2",  
            self.image_callback,
            qos_profile
        )

        # Publisher for inference result
        self.publisher_ = self.create_publisher(Float32, '/uc1_gestures/tactile_inference', 10)

        # opencv bridge
        self.bridge = CvBridge()

    def image_callback(self, msg):
        try:
            # sample image
            #cv_image = self.bridge.imgmsg_to_cv2(msg, desired_encoding='mono8')
            self.get_logger().info("Images received for inference.")

            gesture_sum = 0

            for i, img_msg in enumerate(msg.images):
                try:
                    cv_image = self.bridge.imgmsg_to_cv2(img_msg, desired_encoding='mono8')
                    #self.get_logger().info(f"Received image {i} with shape {cv_image.shape}")
                
                    # Example: show each image in a window
                    #cv2.imshow(f"Image {i}", cv_image)
                    # preprocessing (handsnet takes 68x100 grayscale images)
                    input_image = cv2.resize(cv_image, (100, 68)).astype(np.int8)
                    
                    input_image_net = input_image[np.newaxis, np.newaxis, :, :]  # Shape: [1, 1, H, W]
                    input_image_net = (input_image_net).astype(np.float32)  

                    # inference
                    input_feed = {self.input_name: input_image_net}
                    output = self.session.run([self.output_name], input_feed)
                    probability = output[0][0]
                    print(output)

                    if(probability[0] > 0.8):
                        self.get_logger().info(f"Inference result published, HAND")
                        gesture_sum += 1
                    else:
                        self.get_logger().info(f"Inference result published, NO HAND")

                    #self.get_logger().info(f"Inference result published: {probability[0]:.4f}")

                except Exception as e:
                    self.get_logger().error(f"Error converting image {i}: {e}")

            input_image_norm = input_image/255.0
            cv2.imshow("Debug Input Image", input_image_norm)
            cv2.waitKey(1)

            # Publish the result
            gesture_result = 0
            if(gesture_sum > 0):
                gesture_result = 1
            result_msg = Float32()
            result_msg.data = float(gesture_result) 
            self.publisher_.publish(result_msg)
        
        except CvBridgeError as e:
            self.get_logger().error(f"CvBridge Error: {str(e)}")

def main(args=None):
    rclpy.init(args=args)
    node = TactileInferenceNode()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
