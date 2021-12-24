/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "DefPosition"
 * 	found in "DefPosition.asn"
 * 	`asn1c -gen-PER`
 */

#include "PositionalAccuracy.h"

asn_TYPE_member_t asn_MBR_PositionalAccuracy_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct PositionalAccuracy, semiMajor),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_SemiMajorAxisAccuracy,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"semiMajor"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct PositionalAccuracy, semiMinor),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_SemiMinorAxisAccuracy,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"semiMinor"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct PositionalAccuracy, orientation),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_SemiMajorAxisOrientation,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"orientation"
		},
};
static const ber_tlv_tag_t asn_DEF_PositionalAccuracy_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_PositionalAccuracy_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* semiMajor */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* semiMinor */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 } /* orientation */
};
asn_SEQUENCE_specifics_t asn_SPC_PositionalAccuracy_specs_1 = {
	sizeof(struct PositionalAccuracy),
	offsetof(struct PositionalAccuracy, _asn_ctx),
	asn_MAP_PositionalAccuracy_tag2el_1,
	3,	/* Count of tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	-1,	/* First extension addition */
};
asn_TYPE_descriptor_t asn_DEF_PositionalAccuracy = {
	"PositionalAccuracy",
	"PositionalAccuracy",
	&asn_OP_SEQUENCE,
	asn_DEF_PositionalAccuracy_tags_1,
	sizeof(asn_DEF_PositionalAccuracy_tags_1)
		/sizeof(asn_DEF_PositionalAccuracy_tags_1[0]), /* 1 */
	asn_DEF_PositionalAccuracy_tags_1,	/* Same as above */
	sizeof(asn_DEF_PositionalAccuracy_tags_1)
		/sizeof(asn_DEF_PositionalAccuracy_tags_1[0]), /* 1 */
	{ 0, 0, SEQUENCE_constraint },
	asn_MBR_PositionalAccuracy_1,
	3,	/* Elements count */
	&asn_SPC_PositionalAccuracy_specs_1	/* Additional specs */
};
