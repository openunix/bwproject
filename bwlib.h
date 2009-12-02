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
 * * File Name	: cmn_defs.h (Common project-wide definitions)
 * Description	:
 * This file can and will be inlcuded by every other file in this project.
 * Only the most common project-wide definitions must go into this header.
 * This cmn_defs.h header will include system header files under OS specific
 * compilation flags. No HAL, RAID, INTERFACE or PROTOCOL specific information 
 * will be included here.
 *
 *
 * * History	:
 *	06-23-2004:	Created this file
 *	08-26-2004: Version 1
 * TODO:
 *	None
 *----------------------------------------------------------------------------
 */

#ifndef LSI_MEGA_SWR_COMMON_DEFS_H
#define LSI_MEGA_SWR_COMMON_DEFS_H

#define LSIRAID_DRIVER_CODENAME		"Athens"
#define LSIRAID_VERSION_STRING		"13.07.0318.2009"
#define LSIRAID_DRIVER_RELEASE_DATE	"03/18/2009"
#define LSIRAID_DRIVER_SIGNATURE	"megasr"
#define LSIRAID_DRIVER_NAME			"LSI MegaSR RAID5"

#define DRIVER_VERSION_LEN		sizeof(LSIRAID_VERSION_STRING)
#define	DRIVER_REL_DATE_LEN		sizeof(LSIRAID_DRIVER_RELEASE_DATE)
#define DRIVER_SIGNATURE_LEN	sizeof(LSIRAID_DRIVER_SIGNATURE)
#define DRIVER_NAME_LEN			sizeof(LSIRAID_DRIVER_NAME)

/****************************************************/
/* Driver Features which can be enabled or disabled */
/****************************************************/

/* Platform support */
#define ADP_ICH7
//#define ADP_ICH8
#define ADP_ICH9
#define ADP_1064
#define ADP_1068
#define ADP_ESB2

/*
 * When forcing SWR5 driver to load on PCI IDs unknown at compile time,
 * users must specify the adapter class from one of these values below.
 * How users specify is different in Windows and Linux.
 */
typedef enum {

	MEGASR_ADP_CLASS_ICH	= 0,
	MEGASR_ADP_CLASS_ESB2	= 1,
	MEGASR_ADP_CLASS_MPT	= 2,
	MEGASR_ADP_CLASS_ICH9	= 3

} megasr_adapter_class_t;

#define MEGASR_DYNAMIC_PCIIDS_DEFAULT_ADP_CLASS		MEGASR_ADP_CLASS_ESB2

#define EVT_DESCRIPTION_DEFINE			//Macro to cause event_msg.h to declare evt_description as global instead of extern
/* Feature support common for all OS's */
//#define MEGASR_CACHE_SUPPORT			//Macro to enable caching support in the driver

// RLM supported DOS tool should define this macro
// #define BYPASS_MORPHING_SUPPORT				// This macro is used for bypass Morphing and access logical drives

#define MEGASR_MPT_READ_AGAIN_MEDIA_ERR	//Macro to enable read upto media error sector in MPT Layer
//#define MEGASR_MPT_RING_BUFFER_SUPPORT	//Macro to enable Ring buffer debug support in MPT layer

/* Common data types built on OS-specific data types */
typedef void void_t;
typedef void_t pvt_data_t;

/* Function typedefs */
typedef void_t (*timer_fn_t)(void_t*, void_t*);
typedef void_t (*mem_added_fn_t)(pvt_data_t *os_context, pvt_data_t *context);

#ifdef LSI_LINUX
#include "osl/lin/lin_defs.h"
#endif

#ifdef LSI_WINDOWS
#include "osl/win/win_defs.h"
#endif

typedef unsigned long handle_t;
typedef uint8_t	boolean_t;
typedef uint64_t sectors_t;

// For compatibility with FW header files
#include "external/mpi_type.h"
#include "hal/common/scsi_hal.h"

/* Common definitions */
#define LSI_RAID_1_MB_SIZE		0x100000	/* 1024 * 1024*/
#define LSRAID_SECTOR_SIZE		0x200 		/* 512 bytes */
#define LSIRAID_SECTOR_SHIFT	9
#define ATAPI_SECTOR_SIZE		0x800		/* 2048 bytes */
#define LSIRAID_BYTES_TO_SECTORS(byte_size) (byte_size >> LSIRAID_SECTOR_SHIFT)
#define LSIRAID_SECTORS_TO_BYTES(sectors) (sectors << LSIRAID_SECTOR_SHIFT)
#define TIMER_FREQ				5

