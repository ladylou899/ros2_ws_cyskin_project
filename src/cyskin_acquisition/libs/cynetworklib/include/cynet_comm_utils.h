#ifndef CYNET_COMM_UTILS_H
#define CYNET_COMM_UTILS_H

/*
 * This class is a utility class that helps encode and decode packets of bootloader
 * or application type.  Some application type packets are generic and possible to
 * be decoded by this utility.  Other packets are custom user packets are minimally
 * processed here.
 */

#include <string>
#include <stdint.h>
#include <functional>
#include "cynet_config.h"
#include "cynet_ihb_info.h"
#ifdef CY_SUPPORT_SKIN
# include <skin_const.h>
# include <skin_const_pc.h>
#endif

#define CY_CHECKSUM_SUM 0
#define CY_CHECKSUM_CRC_16 1
#define CY_CHECKSUM_CRC_8 2
#define CY_CHECKSUM_AUTO 0xFF

class CyComm;
class CyTransmitProgress;

class CyCommUtils
{
	public:
		CyCommUtils(CyComm *c, int32_t cst_btld, int32_t cst_app);
		~CyCommUtils() {}

		/*
		 * encode functions: These functions encode a message and send it through `comm`.
		 * The return value is the same as `comm::write`
		 */
		int32_t send_bootloader_ping(CyIhbInfo ihb, CyTransmitProgress *status = NULL);
		int32_t send_bootloader_version_request(CyIhbInfo ihb, CyTransmitProgress *status = NULL);
		int32_t send_bootloader_exit(CyIhbInfo ihb, CyTransmitProgress *status = NULL);
		int32_t send_bootloader_get_subnets(CyIhbInfo ihb, CyTransmitProgress *status = NULL);
		int32_t send_bootloader_get_node(CyIhbInfo ihb, uint8_t subnet_n, uint8_t node_n, CyTransmitProgress *status = NULL);
		int32_t send_bootloader_start_host_mode(CyIhbInfo ihb, uint8_t subnet_n, uint8_t node_n, CyTransmitProgress *status = NULL);

		int32_t send_discovery_ping(CyTransmitProgress *status = NULL);
		int32_t send_discovery_set_id(CyIhbInfo ihb, uint16_t short_id, CyTransmitProgress *status = NULL);
		int32_t send_ping(CyIhbInfo ihb, CyTransmitProgress *status = NULL);
		int32_t send_custom(CyIhbInfo ihb, uint8_t command, unsigned char *data, uint8_t len, CyTransmitProgress *status = NULL);

#ifdef CY_SUPPORT_SKIN
		int32_t send_skin_module_program(CyIhbInfo ihb, uint8_t length, uint16_t address, uint8_t *data, uint8_t checksum, CyTransmitProgress *status = NULL);
		int32_t send_skin_module_program_end(CyIhbInfo ihb, CyTransmitProgress *status = NULL);
		int32_t send_skin_cold_reboot(CyIhbInfo ihb, CyTransmitProgress *status = NULL);
		int32_t send_skin_warm_reboot(CyIhbInfo ihb, CyTransmitProgress *status = NULL);
		int32_t send_skin_module_cold_reboot(CyIhbInfo ihb, CyTransmitProgress *status = NULL);
		int32_t send_skin_module_warm_reboot(CyIhbInfo ihb, CyTransmitProgress *status = NULL);
		int32_t send_skin_set_module_grouping(CyIhbInfo ihb, uint8_t module_id, uint8_t grouping, CyTransmitProgress *status = NULL);
		int32_t send_skin_set_auto_sync(CyIhbInfo ihb, uint8_t auto_sync, CyTransmitProgress *status = NULL);
		int32_t send_skin_set_auto_sync_period(CyIhbInfo ihb, uint16_t auto_sync_period, CyTransmitProgress *status = NULL);
		int32_t send_skin_set_comm_speed(CyIhbInfo ihb, uint8_t speed, CyTransmitProgress *status = NULL);
		int32_t send_skin_get_comm_speed(CyIhbInfo ihb, CyTransmitProgress *status = NULL);
		int32_t send_skin_sync(CyIhbInfo ihb, CyTransmitProgress *status = NULL);
		int32_t send_skin_declare(CyIhbInfo ihb, CyTransmitProgress *status = NULL);
		int32_t send_skin_module_details(CyIhbInfo ihb, uint8_t module_id, CyTransmitProgress *status = NULL);
		int32_t send_skin_version(CyIhbInfo ihb, CyTransmitProgress *status = NULL);
		int32_t send_skin_module_btldr_version(CyIhbInfo ihb, uint8_t module_id, CyTransmitProgress *status = NULL);
		int32_t send_skin_module_app_version(CyIhbInfo ihb, uint8_t module_id, CyTransmitProgress *status = NULL);
		int32_t send_skin_uid(CyIhbInfo ihb, CyTransmitProgress *status = NULL);
		int32_t send_skin_cdc_speed(CyIhbInfo ihb, uint8_t module_id, uint8_t speed, CyTransmitProgress *status = NULL);
		int32_t send_skin_set_cut_sensors(CyIhbInfo ihb, uint8_t module_id, uint16_t cut_sensors, CyTransmitProgress *status = NULL);
		int32_t send_skin_cdc_control(CyIhbInfo ihb, uint8_t module_id, uint8_t ctl, CyTransmitProgress *status = NULL);
		int32_t send_skin_phase_shift(CyIhbInfo ihb, uint8_t phase, CyTransmitProgress *status = NULL);
#endif

