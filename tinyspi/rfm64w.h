/* rfm64w.h - HopeRF RFM64W 433 MHz Tx/Rx module
 *
 * (c) David Haworth
 *
 *  This file is part of tiny-bare-metal.
 *
 *  tiny-bare-metal is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  tiny-bare-metal is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with tiny-bare-metal.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef RFM64W_H
#define RFM64W_H	1

#include "tinyspi.h"

/* The RFM64W has an SPI interface with two chip selects called NSS_CONFIG and NSS_DATA, both active low.
 * NSS_CONFIG takes priority, so if the device is the only device on the bus, it's sufficient to tie NSS_DATA
 * to 0v and use NSS_CONFIG to select configuration (0) or data (1)
 *
 * The first byte sent to the config port is the address. It consists of:
 *
 *	Bit		Description
 *	7		Start bit (0)
 *	6		Read (1) or write (0)
 *	5		A4
 *	4		A3
 *	3		A2
 *	2		A1
 *	1		A0
 *	0		Stop bit (0)
 *
 * Bytes are sent MSB first.
 * After a write/address byte, the data is sent. The current value of the register comes back on MISO. The
 * register's new value is effective from the rising edge of NSS_CONFIG
 * "Note that when writing more than one register successively, it is not compulsory to toggle NSS_CONFIG back high
 * between two write sequences. The bytes are alternatively considered as address and value. In this instance, all
 * new values will become effective on rising edge of NSS_CONFIG."
 * So it seems that there's a complete set of shadow config registers that get transferred on the rising edge of
 * NSS_CONFIG.
 *
 * After a read/address byte, a dummy byte is sent and ignored. The current value of the register comes back on MISO.
 * Question: is this the current value, or the value of the shadow register?
 *
 * To write to the data fifo, just send the byte. "Note that it is compulsory to toggle NSS_DATA back high between
 * each byte written."
 * Question: is activating NSS_CONFIG enough, or is it necessary to send NSS_DATA high? If the latter, then five
 * pins are needed and the attiny85 is out of the questions, unless a simple transistor inverter is enough.
*/

/* Config registers
*/
#define R64_REG_MODULE_MODE		0	/* Bit fields: see below */
#define R64_REG_DATA_MODE		1	/* Bit fields: see below */
#define R64_REG_FREQ_DEV		2	/* Single side frequency deviation in FSK Tx mode */
#define R64_REG_BR_C			3	/* C coefficient of the bit rate */
#define R64_REG_BR_D			4	/* D coefficient of the bit rate */
#define R64_REG_PWR_BAND		5	/* Bit fields: see below */
#define R64_REG_R1				6	/* R counter when RPS_select = 0 */
#define R64_REG_P1				7	/* P counter when RPS_select = 0 */
#define R64_REG_S1				8	/* S counter when RPS_select = 0 */
#define R64_REG_R2				9	/* R counter when RPS_select = 1 */
#define R64_REG_P2				10	/* P counter when RPS_select = 1 */
#define R64_REG_S2				11	/* S counter when RPS_select = 1 */
/* There's a strange line in the table claiming that bits 2-0 of register 12 are reserved. Ignore. */
#define R64_REG_FIFO			12	/* Bit fields: see below */
#define R64_REG_IRQ				13	/* Bit fields: see below */
#define R64_REG_FIFO_FILL		14	/* Bit fields: see below */
/* There's a strange line in the table claiming that Fifo_overrun_clr is bit 4 of register 13. Assume 14 */
#define R64_REG_RSSI_THRSH		15	/* RSSI_irq_thresh */
#define R64_REG_RXFILTER		16	/* Bit fields: see below */
#define R64_REG_RXPOLYFILT		17	/* Bit fields: see below */
#define R64_REG_RXSYNC			18	/* Bit fields: see below */
#define R64_REG_OOK_THRSH_1		19	/* OOK fixed threshold/min threshold */
#define R64_REG_RSSI_VAL		20	/* RSSI output: READ ONLY, not to be written */
#define R64_REG_OOK_THRSH_2		21	/* Bit fields: see below */
#define R64_REG_SYNC_3			22	/* Bits 31-24 of sync word */
#define R64_REG_SYNC_2			23	/* Bits 23-16 of sync word */
#define R64_REG_SYNC_1			24	/* Bits 15-8 of sync word */
#define R64_REG_SYNC_0			25	/* Bits 7-0 of sync word */
#define R64_REG_TX_PARAM		26	/* Bit fields: see below */
#define R64_REG_OSC_PARAM		27	/* Bit fields: see below */
#define R64_REG_PKT_ENC_LEN		28	/* Bit fields: see below */
#define R64_REG_NODE_ADRS		29	/* Node's local address */
#define R64_REG_PKT_CFG			30	/* Bit fields: see below */
#define	R64_REG_FIFO_CFG		31	/* Bit fields: see below */


