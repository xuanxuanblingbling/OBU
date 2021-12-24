/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "SecMsg"
 *     found in "SecMsg.asn"
 *     `asn1c -gen-PER`
 */

#ifndef    _CipherText_H_
#define    _CipherText_H_


#include <asn_application.h>

/* Including external dependencies */
#include "Opaque.h"

#ifdef __cplusplus
extern "C" {
#endif

/* CipherText */
typedef Opaque_t     CipherText_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_CipherText;
asn_struct_free_f CipherText_free;
asn_struct_print_f CipherText_print;
asn_constr_check_f CipherText_constraint;
ber_type_decoder_f CipherText_decode_ber;
der_type_encoder_f CipherText_encode_der;
xer_type_decoder_f CipherText_decode_xer;
xer_type_encoder_f CipherText_encode_xer;
oer_type_decoder_f CipherText_decode_oer;
oer_type_encoder_f CipherText_encode_oer;
per_type_decoder_f CipherText_decode_uper;
per_type_encoder_f CipherText_encode_uper;

#ifdef __cplusplus
}
#endif

#endif    /* _CipherText_H_ */
#include <asn_internal.h>
