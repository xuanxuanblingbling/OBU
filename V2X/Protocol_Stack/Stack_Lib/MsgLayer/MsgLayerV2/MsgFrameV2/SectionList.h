/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "Map"
 * 	found in "Map.asn"
 * 	`asn1c -gen-PER`
 */

#ifndef	_SectionList_H_
#define	_SectionList_H_


#include <asn_application.h>

/* Including external dependencies */
#include <asn_SEQUENCE_OF.h>
#include <constr_SEQUENCE_OF.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct Section;

/* SectionList */
typedef struct SectionList {
	A_SEQUENCE_OF(struct Section) list;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} SectionList_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_SectionList;
extern asn_SET_OF_specifics_t asn_SPC_SectionList_specs_1;
extern asn_TYPE_member_t asn_MBR_SectionList_1[1];
extern asn_per_constraints_t asn_PER_type_SectionList_constr_1;

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "Section.h"

#endif	/* _SectionList_H_ */
#include <asn_internal.h>
