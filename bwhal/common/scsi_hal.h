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
 * * File Name	: scsi_hal.h
 * Programer(s) : Kolli, Neela Syam; Khan, Ismail; Bagalkote, Sreenivas;
 * Created on	: 06-23-2004
 *
 * Description	:
 * This header is used only below the HAL, by the hardware implementations.
 * It will _not_ have any RAID knowledge.
 *
 * * History	:
 *	06-23-2004:	Created this file
 *  08-26-2004: Version 1
 * TODO	:
 *	None
 *---------------------------------------------------------------------------- */

#ifndef LSI_MEGA_SWR_SCSI_HAL_H
#define LSI_MEGA_SWR_SCSI_HAL_H

#define CDB_LENGTH_10	10
#define CDB_LENGTH_16	16
#define MAX_CDB_LENGTH	16

#define SCSI_INQUIRY_VENDOR_ID_LEN 8
#define SCSI_INQUIRY_PRODUCT_REVISION_LEVEL_LEN 4
#define SCSI_INQUIRY_PRODUCT_ID_LEN 16
#define SCSI_INQUIRY_IDENTIFIER_HEADER_LEN 4
#define SCSI_INQUIRY_VENDOR_SPECIFIC_LEN 20
#define LSI_COERCED_PRODUCT_ID_LEN 8


/* SCSI LSI_CDB operation codes */

/* 6-byte commands: */
#define LSI_SCSIOP_TEST_UNIT_READY		0x00
#define LSI_SCSIOP_REZERO_UNIT			0x01
#define LSI_SCSIOP_REWIND				0x01
#define LSI_SCSIOP_REQUEST_BLOCK_ADDR	0x02
#define LSI_SCSIOP_REQUEST_SENSE		0x03
#define LSI_SCSIOP_FORMAT_UNIT			0x04
#define LSI_SCSIOP_READ_BLOCK_LIMITS	0x05
#define LSI_SCSIOP_REASSIGN_BLOCKS		0x07
#define LSI_SCSIOP_INIT_ELEMENT_STATUS	0x07
#define LSI_SCSIOP_READ6				0x08
#define LSI_SCSIOP_RECEIVE				0x08
#define LSI_SCSIOP_WRITE6				0x0A
#define LSI_SCSIOP_PRINT				0x0A
#define LSI_SCSIOP_SEND					0x0A
#define LSI_SCSIOP_SEEK6				0x0B
#define LSI_SCSIOP_TRACK_SELECT			0x0B
#define LSI_SCSIOP_SLEW_PRINT			0x0B
#define LSI_SCSIOP_SEEK_BLOCK			0x0C
#define LSI_SCSIOP_PARTITION			0x0D
#define LSI_SCSIOP_READ_REVERSE			0x0F
#define LSI_SCSIOP_WRITE_FILEMARKS		0x10
#define LSI_SCSIOP_FLUSH_BUFFER			0x10
#define LSI_SCSIOP_SPACE				0x11
#define LSI_SCSIOP_INQUIRY				0x12
#define LSI_SCSIOP_VERIFY6				0x13
#define LSI_SCSIOP_RECOVER_BUF_DATA		0x14
#define LSI_SCSIOP_MODE_SELECT			0x15
#define LSI_SCSIOP_RESERVE_UNIT			0x16
#define LSI_SCSIOP_RELEASE_UNIT			0x17
#define LSI_SCSIOP_COPY					0x18
#define LSI_SCSIOP_ERASE				0x19
#define LSI_SCSIOP_MODE_SENSE			0x1A
#define LSI_SCSIOP_START_STOP_UNIT		0x1B
#define LSI_SCSIOP_STOP_PRINT			0x1B
#define LSI_SCSIOP_LOAD_UNLOAD			0x1B
#define LSI_SCSIOP_RECEIVE_DIAGNOSTIC	0x1C
#define LSI_SCSIOP_SEND_DIAGNOSTIC		0x1D
#define LSI_SCSIOP_MEDIUM_REMOVAL		0x1E

