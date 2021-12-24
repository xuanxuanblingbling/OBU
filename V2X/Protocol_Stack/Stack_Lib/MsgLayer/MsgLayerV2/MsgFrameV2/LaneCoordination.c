/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "RSC"
 * 	found in "RSC.asn"
 * 	`asn1c -gen-PER`
 */

#include "LaneCoordination.h"

asn_TYPE_member_t asn_MBR_LaneCoordination_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct LaneCoordination, targetLane),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_ReferenceLink,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"targetLane"
		},
	{ ATF_POINTER, 7, offsetof(struct LaneCoordination, relatedPath),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_ReferencePath,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"relatedPath"
		},
	{ ATF_POINTER, 6, offsetof(struct LaneCoordination, tBegin),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_DDateTime,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"tBegin"
		},
	{ ATF_POINTER, 5, offsetof(struct LaneCoordination, tEnd),
		(ASN_TAG_CLASS_CONTEXT | (3 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_DDateTime,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"tEnd"
		},
	{ ATF_POINTER, 4, offsetof(struct LaneCoordination, recommendedSpeed),
		(ASN_TAG_CLASS_CONTEXT | (4 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_Speed,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"recommendedSpeed"
		},
	{ ATF_POINTER, 3, offsetof(struct LaneCoordination, recommendedBehavior),
		(ASN_TAG_CLASS_CONTEXT | (5 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_DriveBehavior,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"recommendedBehavior"
		},
	{ ATF_POINTER, 2, offsetof(struct LaneCoordination, info),
		(ASN_TAG_CLASS_CONTEXT | (6 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_CoordinationInfo,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"info"
		},
	{ ATF_POINTER, 1, offsetof(struct LaneCoordination, description),
		(ASN_TAG_CLASS_CONTEXT | (7 << 2)),
		+1,	/* EXPLICIT tag at current level */
		&asn_DEF_Description,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"description"
		},
};
static const int asn_MAP_LaneCoordination_oms_1[] = { 1, 2, 3, 4, 5, 6, 7 };
static const ber_tlv_tag_t asn_DEF_LaneCoordination_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_LaneCoordination_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* targetLane */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* relatedPath */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 }, /* tBegin */
    { (ASN_TAG_CLASS_CONTEXT | (3 << 2)), 3, 0, 0 }, /* tEnd */
    { (ASN_TAG_CLASS_CONTEXT | (4 << 2)), 4, 0, 0 }, /* recommendedSpeed */
    { (ASN_TAG_CLASS_CONTEXT | (5 << 2)), 5, 0, 0 }, /* recommendedBehavior */
    { (ASN_TAG_CLASS_CONTEXT | (6 << 2)), 6, 0, 0 }, /* info */
    { (ASN_TAG_CLASS_CONTEXT | (7 << 2)), 7, 0, 0 } /* description */
};
asn_SEQUENCE_specifics_t asn_SPC_LaneCoordination_specs_1 = {
	sizeof(struct LaneCoordination),
	offsetof(struct LaneCoordination, _asn_ctx),
	asn_MAP_LaneCoordination_tag2el_1,
	8,	/* Count of tags in the map */
	asn_MAP_LaneCoordination_oms_1,	/* Optional members */
	7, 0,	/* Root/Additions */
	8,	/* First extension addition */
};
asn_TYPE_descriptor_t asn_DEF_LaneCoordination = {
	"LaneCoordination",
	"LaneCoordination",
	&asn_OP_SEQUENCE,
	asn_DEF_LaneCoordination_tags_1,
	sizeof(asn_DEF_LaneCoordination_tags_1)
		/sizeof(asn_DEF_LaneCoordination_tags_1[0]), /* 1 */
	asn_DEF_LaneCoordination_tags_1,	/* Same as above */
	sizeof(asn_DEF_LaneCoordination_tags_1)
		/sizeof(asn_DEF_LaneCoordination_tags_1[0]), /* 1 */
	{ 0, 0, SEQUENCE_constraint },
	asn_MBR_LaneCoordination_1,
	8,	/* Elements count */
	&asn_SPC_LaneCoordination_specs_1	/* Additional specs */
};

