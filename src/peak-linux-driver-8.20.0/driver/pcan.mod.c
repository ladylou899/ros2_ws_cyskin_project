#include <linux/module.h>
#include <linux/export-internal.h>
#include <linux/compiler.h>

MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};



static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0x9dd4105e, "free_irq" },
	{ 0x0dba6eb8, "usb_alloc_urb" },
	{ 0xa61fd7aa, "__check_object_size" },
	{ 0xd6d46b9d, "usb_free_urb" },
	{ 0xc2614bbe, "param_ops_uint" },
	{ 0xc2614bbe, "param_ops_ulong" },
	{ 0x092a35a2, "_copy_from_user" },
	{ 0xef95a802, "pci_enable_device" },
	{ 0x534ed5f3, "__msecs_to_jiffies" },
	{ 0xd710adbf, "__kmalloc_noprof" },
	{ 0x680628e7, "ktime_get_ts64" },
	{ 0x3035da58, "usb_get_current_frame_number" },
	{ 0x82c6f73b, "proc_create" },
	{ 0xc2614bbe, "param_ops_ushort" },
	{ 0x954b0cc3, "pci_iomap" },
	{ 0xa53f4e29, "memmove" },
	{ 0x40a621c5, "snprintf" },
	{ 0xcce79cbd, "i2c_bit_add_bus" },
	{ 0x22b38870, "sysfs_add_file_to_group" },
	{ 0xc87f4bab, "finish_wait" },
	{ 0xaba46e12, "usb_register_driver" },
	{ 0x04cf7d01, "__pci_register_driver" },
	{ 0x12ad300e, "iounmap" },
	{ 0xc2614bbe, "param_array_ops" },
	{ 0xbd06710b, "pci_request_regions" },
	{ 0xa53f4e29, "memcpy" },
	{ 0xcb8b6ec6, "kfree" },
	{ 0xfc8fa4ce, "seq_lseek" },
	{ 0x0feb1e94, "usleep_range_state" },
	{ 0x0db8d68d, "prepare_to_wait_event" },
	{ 0x2352b148, "timer_delete_sync" },
	{ 0x7851be11, "net_ratelimit" },
	{ 0x16ab4215, "__wake_up" },
	{ 0xe5305ebf, "pci_irq_vector" },
	{ 0xc2614bbe, "param_ops_byte" },
	{ 0xe1e1f979, "_raw_spin_lock_irqsave" },
	{ 0x5723059f, "msleep_interruptible" },
	{ 0xc720a5c5, "pci_unregister_driver" },
	{ 0x24db4285, "__release_region" },
	{ 0xd272d446, "__fentry__" },
	{ 0x5a844b26, "__x86_indirect_thunk_rax" },
	{ 0xe8213e80, "_printk" },
	{ 0xab8c49a5, "usb_clear_halt" },
	{ 0x6ac784f4, "schedule_timeout" },
	{ 0xd272d446, "schedule" },
	{ 0x76a26ca1, "usb_bulk_msg" },
	{ 0xe034b191, "usb_reset_device" },
	{ 0xd272d446, "__stack_chk_fail" },
	{ 0x8ce83585, "queue_delayed_work_on" },
	{ 0x4d40f3a6, "const_pcpu_hot" },
	{ 0x5a844b26, "__x86_indirect_thunk_rdx" },
	{ 0x0819dba7, "usb_submit_urb" },
	{ 0x9878df8a, "_dev_info" },
	{ 0x1c4d4c28, "i2c_del_adapter" },
	{ 0x61079369, "print_hex_dump" },
	{ 0x90a48d82, "__ubsan_handle_out_of_bounds" },
	{ 0x7a5ffe84, "init_wait_entry" },
	{ 0x9878df8a, "_dev_err" },
	{ 0x9126ce86, "request_threaded_irq" },
	{ 0x5a844b26, "__x86_indirect_thunk_r14" },
	{ 0x32feeafc, "mod_timer" },
	{ 0xbd03ed67, "random_kmalloc_seed" },
	{ 0xf46d5bf3, "mutex_lock" },
	{ 0x3019c1c7, "dma_alloc_attrs" },
	{ 0x9d89dcf0, "pci_read_config_word" },
	{ 0x837202b8, "usb_control_msg" },
	{ 0xc609ff70, "strncpy" },
	{ 0x60cb08fa, "usb_set_interface" },
	{ 0x680628e7, "ktime_get_raw_ts64" },
	{ 0x97dd6ca9, "ioremap" },
	{ 0x14fcde53, "class_unregister" },
	{ 0x680628e7, "ktime_get_real_ts64" },
	{ 0x402db74e, "memcmp" },
	{ 0xb90a7d07, "sysfs_remove_file_from_group" },
	{ 0xa24b1056, "_raw_spin_trylock" },
	{ 0xc1e6c71e, "__mutex_init" },
	{ 0xef4e4365, "usb_deregister" },
	{ 0xe54e0a6b, "__fortify_panic" },
	{ 0xe199f25f, "jiffies_to_msecs" },
	{ 0x81a1a811, "_raw_spin_unlock_irqrestore" },
	{ 0x022d2c4d, "pci_iounmap" },
	{ 0xb311a158, "ns_to_timespec64" },
	{ 0x2044b429, "ioport_resource" },
	{ 0x27683a56, "memset" },
	{ 0x9878df8a, "_dev_warn" },
	{ 0x07d971fc, "pci_alloc_irq_vectors_affinity" },
	{ 0x33ba6a25, "pci_set_master" },
	{ 0xc2614bbe, "param_ops_charp" },
	{ 0xd272d446, "__x86_return_thunk" },
	{ 0x092a35a2, "_copy_to_user" },
	{ 0x31228bf6, "dma_get_required_mask" },
	{ 0x5403c125, "__init_waitqueue_head" },
	{ 0x888b8f57, "strcmp" },
	{ 0x058c185a, "jiffies" },
	{ 0x64198441, "dma_set_coherent_mask" },
	{ 0xb3f8c2e9, "pv_ops" },
	{ 0xbd4e501f, "seq_read" },
	{ 0xdd6830c7, "sprintf" },
	{ 0xcd973881, "device_create_with_groups" },
	{ 0x82fd7238, "__ubsan_handle_shift_out_of_bounds" },
	{ 0x970a5970, "dma_free_attrs" },
	{ 0xf46d5bf3, "mutex_unlock" },
	{ 0x85acaba2, "cancel_delayed_work_sync" },
	{ 0x02f9bbf0, "init_timer_key" },
	{ 0x2b718ccd, "pci_release_regions" },
	{ 0xcbae5412, "__const_udelay" },
	{ 0xc9a51767, "driver_for_each_device" },
	{ 0x5a844b26, "__x86_indirect_thunk_rcx" },
	{ 0x11169e9e, "__register_chrdev" },
	{ 0x6fdeeff0, "device_destroy" },
	{ 0x33c78c8a, "remove_proc_entry" },
	{ 0x70db3fe4, "__kmalloc_cache_noprof" },
	{ 0xd6d46b9d, "usb_kill_urb" },
	{ 0x97acb853, "ktime_get" },
	{ 0x75738bed, "__warn_printk" },
	{ 0xf2c4f3f1, "seq_printf" },
	{ 0x71798f7e, "delayed_work_timer_fn" },
	{ 0x0a589842, "simple_strtoul" },
	{ 0x91312ce0, "i2c_transfer" },
	{ 0x33ba6a25, "pci_disable_device" },
	{ 0x1c85979c, "usb_reset_endpoint" },
	{ 0xcb077514, "single_release" },
	{ 0x64198441, "dma_set_mask" },
	{ 0x5a844b26, "__x86_indirect_thunk_r12" },
	{ 0xe4de56b4, "__ubsan_handle_load_invalid_value" },
	{ 0x2044b429, "iomem_resource" },
	{ 0x003b23f9, "single_open" },
	{ 0xbf58f025, "pci_write_config_word" },
	{ 0x8a64c8b7, "pci_free_irq_vectors" },
	{ 0x5a844b26, "__x86_indirect_thunk_r8" },
	{ 0xd272d446, "BUG_func" },
	{ 0xb6064240, "class_register" },
	{ 0x12ca6142, "ktime_get_with_offset" },
	{ 0x7851be11, "__SCT__might_resched" },
	{ 0xfed1e3bc, "kmalloc_caches" },
	{ 0x52ebbba3, "__request_region" },
	{ 0xaef1f20d, "system_wq" },
	{ 0x52b15b3b, "__unregister_chrdev" },
	{ 0xba157484, "module_layout" },
};