/* 10-byte commands */
#define LSI_SCSIOP_READ_FORMATTED_CAPACITY	0x23
#define LSI_SCSIOP_READ_CAPACITY			0x25
#define LSI_SCSIOP_READ						0x28
#define LSI_SCSIOP_WRITE					0x2A
#define LSI_SCSIOP_SEEK						0x2B
#define LSI_SCSIOP_LOCATE					0x2B
#define LSI_SCSIOP_POSITION_TO_ELEMENT		0x2B
#define LSI_SCSIOP_WRITE_VERIFY				0x2E
#define LSI_SCSIOP_VERIFY					0x2F
#define LSI_SCSIOP_SEARCH_DATA_HIGH			0x30
#define LSI_SCSIOP_SEARCH_DATA_EQUAL		0x31
#define LSI_SCSIOP_SEARCH_DATA_LOW			0x32
#define LSI_SCSIOP_SET_LIMITS				0x33
#define LSI_SCSIOP_READ_POSITION			0x34
#define LSI_SCSIOP_SYNCHRONIZE_CACHE		0x35
#define LSI_SCSIOP_COMPARE					0x39
#define LSI_SCSIOP_COPY_COMPARE				0x3A
#define LSI_SCSIOP_WRITE_DATA_BUFF			0x3B
#define LSI_SCSIOP_READ_DATA_BUFF			0x3C
#define LSI_SCSIOP_WRITE_LONG				0x3F
#define LSI_SCSIOP_CHANGE_DEFINITION		0x40
#define LSI_SCSIOP_READ_SUB_CHANNEL			0x42
#define LSI_SCSIOP_READ_TOC					0x43
#define LSI_SCSIOP_READ_HEADER				0x44
#define LSI_SCSIOP_PLAY_AUDIO				0x45
#define LSI_SCSIOP_GET_CONFIGURATION		0x46
#define LSI_SCSIOP_PLAY_AUDIO_MSF			0x47
#define LSI_SCSIOP_PLAY_TRACK_INDEX			0x48
#define LSI_SCSIOP_PLAY_TRACK_RELATIVE		0x49
#define LSI_SCSIOP_GET_EVENT_STATUS			0x4A
#define LSI_SCSIOP_PAUSE_RESUME				0x4B
#define LSI_SCSIOP_LOG_SELECT				0x4C
#define LSI_SCSIOP_LOG_SENSE				0x4D
#define LSI_SCSIOP_STOP_PLAY_SCAN			0x4E
#define LSI_SCSIOP_READ_DISK_INFORMATION	0x51
#define LSI_SCSIOP_READ_DISC_INFORMATION	0x51	/* proper use of disc over disk */
#define LSI_SCSIOP_READ_TRACK_INFORMATION	0x52
#define LSI_SCSIOP_RESERVE_TRACK_RZONE		0x53
#define LSI_SCSIOP_SEND_OPC_INFORMATION		0x54	/* optimum power calibration */
#define LSI_SCSIOP_MODE_SELECT10			0x55
#define LSI_SCSIOP_RESERVE_UNIT10			0x56
#define LSI_SCSIOP_RELEASE_UNIT10			0x57
#define LSI_SCSIOP_MODE_SENSE10				0x5A
#define LSI_SCSIOP_CLOSE_TRACK_SESSION		0x5B
#define LSI_SCSIOP_READ_BUFFER_CAPACITY		0x5C
#define LSI_SCSIOP_SEND_CUE_SHEET			0x5D
#define LSI_SCSIOP_PERSISTENT_RESERVE_IN	0x5E
#define LSI_SCSIOP_PERSISTENT_RESERVE_OUT	0x5F

/* 12-byte commands */
#define LSI_SCSIOP_READ12               0xA8
#define LSI_SCSIOP_WRITE12              0xAA
#define LSI_SCSIOP_REPORT_LUNS			0xA0
#define LSI_SCSIOP_BLANK				0xA1
#define LSI_SCSIOP_ATA_PASSTHRU			0xA1
#define LSI_SCSIOP_SEND_EVENT			0xA2
#define LSI_SCSIOP_SEND_KEY				0xA3
#define LSI_SCSIOP_REPORT_KEY			0xA4
#define LSI_SCSIOP_MOVE_MEDIUM			0xA5
#define LSI_SCSIOP_LOAD_UNLOAD_SLOT		0xA6
#define LSI_SCSIOP_EXCHANGE_MEDIUM		0xA6
#define LSI_SCSIOP_SET_READ_AHEAD		0xA7
#define LSI_SCSIOP_READ_DVD_STRUCTURE	0xAD
#define LSI_SCSIOP_REQUEST_VOL_ELEMENT	0xB5
#define LSI_SCSIOP_SEND_VOLUME_TAG		0xB6
#define LSI_SCSIOP_READ_ELEMENT_STATUS	0xB8
#define LSI_SCSIOP_READ_CD_MSF			0xB9
#define LSI_SCSIOP_SCAN_CD				0xBA
#define LSI_SCSIOP_SET_CD_SPEED			0xBB
#define LSI_SCSIOP_PLAY_CD				0xBC
#define LSI_SCSIOP_MECHANISM_STATUS		0xBD
#define LSI_SCSIOP_READ_CD				0xBE
#define LSI_SCSIOP_SEND_DVD_STRUCTURE	0xBF
#define LSI_SCSIOP_INIT_ELEMENT_RANGE	0xE7

