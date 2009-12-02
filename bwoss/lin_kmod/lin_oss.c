/*
 *----------------------------------------------------------------------------
 *	LSI Corporation
 *	1621 Barber Lane
 *	Milpitas, California 95035
 *----------------------------------------------------------------------------
 * Copyright © 2004-2006, LSI Corporation All Rights Reserved.
 * LSI's source code is an unpublished work and the use of copyright
 * notice does not imply otherwise. This source code contains confidential,
 * trade secret material of LSI Corporation. Any attempt or
 * participation in deciphering, decoding, reverse engineering or
 * in any way altering the source code is strictly prohibited, unless the
 * prior written consent of LSI Corporation.
 *
 * Description	:
 * This file contains the Linux OS implementation of the OSS routines.
 *
 *---------------------------------------------------------------------------- */
#include <linux/types.h>
#include <linux/spinlock.h>

#include "../../cmn_defs.h"
#include "lin_oss.h"
#include "../oss_iface.h"
#include "../../osl/lin/linux_osl.h"

extern void osl_timeout(unsigned long);
pvt_data_t * lin_get_linux_adp(void *data);

/**
 *@brief
 * Operating System Layer Spin lock IRQ restore
 * This function is used to lock the driver for critical operations and it 
 * is used for SMP support.
 * 
 *@param 	os_context	: Pointer to OS specific information structure
 *@param 	flags		: Spin lock information flag
 *@return	None
 */
void_t oss_spin_lock_irqsave(pvt_data_t* os_context, unsigned long *flags)
{
	linux_adp_t * lxadp = (linux_adp_t*) lin_get_linux_adp(os_context);

	spin_lock_irqsave(lxadp->host_lock,*flags);
}

/**
 *@brief
 * Operating System Layer Spin unlock IRQ restore
 * This function is used to unlock the driver for critical operations and it 
 * is used for SMP support.
 * 
 * In windows miniport driver this function is not required as the 
 * driver is single threaded
 *
 *@param 	os_context	: Pointer to OS specific information structure
 *@param 	flags		: Spin lock information flag captured while locking
 *@return	None
 */
void_t oss_spin_unlock_irqrestore(pvt_data_t* os_context, unsigned long flags)
{
	linux_adp_t * lxadp = (linux_adp_t*) lin_get_linux_adp(os_context);

	spin_unlock_irqrestore(lxadp->host_lock,flags);
}

/**
 *@brief
 * Operating System Layer Spin lock
 * This function is used to lock the driver for critical operations and it 
 * is used for SMP support.
 * 
 * In windows miniport driver this function is not required as the 
 * driver is single threaded
 *
 *@param 	os_context	: Pointer to OS specific information structure
 *@return	None
 */
void_t oss_spin_lock(pvt_data_t *os_context)
{
	linux_adp_t * lxadp = (linux_adp_t*) lin_get_linux_adp(os_context);

	spin_lock(lxadp->host_lock);
}

/**
 *@brief
 * Operating System Layer Spin unlock
 * This function is used to unlock the driver for critical operations and it 
 * is used for SMP support.
 * 
 * In windows miniport driver this function is not required as the 
 * driver is single threaded
 *
 *@param 	os_context	: Pointer to OS specific information structure
 *@return	None
 */
void_t oss_spin_unlock(pvt_data_t *os_context)
{
	linux_adp_t * lxadp = (linux_adp_t*) lin_get_linux_adp(os_context);

	spin_unlock(lxadp->host_lock);
}

void_t oss_memset(uint8_t *buffer, uint32_t length, uint8_t fill_char)
{
	memset(buffer, fill_char, length);
}

void_t oss_memcpy(uint8_t *src, uint8_t *dst, uint32_t count)
{
	memcpy(dst, src, count);
}

uint8_t *oss_claim_resource(pvt_data_t *os_context, io_resource_t *io_res)
{
	uint32_t	length	= io_res->length;
	unsigned long		baddr	= (unsigned long) io_res->paddr;

	if(io_res->io_type == RES_TYPE_MEM) {

		if (check_mem_region(baddr, length)) {
			con_log(CL_ERR, ("megaswr[osl]: mem region busy\n"));
			return NULL;
		}

		request_mem_region(baddr, length, LSIRAID_DRIVER_SIGNATURE);
		io_res->vaddr = (uint8_t*) ioremap_nocache(baddr, length);

		return io_res->vaddr;

	} else {
		if(!request_region(baddr, length, LSIRAID_DRIVER_SIGNATURE))
			return NULL;

		io_res->vaddr = (uint8_t*) baddr;
		return io_res->vaddr;
	}
}

uint32_t oss_free_resource(pvt_data_t *os_context, io_resource_t *io_resource)
{
	iounmap(io_resource->vaddr);

	if(io_resource->length)
		release_mem_region((unsigned long)io_resource->paddr, io_resource->length);

	return 0;
}

void_t oss_stall_execution(pvt_data_t *os_context, uint32_t micro_secs)
{
	for(; micro_secs; micro_secs--) {
		udelay(1);
		rmb();
	}
}

