/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "VPM"
 * 	found in "VPM.asn"
 * 	`asn1c -gen-PER`
 */

#ifndef	_SetTollDataRs_H_
#define	_SetTollDataRs_H_


#include <asn_application.h>

/* Including external dependencies */
#include <OCTET_STRING.h>
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct AccountInfo;
struct TransCredential;

/* SetTollDataRs */
typedef struct SetTollDataRs {
	OCTET_STRING_t	*tacInfo	/* OPTIONAL */;
	OCTET_STRING_t	*authenticator	/* OPTIONAL */;
	struct AccountInfo	*accountInfo	/* OPTIONAL */;
	struct TransCredential	*transCredential	/* OPTIONAL */;
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} SetTollDataRs_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_SetTollDataRs;
extern asn_SEQUENCE_specifics_t asn_SPC_SetTollDataRs_specs_1;
extern asn_TYPE_member_t asn_MBR_SetTollDataRs_1[4];

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "AccountInfo.h"
#include "TransCredential.h"

#endif	/* _SetTollDataRs_H_ */
#include <asn_internal.h>