// 16-byte commands
#define LSI_SCSIOP_READ16               0x88
#define LSI_SCSIOP_WRITE16              0x8A
#define LSI_SCSIOP_VERIFY16             0x8F
#define LSI_SCSIOP_SYNCHRONIZE_CACHE16  0x91
#define LSI_SCSIOP_READ_CAPACITY16      0x9E

// command for internal purposes
#define LSI_SCSIOP_ISSUE_IDENTIFY_INTERNAL	0xFD
#define LSI_SCSIOP_UDMA_INTERNAL			0xFE

/* SCSI bus status codes. */
#define SCSISTAT_GOOD					0x00
#define SCSISTAT_CHECK_CONDITION		0x02
#define SCSISTAT_CONDITION_MET			0x04
#define SCSISTAT_BUSY					0x08
#define SCSISTAT_INTERMEDIATE			0x10
#define SCSISTAT_INTERMEDIATE_COND_MET	0x14
#define SCSISTAT_RESERVATION_CONFLICT	0x18
#define SCSISTAT_COMMAND_TERMINATED		0x22
#define SCSISTAT_QUEUE_FULL				0x28

#define INQUIRYDATABUFFERSIZE			36
#define MAX_INQUIRY_DATABUFFERSIZE		96
#define REQSENSE_LENGTH					18

/* SCSI Inquiry Data */
#pragma pack(push, inquiry, 1)
typedef struct	scsi_inquiry_data {
	uint8_t DeviceType : 5;
	uint8_t DeviceTypeQualifier : 3;
	uint8_t DeviceTypeModifier : 7;
	uint8_t RemovableMedia : 1;
	union {
		uint8_t Versions;
		struct {
			uint8_t ANSIVersion : 3;
			uint8_t ECMAVersion : 3;
			uint8_t ISOVersion : 2;
		};
	};
	uint8_t ResponseDataFormat : 4;
	uint8_t HiSupport : 1;
	uint8_t NormACA : 1;
	uint8_t TerminateTask : 1;
	uint8_t AERC : 1;
	uint8_t AdditionalLength;
	uint8_t Reserved;
	uint8_t Addr16 : 1;				/* defined only for SIP devices. */
	uint8_t Addr32 : 1;				/* defined only for SIP devices. */
	uint8_t AckReqQ : 1;			/* defined only for SIP devices. */
	uint8_t MediumChanger : 1;
	uint8_t MultiPort : 1;
	uint8_t ReservedBit2 : 1;
	uint8_t EnclosureServices : 1;
	uint8_t ReservedBit3 : 1;
	uint8_t SoftReset : 1;
	uint8_t CommandQueue : 1;
	uint8_t TransferDisable : 1;	/* defined only for SIP devices. */
	uint8_t LinkedCommands : 1;
	uint8_t Synchronous : 1;		/* defined only for SIP devices. */
	uint8_t Wide16Bit : 1;			/* defined only for SIP devices. */
	uint8_t Wide32Bit : 1;			/* defined only for SIP devices. */
	uint8_t RelativeAddressing : 1;
	uint8_t VendorId[SCSI_INQUIRY_VENDOR_ID_LEN];
	uint8_t ProductId[SCSI_INQUIRY_PRODUCT_ID_LEN];
	uint8_t ProductRevisionLevel[SCSI_INQUIRY_PRODUCT_REVISION_LEVEL_LEN];
	uint8_t VendorSpecific[SCSI_INQUIRY_VENDOR_SPECIFIC_LEN];
	uint8_t Reserved3[40];
} scsi_inquiry_data_t;
#pragma pack(pop, inquiry)

/* DeviceType field */
#define DIRECT_ACCESS_DEVICE			0x00	/* disks */
#define SEQUENTIAL_ACCESS_DEVICE		0x01	/* tapes */
#define PRINTER_DEVICE					0x02	/* printers */
#define PROCESSOR_DEVICE				0x03	/* scanners, printers, etc */
#define WRITE_ONCE_READ_MULTIPLE_DEVICE 0x04	/* worms */
#define READ_ONLY_DIRECT_ACCESS_DEVICE	0x05	/* cdroms */
#define SCANNER_DEVICE					0x06	/* scanners */
#define OPTICAL_DEVICE					0x07	/* optical disks */
#define MEDIUM_CHANGER					0x08	/* jukebox */
#define COMMUNICATION_DEVICE			0x09	/* network */
#define ARRAY_CONTROLLER_TYPE			0xC		/* array controller: e.g. RAID*/
#define LOGICAL_UNIT_NOT_PRESENT_DEVICE 0x7F


#define DEVICE_QUALIFIER_ACTIVE			0x00
#define DEVICE_QUALIFIER_NOT_ACTIVE		0x01
#define DEVICE_QUALIFIER_NOT_SUPPORTED	0x03

/* DeviceTypeQualifier field */
#define DEVICE_CONNECTED	0x00


