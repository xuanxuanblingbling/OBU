/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "DefPosition"
 * 	found in "DefPosition.asn"
 * 	`asn1c -gen-PER`
 */

#include "PositionConfidenceSet.h"

asn_TYPE_member_t asn_MBR_PositionConfidenceSet_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct PositionConfidenceSet, pos),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_PositionConfidence,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"pos"
		},
	{ ATF_POINTER, 1, offsetof(struct PositionConfidenceSet, elevation),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_ElevationConfidence,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"elevation"
		},
};
static const int asn_MAP_PositionConfidenceSet_oms_1[] = { 1 };
static const ber_tlv_tag_t asn_DEF_PositionConfidenceSet_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_PositionConfidenceSet_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* pos */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 } /* elevation */
};
asn_SEQUENCE_specifics_t asn_SPC_PositionConfidenceSet_specs_1 = {
	sizeof(struct PositionConfidenceSet),
	offsetof(struct PositionConfidenceSet, _asn_ctx),
	asn_MAP_PositionConfidenceSet_tag2el_1,
	2,	/* Count of tags in the map */
	asn_MAP_PositionConfidenceSet_oms_1,	/* Optional members */
	1, 0,	/* Root/Additions */
	-1,	/* First extension addition */
};
asn_TYPE_descriptor_t asn_DEF_PositionConfidenceSet = {
	"PositionConfidenceSet",
	"PositionConfidenceSet",
	&asn_OP_SEQUENCE,
	asn_DEF_PositionConfidenceSet_tags_1,
	sizeof(asn_DEF_PositionConfidenceSet_tags_1)
		/sizeof(asn_DEF_PositionConfidenceSet_tags_1[0]), /* 1 */
	asn_DEF_PositionConfidenceSet_tags_1,	/* Same as above */
	sizeof(asn_DEF_PositionConfidenceSet_tags_1)
		/sizeof(asn_DEF_PositionConfidenceSet_tags_1[0]), /* 1 */
	{ 0, 0, SEQUENCE_constraint },
	asn_MBR_PositionConfidenceSet_1,
	2,	/* Elements count */
	&asn_SPC_PositionConfidenceSet_specs_1	/* Additional specs */
};

