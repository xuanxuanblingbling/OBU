/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "Map"
 * 	found in "Map.asn"
 * 	`asn1c -gen-PER`
 */

#ifndef	_RoadPoint_H_
#define	_RoadPoint_H_


#include <asn_application.h>

/* Including external dependencies */
#include "PositionOffsetLLV.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* RoadPoint */
typedef struct RoadPoint {
	PositionOffsetLLV_t	 posOffset;
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} RoadPoint_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_RoadPoint;
extern asn_SEQUENCE_specifics_t asn_SPC_RoadPoint_specs_1;
extern asn_TYPE_member_t asn_MBR_RoadPoint_1[1];

#ifdef __cplusplus
}
#endif

#endif	/* _RoadPoint_H_ */
#include <asn_internal.h>
