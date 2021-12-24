/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "SecMsg"
 * 	found in "SecMsg.asn"
 * 	`asn1c -gen-PER`
 */

#ifndef	_RecipientInfo_H_
#define	_RecipientInfo_H_


#include <asn_application.h>

/* Including external dependencies */
#include "PreSharedKeyRecipientInfo.h"
#include "SymmRecipInfo.h"
#include "PKRecipientInfo.h"
#include <constr_CHOICE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum RecipientInfo_PR {
	RecipientInfo_PR_NOTHING,	/* No components present */
	RecipientInfo_PR_pskRecipientInfo,
	RecipientInfo_PR_symmRecipInfo,
	RecipientInfo_PR_certRecipInfo,
	RecipientInfo_PR_signedDataRecipInfo
} RecipientInfo_PR;

/* RecipientInfo */
typedef struct RecipientInfo {
	RecipientInfo_PR present;
	union RecipientInfo_u {
		PreSharedKeyRecipientInfo_t	 pskRecipientInfo;
		SymmRecipInfo_t	 symmRecipInfo;
		PKRecipientInfo_t	 certRecipInfo;
		PKRecipientInfo_t	 signedDataRecipInfo;
	} choice;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} RecipientInfo_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_RecipientInfo;
extern asn_CHOICE_specifics_t asn_SPC_RecipientInfo_specs_1;
extern asn_TYPE_member_t asn_MBR_RecipientInfo_1[4];
extern asn_per_constraints_t asn_PER_type_RecipientInfo_constr_1;

#ifdef __cplusplus
}
#endif

#endif	/* _RecipientInfo_H_ */
#include <asn_internal.h>