/* Blocking sleep for windows and it is same as oss_stall_execution  */
void_t oss_stall_execution_msleep(pvt_data_t *os_context, uint32_t micro_secs)
{
#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,10)
    msleep(micro_secs/1000);
#else //msleep not avilable and also the problem of stack dump does not appear.
    oss_stall_execution(os_context, micro_secs);
#endif
}

uint16_t oss_read_port_ushort(pvt_data_t *os_context, uint16_t *addr)
{
	return inw((unsigned long) addr);
}

uint8_t oss_read_port_uchar(pvt_data_t *os_context, uint8_t *addr)
{
	return inb((unsigned long) addr);
}

uint32_t oss_read_port_ulong(pvt_data_t *os_context, uint32_t *addr)
{
	return inl((unsigned long) addr);
}

uint32_t oss_read_register_ulong(pvt_data_t *os_context, uint32_t *addr)
{
	return readl(addr);
}

void_t oss_read_port_buffer_ushort(pvt_data_t *os_context, uint16_t *addr,
		uint16_t *buffer, uint32_t count)
{
	insw((unsigned long) addr, buffer, count);
}

void_t oss_write_register_ulong(pvt_data_t *os_context, uint32_t *addr,
		uint32_t value)
{
	writel(value, addr);
}

void_t oss_write_port_ulong(pvt_data_t *os_context, uint32_t *addr, uint32_t
		value)
{
	outl(value, (unsigned long) addr);
}

void_t oss_write_port_uchar(pvt_data_t *os_context, uint8_t *addr, uint8_t
		value)
{
	outb(value, (unsigned long) addr);
}

void_t oss_breakpoint(void_t)
{
	con_log(CL_ERR, ("megaswr[osl]: breakpoint called\n"));
	/**@todo manoj implement linux driver panic function */
}

void_t oss_rescan(pvt_data_t *os_context, uint8_t bus)
{
}

/*
 * This routine returns a new handle to a timer entry.
 */
handle_t oss_create_timer(pvt_data_t *os_cxt)
{
	uint8_t				i;
	linux_adp_t			*lxadp;
	timer_object_t		*to = NULL;
	struct timer_list	*tp;

	if (!os_cxt) {
		con_log(CL_ERR, ("megaswr[osl]:  err Invalid parameter\n"));
		return INVALID_HANDLE;
	}

	lxadp	= (linux_adp_t*) lin_get_linux_adp(os_cxt);

	if (lxadp->timer_count > MAX_TIMERS) {
		con_log(CL_ERR, ("megaswr[osl]:  err Too many timers\n"));
		return INVALID_HANDLE;
	}

	for(i = 0; i < MAX_TIMERS; i++) {
		if(!lxadp->timer_objects[i].used_flag) {
			to		= &lxadp->timer_objects[i];
			lxadp->timer_objects[i].used_flag = 1;
			break;
		}
	}

	if (!to) {
		con_log(CL_ERR, ("megaswr[osl]:  err could not find a timer object\n"));
		return INVALID_HANDLE;
	}

	lxadp->timer_count++;
	to->active_flag	= 0;
	to->seconds	= 0;
	to->timer_fn	= NULL;
	to->context1	= NULL;
	to->context2	= NULL;

	tp		= &to->timer;
	tp->function	= osl_timeout;
	tp->data	= (unsigned long) to;
	tp->expires	= 0;

	init_timer(tp);

	return ((handle_t)to);
}

/*
* Description	:	Performs any necessary action needed to restart our main timer thread with the OS.
*
* Parameters	:
* @param1 pv	: os_ext - this should be the actual OS device extension, not our internal context data structure
*
* Return	:
*	none
*/
void_t oss_resume_timer(pvt_data_t *os_ext)
{
	/* won't be used for Linux */
	return;
}

/*
 * This routine is called to schedule the timer thread.
 */
uint32_t oss_schedule_timer(pvt_data_t *os_cxt, handle_t handle, uint32_t
		seconds, timer_fn_t fn, void_t *context1, void_t *context2)
{
	timer_object_t*		to;
	struct timer_list*	tp;
	
	if((!os_cxt) || (!handle) || (seconds <= 0) || (!fn)){
		con_log(CL_DEBUG, ("megaswr[osl]: Schedule Timer: Invalid parameter\n"));
		return LSI_FALSE;
	}

	to			= (timer_object_t*) handle;
	to->active_flag	= 1;
	to->seconds	= seconds;
	to->timer_fn= fn;
	to->context1= context1;
	to->context2= context2;

	tp			= &to->timer;
	tp->function= osl_timeout;
	tp->data	= (unsigned long) to;
	tp->expires	= jiffies + seconds * HZ;

	add_timer(tp);
	return LSI_TRUE;
}

/*
 * This routine is called to destroy timer.
 */
