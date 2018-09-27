#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "swd.h"

u8 io_byte;
u32 io_word;

const u8 even_parity[] =
{
    0x00, 0x10, 0x10, 0x00,
    0x10, 0x00, 0x00, 0x10,
    0x10, 0x00, 0x00, 0x10,
    0x00, 0x10, 0x10, 0x00
};

#define get_bit(x, bit_index) ((x >> bit_index) & 0x1)

void set_bit(u32 *x, u32 bit_index, u32 b)
{
    u32 _x;
    u32 bit_mask;
    _x = *x;
    if (get_bit(_x, bit_index) != b) {
        if (b == 0) {
            bit_mask = ~(0x1 << bit_index);
            *x = (_x) & bit_mask;
        } else {    /* b == 1 */
            bit_mask = (0x1 << bit_index);
            *x = (_x) | bit_mask;
        }
    }
}


void swd_clk()
{
	gpio_set(SWD_CLK, 1);
	usleep(10);
	gpio_set(SWD_CLK, 0);
	usleep(10);
}

void SW_ShiftReset(void)
{
    u8 i;

    // Drive SWDIO high
	gpio_set(SWD_IO, 1);

    // Complete 64 SWCLK cycles
    for (i = 64; i != 0; i--)
    {
		swd_clk();
    }
}

void SW_ShiftByteOut(u8 byte)
{
	u32 i;
    // Make sure SWDIO is an output
	//gpio_set(SWD_IO, 1);

    // Shift 8-bits out on SWDIO
    for(i = 0; i < 8; i++) {
        gpio_set(SWD_IO, get_bit(byte, i));
		swd_clk();
    }

}

u8 SW_ShiftByteIn(void)
{
	u32 i;
	u32 byte; /* FIXME: u8 */

	for(i = 0; i < 8; i++) {
		set_bit(&byte, i, gpio_get(SWD_IO));
		swd_clk();
	}

    // Return the byte that was shifted in
    return (u8)byte;
}

u8 SW_CalcDataParity(u8 *byte_array)
{
    u8 parity;

    // Calculate column parity, reducing down to 4 columns
    parity  = byte_array[0];
    parity ^= byte_array[1];
    parity ^= byte_array[2];
    parity ^= byte_array[3];
    parity ^= parity >> 4;

    // Use lookup table to get parity on 4 remaining bits. The cast (bit)
    // converts any non-zero value to 1.
    if (even_parity[parity & 0xF]) {
        return 1;
    } else {
        return 0;
    }
}

u8 ack_error;

u8 SW_ShiftPacket(u8 request, u8 retry)
{
    u8 ack, limit, i;
	u8 b0, b1, b2;
	u8 *byte_array = (u8 *)(&io_word);

    // If retry parameter is zero, use the default value instead
    if (retry == 0)
    {
        retry = DAP_RETRY_COUNT;
    }
    limit = retry;

    // While waiting, do request phase (8-bit request, turnaround, 3-bit ack)
    do
    {
        // Turnaround or idle cycle, makes or keeps SWDIO an output
        gpio_mode(SWD_IO, "out");
		gpio_set(SWD_IO, 0);
		swd_clk();

        // Shift out the 8-bit packet request
        SW_ShiftByteOut(request);

		swd_clk();

        io_byte = 0;

        gpio_mode(SWD_IO, "in");
        b0 = gpio_get(SWD_IO);  swd_clk();
        b1 = gpio_get(SWD_IO);  swd_clk();
        b2 = gpio_get(SWD_IO);  swd_clk();

        set_bit((u32 *)&io_byte, 0, b0);    /* FIXME: u8 */
        set_bit((u32 *)&io_byte, 1, b1);    /* FIXME: u8 */
        set_bit((u32 *)&io_byte, 2, b2);    /* FIXME: u8 */

		ack = io_byte;

        // Check if we need to retry the request
        if ((ack == SW_ACK_WAIT) && --retry)
        {
            // Delay an increasing amount with each retry
            for (i=retry; i < limit; i++);
        }
        else
        {
            break;  // Request phase complete (or timeout)
        }
    }
    while (1);

    // If the request was accepted, do the data transfer phase (turnaround if
    // writing, 32-bit data, and parity)
    if (ack == SW_ACK_OK)
    {
        if (request & SW_REQ_RnW)
        {
            gpio_mode(SWD_IO, "in");
            // Swap endian order while shifting in 32-bits of data
            byte_array[0] = SW_ShiftByteIn();
            byte_array[1] = SW_ShiftByteIn();
            byte_array[2] = SW_ShiftByteIn();
            byte_array[3] = SW_ShiftByteIn();

            // Shift in the parity bit
			b0 = gpio_get(SWD_IO);
			swd_clk();

            // Check for parity error
            if (b0 ^ SW_CalcDataParity(byte_array))
            {
                ack = SW_ACK_PARITY_ERR;
            }
        }
        else
        {
            // Turnaround cycle makes SWDIO an output
            gpio_mode(SWD_IO, "out");
            swd_clk();

            // Swap endian order while shifting out 32-bits of data
            SW_ShiftByteOut(byte_array[0]);
            SW_ShiftByteOut(byte_array[1]);
            SW_ShiftByteOut(byte_array[2]);
            SW_ShiftByteOut(byte_array[3]);

            // Shift out the parity bit
            gpio_set(SWD_IO, get_bit(SW_CalcDataParity(byte_array), 0)); 
            //gpio_set(SWD_IO, 0); 
			swd_clk();
        }
    }
    // TODO: Add error (FAULT, line, parity) handling here?  RESEND on parity error?

    // Turnaround or idle cycle, always leave SWDIO an output
    gpio_mode(SWD_IO, "out");
	gpio_set(SWD_IO, 0);
	swd_clk();

    // Update the global error accumulator if there was an error
    if (ack != SW_ACK_OK)
    {
        ack_error = ack;
    }
    return ack;
}

