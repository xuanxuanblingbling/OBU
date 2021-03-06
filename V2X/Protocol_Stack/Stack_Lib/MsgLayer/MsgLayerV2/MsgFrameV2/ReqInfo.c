/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "VIR"
 * 	found in "VIR.asn"
 * 	`asn1c -gen-PER`
 */

#include "ReqInfo.h"

static asn_oer_constraints_t asn_OER_type_ReqInfo_constr_1 CC_NOTUSED = {
	{ 0, 0 },
	-1};
asn_per_constraints_t asn_PER_type_ReqInfo_constr_1 CC_NOTUSED = {
	{ APC_CONSTRAINED | APC_EXTENSIBLE,  3,  3,  0,  4 }	/* (0..4,...) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
asn_TYPE_member_t asn_MBR_ReqInfo_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct ReqInfo, choice.laneChange),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_Req_LaneChange,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"laneChange"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct ReqInfo, choice.clearTheWay),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_Req_ClearTheWay,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"clearTheWay"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct ReqInfo, choice.signalPriority),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_Req_SignalPriority,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"signalPriority"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct ReqInfo, choice.sensorSharing),
		(ASN_TAG_CLASS_CONTEXT | (3 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_Req_SensorSharing,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"sensorSharing"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct ReqInfo, choice.parking),
		(ASN_TAG_CLASS_CONTEXT | (4 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_Req_ParkingArea,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"parking"
		},
};
static const asn_TYPE_tag2member_t asn_MAP_ReqInfo_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* laneChange */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* clearTheWay */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 }, /* signalPriority */
    { (ASN_TAG_CLASS_CONTEXT | (3 << 2)), 3, 0, 0 }, /* sensorSharing */
    { (ASN_TAG_CLASS_CONTEXT | (4 << 2)), 4, 0, 0 } /* parking */
};
asn_CHOICE_specifics_t asn_SPC_ReqInfo_specs_1 = {
	sizeof(struct ReqInfo),
	offsetof(struct ReqInfo, _asn_ctx),
	offsetof(struct ReqInfo, present),
	sizeof(((struct ReqInfo *)0)->present),
	asn_MAP_ReqInfo_tag2el_1,
	5,	/* Count of tags in the map */
	0, 0,
	5	/* Extensions start */
};
asn_TYPE_descriptor_t asn_DEF_ReqInfo = {
	"ReqInfo",
	"ReqInfo",
	&asn_OP_CHOICE,
	0,	/* No effective tags (pointer) */
	0,	/* No effective tags (count) */
	0,	/* No tags (pointer) */
	0,	/* No tags (count) */
	{ &asn_OER_type_ReqInfo_constr_1, &asn_PER_type_ReqInfo_constr_1, CHOICE_constraint },
	asn_MBR_ReqInfo_1,
	5,	/* Elements count */
	&asn_SPC_ReqInfo_specs_1	/* Additional specs */
};

