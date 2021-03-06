/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "SecMsg"
 *     found in "SecMsg.asn"
 *     `asn1c -gen-PER`
 */

#ifndef    _SymmetricCipherText_H_
#define    _SymmetricCipherText_H_


#include <asn_application.h>

/* Including external dependencies */
#include "CipherText.h"
#include "SM4CipherText.h"
#include "AesCcmCipherText.h"
#include <constr_CHOICE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum SymmetricCipherText_PR {
    SymmetricCipherText_PR_NOTHING,    /* No components present */
    SymmetricCipherText_PR_sm4Ecb,
    SymmetricCipherText_PR_sm4Cbc,
    SymmetricCipherText_PR_sm4Cfb,
    SymmetricCipherText_PR_sm4Ofb,
    SymmetricCipherText_PR_aesCcm
} SymmetricCipherText_PR;

/* SymmetricCipherText */
typedef struct SymmetricCipherText {
    SymmetricCipherText_PR present;
    union SymmetricCipherText_u {
        CipherText_t     sm4Ecb;
        SM4CipherText_t     sm4Cbc;
        SM4CipherText_t     sm4Cfb;
        SM4CipherText_t     sm4Ofb;
        AesCcmCipherText_t     aesCcm;
    } choice;

    /* Context for parsing across buffer boundaries */
    asn_struct_ctx_t _asn_ctx;
} SymmetricCipherText_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_SymmetricCipherText;
extern asn_CHOICE_specifics_t asn_SPC_SymmetricCipherText_specs_1;
extern asn_TYPE_member_t asn_MBR_SymmetricCipherText_1[5];
extern asn_per_constraints_t asn_PER_type_SymmetricCipherText_constr_1;

#ifdef __cplusplus
}
#endif

#endif    /* _SymmetricCipherText_H_ */
#include <asn_internal.h>
