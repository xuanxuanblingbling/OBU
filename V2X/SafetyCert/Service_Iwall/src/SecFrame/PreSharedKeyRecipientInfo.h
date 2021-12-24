/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "SecMsg"
 *     found in "SecMsg.asn"
 *     `asn1c -gen-PER`
 */

#ifndef    _PreSharedKeyRecipientInfo_H_
#define    _PreSharedKeyRecipientInfo_H_


#include <asn_application.h>

/* Including external dependencies */
#include "HashAlgorithm.h"
#include "HashedId8.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* PreSharedKeyRecipientInfo */
typedef struct PreSharedKeyRecipientInfo {
    HashAlgorithm_t     hashAlg;
    HashedId8_t     symKeyHash;

    /* Context for parsing across buffer boundaries */
    asn_struct_ctx_t _asn_ctx;
} PreSharedKeyRecipientInfo_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_PreSharedKeyRecipientInfo;
extern asn_SEQUENCE_specifics_t asn_SPC_PreSharedKeyRecipientInfo_specs_1;
extern asn_TYPE_member_t asn_MBR_PreSharedKeyRecipientInfo_1[2];

#ifdef __cplusplus
}
#endif

#endif    /* _PreSharedKeyRecipientInfo_H_ */
#include <asn_internal.h>