/* Memory requirements */
#define TOTAL_STATIC_MEM_REQ			314571	/* we need 314,571 bytes of static memory (30% of 1MB) */
#define TOTAL_DMA_MEM_FOR_DDF_HIBER		17*1024	/* we need ~17Ks of dynamic memory in low memory conditions for cod (calculated) */
#define MAX_R5_IO_SPLIT_SIZE_LOW_MEM	512		/* the maximum I/O size to send for R5 LDs in low memory conditions */

/* maximum number of blocks supported during hibernation*/
#define MAX_BLOCK_COUNT_PER_IO_HIBER_SCSIPORT	(6)		//3k max

/* maximum DMA memory requirement during hibernation*/
#define TOTAL_DMA_MEM_FOR_IO_HIBER		(MAX_BLOCK_COUNT_PER_IO_HIBER_SCSIPORT * LSRAID_SECTOR_SIZE * (MAX_PD_PER_ADP + 1))

/* Debug Message Levels */
#define CL_INFO					0x00000001	/* Verbose debug messages	*/
#define CL_WARN					0x00000002	/* Warnings and extra info	*/
#define CL_ERR					0x00000004	/* Print unconditionally	*/
#define CL_ANN					0x00000008	/* Announce unconditionally	*/

#define CL_DEBUG				0x00000010	/* Development dbg msgs		*/
#define CL_CFG					0x00000020	/* Debug config modules		*/
#define CL_RAID					0x00000040	/* Debug raid modules		*/
#define CL_RCL					0x00000080	/* Debug RCL layer			*/

#define CL_IOCTL				0x00000100	/* Debug IOCTL layer		*/
#define CL_R5_DEBUG				0x00000200	/* Raid5 code debug messages*/
#define CL_R5ST					0x00000400	/* Raid5 code debug messages*/
#define CL_HAMMER				0x00000800	/* Hammer test IOCTLs		*/

#define CL_REC					0x00001000	/* Recovery, abort, reset path			*/
#define CL_HAL					0x00002000	/* Debug HAL Layer						*/
#define CL_IBUTT				0x00004000	/* Debug iButton module					*/
#define CL_WMI					0x00008000	/* Debug Windows Management Interface	*/

#define CL_R1_CMD_RECOVERY		0x00010000	/* R1 Error Recovery path			*/
#define CL_ST					0x00020000	/* Special task debug messages		*/
#define CL_EVTMGR				0x00040000	/* Event Manager					*/
#define CL_ENQ					0x00080000	/* Enquiry related debug messages	*/
#define CL_SBBM					0x00100000	/* SBBM debug messages	*/
#define CL_ENCL       			0x00200000	/* Encl(SGPIO) debug messages	*/
#define CL_OSL       			0x00400000	/* osl related debugging */
#define CL_MM       			0x00800000	// memory manager debug message

#define CL_CACHE       			0x01000000	// Cache Layer debug message

#define CL_ALL					0xffffffff	/* All debug levels			*/
extern uint32_t dbglvl_g;					/* Bitmap to ctrl dbg msgs	*/
extern uint32_t	megasr_raid1_double_buffer;

#define DRIVER_DBG_LEVEL		(CL_ANN|CL_WARN|CL_ERR )

/* Success / Failure Values */
#define LSI_TRUE						0
#define LSI_FALSE						1

#define LSI_PWR_START_PENDING			2

#define LSI_SUCCESS						0
#define LSI_FAILURE						1


#define INVALID_HANDLE					0xFFFFFFFF

#define INVALID_DRV_ID					0xFF
#define LSI_INVALID_BLOCK_COUNT			0xFFFF

/* Request completion codes */
#define COMPLETE_REQUEST_TO_OS			1
#define REQUEST_DONE					2
#define REQUEST_PENDING					4

/* Memory flags definitions */
#define PHYSICAL_ADDRESS_NOT_REQUIRED	1
#define PHYSICAL_ADDRESS_REQUIRED		2
#define ALLOC_FROM_STATIC_POOL			4
#define ALLOC_FROM_DYNAMIC_POOL		 	8	// @FIXME: remove this

/* Reset Flags */
#define NO_RESET						0
#define DEV_RESET						1
#define BUS_RESET						2
#define ADP_RESET						3