/* Sense Data Format */
typedef struct	_lsi_sense_data {
	uint8_t ErrorCode : 7;
	uint8_t Valid : 1;
	uint8_t SegmentNumber;
	uint8_t SenseKey : 4;
	uint8_t Reserved : 1;
	uint8_t IncorrectLength : 1;
	uint8_t EndOfMedia : 1;
	uint8_t FileMark : 1;
	uint8_t Information[4];
	uint8_t AdditionalSenseLength;
	uint8_t CommandSpecificInformation[4];
	uint8_t AdditionalSenseCode;
	uint8_t AdditionalSenseCodeQualifier;
	uint8_t FieldReplaceableUnitCode;
	uint8_t SenseKeySpecific[3];
}
lsi_sense_data, *psi_sense_data;

/* Default request sense buffer size */
#define SENSE_BUFFER_SIZE	18

/* Sense codes */
#define SCSI_SENSE_NO_SENSE			0x00
#define SCSI_SENSE_RECOVERED_ERROR	0x01
#define SCSI_SENSE_NOT_READY		0x02
#define SCSI_SENSE_MEDIUM_ERROR		0x03
#define SCSI_SENSE_HARDWARE_ERROR	0x04
#define SCSI_SENSE_ILLEGAL_REQUEST	0x05
#define SCSI_SENSE_UNIT_ATTENTION	0x06
#define SCSI_SENSE_DATA_PROTECT		0x07
#define SCSI_SENSE_BLANK_CHECK		0x08
#define SCSI_SENSE_UNIQUE			0x09
#define SCSI_SENSE_COPY_ABORTED		0x0A
#define SCSI_SENSE_ABORTED_COMMAND	0x0B
#define SCSI_SENSE_EQUAL			0x0C
#define SCSI_SENSE_VOL_OVERFLOW		0x0D
#define SCSI_SENSE_MISCOMPARE		0x0E
#define SCSI_SENSE_RESERVED			0x0F

/* Additional tape bit */
#define SCSI_ILLEGAL_LENGTH 0x20
#define SCSI_EOM			0x40
#define SCSI_FILE_MARK		0x80

/* Additional Sense codes */
#define SCSI_ADSENSE_NO_SENSE			0x00
#define SCSI_ADSENSE_LUN_NOT_READY		0x04

#define SCSI_ADSENSE_TRACK_ERROR		0x14
#define SCSI_ADSENSE_SEEK_ERROR			0x15
#define SCSI_ADSENSE_REC_DATA_NOECC		0x17
#define SCSI_ADSENSE_REC_DATA_ECC		0x18

#define SCSI_ADSENSE_ILLEGAL_COMMAND	0x20
#define SCSI_ADSENSE_ILLEGAL_BLOCK		0x21
#define SCSI_ADSENSE_INVALID_CDB		0x24
#define SCSI_ADSENSE_INVALID_LUN		0x25
#ifdef SCSI_ADWRITE_PROTECT
	#undef SCSI_ADWRITE_PROTECT /*Windows Vista includes files define this too*/
#endif
#define SCSI_ADWRITE_PROTECT			0x27
#define SCSI_ADSENSE_MEDIUM_CHANGED		0x28
#define SCSI_ADSENSE_BUS_RESET			0x29

#define SCSI_ADSENSE_INVALID_MEDIA		0x30
#define SCSI_ADSENSE_NO_MEDIA_IN_DEVICE 0x3a
#define SCSI_ADSENSE_POSITION_ERROR		0x3b

/* the second is for legacy apps. */
#define SCSI_ADSENSE_FAILURE_PREDICTION_THRESHOLD_EXCEEDED	0x5d
#define SCSI_FAILURE_PREDICTION_THRESHOLD_EXCEEDED			SCSI_ADSENSE_FAILURE_PREDICTION_THRESHOLD_EXCEEDED

#define SCSI_ADSENSE_COPY_PROTECTION_FAILURE				0x6f

#define SCSI_ADSENSE_VENDOR_UNIQUE							0x80

#define SCSI_ADSENSE_MUSIC_AREA								0xA0
#define SCSI_ADSENSE_DATA_AREA								0xA1
#define SCSI_ADSENSE_VOLUME_OVERFLOW						0xA7

/* SCSI_ADSENSE_LUN_NOT_READY (0x04) qualifiers */
#define SCSI_SENSEQ_CAUSE_NOT_REPORTABLE			0x00
#define SCSI_SENSEQ_BECOMING_READY					0x01
#define SCSI_SENSEQ_INIT_COMMAND_REQUIRED			0x02
#define SCSI_SENSEQ_MANUAL_INTERVENTION_REQUIRED	0x03
#define SCSI_SENSEQ_FORMAT_IN_PROGRESS				0x04
#define SCSI_SENSEQ_OPERATION_IN_PROGRESS			0x07
#define SCSI_SENSEQ_LONG_WRITE_IN_PROGRESS			0x08

