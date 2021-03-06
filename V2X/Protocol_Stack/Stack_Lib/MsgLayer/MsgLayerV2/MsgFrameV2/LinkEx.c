/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "Map"
 * 	found in "Map.asn"
 * 	`asn1c -gen-PER`
 */

#include "LinkEx.h"

asn_TYPE_member_t asn_MBR_LinkEx_1[] = {
	{ ATF_POINTER, 1, offsetof(struct LinkEx, name),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_DescriptiveName,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"name"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct LinkEx, upstreamNodeId),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_NodeReferenceID,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"upstreamNodeId"
		},
	{ ATF_POINTER, 4, offsetof(struct LinkEx, speedLimits),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_SpeedLimitList,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"speedLimits"
		},
	{ ATF_POINTER, 3, offsetof(struct LinkEx, linkWidth),
		(ASN_TAG_CLASS_CONTEXT | (3 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_LaneWidth,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"linkWidth"
		},
	{ ATF_POINTER, 2, offsetof(struct LinkEx, refLine),
		(ASN_TAG_CLASS_CONTEXT | (4 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_PointList,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"refLine"
		},
	{ ATF_POINTER, 1, offsetof(struct LinkEx, movements_ex),
		(ASN_TAG_CLASS_CONTEXT | (5 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_MovementExList,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"movements-ex"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct LinkEx, sections),
		(ASN_TAG_CLASS_CONTEXT | (6 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_SectionList,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"sections"
		},
};
static const int asn_MAP_LinkEx_oms_1[] = { 0, 2, 3, 4, 5 };
static const ber_tlv_tag_t asn_DEF_LinkEx_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_LinkEx_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* name */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* upstreamNodeId */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 }, /* speedLimits */
    { (ASN_TAG_CLASS_CONTEXT | (3 << 2)), 3, 0, 0 }, /* linkWidth */
    { (ASN_TAG_CLASS_CONTEXT | (4 << 2)), 4, 0, 0 }, /* refLine */
    { (ASN_TAG_CLASS_CONTEXT | (5 << 2)), 5, 0, 0 }, /* movements-ex */
    { (ASN_TAG_CLASS_CONTEXT | (6 << 2)), 6, 0, 0 } /* sections */
};
asn_SEQUENCE_specifics_t asn_SPC_LinkEx_specs_1 = {
	sizeof(struct LinkEx),
	offsetof(struct LinkEx, _asn_ctx),
	asn_MAP_LinkEx_tag2el_1,
	7,	/* Count of tags in the map */
	asn_MAP_LinkEx_oms_1,	/* Optional members */
	5, 0,	/* Root/Additions */
	7,	/* First extension addition */
};
asn_TYPE_descriptor_t asn_DEF_LinkEx = {
	"LinkEx",
	"LinkEx",
	&asn_OP_SEQUENCE,
	asn_DEF_LinkEx_tags_1,
	sizeof(asn_DEF_LinkEx_tags_1)
		/sizeof(asn_DEF_LinkEx_tags_1[0]), /* 1 */
	asn_DEF_LinkEx_tags_1,	/* Same as above */
	sizeof(asn_DEF_LinkEx_tags_1)
		/sizeof(asn_DEF_LinkEx_tags_1[0]), /* 1 */
	{ 0, 0, SEQUENCE_constraint },
	asn_MBR_LinkEx_1,
	7,	/* Elements count */
	&asn_SPC_LinkEx_specs_1	/* Additional specs */
};