static const u32 ____version_ext_crcs[]
__used __section("__version_ext_crcs") = {
	0x9dd4105e,
	0x0dba6eb8,
	0xa61fd7aa,
	0xd6d46b9d,
	0xc2614bbe,
	0xc2614bbe,
	0x092a35a2,
	0xef95a802,
	0x534ed5f3,
	0xd710adbf,
	0x680628e7,
	0x3035da58,
	0x82c6f73b,
	0xc2614bbe,
	0x954b0cc3,
	0xa53f4e29,
	0x40a621c5,
	0xcce79cbd,
	0x22b38870,
	0xc87f4bab,
	0xaba46e12,
	0x04cf7d01,
	0x12ad300e,
	0xc2614bbe,
	0xbd06710b,
	0xa53f4e29,
	0xcb8b6ec6,
	0xfc8fa4ce,
	0x0feb1e94,
	0x0db8d68d,
	0x2352b148,
	0x7851be11,
	0x16ab4215,
	0xe5305ebf,
	0xc2614bbe,
	0xe1e1f979,
	0x5723059f,
	0xc720a5c5,
	0x24db4285,
	0xd272d446,
	0x5a844b26,
	0xe8213e80,
	0xab8c49a5,
	0x6ac784f4,
	0xd272d446,
	0x76a26ca1,
	0xe034b191,
	0xd272d446,
	0x8ce83585,
	0x4d40f3a6,
	0x5a844b26,
	0x0819dba7,
	0x9878df8a,
	0x1c4d4c28,
	0x61079369,
	0x90a48d82,
	0x7a5ffe84,
	0x9878df8a,
	0x9126ce86,
	0x5a844b26,
	0x32feeafc,
	0xbd03ed67,
	0xf46d5bf3,
	0x3019c1c7,
	0x9d89dcf0,
	0x837202b8,
	0xc609ff70,
	0x60cb08fa,
	0x680628e7,
	0x97dd6ca9,
	0x14fcde53,
	0x680628e7,
	0x402db74e,
	0xb90a7d07,
	0xa24b1056,
	0xc1e6c71e,
	0xef4e4365,
	0xe54e0a6b,
	0xe199f25f,
	0x81a1a811,
	0x022d2c4d,
	0xb311a158,
	0x2044b429,
	0x27683a56,
	0x9878df8a,
	0x07d971fc,
	0x33ba6a25,
	0xc2614bbe,
	0xd272d446,
	0x092a35a2,
	0x31228bf6,
	0x5403c125,
	0x888b8f57,
	0x058c185a,
	0x64198441,
	0xb3f8c2e9,
	0xbd4e501f,
	0xdd6830c7,
	0xcd973881,
	0x82fd7238,
	0x970a5970,
	0xf46d5bf3,
	0x85acaba2,
	0x02f9bbf0,
	0x2b718ccd,
	0xcbae5412,
	0xc9a51767,
	0x5a844b26,
	0x11169e9e,
	0x6fdeeff0,
	0x33c78c8a,
	0x70db3fe4,
	0xd6d46b9d,
	0x97acb853,
	0x75738bed,
	0xf2c4f3f1,
	0x71798f7e,
	0x0a589842,
	0x91312ce0,
	0x33ba6a25,
	0x1c85979c,
	0xcb077514,
	0x64198441,
	0x5a844b26,
	0xe4de56b4,
	0x2044b429,
	0x003b23f9,
	0xbf58f025,
	0x8a64c8b7,
	0x5a844b26,
	0xd272d446,
	0xb6064240,
	0x12ca6142,
	0x7851be11,
	0xfed1e3bc,
	0x52ebbba3,
	0xaef1f20d,
	0x52b15b3b,
	0xba157484,
};
static const char ____version_ext_names[]
__used __section("__version_ext_names") =
	"free_irq\0"
	"usb_alloc_urb\0"
	"__check_object_size\0"
	"usb_free_urb\0"
	"param_ops_uint\0"
	"param_ops_ulong\0"
	"_copy_from_user\0"
	"pci_enable_device\0"
	"__msecs_to_jiffies\0"
	"__kmalloc_noprof\0"
	"ktime_get_ts64\0"
	"usb_get_current_frame_number\0"
	"proc_create\0"
	"param_ops_ushort\0"
	"pci_iomap\0"
	"memmove\0"
	"snprintf\0"
	"i2c_bit_add_bus\0"
	"sysfs_add_file_to_group\0"
	"finish_wait\0"
	"usb_register_driver\0"
	"__pci_register_driver\0"
	"iounmap\0"
	"param_array_ops\0"
	"pci_request_regions\0"
	"memcpy\0"
	"kfree\0"
	"seq_lseek\0"
	"usleep_range_state\0"
	"prepare_to_wait_event\0"
	"timer_delete_sync\0"
	"net_ratelimit\0"
	"__wake_up\0"
	"pci_irq_vector\0"
	"param_ops_byte\0"
	"_raw_spin_lock_irqsave\0"
	"msleep_interruptible\0"
	"pci_unregister_driver\0"
	"__release_region\0"
	"__fentry__\0"
	"__x86_indirect_thunk_rax\0"
	"_printk\0"
	"usb_clear_halt\0"
	"schedule_timeout\0"
	"schedule\0"
	"usb_bulk_msg\0"
	"usb_reset_device\0"
	"__stack_chk_fail\0"
	"queue_delayed_work_on\0"
	"const_pcpu_hot\0"
	"__x86_indirect_thunk_rdx\0"
	"usb_submit_urb\0"
	"_dev_info\0"
	"i2c_del_adapter\0"
	"print_hex_dump\0"
	"__ubsan_handle_out_of_bounds\0"
	"init_wait_entry\0"
	"_dev_err\0"
	"request_threaded_irq\0"
	"__x86_indirect_thunk_r14\0"
	"mod_timer\0"
	"random_kmalloc_seed\0"
	"mutex_lock\0"
	"dma_alloc_attrs\0"
	"pci_read_config_word\0"
	"usb_control_msg\0"
	"strncpy\0"
	"usb_set_interface\0"
	"ktime_get_raw_ts64\0"
	"ioremap\0"
	"class_unregister\0"
	"ktime_get_real_ts64\0"
	"memcmp\0"
	"sysfs_remove_file_from_group\0"
	"_raw_spin_trylock\0"
	"__mutex_init\0"
	"usb_deregister\0"
	"__fortify_panic\0"
	"jiffies_to_msecs\0"
	"_raw_spin_unlock_irqrestore\0"
	"pci_iounmap\0"
	"ns_to_timespec64\0"
	"ioport_resource\0"
	"memset\0"
	"_dev_warn\0"
	"pci_alloc_irq_vectors_affinity\0"
	"pci_set_master\0"
	"param_ops_charp\0"
	"__x86_return_thunk\0"
	"_copy_to_user\0"
	"dma_get_required_mask\0"
	"__init_waitqueue_head\0"
	"strcmp\0"
	"jiffies\0"
	"dma_set_coherent_mask\0"
	"pv_ops\0"
	"seq_read\0"
	"sprintf\0"
	"device_create_with_groups\0"
	"__ubsan_handle_shift_out_of_bounds\0"
	"dma_free_attrs\0"
	"mutex_unlock\0"
	"cancel_delayed_work_sync\0"
	"init_timer_key\0"
	"pci_release_regions\0"
	"__const_udelay\0"
	"driver_for_each_device\0"
	"__x86_indirect_thunk_rcx\0"
	"__register_chrdev\0"
	"device_destroy\0"
	"remove_proc_entry\0"
	"__kmalloc_cache_noprof\0"
	"usb_kill_urb\0"
	"ktime_get\0"
	"__warn_printk\0"
	"seq_printf\0"
	"delayed_work_timer_fn\0"
	"simple_strtoul\0"
	"i2c_transfer\0"
	"pci_disable_device\0"
	"usb_reset_endpoint\0"
	"single_release\0"
	"dma_set_mask\0"
	"__x86_indirect_thunk_r12\0"
	"__ubsan_handle_load_invalid_value\0"
	"iomem_resource\0"
	"single_open\0"
	"pci_write_config_word\0"
	"pci_free_irq_vectors\0"
	"__x86_indirect_thunk_r8\0"
	"BUG_func\0"
	"class_register\0"
	"ktime_get_with_offset\0"
	"__SCT__might_resched\0"
	"kmalloc_caches\0"
	"__request_region\0"
	"system_wq\0"
	"__unregister_chrdev\0"
	"module_layout\0"
;

MODULE_INFO(depends, "i2c-algo-bit");

MODULE_ALIAS("usb:v0C72p000Cd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0C72p000Dd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0C72p0012d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0C72p0011d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0C72p0013d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0C72p0014d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("pci:v0000001Cd00000001sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v0000001Cd00000003sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v0000001Cd00000004sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v0000001Cd00000005sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v0000001Cd00000006sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v0000001Cd00000007sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v0000001Cd00000008sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v0000001Cd00000009sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v0000001Cd00000002sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v0000001Cd0000000Asv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v0000001Cd00000010sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v0000001Cd00000013sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v0000001Cd00000014sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v0000001Cd00000016sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v0000001Cd00000017sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v0000001Cd00000018sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v0000001Cd00000019sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v0000001Cd0000001Asv*sd*bc*sc*i*");

MODULE_INFO(srcversion, "4D8A17286A9F60256682269");