/* Timer Active Flags */
#define TIMER_OFF						0
#define TIMER_ON						1

#define UNIT_PAUSED						(0x00)
#define UNIT_READY						(0x01)

typedef enum {
	SCSI_PACKET			= 0,
	IOCTL_TYPE_PACKET	= 1,
	DEVICE_PROPERTIES	= 2,
	INTERNAL_PACKET		= 3
} IO_PACKET_TYPE;

/* Failure Packet Status */
#define STS_SUCCESS					0x00
#define STS_CLEAN_ABORT				0x01
#define STS_DIRTY_ABORT				0x02
#define STS_TIME_OUT				0x03
#define STS_ERROR					0x04
#define STS_RESET					0x05
#define STS_UNSUPPORTED				0x06
#define STS_SCSI_ERROR				0x07
#define STS_PENDING					0x08
#define STS_BUSY					0x09
#define STS_NO_DEVICE				0x0A
#define	STS_MEDERR					0x0B
#define STS_SUGGEST_RETRY			0x0C
#define STS_CD_DVD_ERROR			0x0D

/* Power Mgmt States */
#define PM_S5							5		/* Shutdown */
#define PM_S4							4
#define PM_S3							3
#define PM_S2							2
#define PM_S1							1
#define PM_S0							0		/* On */

#define MAX_IO_PER_ADP_PERF				16

#define MAX_IO_PER_ADP					16
#define MAX_PATH_PER_ADP				1
/* maximum number of ports is number of bus for OSL. It is decided to have 3
 * bus, 0-for pass thru devices, 1-for logical drives, 2- for supporting
 * logical drive deletion
 */
#define MAX_BUS_PER_ADP					3	
#define MAX_PD_PER_ADP					8
#define MAX_RAID5_POOLS					MAX_PD_PER_ADP - 2	/* 6 pools - calculated max number of allocs that can be made for 8 PDs */
#define MAX_LUN_PER_ADP					8
#define MAX_PD_PER_LD					8	
#define MAX_LD_PER_ADP					8	
#define MAX_SPANS_PER_LD				4
#define MAX_FLOOR_LEVELS				2
#define MAX_NODES_IN_FLOOR				2
#define MAX_SUPPORTED_ADAPTERS			4
#define MAX_TIMERS						30
#define MAX_TRANSFER_LENGTH				(128 * 1024) /* 128K */
#define MAX_SGE_CNT						64
#define MAX_SGE_COUNT_FOR_OS			(MAX_SGE_CNT - 1)
#define MAX_SG_RAID_1_DOUBLE_BUFFER		4

/** Following definitions are used by the hibernation path to reduce memory consumption **/

/* Maximum number of HAL packets during hibernation and crash dump mode */
#define	MAX_HALP_COUNT_IN_HIBER			(16)

/* Maximum number of Scatter gather elements during hibernation and crash dump mode */
#define	MAX_HAL_SGE_COUNT_IN_HIBER		(8)

/* Maximum number of Scatter gather elements reported to OS during hibernation and crash dump mode */
#define MAX_SGE_COUNT_FOR_OS_HIBER		(MAX_HAL_SGE_COUNT_IN_HIBER - 1)

/*
 * Bus numbers
 *
 * Started exporting LDs on channel # 2 to be consistent with HWR
 */
#define PT_BUS							0
#define LD_BUS							2

/*
 * Common LED definitions
 */
#define NO_LED_PORT_PRESENT	0xFFFFFFFF

/*
 * FSC ICH7R LED definitions
 */
#define FSC_ACTIVITY_LED_PORT	0x200
#define FSC_FAULT_LED_PORT		0x201

/*
 * Coalescing parameters
 */
#define COALESCING_MAX_SIZE_R0			MAX_TRANSFER_LENGTH	//!< The maximum IO size to consider for coalescing on RAID0
#define COALESCING_MAX_SIZE_R1			MAX_TRANSFER_LENGTH	//!< The maximum IO size to consider for coalescing on RAID1
#define COALESCING_MAX_SIZE_R5			(512 * 1024)		//!< The maximum IO size to consider for coalescing on RAID5, it is not depend on max host IO size
#define COALESCING_MAX_SGE_R0			MAX_SGE_COUNT_FOR_OS				//!< The maximum scatter gather entries to consider for coalescing on RAID0
#define COALESCING_MAX_SGE_R1			MAX_SGE_COUNT_FOR_OS				//!< The maximum scatter gather entries to consider for coalescing on RAID1
#define COALESCING_MAX_SGE_R5			MAX_BIG_SGE_CNT				//!< The maximum scatter gather entries to consider for coalescing on RAID5
#define	MEGASR_DEFAULT_COALESCING_THRESHOLD			16		//!< Default coalescing threshold value

