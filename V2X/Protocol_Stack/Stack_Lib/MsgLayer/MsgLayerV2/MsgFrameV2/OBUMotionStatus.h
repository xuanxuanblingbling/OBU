/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "VPM"
 * 	found in "VPM.asn"
 * 	`asn1c -gen-PER`
 */

#ifndef	_OBUMotionStatus_H_
#define	_OBUMotionStatus_H_


#include <asn_application.h>

/* Including external dependencies */
#include "Heading.h"
#include "Speed.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct Position3D;

/* OBUMotionStatus */
typedef struct OBUMotionStatus {
	struct Position3D	*pos	/* OPTIONAL */;
	Heading_t	*heading	/* OPTIONAL */;
	Speed_t	*speed	/* OPTIONAL */;
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} OBUMotionStatus_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_OBUMotionStatus;
extern asn_SEQUENCE_specifics_t asn_SPC_OBUMotionStatus_specs_1;
extern asn_TYPE_member_t asn_MBR_OBUMotionStatus_1[3];

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "Position3D.h"

#endif	/* _OBUMotionStatus_H_ */
#include <asn_internal.h>