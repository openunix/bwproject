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
 * File Name	: oss_iface.h (OS Services)
 * Description	:
 * This file contains all the function prototypes that are exported by OSS.
 *
 * History	:
 *	12-27-2005:	Created this file
 *---------------------------------------------------------------------------- */

#ifndef LSI_OSS_IFACE_H
#define LSI_OSS_IFACE_H

#define TIMER_FREQ 5
#define OSS_MAX_DEVICE_QUEUE_DEPTH 255
#define OSS_MAX_DEVICE_QUEUE_DEPTH_LOW_MEM 1

uint8_t		*oss_claim_resource(pvt_data_t *os_context, io_resource_t *io_resource);
uint32_t	oss_free_resource(pvt_data_t *os_context, io_resource_t *io_resource);
void_t		oss_stall_execution(pvt_data_t *os_context, uint32_t micro_secs);
void_t		oss_stall_execution_msleep(pvt_data_t *os_context, uint32_t micro_secs);
uint16_t	oss_read_port_ushort(pvt_data_t *os_context, uint16_t *addr);
uint32_t	oss_read_port_ulong(pvt_data_t *os_context, uint32_t *addr);
uint8_t		oss_read_port_uchar(pvt_data_t *os_context, uint8_t *addr);
uint32_t	oss_read_register_ulong(pvt_data_t *os_context, uint32_t *addr);
void_t		oss_write_port_ulong(pvt_data_t *os_context, uint32_t *addr, uint32_t value);
void_t		oss_write_register_ulong(pvt_data_t *os_context, uint32_t *addr, uint32_t int_value);
void_t		oss_write_port_uchar(pvt_data_t *os_context, uint8_t *addr, uint8_t int_value);
void_t		oss_read_port_buffer_ushort(pvt_data_t *os_context, uint16_t *addr, uint16_t *buffer, uint32_t count);
void_t		oss_memset(uint8_t *buffer, uint32_t length, uint8_t fill_char);
void_t		oss_memcpy(uint8_t *src, uint8_t *dst, uint32_t count);
int32_t		oss_memcmp(uint8_t *src1, uint8_t *src2, uint32_t size);
void_t		oss_memmove(uint8_t *dest, uint8_t *src, uint32_t size);
void_t		oss_breakpoint(void_t);
void_t		oss_rescan(pvt_data_t *os_context, uint8_t bus);
void_t		oss_xor_buffer(uint32_t *dest, uint32_t *buf1, uint32_t *buf2, uint32_t *buf3, uint32_t xor_len);
void_t		oss_spin_lock(pvt_data_t *os_context);
void_t		oss_spin_unlock(pvt_data_t *os_context);
void_t		oss_spin_lock_irqsave(pvt_data_t* os_context, unsigned long *flags);
void_t		oss_spin_unlock_irqrestore(pvt_data_t* os_context, unsigned long
		flags);
handle_t	oss_create_timer(pvt_data_t *os_context);
uint32_t	oss_schedule_timer(pvt_data_t *os_context, handle_t	timer_handle, uint32_t seconds, timer_fn_t callback, void_t *context1, void_t *context2);
void_t		oss_destroy_timer(pvt_data_t *os_context, handle_t timer_handle);
boolean_t	oss_get_os_time(uint32_t *os_time);
boolean_t	oss_set_device_queue_depth(pvt_data_t *os_context, uint8_t bus, uint8_t target, uint8_t lun, uint32_t depth);
void_t		oss_resume_timer(pvt_data_t *os_ext);

extern lsi_timer_t *osl_get_timer_struct(pvt_data_t *os_context);
extern uint32_t osl_get_system_io_bus_number(pvt_data_t *os_context);
extern uint8_t osl_get_adapter_interface_type(pvt_data_t *os_context);
extern addr_t *osl_get_os_ext(pvt_data_t *os_context);

#endif /* LSI_OSS_IFACE_H */

/* vim: set ts=4 sw=4 tw=78 wrap ai si: */
