/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "RSI"
 * 	found in "RSI.asn"
 * 	`asn1c -gen-PER`
 */

#ifndef	_ReferencePath_H_
#define	_ReferencePath_H_


#include <asn_application.h>

/* Including external dependencies */
#include "PathPointList.h"
#include "Radius.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ReferencePath */
typedef struct ReferencePath {
	PathPointList_t	 activePath;
	Radius_t	 pathRadius;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} ReferencePath_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_ReferencePath;
extern asn_SEQUENCE_specifics_t asn_SPC_ReferencePath_specs_1;
extern asn_TYPE_member_t asn_MBR_ReferencePath_1[2];

#ifdef __cplusplus
}
#endif

#endif	/* _ReferencePath_H_ */
#include <asn_internal.h>