/* SCSI_ADSENSE_NO_SENSE (0x00) qualifiers */
#define SCSI_SENSEQ_FILEMARK_DETECTED			0x01
#define SCSI_SENSEQ_END_OF_MEDIA_DETECTED		0x02
#define SCSI_SENSEQ_SETMARK_DETECTED			0x03
#define SCSI_SENSEQ_BEGINNING_OF_MEDIA_DETECTED 0x04

/* SCSI_ADSENSE_ILLEGAL_BLOCK (0x21) qualifiers */
#define SCSI_SENSEQ_ILLEGAL_ELEMENT_ADDR	0x01

/* SCSI_ADSENSE_POSITION_ERROR (0x3b) qualifiers */
#define SCSI_SENSEQ_DESTINATION_FULL	0x0d
#define SCSI_SENSEQ_SOURCE_EMPTY		0x0e

/* SCSI_ADSENSE_INVALID_MEDIA (0x30) qualifiers */

#define SCSI_SENSEQ_INCOMPATIBLE_MEDIA_INSTALLED	0x00
#define SCSI_SENSEQ_UNKNOWN_FORMAT					0x01
#define SCSI_SENSEQ_INCOMPATIBLE_FORMAT				0x02

/* SCSI_ADSENSE_COPY_PROTECTION_FAILURE (0x6f) qualifiers */

#define SCSI_SENSEQ_AUTHENTICATION_FAILURE							0x00
#define SCSI_SENSEQ_KEY_NOT_PRESENT									0x01
#define SCSI_SENSEQ_KEY_NOT_ESTABLISHED								0x02
#define SCSI_SENSEQ_READ_OF_SCRAMBLED_SECTOR_WITHOUT_AUTHENTICATION 0x03
#define SCSI_SENSEQ_MEDIA_CODE_MISMATCHED_TO_LOGICAL_UNIT			0x04
#define SCSI_SENSEQ_LOGICAL_UNIT_RESET_COUNT_ERROR					0x05

/* SCSI Packet */
typedef struct scsi_packet {
	uint32_t	cdb_len;
	union {
		uint8_t lsi_cdb[16];		// TODO Atul: Remove this union and adjust driver code
	} u;
} scsi_packet_t;

/* Read Capacity Data - returned in Big Endian format */
typedef struct	_lsi_read_capacity_data {
	uint32_t	logical_block_addr;
	uint32_t	bytes_per_block;
} lsi_read_capacity_data_t;

/* Read Capacity Data Extended - returned in Big Endian format */
typedef struct	_lsi_read_capacity_data_ex {
	uint64_t	logical_block_addr;
	uint32_t	bytes_per_block;
} lsi_read_capacity_data_ex_t;

#define VPD_SUPPORTED_PAGES         0x00
#define VPD_SERIAL_NUMBER           0x80
#define VPD_DEVICE_IDENTIFIERS      0x83

#define MODESENSE_CACHE_MODE_PAGE	0x08

typedef struct vpd_supported_pages_page {
    uint8_t DeviceType : 5;
    uint8_t DeviceTypeQualifier : 3;
    uint8_t PageCode;
    uint8_t Reserved;
    uint8_t PageLength;
    uint8_t SupportedPageList[0];
} vpd_supported_pages_page_t;

//Structures defined from SCSI Primary Commands rev 21b (12/01/2004) sec 7.6
typedef struct vpd_identification_page {
    uint8_t deviceType : 5;
    uint8_t deviceTypeQualifier : 3;
    uint8_t pageCode;
    uint8_t reserved;
    uint8_t pageLength;
    //
    // The following field is actually a variable length array of identification
    // descriptors.  Unfortunately there's no C notation for an array of
    // variable length structures so we're forced to just pretend.
    // 
    uint8_t descriptors[0];
} vpd_identification_page_t;

typedef struct vpd_identification_descriptor {
    uint8_t codeSet : 4;
    uint8_t protocol : 4;
    uint8_t identifierType : 4;
    uint8_t association : 2;
    uint8_t reserved : 1;
    uint8_t piv : 1;
    uint8_t reserved2;
    uint8_t identifierLength;
    uint8_t identifier[1];
} vpd_identification_descriptor_t;

/* Mode Sense/Select */
typedef enum {
	ScsiModePageControlCurrent = 0,
	ScsiModePageControlChangeable = 1,
	ScsiModePageControlDefault = 2,
	ScsiModePageControlSaved = 3
} scsi_mode_page_control_e;

