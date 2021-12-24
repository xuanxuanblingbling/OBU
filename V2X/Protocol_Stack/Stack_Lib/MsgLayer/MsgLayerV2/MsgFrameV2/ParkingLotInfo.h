/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "PAM"
 * 	found in "PAM.asn"
 * 	`asn1c -gen-PER`
 */

#ifndef	_ParkingLotInfo_H_
#define	_ParkingLotInfo_H_


#include <asn_application.h>

/* Including external dependencies */
#include <NativeInteger.h>
#include "DescriptiveName.h"
#include "AVPType.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ParkingLotInfo */
typedef struct ParkingLotInfo {
	long	*id	/* OPTIONAL */;
	DescriptiveName_t	*name	/* OPTIONAL */;
	long	*number	/* OPTIONAL */;
	long	*buildingLayerNum	/* OPTIONAL */;
	AVPType_t	*avpType	/* OPTIONAL */;
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} ParkingLotInfo_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_ParkingLotInfo;
extern asn_SEQUENCE_specifics_t asn_SPC_ParkingLotInfo_specs_1;
extern asn_TYPE_member_t asn_MBR_ParkingLotInfo_1[5];

#ifdef __cplusplus
}
#endif

#endif	/* _ParkingLotInfo_H_ */
#include <asn_internal.h>