		/*
		 * decode functions: These functions decode a message and return various information.
		 * The input to these functions is the complete packet, header included.
		 */
		/* get_msg_status decodes and retrieves the status of message (one of CYRET_*) */
		uint8_t get_bootloader_msg_status(unsigned char *data, uint32_t len);
		std::string get_bootloader_version(unsigned char *data, uint32_t len);
		uint8_t get_bootloader_id(unsigned char *data, uint32_t len);

		uint8_t get_app_error(unsigned char *data, uint32_t len, uint8_t *command, uint8_t *error);
		const char *get_error_string(uint8_t error);	/* translate CY_CMD_ERROR_* to strings */

#ifdef CY_SUPPORT_SKIN
		uint8_t get_skin_module_program_status(unsigned char *data, uint32_t len, uint16_t *address);
		uint8_t get_skin_set_module_grouping(unsigned char *data, uint32_t len, uint8_t *module_id);
		uint8_t get_skin_get_comm_speed(unsigned char *data, uint32_t len, uint8_t *speed);
		/*
		 * declare could be responded both in bootloader and application.  If `modules_received` is 0,
		 * it's a bootloader response and only `module_count` is valid.
		 */
		uint8_t get_skin_declare(unsigned char *data, uint32_t len, uint8_t *module_count, uint8_t *module_start,
		uint8_t *modules_received, uint8_t sensor_count[SKIN_MODULE_COUNT_MAX]);
		
		/*
		 * details could also be responded both in bootloader and application.  If `cdc_output_count` is 0,
		 * then it's a bootloader response and only `module_id` and `module_sui` are valid.
		 */
		uint8_t get_skin_module_details(unsigned char *data, uint32_t len, uint8_t *module_id, uint32_t *module_sui, uint8_t *cdc_output_count,
		uint8_t *sensor_grouping, uint16_t *uncut_sensors, uint8_t *cdc_control, uint8_t *cdc_speed);
		std::string get_skin_version(unsigned char *data, uint32_t len);
		std::string get_skin_module_btldr_version(unsigned char *data, uint32_t len, uint8_t *module_id);
		std::string get_skin_module_app_version(unsigned char *data, uint32_t len, uint8_t *module_id);
		uint8_t get_skin_uid(unsigned char *data, uint32_t len, uint32_t *uid);
		uint8_t get_skin_cdc_speed(unsigned char *data, uint32_t len, uint8_t *module_id, uint8_t *speed);
		uint8_t get_skin_set_cut_sensors(unsigned char *data, uint32_t len, uint8_t *module_id, uint16_t *cut_sensors);
		uint8_t get_skin_cdc_control(unsigned char *data, uint32_t len, uint8_t *module_id, uint8_t *ctl);
		uint8_t get_skin_phase_shift(unsigned char *data, uint32_t len, uint8_t *phase);

		uint8_t get_skin_module_program_error(unsigned char *data, uint32_t len, uint16_t *address, uint8_t *module_id, uint8_t *error);
		uint8_t get_skin_set_module_grouping_error(unsigned char *data, uint32_t len, uint8_t *module_id);
		uint8_t get_skin_sync_error(unsigned char *data, uint32_t len, uint8_t *module_id);
		uint8_t get_skin_module_version_btldr_error(unsigned char *data, uint32_t len, uint8_t *module_id);
		uint8_t get_skin_module_version_app_error(unsigned char *data, uint32_t len, uint8_t *module_id);
		uint8_t get_skin_cdc_speed_error(unsigned char *data, uint32_t len, uint8_t *module_id);
		uint8_t get_skin_set_cut_sensors_error(unsigned char *data, uint32_t len, uint8_t *module_id);
		uint8_t get_skin_cdc_control_error(unsigned char *data, uint32_t len, uint8_t *module_id);

		const char *get_skin_program_error_string(uint8_t error);	/* translate SKIN_BOOTLOAD_* to strings */
#endif

	private:
		CyComm *comm;
		int32_t checksum_type_bootload;
		int32_t checksum_type_app;
		/*
		 * common functionality of send and get
		 *
		 * len is the size of the variable length payload, not including the header and footer
		 * sizes, which are fixed and known.
		 */
		/*
		 * caller of send_bootloader_packet must fill CY_BTLDR/APP_CMD(data) with the command
		 * and CY_BTLDR/APP_DATA(data, i) for i in [0, len-1) with data
		 */
		int32_t send_bootloader_packet(CyIhbInfo ihb, unsigned char *data, uint16_t len, CyTransmitProgress *status);
		int32_t send_packet(CyIhbInfo ihb, unsigned char *data, uint8_t len, CyTransmitProgress *status);
};

typedef int32_t CyUSec;

#define CY_0_MSEC	0
#define CY_INFINITE	0
#define CY_100_USEC 	100
#define CY_200_USEC 	200
#define CY_500_USEC 	500
#define CY_1_MSEC 	1000
#define CY_2_MSEC 	2000
#define CY_5_MSEC 	(5 * CY_1_MSEC)
#define CY_10_MSEC 	(2 * CY_5_MSEC)
#define CY_25_MSEC 	(5 * CY_5_MSEC)
#define CY_50_MSEC 	(2 * CY_25_MSEC)
#define CY_100_MSEC 	(2 * CY_50_MSEC)
#define CY_250_MSEC	(2 * CY_100_MSEC + CY_50_MSEC)
#define CY_500_MSEC	(2 * CY_250_MSEC)
#define CY_1_SEC	(10 * CY_100_MSEC)
#define CY_2_SEC	(2 * CY_1_SEC)
#define CY_5_SEC	(5 * CY_1_SEC)
#define CY_10_SEC	(2 * CY_5_SEC)

bool wait_func_change(std::function<bool ()>, CyUSec timeout = CY_0_MSEC, CyUSec microsec = CY_10_MSEC);

#endif