typedef enum {
	ScsiModePageUnitAttention = 0x00,
	ScsiModePageErrorRecovery = 0x01,
	ScsiModePageDisconnnectReconnect = 0x02,
	ScsiModePageFormat = 0x03,
	ScsiModePageRigidDriveGeometry = 0x04,
	ScsiModePageVerifyErrorRecovery = 0x07,
	ScsiModePageCaching = 0x08,
	ScsiModePageControlMode = 0x0A,
	ScsiModePageControlModeAlias = 0x1A,
	ScsiModePageNotchAndPartition = 0x0C,
	ScsiModePagePowerCondition = 0x0D,
	ScsiModePageXor = 0x10,
	ScsiModePageInformationExceptions = 0x1C,
	ScsiModePageAllSupported = 0x3F
} scsi_mode_page_e;

typedef struct _lsi_mode10_param_list {
	uint16_t SenseDataLength;                      // big-endian
	// must be 0 for mode select (10)
	uint8_t MediumType;                            // always zero for ST34501W
	uint8_t Reserved1 : 4;
	uint8_t DpoFuaSupported : 1;                   // if TRUE, DisablePageOut and ForceUnitAccess bits of read and write commands are supported
	// must be FALSE for mode select (10)
	uint8_t Reserved2 : 2;
	uint8_t WriteProtected : 1;                    // if TRUE, medium cannot be written to ???but it can save mode settings???
	// must be FALSE for mode select (10)
	uint8_t Reserved3[ 2 ];
	uint16_t BlockDescriptorLength;                // Seagate drives return either 8 (one descriptor sent by drive (sense) or host (select)) or 0 (none sent)
} lsi_mode10_param_list_t; // for mode sense (10) and mode select (10)

typedef struct _lsi_mode_block_descriptor {
	uint8_t DensityCode;
	uint8_t NumberOfBlocks[ 3 ];
	uint8_t Reserved1;
	uint8_t BlockLength[ 3 ];
} lsi_mode_block_descriptor_t; // for mode sense (6), mode sense (10), mode select (6), mode select (10)

typedef struct _lsi_mode_caching_page {
	uint8_t PageCode   : 6;
	uint8_t Reserved1  : 1;
	uint8_t ParameterIsSavable : 1;                // must be FALSE for mode select (6) and (10)
	uint8_t PageLength;
	uint8_t ReadCacheDisable : 1;
	uint8_t MultiplicationFactor : 1;              // if TRUE, min/max prefetch are multiplied by some constant of ???unknown origin
	uint8_t WriteCacheEnable : 1;
	uint8_t SizeEnable : 1;                        // always FALSE for ST34501W, so NumberOfCacheSegments controls size of segments, not CacheSegmentSize
	uint8_t PrefetchAcrossTimeDiscontinuities : 1;
	uint8_t CachingAnalysisPermitted : 1;
	uint8_t AbortPrefetchUponSelection : 1;
	uint8_t InitiatorControl : 1;                  // if TRUE on Seagate drives, disables adaptive read look ahead (ARLA)
	uint8_t DemandReadRetentionPriority : 4;       // always 0 on ST34501W because doesn't distinguish caching host-requested from prefetched data
	uint8_t WriteRetentionPriority : 4;            // always 0 on ST34501W because does distinguish caching host-requested from prefetched data
	uint16_t DisablePrefetchTransferLength;        // big-endian, no prefetch if more than this many blocks in single request
	uint16_t MinimumPrefetch;                      // big-endian, mandatory to prefetch this many sectors ??or is it blocks??
	uint16_t MaximumPrefetch;                      // big-endian, can get up to this many, but may abort beforehand due to ???
	uint16_t MaximumPrefetchCeiling;               // big-endian, drive truncates MaximumPrefetch to this value
	uint8_t Reserved2 : 5;
	uint8_t DisableReadAhead : 1;
	uint8_t LogicalBlockCacheSegmentSize : 1;      // not used by ST34501W today
	uint8_t ForceSequentialWrite : 1;              // if FALSE, target can reorder media writes for command completion speed
	uint8_t NumberOfCacheSegments;
	uint16_t CacheSegmentSize;
	uint8_t Reserved3;
	uint8_t NonCacheSegmentSize[3];                // bytes to reserve for SCSI buffering
} lsi_mode_caching_page_t; // page 8 from ScsiModeSense

typedef struct _lsi_mode_sense_caching_page {
	lsi_mode10_param_list_t Parms;
	lsi_mode_caching_page_t Caching;
} lsi_mode_sense_caching_page_t;

typedef struct _lsi_mode_sense10 {
	uint8_t OperationCode;    // 0x5A - SCSIOP_MODE_SENSE10
	uint8_t Reserved1 : 3;
	uint8_t Dbd : 1;
	uint8_t Reserved2 : 1;
	uint8_t LogicalUnitNumber : 3;
	uint8_t PageCode : 6;
	uint8_t Pc : 2;
	uint8_t Reserved3[4];
	uint8_t AllocationLength[2];
	uint8_t Control;
} lsi_mode_sense10_t;