/*
 * Misc. definitions
 */
#define DIFF_BTWN_WIN_FW_TIME 12591158400 /* The number of seconds between Jan 1, 1601 GMT and Jan 1, 2000 GMT is 12,591,158,400. (Leap years taken into account)*/
#define NUM_100_NS_INTERVALS_IN_1_SEC 10000000 // There are 10,000,000 100-nanosecond intervals in 1 second.
#define NUM_SECS_IN_MIN 60 // Number of seconds in one minute
#define NUM_SECS_IN_HOUR (NUM_SECS_IN_MIN*60) // Number of seconds in one hour
#define NUM_SECS_IN_DAY (NUM_SECS_IN_HOUR*24) // Number of seconds in one day
#define NUM_SECS_IN_YEAR (NUM_SECS_IN_DAY*365) // Number of seconds in one year
#define NUM_SECS_IN_LEAP_YEAR (NUM_SECS_IN_DAY*366) // Number of seconds in a leap year (one extra day)
#define STARTING_LEAP_YEAR 2000 // Since FW Time begins at Jan 1, 2000, this is the first leap year to consider
#define NUM_SECS_IN_JAN (NUM_SECS_IN_DAY*31) // Number of seconds in one day
#define NUM_SECS_IN_FEB (NUM_SECS_IN_DAY*28) // Number of seconds in one day
#define NUM_SECS_IN_FEB_LEAP (NUM_SECS_IN_DAY*29) // Number of seconds in one day
#define NUM_SECS_IN_MAR (NUM_SECS_IN_DAY*31) // Number of seconds in one day
#define NUM_SECS_IN_APR (NUM_SECS_IN_DAY*30) // Number of seconds in one day
#define NUM_SECS_IN_MAY (NUM_SECS_IN_DAY*31) // Number of seconds in one day
#define NUM_SECS_IN_JUN (NUM_SECS_IN_DAY*30) // Number of seconds in one day
#define NUM_SECS_IN_JLY (NUM_SECS_IN_DAY*31) // Number of seconds in one day
#define NUM_SECS_IN_AUG (NUM_SECS_IN_DAY*31) // Number of seconds in one day
#define NUM_SECS_IN_SEP (NUM_SECS_IN_DAY*30) // Number of seconds in one day
#define NUM_SECS_IN_OCT (NUM_SECS_IN_DAY*31) // Number of seconds in one day
#define NUM_SECS_IN_NOV (NUM_SECS_IN_DAY*30) // Number of seconds in one day
#define NUM_SECS_IN_DEC (NUM_SECS_IN_DAY*31) // Number of seconds in one day
#define DEFAULT_ST_RATE 30
#define ENCLOSURE_CTRL_INDEX 0
#define BGI_CALLBACK_WAIT 30	// wait 30 seconds before issuing the callback to scan for any R5 LDs that are inconsistent and not running bgi
#define HUNDRED_MICROSEC 100
#define MEGASR_STRIPE_SIZE_64K		(64 * 1024)	/* 64 K stripe size*/
#define MEGASWR_MIN(a, b)	((a) < (b) ? (a) : (b))
#define MEGASWR_MAX(a, b)	((a) > (b) ? (a) : (b))

typedef enum {
	UNKNOWN_MEM_POOL_TYPE	= 0,
	DYNAMIC_MEM_POOL		= 1,
	STATIC_MEM_POOL			= 2,
	NO_PHY_ADDR_MEM_POOL	= 3
} mem_pool_type_e;

typedef enum {
	IODIR_UNDEFINED		= 0,
	IODIR_FROM_DEVICE	= 1,
	IODIR_TO_DEVICE		= 2,
	IODIR_BIDIRECTIONAL = 3,
	IODIR_NONE			= 4		/* WARNING !! Please note that only 4 bit is used to use this enum */
} IO_DIRECTION;					/* So max value it can have is 0xf */