u8 SW_Response(u8 SW_Ack)
{
    switch (SW_Ack)
	{
		case SW_ACK_OK:     return HOST_COMMAND_OK;
		case SW_ACK_WAIT:   return HOST_AP_TIMEOUT;
		case SW_ACK_FAULT:  return HOST_ACK_FAULT;
		default:            return HOST_WIRE_ERROR;
	}
}

u8 SWD_LineReset(void)
{
    u8 ack;

    // Complete SWD reset sequence (50 cycles high followed by 2 or more idle cycles)
    SW_ShiftReset();
    SW_ShiftByteOut(0);

    // Now read the DPIDR register to move the SWD out of reset
    ack = SW_ShiftPacket(SW_IDCODE_RD, 1);

    SW_ShiftByteOut(0);

    return SW_Response(ack);
}

u8 SW_Request(u8 DAP_Addr)
{
    u8 req;

    // Convert the DAP address into a SWD packet request value
    req = DAP_Addr & DAP_CMD_MASK;      // mask off the bank select bits
    req = req | even_parity[req];       // compute and add parity bit
    req = req << 1;                     // move address/parity bits
    req = req | SW_REQ_PARK_START;      // add start and park bits
    return req;
}

void SW_DAP_Read(u8 cnt, u8 DAP_Addr, u32 * read_data)
{
    u8 req;

    // Format the packet request header
    req = SW_Request(DAP_Addr);

    // Shift the first packet and if DP access, send the results
    SW_ShiftPacket(req, 0);
    if (!(req & SW_REQ_APnDP))
    {
        *read_data = io_word;
        read_data++;
    }

    // Perform the requested number of reads
    for (; cnt != 0; cnt--)
    {
        SW_ShiftPacket(req, 0);
        *read_data = io_word;
        read_data++;
    }

    // For AP access, get and send results of the last read
    if (req & SW_REQ_APnDP)
    {
        SW_ShiftPacket(SW_RDBUFF_RD, 0);
        *read_data = io_word;
        read_data++;
    }
}

void SW_DAP_Write(u8 cnt, u8 DAP_Addr, u32 * write_data, u8 final)
{
    u8 req;

    // Format the packet request header
    req = SW_Request(DAP_Addr);

    // Perform the requested number of writes
    do
    {
        io_word = *write_data;
        write_data++;
        SW_ShiftPacket(req, 0);
    }
    while (cnt-- != 0);

    // For AP access, check results of last write (use default retry count
    // because previous write may need time to complete)
    if (final && (req & SW_REQ_APnDP))
    {
        SW_ShiftPacket(SW_RDBUFF_RD, 0);
    }
}

u8 SWD_DAP_Move(u8 cnt, u8 dap, u32 * transfer_data)
{
    u8 resp;
    // Reset global error accumulator
    ack_error = SW_ACK_OK;

    // Determine if this is a read or write transfer
    if (dap & DAP_CMD_RnW)
    {
        // Perform the requested number of reads
        //printf("DAP Read\n");
        SW_DAP_Read(cnt, dap, transfer_data);
    }
    else
    {
        //printf("DAP Write\n");
        SW_DAP_Write(cnt, dap, transfer_data, 1);
    }

    // Finish with idle cycles
    SW_ShiftByteOut(0);

    // Return the accumulated error result
    resp = SW_Response(ack_error);

    if (resp != HOST_COMMAND_OK) {
        printf("%s resp: 0x%x\n", __func__, resp);
    }

    return resp;
}

u8 SWD_ClearErrors(void)
{
    u8 ack;

    // First read the DP-CSR register and send the value to the host.
    SW_ShiftPacket(SW_CTRLSTAT_RD, 1);
    //SendLongToHost(io_word.U32);

    // Clear all error/sticky bits by writing to the abort register.
    io_word = 0x1E;
    SW_ShiftPacket(SW_ABORT_WR, 1);

    // Read the DP-CSR register again and send the results to the host.
    ack = SW_ShiftPacket(SW_CTRLSTAT_RD, 1);
    SW_ShiftByteOut(0);

    return SW_Response(ack);
}

