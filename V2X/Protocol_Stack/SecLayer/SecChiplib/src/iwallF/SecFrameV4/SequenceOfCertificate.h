/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "CER"
 * 	found in "CER.asn"
 * 	`asn1c -gen-PER`
 */

#ifndef	_SequenceOfCertificate_H_
#define	_SequenceOfCertificate_H_


#include <asn_application.h>

/* Including external dependencies */
#include <asn_SEQUENCE_OF.h>
#include <constr_SEQUENCE_OF.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct Certificate;

/* SequenceOfCertificate */
typedef struct SequenceOfCertificate {
	A_SEQUENCE_OF(struct Certificate) list;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} SequenceOfCertificate_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_SequenceOfCertificate;
extern asn_SET_OF_specifics_t asn_SPC_SequenceOfCertificate_specs_1;
extern asn_TYPE_member_t asn_MBR_SequenceOfCertificate_1[1];

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "Certificate.h"

#endif	/* _SequenceOfCertificate_H_ */
#include <asn_internal.h>