typedef enum {
	LED_UNDEFINED						= 0,
	LED_DRIVE_SLOT_EMPTY				= 1,
	LED_DRIVE_ONLINE					= 2,
	LED_DRIVE_IDENTIFY					= 3,
	LED_DRIVE_PREPARED_FOR_REMOVAL		= 4,
	LED_DRIVE_REBUILDING				= 5,
	LED_DRIVE_FAILED					= 6,
	LED_DRIVE_OFFLINE					= 7,
	LED_DRIVE_ONLINE_FAILURE_PREDICTED	= 8,
	LED_DRIVE_CHKCON					= 9,
	LED_DRIVE_ACTIVITY_ON				= 10,
	LED_DRIVE_ACTIVITY_OFF				= 11,
	LED_DRIVE_MAX						= 15
} led_state_e;

typedef enum {
	RES_TYPE_UNDEFINED	= 0,
	RES_TYPE_IO			= 1,
	RES_TYPE_MEM		= 2,
	RES_TYPE_IRQ		= 3
} RES_TYPE;

typedef enum {
	FIRE_STATUS_UNDEFINED	= 0,
	FIRE_TO_HAL				= 1,
	DONT_FIRE_TO_HAL		= 2,
	INSUFFICIENT_RESOURCES	= 3,
	LOCK_FAILED				= 4
} firing_to_hal_e;

typedef enum {
	NO_IBTN			= 0,
	SATA_IBTN		= 1,
	SAS_IBTN		= 2
} ibutton_t;

typedef struct	io_resource {
	void_t		*vaddr;
	void_t		*paddr;
	RES_TYPE	io_type;
	uint32_t	length;
} io_resource_t;

typedef struct	device_id {
	uint8_t	path;
	uint8_t	bus;
	uint8_t	target;
	uint8_t	lun;
} device_id_t;

typedef struct _device_page0{
    uint16_t    slot;
    uint16_t    enclosureHandle;
    uint16_t    parentDevHandle;
    uint16_t    flags;
    uint32_t    deviceInfo;
} device_page0_t;

typedef struct	_cmn_sge {
	uint8_t		*vaddr;
	uint8_t		*paddr;
	uint32_t	length;
} cmn_sge_t;

typedef struct	_cmn_sgl {
	uint8_t		sge_count;
	cmn_sge_t	sge[MAX_SGE_CNT];
} cmn_sgl_t;

typedef struct _single_node_sgl {
	uint8_t		sge_count;
	cmn_sge_t	sge[1];
}single_node_sgl_t;

typedef struct	_hal_cmn_sgl {
	uint8_t		sge_count;
	cmn_sge_t	sge[0];
} hal_cmn_sgl_t;

#define MAX_BIG_SGE_CNT		128

/**
*@brief
* This structure is used by RCL packet to facilitate smaller HAL packet to
* bigger RCL packets
*/
typedef struct	_big_cmn_sgl_t {
	uint8_t		sge_count;		//!< Scatter gather element count
	cmn_sge_t	sge[MAX_BIG_SGE_CNT]; //!< Scatter gather elements
} big_cmn_sgl_t;

typedef struct _timer {
	uint8_t				active_calls;
	uint8_t				active;
	struct {
		timer_fn_t		callback;
		uint32_t		timeout;
		void_t			*context1, *context2;
	} arr[MAX_TIMERS];
} lsi_timer_t;

