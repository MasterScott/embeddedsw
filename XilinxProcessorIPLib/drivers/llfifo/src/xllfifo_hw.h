/******************************************************************************
*
* Copyright (C) 2005 - 2014 Xilinx, Inc.  All rights reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* Use of the Software is limited solely to applications:
* (a) running on a Xilinx device, or
* (b) that interact with a Xilinx device through a bus or interconnect.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* XILINX  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
* OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
* Except as contained in this notice, the name of the Xilinx shall not be used
* in advertising or otherwise to promote the sale, use or other dealings in
* this Software without prior written authorization from Xilinx.
*
******************************************************************************/
/*****************************************************************************/
/**
*
* @file xllfifo_hw.h
*
* This header file contains identifiers and low-level driver functions (or
* macros) that can be used to access the xps_ll_fifo core.
* High-level driver functions are defined in xpfifo.h.
*
* <pre>
* MODIFICATION HISTORY:
*
* Ver   Who  Date     Changes
* ----- ---- -------- -------------------------------------------------------
* 1.00a jvb  10/16/06 First release.
* 1.02a jz   12/04/09  Hal phase 1 support
* 2.00a hbm  01/20/10  Hal phase 1 support, bump up major release
* 2.03a asa  14/08/12  Added XLLF_TDR_OFFSET, XLLF_RDR_OFFSET
*		       defines for the new registers, and XLLF_INT_TFPF_MASK,
*		       XLLF_INT_TFPE_MASK, XLLF_INT_RFPF_MASK and
*		       XLLF_INT_RFPE_MASK for the new version of the
*		       AXI4-Stream FIFO core (v2.01a and later)
* </pre>
*
******************************************************************************/

#ifndef XLLFIFO_HW_H		/* prevent circular inclusions */
#define XLLFIFO_HW_H		/* by using protection macros */

