/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "SensorSharing"
 * 	found in "SensorSharing.asn"
 * 	`asn1c -gen-PER`
 */

#ifndef	_EquipmentType_H_
#define	_EquipmentType_H_


#include <asn_application.h>

/* Including external dependencies */
#include <NativeEnumerated.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum EquipmentType {
	EquipmentType_unknown	= 0,
	EquipmentType_rsu	= 1,
	EquipmentType_obu	= 2,
	EquipmentType_vru	= 3
	/*
	 * Enumeration is extensible
	 */
} e_EquipmentType;

/* EquipmentType */
typedef long	 EquipmentType_t;

/* Implementation */
extern asn_per_constraints_t asn_PER_type_EquipmentType_constr_1;
extern asn_TYPE_descriptor_t asn_DEF_EquipmentType;
extern const asn_INTEGER_specifics_t asn_SPC_EquipmentType_specs_1;
asn_struct_free_f EquipmentType_free;
asn_struct_print_f EquipmentType_print;
asn_constr_check_f EquipmentType_constraint;
ber_type_decoder_f EquipmentType_decode_ber;
der_type_encoder_f EquipmentType_encode_der;
xer_type_decoder_f EquipmentType_decode_xer;
xer_type_encoder_f EquipmentType_encode_xer;
oer_type_decoder_f EquipmentType_decode_oer;
oer_type_encoder_f EquipmentType_encode_oer;
per_type_decoder_f EquipmentType_decode_uper;
per_type_encoder_f EquipmentType_encode_uper;

#ifdef __cplusplus
}
#endif

#endif	/* _EquipmentType_H_ */
#include <asn_internal.h>