typedef enum {
	UNDEFINED_ALLOC					= 0,
	R0_HAL_ALLOC1					= 1,
	R0_HAL_ALLOC2					= 2,
	R0_RCL_ALLOC1					= 3,
	R1_HAL_ALLOC1					= 4,
	R1_HAL_ALLOC2					= 5,
	R1_HAL_ALLOC3					= 6,
	R1_RCL_ALLOC1					= 7,
	R5_HAL_ALLOC1					= 8,
	R5_HAL_ALLOC2					= 9,
	R5_HAL_ALLOC3					= 10,
	R5_HAL_ALLOC4					= 11,
	R5_HAL_ALLOC5					= 12,
	R5_HAL_ALLOC6					= 13,
	R5_HAL_ALLOC7					= 14,
	R5_REBUILDING_RCL_ALLOC1		= 15,
	R5_REBUILDING_HAL_ALLOC1		= 16,
	R5_XOR_BUDDY_ALLOC1				= 17,
	R5_XOR_BUDDY_ALLOC2				= 18,
	R5_XOR_BUDDY_ALLOC3				= 19,
	R5_XOR_BUDDY_ALLOC4				= 20,
	LIN_OSL_RCL_ALLOC1				= 21,
	LIN_OSL_RCL_ALLOC2				= 22,
	WIN_OSL_RCL_ALLOC1				= 23,
	WIN_OSL_RCL_ALLOC2				= 24,
	IOCTL_SCSI_PT_RCL_ALLOC1		= 25,
	IOCTL_SCSI_PT_HAL_ALLOC1		= 26,
	IOCTL_PD_INQUIRY_HAL_ALLOC1		= 27,
	CFG_LDF_UPDATE_1				= 28,
	CFG_LDF_UPDATE_2				= 29,
	CFG_MGR_SYNC_CACHE_ALLOC1		= 30,
	CFG_MGR_START_STOP_ALLOC1		= 31,
	CFG_MGR_MODESENSE_ALLOC1		= 32,
	CFG_MGR_MODESELECT_ALLOC1		= 33,
	HAL_10XX_ASYNC_INQ_ALLOC1		= 34,
	HAL_10XX_ASYNC_TUR_ALLOC1		= 35,
	HAL_10XX_ASYNC_READCAP_ALLOC1	= 36,
	R10_HAL_ALLOC1					= 37,
	WIN_OSL_OS_ALLOC1				= 38,
	HAL_10XX_WRITE_LONG_ALLOC1		= 39, 
	R1_HAL_10XX_WRITE_LONG_ALLOC1	= 40,
	R5_HAL_10XX_WRITE_LONG_ALLOC1	= 41,
 	HAL_10XX_ASYNC_MSG_SEP_REQUEST	= 42,
	WIN_OSL_OS_ALLOC2				= 43,
	HAL_MODESELECT_ALLOC1			= 44,
	HAL_AHCI_ALLOC1					= 45,
	CFG_MGR_SMART_ALLOC1			= 46,
	CFG_MGR_SMART_ALLOC2			= 47,
	R5_HAL_ALLOC8					= 48,
	HAL_10XX_SLOT_ENCLOSURE			= 49,
	HAL_AHCI_READ_LOG_EXT			= 50,
	RCL_PT_ALLOC1					= 51,
	CFG_MGR_LD_ASYNC_ALLOC1			= 52,
	HAL_AHCI_REQUEST_SENSE			= 53,
	RCL_CACHE_ALLOC1				= 54,
	RCL_CACHE_ALLOC2				= 55,
	CFG_MGR_SET_LD_CACHE_ALLOC1		= 56,
	CFG_MGR_SMART_RCLP_ALLOC1		= 57,
	LIN_OSL_RCL_ALLOC3				= 58,
	DDF_UPDATE_HP_ALLOC				= 59,
	R1_WRITEBACK_ALLOC				= 60,
	R1_DOUBLEBUFFER_ALLOC				= 61,
	/* Maximum possible value is 0x7F */
} owner_e;

#ifdef DEBUG_BUILD
//Used by the cfg mgr when deleting an LD in a checked build of the driver, used for debugging purposes
#define LD_DEBUG_DELETED_NAME		"DELETED LD"
#define LD_DEBUG_DELETED_NAME_LEN	sizeof(LD_DEBUG_DELETED_NAME)
#endif

//Memory Alignment Boundary
typedef enum {
	BOUNDARY_1_BYTE		= 0,
	BOUNDARY_2_BYTE		= 1,
	BOUNDARY_4_BYTE		= 2,
	BOUNDARY_8_BYTE		= 3,	
	BOUNDARY_16_BYTE	= 4,
	BOUNDARY_32_BYTE	= 5,
	BOUNDARY_64_BYTE	= 6,
	BOUNDARY_128_BYTE	= 7,
	BOUNDARY_256_BYTE	= 8,
	BOUNDARY_512_BYTE	= 9,
	BOUNDARY_1_KBYTE	= 10,
	BOUNDARY_2_KBYTE	= 11,
	BOUNDARY_4_KBYTE	= 12
} alignment_mask_e;