void target_mem_write(u32 addr, u32 data)
{
    SWD_DAP_Move(0, MEMAP_TAR_WR, &addr);
    SWD_DAP_Move(0, MEMAP_DRW_WR, &data);
}

u32 target_mem_read(u32 addr)
{
    u32 data = 0;

    u32 csw = 0x23000002;
    SWD_DAP_Move(0, MEMAP_CSW_WR, &csw);

    SWD_DAP_Move(0, MEMAP_TAR_WR, &addr);
    SWD_DAP_Move(0, MEMAP_DRW_RD, &data);

    printf("[0x%08x]: 0x%08x\n", addr, data);

    return data;
}

void connect_and_halt_core()
{
    u32 rw_data;

    // Select MEM BANK 0
    rw_data = MEMAP_BANK_0;
    SWD_DAP_Move(0, DAP_SELECT_WR, &rw_data);

    // 32 bit memory access, auto increment
    rw_data = 0x23000002;
    SWD_DAP_Move(0, MEMAP_CSW_WR, &rw_data);

    // DHCSR.C_DEBUGEN = 1
    rw_data = DHCSR;
    SWD_DAP_Move(0, MEMAP_TAR_WR, &rw_data);
    rw_data = 0xA05F0001;
    SWD_DAP_Move(0, MEMAP_DRW_WR, &rw_data);

    // DEMCR.VC_CORERESET = 1
    rw_data = DEMCR;
    SWD_DAP_Move(0, MEMAP_TAR_WR, &rw_data);
    rw_data = 0x1;
    SWD_DAP_Move(0, MEMAP_DRW_WR, &rw_data);

    // reset the core
    rw_data = AIRCR;
    SWD_DAP_Move(0, MEMAP_TAR_WR, &rw_data);
    rw_data = 0xFA050004;
    SWD_DAP_Move(0, MEMAP_DRW_WR, &rw_data);

    // CTRL1.core_reset_ap = 0
    rw_data = CHIPAP_BANK_0;
    SWD_DAP_Move(0, DAP_SELECT_WR, &rw_data);
    rw_data = 0;
    SWD_DAP_Move(0, CHIPAP_CTRL1_WR, &rw_data);

    // Select MEM BANK 0
    rw_data = MEMAP_BANK_0;
    SWD_DAP_Move(0, DAP_SELECT_WR, &rw_data);
}


int main()
{
    u8 rv;
    u32 idcode;
    u32 transfer_data;

    gpio_init();

    SW_ShiftReset();

    SW_ShiftByteOut(0x9E);

    SW_ShiftByteOut(0xE7);

    rv = SWD_LineReset();
    printf("rv: 0x%x\n", rv);

	SWD_DAP_Move(0, DAP_IDCODE_RD, &idcode);

    printf("idcode: [0x%08x]\n", idcode);

    io_word = 0x1E;
    SW_ShiftPacket(SW_ABORT_WR, 1);

    transfer_data = 0x00;   /* select AP-0x0, BANK-0x00 */
    SWD_DAP_Move(0, DAP_SELECT_WR, &transfer_data);

    transfer_data = 0x50000000;
    SWD_DAP_Move(0, DAP_CTRLSTAT_WR, &transfer_data);

    transfer_data = 0;
    SWD_DAP_Move(0, DAP_CTRLSTAT_RD, &transfer_data);
    printf("%s-%d DAP_CTRLSTAT: 0x%x\n", __func__, __LINE__, transfer_data);

    transfer_data = 0x50000F00;
    SWD_DAP_Move(0, DAP_CTRLSTAT_WR, &transfer_data);

    transfer_data = 0xF0;   /* select AP-0x0, BANK-0x0F */
    SWD_DAP_Move(0, DAP_SELECT_WR, &transfer_data);

    transfer_data = 0x00;
    SWD_DAP_Move(0, MEMAP_ID_RD, &transfer_data);

    transfer_data = 0x00;   /* select AP-0x0, BANK-0x00 */
    SWD_DAP_Move(0, DAP_SELECT_WR, &transfer_data);


    target_mem_write(DHCSR, 0xA05F0003);

    target_mem_read(0x08000000);

    target_mem_write(0x20000000, 0x12345678);
    target_mem_read(0x20000000);

#if 0
    while(1) {
        printf("%s-%d\n", __func__, __LINE__);

        target_mem_write(0x40010C0C, 0xFFFFFFFF);
        usleep(1000000);

        target_mem_write(0x40010C0C, 0x0);
        usleep(1000000);
    }
#endif

    //while(1);

    //connect_and_halt_core();


    return 0;
}
