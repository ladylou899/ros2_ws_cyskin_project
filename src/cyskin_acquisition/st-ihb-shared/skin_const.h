#ifndef SKIN_CONST_H
#define SKIN_CONST_H

/*
 * This file includes constants in the skin, such as range of addresses, command
 * responses etc.
 */

/*
 * The address/command scheme is the following:
 * - The first byte sent has the following format:
 *     AAAAAACC
 *   where
 *     * AAAAAA is the address (0 and 0x3F are reserved) and
 *     * CC is a common command.
 *   In this scheme, the 0x03 command means extended command and therefore a
 *   second byte will follow with a command code.
 *
 * The master sends an address/command.  While the slaves are decoding it, it will
 * send the extended command, if any.  The slaves that don't match the address
 * ignore the command. (TODO: they could also decode the command and decide to
 * sleep for a certain time) The slave that matches the address would respond with
 * SKIN_COMMAND_GET_ARGS when it is ready to receive command arguments, if any. It
 * would then respond with SKIN_COMMAND_RESPONSE once it has the command's results
 * ready.  The rest of the communication is per command.
 *
 * For broadcast messages, the master sends 0x3F as address.  The slaves don't respond
 * and the master simply waits enough time (TODO: to be measured) to make sure the slaves
 * have done their job. (TODO: is this alright?)
 */

/* minimum and maximum addresses */
#define SKIN_ADDRESS_MIN 0x01
#define SKIN_ADDRESS_MAX 0x3E

/* invalid address to set when not communicating */
#define SKIN_ADDRESS_INVALID 0x00
/* broadcast address */
#define SKIN_ADDRESS_BROADCAST 0x3F

/* command get arguments.  When this is sent by the slave, the master starts sending command arguments */
#define SKIN_COMMAND_GET_ARGS 0x5A
/* command response value.  When this is sent by the slave, the master starts reading command response */
#define SKIN_COMMAND_RESPONSE 0xC3
/* command no response value to set when not yet ready to respond */
#define SKIN_COMMAND_NO_RESPONSE 0x00

/*
 * response parts of the discovery ping, 0 is a positive response.
 * The response has at least one 1 at 0x04, to make sure none of
 * SKIN_COMMAND_GET_ARGS and SKIN_COMMAND_RESPONSE would be taken as
 * ping response by mistake.
 */
#define SKIN_DISCOVERY_PING_SMALLER 0x3F
#define SKIN_DISCOVERY_PING_GREATER 0xE7
#define SKIN_DISCOVERY_PING_EQUAL 0xFC
#define SKIN_DISCOVERY_PING_NOT_PARTICIPATING 0xDF

/* bootload constants */
#define SKIN_BOOTLOAD_ROW_SIZE 64

/* error reporting values from the bootload phase */
#define SKIN_BOOTLOAD_SUCCESS 0xA5		/* programming successful */
#define SKIN_BOOTLOAD_FAIL 0x3C			/* programming failed or no programming command received */
#define SKIN_BOOTLOAD_CHECKSUM_ERROR 0x18	/* programming failed due to checksum error */
#define SKIN_BOOTLOAD_UNALIGNED 0x24		/* programming failed because given address was unaligned */
#define SKIN_BOOTLOAD_OUT_OF_RANGE 0x42		/* programming failed because given address is out of range */
#define SKIN_BOOTLOAD_BAD_INTERRUPT_VECTOR 0x7E	/* programming failed due to writing to interrupt vector with bad values */
#define SKIN_BOOTLOAD_PROTECTION_ERROR 0x99	/* programming failed because given address is protected */
#define SKIN_BOOTLOAD_READBACK_ERROR 0x66	/* programming failed because data read back from flash mismatches written data */
#define SKIN_BOOTLOAD_INCOMPATIBLE 0xDB		/* programming failed because application is incompatible with bootloader */
#define SKIN_BOOTLOAD_RAM_EXEC_ERROR 0xBD	/* programming didn't start because flash functions couldn't be copied to ram */
#define SKIN_BOOTLOAD_TIMEOUT 0xE7

/* maximum number of sensors on a triangular module */
#define SKIN_SENSOR_COUNT_MAX 12

/* grouping configuration of sensors */
#define SKIN_SENSOR_GROUP_NONE 0x00		/* sensors are individually read */
#define SKIN_SENSOR_GROUP_THREE 0x50		/* sensors are grouped in three groups */
#define SKIN_SENSOR_GROUP_ALL 0xF0		/* all sensors are grouped together */
#define SKIN_SENSOR_GROUP_AUTO 0x88		/* automatically detect and change grouping on the fly, *if* implemented */

/* CDC control */
#define SKIN_CDC_ENABLE 0x00			/* CDC works as normal */
#define SKIN_CDC_DISABLE_EXCITATION 0x50	/* CDC works but doesn't excite CINx pins */
#define SKIN_CDC_DISABLE 0xF0			/* CDC doesn't work and sync is ignored */

/* CDC decimation */
#define SKIN_CDC_SPEED_SLOW 0x00			/* 256 decimation */
#define SKIN_CDC_SPEED_AVERAGE 0x01			/* 128 decimation */
#define SKIN_CDC_SPEED_FAST 0x02			/* 64 decimation */

#endif