typedef enum {
	UNDEFINED_MEM_ALLOC				= 0,
	MEM_10XX_ALLOC1					= 1,
	MEM_10XX_ALLOC2					= 2,
	MEM_10XX_ALLOC3					= 3,
	MEM_10XX_ALLOC4					= 4,
	MEM_10XX_ALLOC5					= 5,
	MEM_10XX_ALLOC6					= 6,
	MEM_10XX_ALLOC7					= 7,
	MEM_10XX_ALLOC8					= 8,
	MEM_AHCI_ALLOC1					= 9,
	MEM_AHCI_ALLOC2					= 10,
	MEM_AHCI_ALLOC3					= 11,
	MEM_AHCI_ALLOC4					= 12,
	MEM_AHCI_ALLOC5					= 13,
	MEM_AHCI_ALLOC6					= 14,
	MEM_AHCI_ALLOC7					= 15,
	MEM_AHCI_ALLOC8					= 16,
	MEM_AHCI_ALLOC9					= 17,
	MEM_AHCI_ALLOC10				= 18,
	MEM_AHCI_ALLOC11				= 19,
	MEM_BBRW_ALLOC1					= 20,
	MEM_HALPKTPOOL_ALLOC1			= 21,
	MEM_MPT_ALLOC1					= 22,
	MEM_MPT_ALLOC2					= 23,
	MEM_MPT_ALLOC3					= 24,
	MEM_MPT_ALLOC4					= 25,
	MEM_MPT_ALLOC5					= 26,
	MEM_MPT_ALLOC6					= 27,
	MEM_MPT_ALLOC7					= 28,
	MEM_MPT_ALLOC8					= 29,
	MEM_MPT_ALLOC9					= 30,
	MEM_MPT_ALLOC10					= 31,
	MEM_MPT_ALLOC11					= 32,
	MEM_RCLPKTPOOL_ALLOC1			= 33,
	MEM_LDF_ALLOC1					= 34,
	MEM_LDF_ALLOC2					= 35,
	MEM_LDF_ALLOC3					= 36,
	MEM_CFG_ALLOC1					= 37,
	MEM_CFG_ALLOC2					= 38,
	MEM_CFG_ALLOC3					= 39,
	MEM_CFG_ALLOC4					= 40,
	MEM_CFG_ALLOC5					= 41,
	MEM_CFG_ALLOC6					= 42,
	MEM_CFGSIM_ALLOC1				= 43,
	MEM_CFGSIM_ALLOC2				= 44,
	MEM_CFGSIM_ALLOC3				= 45,
	MEM_CFGSIM_ALLOC4				= 46,
	MEM_CFGSIM_ALLOC5				= 47,
	MEM_R5ST_ALLOC1					= 48,
	MEM_R0_ALLOC1					= 49,
	MEM_R0_ALLOC2					= 50,
	MEM_R0_ALLOC3					= 51,
	MEM_R1_ALLOC1					= 52,
	MEM_R1_ALLOC2					= 53,
	MEM_R1_ALLOC3					= 54,
	MEM_R1_ALLOC4					= 55,
	MEM_R1_ALLOC5					= 56,
	MEM_R5_ALLOC_DEG_READ_1			= 57,
	MEM_R5_ALLOC_DEG_READ_2			= 58,
	MEM_R5_ALLOC_DEG_READ_3			= 59,
	MEM_R5_ALLOC_DEG_WRITE_1		= 60,
	MEM_R5_ALLOC_DEG_WRITE_2		= 61,
	MEM_R5_ALLOC_DEG_WRITE_3		= 62,
	MEM_R5_ALLOC_DEG_REGEN_PRM_1	= 63,
	MEM_R5_ALLOC3					= 64,
	MEM_EVTMGR_POOL_ALLOC1			= 65,
	MEM_RX_INIT_ALLOC				= 66,
	MEM_10XX_SLOT_ENCL				= 67,
	MEM_RCLCACHE_POOL_ALLOC1		= 68,
	MEM_RCLCACHE_POOL_ALLOC2		= 69,
	MEM_AHCI_REQUEST_SENSE			= 70,
	MEM_CFG_ALLOC7					= 71,
	MEM_CACHE_ALLOC1				= 72,
	HAL_DIAG_RING_BUFF				= 73,
	HAL_DIAG_RELEASE_RING_BUFF		= 74,
	MEM_RECPKTPOOL_ALLOC1			= 75,
	MEM_RAID1_DOUBLE_BUFFER_ALLOC	= 76,
	MEM_MAX_OWNER					= 255
} mem_owner_e;

