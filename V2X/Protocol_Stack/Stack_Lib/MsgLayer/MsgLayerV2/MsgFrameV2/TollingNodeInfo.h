/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "VPM"
 * 	found in "VPM.asn"
 * 	`asn1c -gen-PER`
 */

#ifndef	_TollingNodeInfo_H_
#define	_TollingNodeInfo_H_


#include <asn_application.h>

/* Including external dependencies */
#include "StationOrGantryId.h"
#include "TollingNodeType.h"
#include "TollingDirection.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct Position3D;

/* TollingNodeInfo */
typedef struct TollingNodeInfo {
	StationOrGantryId_t	*id	/* OPTIONAL */;
	struct Position3D	*pos	/* OPTIONAL */;
	TollingNodeType_t	*tollingNodeType	/* OPTIONAL */;
	TollingDirection_t	*tollingDirection	/* OPTIONAL */;
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} TollingNodeInfo_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_TollingNodeInfo;
extern asn_SEQUENCE_specifics_t asn_SPC_TollingNodeInfo_specs_1;
extern asn_TYPE_member_t asn_MBR_TollingNodeInfo_1[4];

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "Position3D.h"

#endif	/* _TollingNodeInfo_H_ */
#include <asn_internal.h>
