/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "SensorSharing"
 * 	found in "SensorSharing.asn"
 * 	`asn1c -gen-PER`
 */

#ifndef	_ObstacleType_H_
#define	_ObstacleType_H_


#include <asn_application.h>

/* Including external dependencies */
#include <NativeEnumerated.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum ObstacleType {
	ObstacleType_unknown	= 0,
	ObstacleType_rockfall	= 1,
	ObstacleType_landslide	= 2,
	ObstacleType_animal_intrusion	= 3,
	ObstacleType_liquid_spill	= 4,
	ObstacleType_goods_scattered	= 5,
	ObstacleType_trafficcone	= 6,
	ObstacleType_safety_triangle	= 7,
	ObstacleType_traffic_roadblock	= 8,
	ObstacleType_inspection_shaft_without_cover	= 9,
	ObstacleType_unknown_fragments	= 10,
	ObstacleType_unknown_hard_object	= 11,
	ObstacleType_unknown_soft_object	= 12
	/*
	 * Enumeration is extensible
	 */
} e_ObstacleType;

/* ObstacleType */
typedef long	 ObstacleType_t;

/* Implementation */
extern asn_per_constraints_t asn_PER_type_ObstacleType_constr_1;
extern asn_TYPE_descriptor_t asn_DEF_ObstacleType;
extern const asn_INTEGER_specifics_t asn_SPC_ObstacleType_specs_1;
asn_struct_free_f ObstacleType_free;
asn_struct_print_f ObstacleType_print;
asn_constr_check_f ObstacleType_constraint;
ber_type_decoder_f ObstacleType_decode_ber;
der_type_encoder_f ObstacleType_encode_der;
xer_type_decoder_f ObstacleType_decode_xer;
xer_type_encoder_f ObstacleType_encode_xer;
oer_type_decoder_f ObstacleType_decode_oer;
oer_type_encoder_f ObstacleType_encode_oer;
per_type_decoder_f ObstacleType_decode_uper;
per_type_encoder_f ObstacleType_encode_uper;

#ifdef __cplusplus
}
#endif

#endif	/* _ObstacleType_H_ */
#include <asn_internal.h>