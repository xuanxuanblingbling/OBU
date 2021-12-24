/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "VPM"
 * 	found in "VPM.asn"
 * 	`asn1c -gen-PER`
 */

#include "ChannelID.h"

/*
 * This type is implemented using NativeEnumerated,
 * so here we adjust the DEF accordingly.
 */
static asn_oer_constraints_t asn_OER_type_ChannelID_constr_1 CC_NOTUSED = {
	{ 0, 0 },
	-1};
asn_per_constraints_t asn_PER_type_ChannelID_constr_1 CC_NOTUSED = {
	{ APC_CONSTRAINED,	 3,  3,  0,  4 }	/* (0..4) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static const asn_INTEGER_enum_map_t asn_MAP_ChannelID_value2enum_1[] = {
	{ 0,	3,	"obu" },
	{ 1,	4,	"esam" },
	{ 2,	3,	"icc" },
	{ 3,	3,	"hmi" },
	{ 4,	6,	"beeper" }
};
static const unsigned int asn_MAP_ChannelID_enum2value_1[] = {
	4,	/* beeper(4) */
	1,	/* esam(1) */
	3,	/* hmi(3) */
	2,	/* icc(2) */
	0	/* obu(0) */
};
const asn_INTEGER_specifics_t asn_SPC_ChannelID_specs_1 = {
	asn_MAP_ChannelID_value2enum_1,	/* "tag" => N; sorted by tag */
	asn_MAP_ChannelID_enum2value_1,	/* N => "tag"; sorted by N */
	5,	/* Number of elements in the maps */
	0,	/* Enumeration is not extensible */
	1,	/* Strict enumeration */
	0,	/* Native long size */
	0
};
static const ber_tlv_tag_t asn_DEF_ChannelID_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (10 << 2))
};
asn_TYPE_descriptor_t asn_DEF_ChannelID = {
	"ChannelID",
	"ChannelID",
	&asn_OP_NativeEnumerated,
	asn_DEF_ChannelID_tags_1,
	sizeof(asn_DEF_ChannelID_tags_1)
		/sizeof(asn_DEF_ChannelID_tags_1[0]), /* 1 */
	asn_DEF_ChannelID_tags_1,	/* Same as above */
	sizeof(asn_DEF_ChannelID_tags_1)
		/sizeof(asn_DEF_ChannelID_tags_1[0]), /* 1 */
	{ &asn_OER_type_ChannelID_constr_1, &asn_PER_type_ChannelID_constr_1, NativeEnumerated_constraint },
	0, 0,	/* Defined elsewhere */
	&asn_SPC_ChannelID_specs_1	/* Additional specs */
};

