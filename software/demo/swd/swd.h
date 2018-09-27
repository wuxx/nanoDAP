#ifndef __SWD_H__
#define __SWD_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

// ARM CoreSight SWD-DP packet request values
#define SW_IDCODE_RD            0xA5
#define SW_ABORT_WR             0x81
#define SW_CTRLSTAT_RD          0x8D
#define SW_CTRLSTAT_WR          0xA9
#define SW_RESEND_RD            0x95
#define SW_SELECT_WR            0xB1
#define SW_RDBUFF_RD            0xBD

// ARM CoreSight SW-DP packet request masks
#define SW_REQ_PARK_START       0x81
#define SW_REQ_PARITY           0x20
#define SW_REQ_A32              0x18
#define SW_REQ_RnW              0x04
#define SW_REQ_APnDP            0x02

// ARM CoreSight SW-DP packet acknowledge values
#define SW_ACK_OK               0x1
#define SW_ACK_WAIT             0x2
#define SW_ACK_FAULT            0x4
#define SW_ACK_PARITY_ERR       0x8

// ARM CoreSight DAP command values
#define DAP_IDCODE_RD           0x02
#define DAP_ABORT_WR            0x00
#define DAP_CTRLSTAT_RD         0x06
#define DAP_CTRLSTAT_WR         0x04
#define DAP_SELECT_WR           0x08
#define DAP_RDBUFF_RD           0x0E

// ARM CoreSight DAP command masks
#define DAP_CMD_PACKED          0x80
#define DAP_CMD_A32             0x0C
#define DAP_CMD_RnW             0x02
#define DAP_CMD_APnDP           0x01
#define DAP_CMD_MASK            0x0F

/*
b0: APnDP  0: DP;    1: AP
b1: RnW    0: Write; 1: Read
*/


#define DAP_RETRY_COUNT         255

// Command Status Response Codes
#define HOST_COMMAND_OK         0x55
#define HOST_INVALID_COMMAND    0x80
#define HOST_COMMAND_FAILED     0x81
#define HOST_AP_TIMEOUT         0x82
#define HOST_WIRE_ERROR         0x83
#define HOST_ACK_FAULT          0x84
#define HOST_DP_NOT_CONNECTED   0x85





// Cortex M3 Debug Registers (AHB addresses)
#define DDFSR   0xE000ED30      // Debug Fault StatusRegister
#define DHCSR   0xE000EDF0      // Debug Halting Control and Status Register
#define DCRSR   0xE000EDF4      // Debug Core Register Selector Register
#define DCRDR   0xE000EDF8      // Debug Core Register Data Register
#define DEMCR   0xE000EDFC      // Debug Exception and Monitor Control Register
#define AIRCR   0xE000ED0C      // The Application Interrupt and Reset Control Register

//  Cortex M3 Memory Access Port
#define MEMAP_BANK_0  0x00000000       // BANK 0 => CSW, TAR, Reserved, DRW
#define MEMAP_BANK_1  0x00000010       // BANK 1 => BD0, BD1, BD2, BD3

// SiM3 Chip Access Port (SiLabs specific Debug Access Port)
#define CHIPAP_BANK_0  0x0A000000      // BANK 0 => CTRL1, CTRL2, LOCK, CRC
#define CHIPAP_BANK_1  0x0A000010      // BANK 1 => INIT_STAT, DAP_IN, DAP_OUT, None
#define CHIPAP_BANK_F  0x0A0000F0      // BANK F => None, None, None, ID

// MEMAP register addresses
#define MEMAP_CSW_WR  0x01
#define MEMAP_CSW_RD  0x03

#define MEMAP_TAR_WR  0x05

#define MEMAP_DRW_WR  0x0D
#define MEMAP_DRW_RD  0x0F

// CHIPAP register addresses
#define CHIPAP_CTRL1_WR     0x01
#define CHIPAP_CTRL2_WR     0x05
#define CHIPAP_ID_WR        0x0D
#define CHIPAP_ID_RD        0x0F

#define MEMAP_ID_RD        0xFF

typedef unsigned int u32;
typedef   signed int s32;

typedef unsigned short u16;
typedef   signed short s16;

typedef unsigned char u8;
typedef   signed char s8;

void gpio_init();
int gpio_get(int gpio_num);
void gpio_set(int gpio_num, int value);
void gpio_mode(int gpio_num, char *direct);

/* BCM GPIO NUM */
#if 0
#define SWD_CLK     (26)
#define SWD_IO      (19)
#else
/* wPi GPIO NUM */
#define SWD_CLK     (25)
#define SWD_IO      (24)
#endif

#endif /* __SWD_H__ */
