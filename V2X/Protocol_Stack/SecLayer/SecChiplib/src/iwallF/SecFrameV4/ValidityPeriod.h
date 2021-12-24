/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "CER"
 * 	found in "CER.asn"
 * 	`asn1c -gen-PER`
 */

#ifndef	_ValidityPeriod_H_
#define	_ValidityPeriod_H_


#include <asn_application.h>

/* Including external dependencies */
#include "Time32.h"
#include "TimeStartAndEnd.h"
#include <constr_CHOICE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum ValidityPeriod_PR {
	ValidityPeriod_PR_NOTHING,	/* No components present */
	ValidityPeriod_PR_timeEnd,
	ValidityPeriod_PR_timeStartAndEnd
} ValidityPeriod_PR;

/* ValidityPeriod */
typedef struct ValidityPeriod {
	ValidityPeriod_PR present;
	union ValidityPeriod_u {
		Time32_t	 timeEnd;
		TimeStartAndEnd_t	 timeStartAndEnd;
	} choice;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} ValidityPeriod_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_ValidityPeriod;
extern asn_CHOICE_specifics_t asn_SPC_ValidityPeriod_specs_1;
extern asn_TYPE_member_t asn_MBR_ValidityPeriod_1[2];
extern asn_per_constraints_t asn_PER_type_ValidityPeriod_constr_1;

#ifdef __cplusplus
}
#endif

#endif	/* _ValidityPeriod_H_ */
#include <asn_internal.h>