/* Mode Select */
typedef struct _lsi_mode_select10 {
	uint8_t OperationCode;    // 0x55 - SCSIOP_MODE_SELECT10
	uint8_t SPBit : 1;
	uint8_t Reserved1 : 3;
	uint8_t PFBit : 1;
	uint8_t LogicalUnitNumber : 3;
	uint8_t Reserved2[5];
	uint8_t ParameterListLength[2];
	uint8_t Control;
} lsi_mode_select10_t;

/* Start Stop Unit */
typedef struct _lsi_start_stop {
	uint8_t OperationCode;    // 0x1B - SCSIOP_START_STOP_UNIT
	uint8_t Immediate: 1;
	uint8_t Reserved1 : 4;
	uint8_t LogicalUnitNumber : 3;
	uint8_t Reserved2[2];
	uint8_t Start : 1;
	uint8_t LoadEject : 1;
	uint8_t Reserved3 : 6;
	uint8_t Control;
} lsi_start_stop_t;

/**
 * define the SCSI request sense structure
 **/
typedef struct  _sense_data {
    uint32_t		responseCode    : 7;
    uint32_t		valid           : 1;
    uint32_t		segmentNumber   : 8;
    uint32_t		senseKey        : 4;
    uint32_t			            : 1;
    uint32_t		ili             : 1;
    uint32_t		eom             : 1;
    uint32_t		filemark        : 1;
	uint32_t						: 8;
	uint8_t			information[3];            
    uint8_t			additionalSenseLength;
    uint8_t			commandSepcificInfo[4];
    uint8_t			asc;
    uint8_t			ascq;
    uint8_t			fruCode;
    uint8_t			sksv;
    uint8_t			fieldPointer[2];
} sense_data;

//
// Macro definitions
//

#define BIG_ENDIAN_ULONG(Ulong) \
		((((uint8_t *)&Ulong)[0] << 24) |\
		(((uint8_t *)&Ulong)[1] << 16) |\
		(((uint8_t *)&Ulong)[2] << 8) |\
		((uint8_t *)&Ulong)[3])

#define BIG_ENDIAN_ULONGLONG(bit_val_32) \
	((((uint64_t)((uint8_t *)&bit_val_32)[0] << 56))| \
	(((uint64_t)((uint8_t *)&bit_val_32)[1] << 48)) | \
	(((uint64_t)((uint8_t *)&bit_val_32)[2] << 40)) | \
	(((uint64_t)((uint8_t *)&bit_val_32)[3] << 32)) | \
	(((uint64_t)((uint8_t *)&bit_val_32)[4] << 24)) | \
	(((uint64_t)((uint8_t *)&bit_val_32)[5] << 16)) | \
	(((uint64_t)((uint8_t *)&bit_val_32)[6] << 8)) | \
	((uint64_t)((uint8_t *)&bit_val_32)[7]))

#define GET_OPCODE_CDB(cdb)	(cdb[0])

#define GET_START_BLOCK(cdb)		((cdb[5] | (cdb[4] << 8) | (cdb[3] << 16) | (cdb[2] << 24)) & 0xffffffff)
	
#define GET_NUMBER_OF_BLOCKS(cdb)	((uint32_t)cdb[8] | ((uint32_t)cdb[7] << 8))
	
#define GET_START_BLOCK16(cdb)		(((uint64_t)(cdb[5] | (cdb[4] << 8) | (cdb[3] << 16) | (cdb[2] << 24)) << 32) |	\
											(uint32_t)(cdb[9] | (cdb[8] << 8) | (cdb[7] << 16) | (cdb[6] << 24)))

#define GET_NUMBER_OF_BLOCKS16(cdb) ((cdb[13] | (cdb[12] << 8) | (cdb[11] << 16) | (cdb[10] << 24)) & 0xffffffff)

#define GET_START_BLOCK12(cdb)				\
	(uint64_t)(					\
		(uint32_t)(cdb[5])		|	\
		(uint32_t)(cdb[4] << 8)		|	\
		(uint32_t)(cdb[3] << 16)	|	\
		(uint32_t)(cdb[2] << 24)		\
	)
#define GET_NUMBER_OF_BLOCKS12(cdb)				\
	(uint32_t)(						\
		(uint32_t)((uint32_t)cdb[6] << 24)	|	\
		(uint32_t)((uint32_t)cdb[7] << 16)	|	\
		(uint32_t)((uint32_t)cdb[8] << 8)	|	\
		(uint32_t)cdb[9]				\
	)

#define GET_START_BLOCK6(cdb)			\
	(uint64_t)(				\
		(uint32_t)(cdb[3])	|	\
		(uint32_t)(cdb[2] << 8)		\
	)
#define GET_NUMBER_OF_BLOCKS6(cdb)	(uint32_t)(cdb[4])