/* Function Prototypes */
uint8_t	*mem_alloc(pvt_data_t *os_cxt, uint32_t size, alignment_mask_e align_boundary, uint32_t flags, uint8_t **phy_addr, mem_owner_e owner);
void_t mem_free(pvt_data_t *os_cxt, uint8_t *vaddr);
void_t lsi_mm_dynamic_free(pvt_data_t *os_cxt, pvt_data_t *handle);
boolean_t lsi_mm_add_sgl_mem_for_ddf(pvt_data_t *adapter, cmn_sgl_t *sgl, uint8_t reclaim);
boolean_t lsi_mm_release_ddf_mem_add_sgl_mem(pvt_data_t *adapter, uint32_t sgl_mem_length_hiber);
boolean_t mem_mgr_set_sgl_mem_request(pvt_data_t *, uint32_t, mem_added_fn_t, uint32_t *, pvt_data_t *);
pvt_data_t* lsi_mm_dynamic_alloc(pvt_data_t *os_cxt, uint32_t nbytes, cmn_sgl_t *sgl, mem_owner_e owner);

#define LSI_CONTROLLER_NAME_LEN 80 /*size of character array in mr.h for the controller information ioctl*/

#define LOWER_32BITS_FROM_64BIT_ADDR(addr) (uint32_t)((addr_t)addr)
#define UPPER_32BITS_FROM_64BIT_ADDR(addr) 0
#ifdef COMPILE_64BIT
	#undef UPPER_32BITS_FROM_64BIT_ADDR
	#define UPPER_32BITS_FROM_64BIT_ADDR(addr) (uint32_t)((((addr_t)addr) & 0xFFFFFFFF00000000) >> 32)
#endif

void_t remove_leading_whitespace(uint8_t *original_chars, uint8_t num_of_chars);
void_t remove_leading_whitespace_null_terminated(uint8_t *original_chars);

#define countof(xx)         (sizeof(xx) / sizeof(xx[0]))

typedef void_t (*rclp_callback_t) (pvt_data_t *, pvt_data_t *);

typedef struct {
	void		*pMfiIoctl;
	uint32_t    status; // this can be STS_PENDING or STS_DONE
} ioctl_packet_t;

/*
 * FIXME Added newly, may need to have some compile error corrections
 */
typedef struct pkt_cmd {
	uint8_t					packet_type;		/* I/O or passthrough or device properties */
    union {
	    scsi_packet_t		scsi_packet;	/* CDB */
		ioctl_packet_t		ioctl_pkt;		/* IOCTL packet */
    } u;
} pkt_cmd_t;
/**
*@struct rcl_packet_public_t
*
*@brief
* This is the open part of an RCL packet which is accessible to the OSL */
#pragma pack(push, 1)
typedef struct _rcl_packet_public_t {
	rclp_callback_t	success_handler;//!< who ever creates rcl pkt should provide
	rclp_callback_t	failure_handler;//!< Who ever creates rcl pkt should provide
	sectors_t		start_blk;		//!< Logical Start Sector of this RCL packet
	pvt_data_t		*os_packet;		//!< OS Packet Pointer for OSL usage. 
	uint32_t		buffer_len;		//!< Data Buffer length
	uint32_t		blk_count;		//!< Number of Sectors in this RCL packet
	uint32_t		sense_len;		//!< Sense Data Length
	uint32_t		status;			//!< RCL command Status
	uint32_t		scsi_status;	//!< SCSI command Status 
	struct megasr_clist list;	//!< RCL queue.
	device_id_t	 	device_id;		//!< Drive ID
	pkt_cmd_t		cmd; 			//!< Packet Command structure
	big_cmn_sgl_t	cmn_sgl;		//!< Scatter Gather List Table
	lsi_sense_data	sense_info;		//!< Sense Data Information
	uint8_t			io_direction;	//!< IO direction of this RCL Packet
	uint8_t			owner;			//!< Owner or allocator of this RCL Packet
	uint8_t			bkup_sge_count;	//!< Back up scatter gather element count
} rcl_packet_public_t;

struct megasas_aen {
	uint16_t	host_no;
	uint16_t	__pad1;
	uint32_t	seq_num;
	uint32_t	class_locale_word;
};

struct megasas_hdr {

	uint8_t			cmd;
	uint8_t			sense_len;
	uint8_t			cmd_status;
	uint8_t			scsi_status;
	
	uint8_t			target_id;
	uint8_t			lun;
	uint8_t			cdb_len;
	uint8_t			sge_count;

	uint32_t		context;
	uint32_t		pad_0;

	uint16_t		flags;
	uint16_t		timeout;

	uint32_t		data_xferlen;

};
	
#pragma pack(pop)

#endif /* LSI_MEGA_SWR_COMMON_DEFS_H */

/* vim: set ts=4 sw=4 nowrap: */

