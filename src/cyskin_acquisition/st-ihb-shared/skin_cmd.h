#ifndef SKIN_CMD_H
#define SKIN_CMD_H

/*
 * This file contains the list of commands that can be sent from the microcontroller
 * to the triangular modules.  The most common commands are sent in the same byte
 * as the address and are located at the two least significant bits:
 *     AAAA AACC
 * where
 *   * AAAAAA is the address and
 *   * CC is a common command (00 means no command).
 * A certain pattern for the common command denotes extended command where a second
 * byte follows containing further command codes.  The extended command will always
 * be in the form:
 *     CCCC CC00
 * to make sure even if it is read by a slave as an address/command combination
 * (i.e. first byte explained above), it would be ignored since 00 is code for
 * no command.
 *
 * These values shouldn't be considered stable until further tests are done.
 *
 * Note that address 0x00 and 0x3F are reserved.
 */

/*
 * The flow of the code on the triangular module would be:
 * <DISCOVERY PHASE>
 * 1. Respond to discovery pings
 * 2. Receive id and go to bootloader phase
 * <BOOTLOADER PHASE>
 * 3. While reprogram, read and (if enabled) install program
 * 4. If start command go to application phase
 * <APPLICATION PHASE>
 * 5. For ever
 * 5.1. Wait for command
 * 5.2. Execute command
 */

/***********************
 * frequent operations *
 ***********************/
/* to make sure extended commands are not taken as frequent operations */
#define SKIN_MODULE_CMD_NONE 0x00
/* read and return sensor values */
#define SKIN_MODULE_CMD_READ 0x01
/* synchronize and start CDC */
#define SKIN_MODULE_CMD_SYNC 0x02
/* extended command */
#define SKIN_MODULE_CMD_EXTENDED 0x03

/************************
 * discovery operations *
 ************************/
/*
 * discovery ping would be responded with a byte in the following format:
 *     ss1gg1ee
 * where `s` is 0 if the SUI is smaller than the pinged SUI, `g` is 0 if the
 * SUI is bigger than the pinged SUI and `e` is 0 if the SUI is equal to the
 * pinged SUI.  The MISO line acts as a wired-AND.
 */
#define SKIN_MODULE_CMD_DISCOVERY_PING 0xE0
/* old id is the ID that was assigned by the IHB last time the discovery was done */
#define SKIN_MODULE_CMD_DISCOVERY_OLD_ID 0xE4
/*
 * receive id would store an id assigned by the IHB and stop participating in the
 * discovery messages.
 */
#define SKIN_MODULE_CMD_DISCOVERY_RECV_ID 0xE8
/* jump to the bootloader application at the end of discovery */
#define SKIN_MODULE_CMD_DISCOVERY_END 0xEC
/*
 * reset the address to 0, so if discovery failed for a previously identified
 * triangle, that triangle wouldn't interfere with communication with the newly
 * identified triangles, because they could end up having the same id.
 */
#define SKIN_MODULE_CMD_DISCOVERY_UNIDENTIFY 0xF0

/************************
 * bootload operations  *
 ************************/
/* reprogram a block, always broadcast */
#define SKIN_MODULE_CMD_BOOTLOAD_REPROGRAM 0x04
/* get result of last reprogram and the calculated checksum */
#define SKIN_MODULE_CMD_BOOTLOAD_RESULT 0x08
/* enable programming */
#define SKIN_MODULE_CMD_BOOTLOAD_ENABLE 0x0C
/* disable programming */
#define SKIN_MODULE_CMD_BOOTLOAD_DISABLE 0x14

/************************
 * Execution Operations *
 ************************/
/* start the application (from bootloader) */
#define SKIN_MODULE_CMD_START 0x20
/* go back to discovery phase */
#define SKIN_MODULE_CMD_COLD_REBOOT 0x24
/* restart application */
#define SKIN_MODULE_CMD_WARM_REBOOT 0x28

/************************
 *   rare operations    *
 ************************/
/* #define UNUSED 0x30 (was set SPI speed, which is no longer needed) */
/* declare number of sensors */
#define SKIN_MODULE_CMD_DECLARE 0x34
/* get bootloader or application version */
#define SKIN_MODULE_CMD_BTLDR_VERSION 0x38
#define SKIN_MODULE_CMD_APP_VERSION 0x3C
/* set grouping of sensors */
#define SKIN_MODULE_CMD_GROUP 0x40
/* change power saving mode */
#define SKIN_MODULE_CMD_USE_HALT 0x44
#define SKIN_MODULE_CMD_USE_WFI 0x48
/* change CDC decimation */
#define SKIN_MODULE_CMD_CDC_SPEED 0x4C
/* set cut sensors */
#define SKIN_MODULE_CMD_SET_CUT_SENSORS 0x50

/************************
 *   debug operations   *
 ************************/
/* ping */
#define SKIN_MODULE_CMD_PING 0x80
/* Read the CDC version */
#define SKIN_MODULE_CMD_CDC_VERSION 0x84
/* disable, disable excitation or enable CDC conversion.  Takes one of SKIN_CDC_* as argument */
#define SKIN_MODULE_CMD_CDC_CONTROL 0x88
/* add a phase shift to measurements which is equal to arg*(id-SKIN_ADDRESS_MIN)*32us */
#define SKIN_MODULE_CMD_PHASE_SHIFT 0x90

#endif