void_t oss_destroy_timer(pvt_data_t *os, handle_t handle)
{
	linux_adp_t		*lxadp = (linux_adp_t*) lin_get_linux_adp(os);
	
	if (handle == INVALID_HANDLE) {
		con_log(CL_ERR, ("megaswr[osl]:  err distroy timer with invalid handle\n"));
		return;
	}
	
	if (((timer_object_t*) handle)->active_flag) {
		del_timer(&(((timer_object_t*) handle)->timer));

		((timer_object_t*) handle)->active_flag	= 0;
	}

	lxadp->timer_count --;
	((timer_object_t*) handle)->used_flag = 0;
}

/**
 * XOR buffer.
 *
 *@param dest: Destination address.
 *@param buf1: first buffer.
 *@param buf2: second buffer.
 *@param buf3: third buffer and is optional.  NULL if not valid.
 *@param xor_len: Number of DWORDS to xor.
 *@return	: None
 */
void_t oss_xor_buffer(uint32_t *dest, uint32_t *buf1, uint32_t *buf2, uint32_t
		*buf3, uint32_t xor_len)
{
	uint32_t ind;

	if ( !buf3 ) {
		for(ind=0;ind<xor_len;ind++) {
			dest[ind] = buf1[ind] ^ buf2[ind];
		}
	} else {
		for(ind=0;ind<xor_len;ind++) {
			dest[ind] = buf1[ind] ^ buf2[ind] ^ buf3[ind];
		}
	}
	return;
}

/**
 *@brief
 * Returns the OS time in seconds since January 1, 2000.
 *@param	os_context: pointer to the os_context structure.
 *@param	os_time: pointer to the variable that will store the value.
 *@return LSI_TRUE if operation was successful, LSI_FALSE otherwise.
 */
boolean_t oss_get_os_time(uint32_t *os_time)
{
	/* CMOS time counted from 1970, So reducing 30 years */
#ifdef __VMKERNEL_MODULE__
	struct timeval tv;
	
	memset(&tv, 0, sizeof(tv));
	do_gettimeofday(&tv);
	
	*os_time = (tv.tv_sec - ((30*365+30/4)*24*60*60));

#else
	*os_time = (LSI_RAID_CURRENT_TIME_IN_SEC - ((30*365+30/4)*24*60*60));
#endif
	return LSI_TRUE;
}

/**
 *@brief
 * Compares count bytes of memory starting at buf1 and buf2 and find if equal
 * or which one is first in lexical order.
 *
 *       returns < 0 if buf1 < buf2
 *       returns  0  if buf1 == buf2
 *       returns > 0 if buf1 > buf2
 */
int32_t oss_memcmp(uint8_t *buf1, uint8_t *buf2, uint32_t count)
{
	return (memcmp(buf1, buf2, count));
}

/**
*@brief
* Moves memory
*
*@param	dest: pointer to the destination buffer to move memory to.
*@param	src: pointer to the source buffer to memory from.
*@param	size: size of the buffers.
*@return none.
*/
void_t oss_memmove(uint8_t *dest, uint8_t *src, uint32_t size)
{
	memmove(dest, src, size);
}

/**
*@brief
* In supported operating systems, sets the specified device's queue depth in the OS.
*
*@param	os_context: pointer to the os_context structure.
*@param	bus: bus number of the device.
*@param	target: target number of the device.
*@param	lun: lun number of the device.
*@param	depth: number of I/O this device can handle.
*@return LSI_TRUE: successful. If not supported by OS, LSI_TRUE will be returned.
*		 LSI_FALSE: failed by OS.
*/
boolean_t oss_set_device_queue_depth(pvt_data_t *os_context, uint8_t bus, uint8_t target, uint8_t lun, uint32_t depth)
{
	return LSI_TRUE;
}

#ifndef COMPILE_64BIT
/**
 * 64-bit division to get remainder on a 32-bit platform
 *
 * @param dividend	: Dividend
 * @param divisor	: Divisor
 *
 * @return remainder
 **/
uint32_t megasr_mod64(uint64_t dividend, uint32_t divisor)
{
	uint32_t		remainder;
	unsigned long	eax_saved;
	unsigned long	ebx_saved;
	unsigned long	edx_saved;

	// save used registers
	asm("" : "=a" (eax_saved), "=d" (edx_saved), "=b" (ebx_saved):);

	asm("divl %1" : "=d" (remainder) : "b" (divisor), "A" (dividend));

	// restore used registers
	asm("" : : "a" (eax_saved), "b" (ebx_saved), "d" (edx_saved));

	return remainder;
}

/**
 * 64-bit division on a 32-bit platform
 *
 * @param dividend	: Dividend
 * @param divisor	: Divisor
 *
 * @return quotient
 **/
uint32_t megasr_div64(uint64_t dividend, uint32_t divisor)
{
	uint32_t		quotient;
	unsigned long	eax_saved;
	unsigned long	ebx_saved;
	unsigned long	edx_saved;

	// save used registers
	asm("" : "=a" (eax_saved), "=d" (edx_saved), "=b" (ebx_saved):);

	asm("divl %1" : "=a" (quotient) : "b" (divisor), "A" (dividend));

	// restore used registers
	asm("" : : "a" (eax_saved), "b" (ebx_saved), "d" (edx_saved));

	return quotient;
}
#endif

/* vim: set ts=4 sw=4 tw=78 wrap ai si: */
