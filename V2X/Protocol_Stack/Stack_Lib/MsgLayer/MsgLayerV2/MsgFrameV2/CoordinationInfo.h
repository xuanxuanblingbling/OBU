/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "RSC"
 * 	found in "RSC.asn"
 * 	`asn1c -gen-PER`
 */

#ifndef	_CoordinationInfo_H_
#define	_CoordinationInfo_H_


#include <asn_application.h>

/* Including external dependencies */
#include <BIT_STRING.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum CoordinationInfo {
	CoordinationInfo_cooperativeLaneChanging	= 0,
	CoordinationInfo_cooperativeVehMerging	= 1,
	CoordinationInfo_laneChangingAtIntersection	= 2,
	CoordinationInfo_no_signalIntersectionPassing	= 3,
	CoordinationInfo_dynamicLaneManagement	= 4,
	CoordinationInfo_laneReservation	= 5,
	CoordinationInfo_laneRestriction	= 6,
	CoordinationInfo_signalPriority	= 7
} e_CoordinationInfo;

/* CoordinationInfo */
typedef BIT_STRING_t	 CoordinationInfo_t;

/* Implementation */
extern asn_per_constraints_t asn_PER_type_CoordinationInfo_constr_1;
extern asn_TYPE_descriptor_t asn_DEF_CoordinationInfo;
asn_struct_free_f CoordinationInfo_free;
asn_struct_print_f CoordinationInfo_print;
asn_constr_check_f CoordinationInfo_constraint;
ber_type_decoder_f CoordinationInfo_decode_ber;
der_type_encoder_f CoordinationInfo_encode_der;
xer_type_decoder_f CoordinationInfo_decode_xer;
xer_type_encoder_f CoordinationInfo_encode_xer;
oer_type_decoder_f CoordinationInfo_decode_oer;
oer_type_encoder_f CoordinationInfo_encode_oer;
per_type_decoder_f CoordinationInfo_decode_uper;
per_type_encoder_f CoordinationInfo_encode_uper;

#ifdef __cplusplus
}
#endif

#endif	/* _CoordinationInfo_H_ */
#include <asn_internal.h>
