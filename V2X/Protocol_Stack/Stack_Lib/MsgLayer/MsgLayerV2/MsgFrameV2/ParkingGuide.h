/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "PAM"
 * 	found in "PAM.asn"
 * 	`asn1c -gen-PER`
 */

#ifndef	_ParkingGuide_H_
#define	_ParkingGuide_H_


#include <asn_application.h>

/* Including external dependencies */
#include <OCTET_STRING.h>
#include <NativeInteger.h>
#include "PAMNodeID.h"
#include <asn_SEQUENCE_OF.h>
#include <constr_SEQUENCE_OF.h>
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ParkingGuide */
typedef struct ParkingGuide {
	OCTET_STRING_t	 vehId;
	struct drivePath {
		A_SEQUENCE_OF(PAMNodeID_t) list;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} drivePath;
	long	*targetParkingSlot	/* OPTIONAL */;
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} ParkingGuide_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_ParkingGuide;
extern asn_SEQUENCE_specifics_t asn_SPC_ParkingGuide_specs_1;
extern asn_TYPE_member_t asn_MBR_ParkingGuide_1[3];

#ifdef __cplusplus
}
#endif

#endif	/* _ParkingGuide_H_ */
#include <asn_internal.h>
