/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "VehSafetyExt"
 * 	found in "VehSafetyExt.asn"
 * 	`asn1c -gen-PER`
 */

#include "FullPositionVector.h"

asn_TYPE_member_t asn_MBR_FullPositionVector_1[] = {
	{ ATF_POINTER, 1, offsetof(struct FullPositionVector, utcTime),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_DDateTime,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"utcTime"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct FullPositionVector, pos),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_Position3D,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"pos"
		},
	{ ATF_POINTER, 6, offsetof(struct FullPositionVector, heading),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_Heading,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"heading"
		},
	{ ATF_POINTER, 5, offsetof(struct FullPositionVector, transmission),
		(ASN_TAG_CLASS_CONTEXT | (3 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_TransmissionState,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"transmission"
		},
	{ ATF_POINTER, 4, offsetof(struct FullPositionVector, speed),
		(ASN_TAG_CLASS_CONTEXT | (4 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_Speed,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"speed"
		},
	{ ATF_POINTER, 3, offsetof(struct FullPositionVector, posAccuracy),
		(ASN_TAG_CLASS_CONTEXT | (5 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_PositionConfidenceSet,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"posAccuracy"
		},
	{ ATF_POINTER, 2, offsetof(struct FullPositionVector, timeConfidence),
		(ASN_TAG_CLASS_CONTEXT | (6 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_TimeConfidence,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"timeConfidence"
		},
	{ ATF_POINTER, 1, offsetof(struct FullPositionVector, motionCfd),
		(ASN_TAG_CLASS_CONTEXT | (7 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_MotionConfidenceSet,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"motionCfd"
		},
};
static const int asn_MAP_FullPositionVector_oms_1[] = { 0, 2, 3, 4, 5, 6, 7 };
static const ber_tlv_tag_t asn_DEF_FullPositionVector_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_FullPositionVector_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* utcTime */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* pos */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 }, /* heading */
    { (ASN_TAG_CLASS_CONTEXT | (3 << 2)), 3, 0, 0 }, /* transmission */
    { (ASN_TAG_CLASS_CONTEXT | (4 << 2)), 4, 0, 0 }, /* speed */
    { (ASN_TAG_CLASS_CONTEXT | (5 << 2)), 5, 0, 0 }, /* posAccuracy */
    { (ASN_TAG_CLASS_CONTEXT | (6 << 2)), 6, 0, 0 }, /* timeConfidence */
    { (ASN_TAG_CLASS_CONTEXT | (7 << 2)), 7, 0, 0 } /* motionCfd */
};
asn_SEQUENCE_specifics_t asn_SPC_FullPositionVector_specs_1 = {
	sizeof(struct FullPositionVector),
	offsetof(struct FullPositionVector, _asn_ctx),
	asn_MAP_FullPositionVector_tag2el_1,
	8,	/* Count of tags in the map */
	asn_MAP_FullPositionVector_oms_1,	/* Optional members */
	7, 0,	/* Root/Additions */
	8,	/* First extension addition */
};
asn_TYPE_descriptor_t asn_DEF_FullPositionVector = {
	"FullPositionVector",
	"FullPositionVector",
	&asn_OP_SEQUENCE,
	asn_DEF_FullPositionVector_tags_1,
	sizeof(asn_DEF_FullPositionVector_tags_1)
		/sizeof(asn_DEF_FullPositionVector_tags_1[0]), /* 1 */
	asn_DEF_FullPositionVector_tags_1,	/* Same as above */
	sizeof(asn_DEF_FullPositionVector_tags_1)
		/sizeof(asn_DEF_FullPositionVector_tags_1[0]), /* 1 */
	{ 0, 0, SEQUENCE_constraint },
	asn_MBR_FullPositionVector_1,
	8,	/* Elements count */
	&asn_SPC_FullPositionVector_specs_1	/* Additional specs */
};