#ifdef __cplusplus
extern "C" {
#endif

/***************************** Include Files *********************************/

#include "xdebug.h"
#include "xil_io.h"
#include "xil_types.h"

/************************** Constant Definitions *****************************/

/* Register offset definitions. Unless otherwise noted, register access is
 * 32 bit.
 */

/** @name Registers
 *  @{
 */
#define XLLF_ISR_OFFSET  0x00000000  /**< Interrupt Status */
#define XLLF_IER_OFFSET  0x00000004  /**< Interrupt Enable */

#define XLLF_TDFR_OFFSET 0x00000008  /**< Transmit Reset */
#define XLLF_TDFV_OFFSET 0x0000000c  /**< Transmit Vacancy */
#define XLLF_TDFD_OFFSET 0x00000010  /**< Transmit Data */
#define XLLF_TLF_OFFSET  0x00000014  /**< Transmit Length */

#define XLLF_RDFR_OFFSET 0x00000018  /**< Receive Reset */
#define XLLF_RDFO_OFFSET 0x0000001c  /**< Receive Occupancy */
#define XLLF_RDFD_OFFSET 0x00000020  /**< Receive Data */
#define XLLF_RLF_OFFSET  0x00000024  /**< Receive Length */
#define XLLF_LLR_OFFSET  0x00000028  /**< Local Link Reset */
#define XLLF_TDR_OFFSET  0x0000002C  /**< Transmit Destination  */
#define XLLF_RDR_OFFSET  0x00000030  /**< Receive Destination  */

/*@}*/

/* Register masks. The following constants define bit locations of various
 * control bits in the registers. Constants are not defined for those registers
 * that have a single bit field representing all 32 bits. For further
 * information on the meaning of the various bit masks, refer to the HW spec.
 */

/** @name Interrupt bits
 *  These bits are associated with the XLLF_IER_OFFSET and XLLF_ISR_OFFSET
 *  registers.
 * @{
 */
#define XLLF_INT_RPURE_MASK       0x80000000 /**< Receive under-read */
#define XLLF_INT_RPORE_MASK       0x40000000 /**< Receive over-read */
#define XLLF_INT_RPUE_MASK        0x20000000 /**< Receive underrun (empty) */
#define XLLF_INT_TPOE_MASK        0x10000000 /**< Transmit overrun */
#define XLLF_INT_TC_MASK          0x08000000 /**< Transmit complete */
#define XLLF_INT_RC_MASK          0x04000000 /**< Receive complete */
#define XLLF_INT_TSE_MASK         0x02000000 /**< Transmit length mismatch */
#define XLLF_INT_TRC_MASK         0x01000000 /**< Transmit reset complete */
#define XLLF_INT_RRC_MASK         0x00800000 /**< Receive reset complete */
#define XLLF_INT_TFPF_MASK        0x00400000 /**< Tx FIFO Programmable Full,
						* AXI FIFO MM2S Only */
#define XLLF_INT_TFPE_MASK        0x00200000 /**< Tx FIFO Programmable Empty
						* AXI FIFO MM2S Only */
#define XLLF_INT_RFPF_MASK        0x00100000 /**< Rx FIFO Programmable Full
						* AXI FIFO MM2S Only */
#define XLLF_INT_RFPE_MASK        0x00080000 /**< Rx FIFO Programmable Empty
						* AXI FIFO MM2S Only */
#define XLLF_INT_ALL_MASK         0xfff80000 /**< All the ints */
#define XLLF_INT_ERROR_MASK       0xf2000000 /**< Error status ints */
#define XLLF_INT_RXERROR_MASK     0xe0000000 /**< Receive Error status ints */
#define XLLF_INT_TXERROR_MASK     0x12000000 /**< Transmit Error status ints */
/*@}*/

/** @name Reset register values
 *  These bits are associated with the XLLF_TDFR_OFFSET and XLLF_RDFR_OFFSET
 *  reset registers.
 * @{
 */
#define XLLF_RDFR_RESET_MASK        0x000000a5 /**< receive reset value */
#define XLLF_TDFR_RESET_MASK        0x000000a5 /**< Transmit reset value */
#define XLLF_LLR_RESET_MASK         0x000000a5 /**< Local Link reset value */
/*@}*/

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/

/**** debug macros ****/
#define XLlFifo_reg_name(RegOffset) \
	(((RegOffset) == XLLF_ISR_OFFSET) ? "ISR": \
	((RegOffset) == XLLF_IER_OFFSET) ? "IER": \
	((RegOffset) == XLLF_TDFR_OFFSET) ? "TDFR {tx reset}": \
	((RegOffset) == XLLF_TDFV_OFFSET) ? "TDFV {tx vacancy}": \
	((RegOffset) == XLLF_TDFD_OFFSET) ? "TDFD {tx data}": \
	((RegOffset) == XLLF_TLF_OFFSET) ? "TLF {tx length}": \
	((RegOffset) == XLLF_RDFR_OFFSET) ? "RDFR {rx reset}": \
	((RegOffset) == XLLF_RDFO_OFFSET) ? "RDFO {rx occupancy}": \
	((RegOffset) == XLLF_RDFD_OFFSET) ? "RDFD {rx data}": \
	((RegOffset) == XLLF_RLF_OFFSET) ? "RLF {rx length}": \
	"unknown")

#define XLlFifo_print_reg_o(BaseAddress, RegOffset, Value) \
	 xdbg_printf(XDBG_DEBUG_FIFO_REG, "0x%08x -> %s(0x%08x)\n", (Value), \
			  XLlFifo_reg_name(RegOffset), \
			 (RegOffset) + (BaseAddress))

#define XLlFifo_print_reg_i(BaseAddress, RegOffset, Value) \
	xdbg_printf(XDBG_DEBUG_FIFO_REG, "%s(0x%08x) -> 0x%08x\n", \
			 XLlFifo_reg_name(RegOffset), \
			(RegOffset) + (BaseAddress), (Value))
/**** end debug macros ****/

/****************************************************************************/
/**
*
* XLlFifo_ReadReg returns the value of the register at the offet,
* <i>RegOffset</i>, from the memory mapped base address, <i>BaseAddress</i>.
*
* @param    BaseAddress specifies the base address of the device.
*
* @param    RegOffset specifies the offset from BaseAddress.
*
* @return   XLlFifo_ReadReg returns the value of the specified register.
*
* @note
* C-style signature:
*    u32 XLlFifo_ReadReg(u32 BaseAddress, u32 RegOffset)
*
*****************************************************************************/
#ifdef DEBUG
extern u32 _xllfifo_rr_value;
#define XLlFifo_ReadReg(BaseAddress, RegOffset) \
	((((RegOffset) > 0x24) ? xdbg_printf(XDBG_DEBUG_ERROR, \
		"XLlFifo_WriteReg: Woah! wrong reg addr: 0x%08x\n", \
		(RegOffset)) : 0), \
	_xllfifo_rr_value = Xil_In32((BaseAddress) + (RegOffset)), \
	XLlFifo_print_reg_i((BaseAddress), (RegOffset), _xllfifo_rr_value), \
	_xllfifo_rr_value)
#else
#define XLlFifo_ReadReg(BaseAddress, RegOffset) \
	(Xil_In32((BaseAddress) + (RegOffset)))
#endif

/****************************************************************************/
/**
*
* XLlFifo_WriteReg writes the value, <i>Value</i>, to the register at the
* offet, <i>RegOffset</i>, from the memory mapped base address,
* <i>BaseAddress</i>.
*
* @param    BaseAddress specifies the base address of the device.
*
* @param    RegOffset specifies the offset from BaseAddress.
*
* @param    Value is value to write to the register.
*
* @return   N/A
*
* @note
* C-style signature:
*    void XLlFifo_WriteReg(u32 BaseAddress, u32 RegOffset, u32 Value)
*
*****************************************************************************/
#ifdef DEBUG
#define XLlFifo_WriteReg(BaseAddress, RegOffset, Value) \
	(((RegOffset) > 0x24) ? xdbg_printf(XDBG_DEBUG_ERROR, \
		"XLlFifo_WriteReg: Woah! wrong reg addr: 0x%08x\n", \
		(RegOffset)) : 0), \
	XLlFifo_print_reg_o((BaseAddress), (RegOffset), (Value)), \
	(Xil_Out32((BaseAddress) + (RegOffset), (Value)))
#else
#define XLlFifo_WriteReg(BaseAddress, RegOffset, Value) \
	((Xil_Out32((BaseAddress) + (RegOffset), (Value))))
#endif

#ifdef __cplusplus
}
#endif
#endif				/* XLLFIFO_HW_H  end of protection macro */
