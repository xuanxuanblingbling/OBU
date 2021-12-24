/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "PSM"
 * 	found in "PSM.asn"
 * 	`asn1c -gen-PER`
 */

#ifndef	_PersonalCrossing_H_
#define	_PersonalCrossing_H_


#include <asn_application.h>

/* Including external dependencies */
#include <NativeEnumerated.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum PersonalCrossing {
	PersonalCrossing_unavailable	= 0,
	PersonalCrossing_request	= 1,
	PersonalCrossing_crossing	= 2,
	PersonalCrossing_finish	= 3
	/*
	 * Enumeration is extensible
	 */
} e_PersonalCrossing;

/* PersonalCrossing */
typedef long	 PersonalCrossing_t;

/* Implementation */
extern asn_per_constraints_t asn_PER_type_PersonalCrossing_constr_1;
extern asn_TYPE_descriptor_t asn_DEF_PersonalCrossing;
extern const asn_INTEGER_specifics_t asn_SPC_PersonalCrossing_specs_1;
asn_struct_free_f PersonalCrossing_free;
asn_struct_print_f PersonalCrossing_print;
asn_constr_check_f PersonalCrossing_constraint;
ber_type_decoder_f PersonalCrossing_decode_ber;
der_type_encoder_f PersonalCrossing_encode_der;
xer_type_decoder_f PersonalCrossing_decode_xer;
xer_type_encoder_f PersonalCrossing_encode_xer;
oer_type_decoder_f PersonalCrossing_decode_oer;
oer_type_encoder_f PersonalCrossing_encode_oer;
per_type_decoder_f PersonalCrossing_decode_uper;
per_type_encoder_f PersonalCrossing_encode_uper;

#ifdef __cplusplus
}
#endif

#endif	/* _PersonalCrossing_H_ */
#include <asn_internal.h>