/* Config register bit fields
 * Note: config registers that contain only one field are not mentioned here.
*/
/* Register 0: R64_REG_MODULE_MODE
*/
#define	R64_MOD_MODE		0xe0
#define R64_BAND			0x1c
#define R64_SUBBAND			0x03

/* Register 1: R64_REG_DATA_MODE
*/
#define R64_DATA_MODE		0xc0
#define	R64_KEY_MODE		0x30
#define R64_OOK_THRSH		0x0c
#define R64_IF_GAIN			0x03

/* Register 5: R64_REG_PWR_BAND
*/
#define R64_PA_RAM			0xc0
#define R64_LOWPWR_RX		0x20
#define R64_TRIM_BAND		0x06
#define R64_RF_FREQ			0x01

/* Register 12: R64_REG_FIFO
*/
#define R64_FIFO_SIZE		0xc0
#define R64_FIFO_THRSH		0x3f

/* Register 13: R64_REG_IRQ
*/
#define R64_STBY_IRQ0		0xc0
#define R64_STBY_IRQ1		0x30
#define R64_TXSTART_IRQ		0x08
#define R64_TX_IRQ1			0x04
#define R64_FIFOFULL		0x02	/* Goes high when FIFO is full */
#define R64_FIFO_NOTMT		0x01	/* Goes low when FIFO is empty */

/* Register 14: R64_REG_FIFO_FILL
*/
#define R64_FIFO_FILLMETHOD	0x80
#define R64_FIFO_FILL		0x40
#define R64_TX_DONE			0x20
#define R64_FIFO_OVERRN_CLR	0x10
#define R64_RSSI_IRQ_EN		0x08	/* Datasheet says "reserved" then describes the bit :-o */
#define R64_RSSI_IRQ		0x04
#define R64_PLL_LOCKED		0x02	/* w1c */
#define R64_PLL_LOCK_EN		0x01

/* Register 16: R64_REG_RXFILTER
*/
#define R64_PASSIVE_FILT	0xf0
#define R64_BUTTER_FILT		0x0f

/* Register 17: R64_REG_RXPOLYFILT
 * Bits 3..0 reserved, default 0x08
*/
#define R64_POLYP_FILT		0xf0

/* Register 18: R64_REG_RXSYNC
 * Bit 0 reserved, default 0
*/
#define R64_POLYPFILT_ON	0x80
#define R64_BITSYNC_OFF		0x40
#define R64_SYNC_ON			0x20
#define R64_SYNC_SIZE		0x18
#define R64_SYNC_TOL		0x06

/* Register 21: R64_REG_OOK_THRSH_2
*/
#define R64_OOK_THRSH_STEP	0xe0
#define R64_OOK_THRSH_DECP	0x1c
#define R64_OOK_THRSH_CUT	0x03

/* Register 26: R64_REG_TX_PARAM
*/
#define R64_INTERP_FILT		0xf0
#define R64_POUT			0x0e
#define R64_ZERO_IF			0x01

/* Register 27: R64_REG_OSC_PARAM
 * Bits 1..0 reserved, default 0
*/
#define R64_CLKOUT_ON		0x80
#define R64_CLKOUT_FREQ		0x7c

/* Register 28: R64_REG_PKT_ENC_LEN
*/
#define R64_MANCHESTER_ON	0x80
#define R64_PAYLOAD_LEN		0x7f

/* Register 30:  R64_REG_PKT_CFG
*/
#define R64_PKT_FORMAT		0x80
#define R64_PREAMBLE_SIZE	0x60
#define R64_WHITENING_ON	0x10
#define R64_CRC_ON			0x08
#define R64_ADRS_FILT		0x06
#define R64_CRC_STATUS		0x01

/* Register 31:  R64_REG_FIFO_CFG
 * Bits 5..0 reserved, default 0
*/
#define R64_CRC_AUTOCLR		0x80
#define R64_FIFO_STBY_ACC	0x40

/* r64_select() - select config or fifo or none
*/
#define R64_SEL_NONE	0
#define R64_SEL_CFG		1
#define R64_SEL_FIFO	2

void r64_select(u8_t sel)
{
	/* ToDo: implement */
}

/* r64_readreg() - read a register
*/
static inline u8_t r64_readreg(u8_t adrs)
{
	(void)spi_writeread((adrs << 1) | 0x40);
	return spi_writeread(0);
}

/* r64_writereg() - write a register
*/
static inline void r64_writereg(u8_t adrs, u8_t val)
{
	(void)spi_writeread((adrs << 1) | 0x00);
	(void)spi_writeread(val);
}

#endif