#define SET_START_BLOCK6(cdb, blk_num) 			\
	cdb[3]	= (uint8_t)(blk_num & 0xff);		\
	cdb[2]	= (uint8_t)((blk_num >> 8) & 0xff);	\

#define SET_BLOCK_COUNT6(cdb, blk_cnt) 			\
	cdb[4]	= (uint8_t)(blk_cnt & 0xff);		\

#define SET_START_BLOCK12(cdb, blk_num) 			\
	cdb[5]	= (uint8_t)(blk_num & 0xff);			\
	cdb[4]	= (uint8_t)((blk_num >> 8) & 0xff);		\
	cdb[3]	= (uint8_t)((blk_num >> 16) & 0xff);	\
	cdb[2]	= (uint8_t)((blk_num >> 24) & 0xff)

#define SET_BLOCK_COUNT12(cdb, blk_num) 			\
	cdb[9]	= (uint8_t)(blk_num & 0xff);			\
	cdb[8]	= (uint8_t)((blk_num >> 8) & 0xff);		\
	cdb[7]	= (uint8_t)((blk_num >> 16) & 0xff);	\
	cdb[6]	= (uint8_t)((blk_num >> 24) & 0xff)

#define SET_START_BLOCK(cdb, blk_num) \
	cdb[5]	= (uint8_t)(blk_num & 0xff);				\
	cdb[4]	= (uint8_t)((blk_num >> 8) & 0xff);			\
	cdb[3]	= (uint8_t)((blk_num >> 16) & 0xff);		\
	cdb[2]	= (uint8_t)((blk_num >> 24) & 0xff)

#define SET_BLOCK_COUNT(cdb, blk_cnt) 					\
	cdb[8]	= (uint8_t)(blk_cnt & 0xff);				\
	cdb[7]	= (uint8_t)((blk_cnt >> 8) & 0xff)

#define SET_START_BLOCK16(cdb, blk_num)					\
	cdb[9]	= (uint8_t)(blk_num & 0xff);				\
	cdb[8]	= (uint8_t)((blk_num >> 8) & 0xff);			\
	cdb[7]	= (uint8_t)((blk_num >> 16) & 0xff);		\
	cdb[6]	= (uint8_t)((blk_num >> 24) & 0xff);		\
	cdb[5]	= (uint8_t)((blk_num >> 32) & 0xff);		\
	cdb[4]	= (uint8_t)((blk_num >> 40) & 0xff);		\
	cdb[3]	= (uint8_t)((blk_num >> 48) & 0xff);		\
	cdb[2]	= (uint8_t)((blk_num >> 56) & 0xff)

#define SET_BLOCK_COUNT16(cdb, blk_cnt)					\
	cdb[13]	= (uint8_t)(blk_cnt & 0xff);				\
	cdb[12]	= (uint8_t)((blk_cnt >> 8) & 0xff);			\
	cdb[11]	= (uint8_t)((blk_cnt >> 16) & 0xff);		\
	cdb[10]	= (uint8_t)((blk_cnt >> 24) & 0xff)

#define	IS_READ(cdb)	\
	(((cdb[0] == LSI_SCSIOP_READ) || (cdb[0] == LSI_SCSIOP_READ16) || (cdb[0] == LSI_SCSIOP_READ12) || (cdb[0] == LSI_SCSIOP_READ6)) ? LSI_TRUE:LSI_FALSE)

#define	IS_WRITE(cdb)	\
	(((cdb[0] == LSI_SCSIOP_WRITE) || (cdb[0] == LSI_SCSIOP_WRITE16) || (cdb[0] == LSI_SCSIOP_WRITE_VERIFY || (cdb[0] == LSI_SCSIOP_WRITE12) || (cdb[0] == LSI_SCSIOP_WRITE6))) ? LSI_TRUE:LSI_FALSE)

#define	IS_RW(cdb)	\
	(((IS_READ(cdb) == LSI_TRUE) || (IS_WRITE(cdb) == LSI_TRUE)) ? LSI_TRUE:LSI_FALSE)

#define	IS_READ16(cdb)	\
	((cdb[0] == LSI_SCSIOP_READ16) ? LSI_TRUE:LSI_FALSE)

#define	IS_WRITE16(cdb)	\
	((cdb[0] == LSI_SCSIOP_WRITE16) ? LSI_TRUE:LSI_FALSE)

#define	IS_RW16(cdb)	\
	(((IS_READ16(cdb) == LSI_TRUE) || (IS_WRITE16(cdb) == LSI_TRUE)) ? LSI_TRUE:LSI_FALSE)

#define IS_START(cdb)   (cdb[4])

#endif /* LSI_MEGA_SWR_SCSI_HAL_H */

/* vim: set ts=4 sw=4 : */
