/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "RSI"
 * 	found in "RSI.asn"
 * 	`asn1c -gen-PER`
 */

#include "ReferenceLink.h"

asn_TYPE_member_t asn_MBR_ReferenceLink_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct ReferenceLink, upstreamNodeId),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_NodeReferenceID,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"upstreamNodeId"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct ReferenceLink, downstreamNodeId),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_NodeReferenceID,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"downstreamNodeId"
		},
	{ ATF_POINTER, 1, offsetof(struct ReferenceLink, referenceLanes),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_ReferenceLanes,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"referenceLanes"
		},
};
static const int asn_MAP_ReferenceLink_oms_1[] = { 2 };
static const ber_tlv_tag_t asn_DEF_ReferenceLink_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_ReferenceLink_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* upstreamNodeId */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* downstreamNodeId */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 } /* referenceLanes */
};
asn_SEQUENCE_specifics_t asn_SPC_ReferenceLink_specs_1 = {
	sizeof(struct ReferenceLink),
	offsetof(struct ReferenceLink, _asn_ctx),
	asn_MAP_ReferenceLink_tag2el_1,
	3,	/* Count of tags in the map */
	asn_MAP_ReferenceLink_oms_1,	/* Optional members */
	1, 0,	/* Root/Additions */
	-1,	/* First extension addition */
};
asn_TYPE_descriptor_t asn_DEF_ReferenceLink = {
	"ReferenceLink",
	"ReferenceLink",
	&asn_OP_SEQUENCE,
	asn_DEF_ReferenceLink_tags_1,
	sizeof(asn_DEF_ReferenceLink_tags_1)
		/sizeof(asn_DEF_ReferenceLink_tags_1[0]), /* 1 */
	asn_DEF_ReferenceLink_tags_1,	/* Same as above */
	sizeof(asn_DEF_ReferenceLink_tags_1)
		/sizeof(asn_DEF_ReferenceLink_tags_1[0]), /* 1 */
	{ 0, 0, SEQUENCE_constraint },
	asn_MBR_ReferenceLink_1,
	3,	/* Elements count */
	&asn_SPC_ReferenceLink_specs_1	/* Additional specs */
};

