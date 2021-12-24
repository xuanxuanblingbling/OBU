/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "PAM"
 * 	found in "PAM.asn"
 * 	`asn1c -gen-PER`
 */

#ifndef	_AVPType_H_
#define	_AVPType_H_


#include <asn_application.h>

/* Including external dependencies */
#include <NativeEnumerated.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum AVPType {
	AVPType_p0	= 0,
	AVPType_p1	= 1,
	AVPType_p2	= 2,
	AVPType_p3	= 3,
	AVPType_p4	= 4,
	AVPType_p5	= 5
	/*
	 * Enumeration is extensible
	 */
} e_AVPType;

/* AVPType */
typedef long	 AVPType_t;

/* Implementation */
extern asn_per_constraints_t asn_PER_type_AVPType_constr_1;
extern asn_TYPE_descriptor_t asn_DEF_AVPType;
extern const asn_INTEGER_specifics_t asn_SPC_AVPType_specs_1;
asn_struct_free_f AVPType_free;
asn_struct_print_f AVPType_print;
asn_constr_check_f AVPType_constraint;
ber_type_decoder_f AVPType_decode_ber;
der_type_encoder_f AVPType_encode_der;
xer_type_decoder_f AVPType_decode_xer;
xer_type_encoder_f AVPType_encode_xer;
oer_type_decoder_f AVPType_decode_oer;
oer_type_encoder_f AVPType_encode_oer;
per_type_decoder_f AVPType_decode_uper;
per_type_encoder_f AVPType_encode_uper;

#ifdef __cplusplus
}
#endif

#endif	/* _AVPType_H_ */
#include <asn_internal.h>
