/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "CER"
 * 	found in "CER.asn"
 * 	`asn1c -gen-PER`
 */

#ifndef	_ValidityRestriction_H_
#define	_ValidityRestriction_H_


#include <asn_application.h>

/* Including external dependencies */
#include "ValidityPeriod.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct GeographicRegion;

/* ValidityRestriction */
typedef struct ValidityRestriction {
	ValidityPeriod_t	 validityPeriod;
	struct GeographicRegion	*region	/* OPTIONAL */;
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} ValidityRestriction_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_ValidityRestriction;
extern asn_SEQUENCE_specifics_t asn_SPC_ValidityRestriction_specs_1;
extern asn_TYPE_member_t asn_MBR_ValidityRestriction_1[2];

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "GeographicRegion.h"

#endif	/* _ValidityRestriction_H_ */
#include <asn_internal.h>
