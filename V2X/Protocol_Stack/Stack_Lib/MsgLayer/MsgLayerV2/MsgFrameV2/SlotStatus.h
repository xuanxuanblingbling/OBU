/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "PAM"
 * 	found in "PAM.asn"
 * 	`asn1c -gen-PER`
 */

#ifndef	_SlotStatus_H_
#define	_SlotStatus_H_


#include <asn_application.h>

/* Including external dependencies */
#include <NativeEnumerated.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum SlotStatus {
	SlotStatus_unknown	= 0,
	SlotStatus_available	= 1,
	SlotStatus_occupied	= 2,
	SlotStatus_reserved	= 3
	/*
	 * Enumeration is extensible
	 */
} e_SlotStatus;

/* SlotStatus */
typedef long	 SlotStatus_t;

/* Implementation */
extern asn_per_constraints_t asn_PER_type_SlotStatus_constr_1;
extern asn_TYPE_descriptor_t asn_DEF_SlotStatus;
extern const asn_INTEGER_specifics_t asn_SPC_SlotStatus_specs_1;
asn_struct_free_f SlotStatus_free;
asn_struct_print_f SlotStatus_print;
asn_constr_check_f SlotStatus_constraint;
ber_type_decoder_f SlotStatus_decode_ber;
der_type_encoder_f SlotStatus_encode_der;
xer_type_decoder_f SlotStatus_decode_xer;
xer_type_encoder_f SlotStatus_encode_xer;
oer_type_decoder_f SlotStatus_decode_oer;
oer_type_encoder_f SlotStatus_encode_oer;
per_type_decoder_f SlotStatus_decode_uper;
per_type_encoder_f SlotStatus_encode_uper;

#ifdef __cplusplus
}
#endif

#endif	/* _SlotStatus_H_ */
#include <asn_internal.h>