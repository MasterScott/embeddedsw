/******************************************************************************
*
* Copyright (C) 2007 - 2018 Xilinx, Inc.  All rights reserved.
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
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* XILINX BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
* OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
* Except as contained in this notice, the name of the Xilinx shall not be used
* in advertising or otherwise to promote the sale, use or other dealings in
* this Software without prior written authorization from Xilinx.
*
******************************************************************************/

#ifndef __NETIF_XEMACLITEIF_H__
#define __NETIF_XEMACLITEIF_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "lwip/netif.h"
#include "netif/etharp.h"
#include "netif/xpqueue.h"
#include "xemaclite.h"
#include "xemaclite_i.h"
#include "xstatus.h"

/* structure within each netif, encapsulating all information required for
 * using a particular emaclite instance
 */
typedef struct {
        XEmacLite *instance;

	/* queue to store overflow packets */
	pq_queue_t *recv_q;
	pq_queue_t *send_q;
} xemacliteif_s;

void 	xemacliteif_setmac(u32_t index, u8_t *addr);
u8_t*	xemacliteif_getmac(u32_t index);
err_t 	xemacliteif_init(struct netif *netif);
int 	xemacliteif_input(struct netif *netif);

#ifdef __cplusplus
}
#endif

#endif /* __NETIF_XEMACLITEIF_H__ */
