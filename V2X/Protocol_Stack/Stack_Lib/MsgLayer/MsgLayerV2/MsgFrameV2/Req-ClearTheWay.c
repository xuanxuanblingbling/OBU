/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "VIR"
 * 	found in "VIR.asn"
 * 	`asn1c -gen-PER`
 */

#include "Req-ClearTheWay.h"

asn_TYPE_member_t asn_MBR_Req_ClearTheWay_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct Req_ClearTheWay, upstreamNode),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_NodeReferenceID,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"upstreamNode"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct Req_ClearTheWay, downstreamNode),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_NodeReferenceID,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"downstreamNode"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct Req_ClearTheWay, targetLane),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_LaneID,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"targetLane"
		},
	{ ATF_POINTER, 3, offsetof(struct Req_ClearTheWay, relatedPath),
		(ASN_TAG_CLASS_CONTEXT | (3 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_ReferencePath,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"relatedPath"
		},
	{ ATF_POINTER, 2, offsetof(struct Req_ClearTheWay, tBegin),
		(ASN_TAG_CLASS_CONTEXT | (4 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_DDateTime,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"tBegin"
		},
	{ ATF_POINTER, 1, offsetof(struct Req_ClearTheWay, tEnd),
		(ASN_TAG_CLASS_CONTEXT | (5 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_DDateTime,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"tEnd"
		},
};
static const int asn_MAP_Req_ClearTheWay_oms_1[] = { 3, 4, 5 };
static const ber_tlv_tag_t asn_DEF_Req_ClearTheWay_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_Req_ClearTheWay_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* upstreamNode */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* downstreamNode */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 }, /* targetLane */
    { (ASN_TAG_CLASS_CONTEXT | (3 << 2)), 3, 0, 0 }, /* relatedPath */
    { (ASN_TAG_CLASS_CONTEXT | (4 << 2)), 4, 0, 0 }, /* tBegin */
    { (ASN_TAG_CLASS_CONTEXT | (5 << 2)), 5, 0, 0 } /* tEnd */
};
asn_SEQUENCE_specifics_t asn_SPC_Req_ClearTheWay_specs_1 = {
	sizeof(struct Req_ClearTheWay),
	offsetof(struct Req_ClearTheWay, _asn_ctx),
	asn_MAP_Req_ClearTheWay_tag2el_1,
	6,	/* Count of tags in the map */
	asn_MAP_Req_ClearTheWay_oms_1,	/* Optional members */
	3, 0,	/* Root/Additions */
	6,	/* First extension addition */
};
asn_TYPE_descriptor_t asn_DEF_Req_ClearTheWay = {
	"Req-ClearTheWay",
	"Req-ClearTheWay",
	&asn_OP_SEQUENCE,
	asn_DEF_Req_ClearTheWay_tags_1,
	sizeof(asn_DEF_Req_ClearTheWay_tags_1)
		/sizeof(asn_DEF_Req_ClearTheWay_tags_1[0]), /* 1 */
	asn_DEF_Req_ClearTheWay_tags_1,	/* Same as above */
	sizeof(asn_DEF_Req_ClearTheWay_tags_1)
		/sizeof(asn_DEF_Req_ClearTheWay_tags_1[0]), /* 1 */
	{ 0, 0, SEQUENCE_constraint },
	asn_MBR_Req_ClearTheWay_1,
	6,	/* Elements count */
	&asn_SPC_Req_ClearTheWay_specs_1	/* Additional specs */
};

