/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "VPM"
 * 	found in "VPM.asn"
 * 	`asn1c -gen-PER`
 */

#include "TransInfo.h"

static asn_oer_constraints_t asn_OER_type_TransInfo_constr_1 CC_NOTUSED = {
	{ 0, 0 },
	-1};
asn_per_constraints_t asn_PER_type_TransInfo_constr_1 CC_NOTUSED = {
	{ APC_CONSTRAINED | APC_EXTENSIBLE,  4,  4,  0,  8 }	/* (0..8,...) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
asn_TYPE_member_t asn_MBR_TransInfo_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct TransInfo, choice.getTollDataRq),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_GetTollDataRq,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"getTollDataRq"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct TransInfo, choice.getTollDataRs),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_GetTollDataRs,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"getTollDataRs"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct TransInfo, choice.getSecureRq),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_GetSecureRq,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"getSecureRq"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct TransInfo, choice.getSecureRs),
		(ASN_TAG_CLASS_CONTEXT | (3 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_GetSecureRs,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"getSecureRs"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct TransInfo, choice.setTollDataRq),
		(ASN_TAG_CLASS_CONTEXT | (4 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_SetTollDataRq,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"setTollDataRq"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct TransInfo, choice.setTollDataRs),
		(ASN_TAG_CLASS_CONTEXT | (5 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_SetTollDataRs,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"setTollDataRs"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct TransInfo, choice.transferChannelRq),
		(ASN_TAG_CLASS_CONTEXT | (6 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_ChannelRq,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"transferChannelRq"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct TransInfo, choice.transferChannelRs),
		(ASN_TAG_CLASS_CONTEXT | (7 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_ChannelRs,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"transferChannelRs"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct TransInfo, choice.setMMIRq),
		(ASN_TAG_CLASS_CONTEXT | (8 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_SetMMIRq,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"setMMIRq"
		},
};
static const asn_TYPE_tag2member_t asn_MAP_TransInfo_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* getTollDataRq */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* getTollDataRs */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 }, /* getSecureRq */
    { (ASN_TAG_CLASS_CONTEXT | (3 << 2)), 3, 0, 0 }, /* getSecureRs */
    { (ASN_TAG_CLASS_CONTEXT | (4 << 2)), 4, 0, 0 }, /* setTollDataRq */
    { (ASN_TAG_CLASS_CONTEXT | (5 << 2)), 5, 0, 0 }, /* setTollDataRs */
    { (ASN_TAG_CLASS_CONTEXT | (6 << 2)), 6, 0, 0 }, /* transferChannelRq */
    { (ASN_TAG_CLASS_CONTEXT | (7 << 2)), 7, 0, 0 }, /* transferChannelRs */
    { (ASN_TAG_CLASS_CONTEXT | (8 << 2)), 8, 0, 0 } /* setMMIRq */
};
asn_CHOICE_specifics_t asn_SPC_TransInfo_specs_1 = {
	sizeof(struct TransInfo),
	offsetof(struct TransInfo, _asn_ctx),
	offsetof(struct TransInfo, present),
	sizeof(((struct TransInfo *)0)->present),
	asn_MAP_TransInfo_tag2el_1,
	9,	/* Count of tags in the map */
	0, 0,
	9	/* Extensions start */
};
asn_TYPE_descriptor_t asn_DEF_TransInfo = {
	"TransInfo",
	"TransInfo",
	&asn_OP_CHOICE,
	0,	/* No effective tags (pointer) */
	0,	/* No effective tags (count) */
	0,	/* No tags (pointer) */
	0,	/* No tags (count) */
	{ &asn_OER_type_TransInfo_constr_1, &asn_PER_type_TransInfo_constr_1, CHOICE_constraint },
	asn_MBR_TransInfo_1,
	9,	/* Elements count */
	&asn_SPC_TransInfo_specs_1	/* Additional specs */
};

