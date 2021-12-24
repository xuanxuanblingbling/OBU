/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "VPM"
 * 	found in "VPM.asn"
 * 	`asn1c -gen-PER`
 */

#include "SetTollDataRs.h"

static int
memb_tacInfo_constraint_1(const asn_TYPE_descriptor_t *td, const void *sptr,
			asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	const OCTET_STRING_t *st = (const OCTET_STRING_t *)sptr;
	size_t size;
	
	if(!sptr) {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: value not given (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
	
	size = st->size;
	
	if((size == 4)) {
		/* Constraint check succeeded */
		return 0;
	} else {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: constraint failed (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
}

static int
memb_authenticator_constraint_1(const asn_TYPE_descriptor_t *td, const void *sptr,
			asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	const OCTET_STRING_t *st = (const OCTET_STRING_t *)sptr;
	size_t size;
	
	if(!sptr) {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: value not given (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
	
	size = st->size;
	
	if((size == 8)) {
		/* Constraint check succeeded */
		return 0;
	} else {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: constraint failed (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
}

static asn_oer_constraints_t asn_OER_memb_tacInfo_constr_2 CC_NOTUSED = {
	{ 0, 0 },
	4	/* (SIZE(4..4)) */};
static asn_per_constraints_t asn_PER_memb_tacInfo_constr_2 CC_NOTUSED = {
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	{ APC_CONSTRAINED,	 0,  0,  4,  4 }	/* (SIZE(4..4)) */,
	0, 0	/* No PER value map */
};
static asn_oer_constraints_t asn_OER_memb_authenticator_constr_3 CC_NOTUSED = {
	{ 0, 0 },
	8	/* (SIZE(8..8)) */};
static asn_per_constraints_t asn_PER_memb_authenticator_constr_3 CC_NOTUSED = {
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	{ APC_CONSTRAINED,	 0,  0,  8,  8 }	/* (SIZE(8..8)) */,
	0, 0	/* No PER value map */
};
asn_TYPE_member_t asn_MBR_SetTollDataRs_1[] = {
	{ ATF_POINTER, 4, offsetof(struct SetTollDataRs, tacInfo),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_OCTET_STRING,
		0,
		{ &asn_OER_memb_tacInfo_constr_2, &asn_PER_memb_tacInfo_constr_2,  memb_tacInfo_constraint_1 },
		0, 0, /* No default value */
		"tacInfo"
		},
	{ ATF_POINTER, 3, offsetof(struct SetTollDataRs, authenticator),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_OCTET_STRING,
		0,
		{ &asn_OER_memb_authenticator_constr_3, &asn_PER_memb_authenticator_constr_3,  memb_authenticator_constraint_1 },
		0, 0, /* No default value */
		"authenticator"
		},
	{ ATF_POINTER, 2, offsetof(struct SetTollDataRs, accountInfo),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_AccountInfo,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"accountInfo"
		},
	{ ATF_POINTER, 1, offsetof(struct SetTollDataRs, transCredential),
		(ASN_TAG_CLASS_CONTEXT | (3 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_TransCredential,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"transCredential"
		},
};
static const int asn_MAP_SetTollDataRs_oms_1[] = { 0, 1, 2, 3 };
static const ber_tlv_tag_t asn_DEF_SetTollDataRs_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_SetTollDataRs_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* tacInfo */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* authenticator */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 }, /* accountInfo */
    { (ASN_TAG_CLASS_CONTEXT | (3 << 2)), 3, 0, 0 } /* transCredential */
};
asn_SEQUENCE_specifics_t asn_SPC_SetTollDataRs_specs_1 = {
	sizeof(struct SetTollDataRs),
	offsetof(struct SetTollDataRs, _asn_ctx),
	asn_MAP_SetTollDataRs_tag2el_1,
	4,	/* Count of tags in the map */
	asn_MAP_SetTollDataRs_oms_1,	/* Optional members */
	4, 0,	/* Root/Additions */
	4,	/* First extension addition */
};
asn_TYPE_descriptor_t asn_DEF_SetTollDataRs = {
	"SetTollDataRs",
	"SetTollDataRs",
	&asn_OP_SEQUENCE,
	asn_DEF_SetTollDataRs_tags_1,
	sizeof(asn_DEF_SetTollDataRs_tags_1)
		/sizeof(asn_DEF_SetTollDataRs_tags_1[0]), /* 1 */
	asn_DEF_SetTollDataRs_tags_1,	/* Same as above */
	sizeof(asn_DEF_SetTollDataRs_tags_1)
		/sizeof(asn_DEF_SetTollDataRs_tags_1[0]), /* 1 */
	{ 0, 0, SEQUENCE_constraint },
	asn_MBR_SetTollDataRs_1,
	4,	/* Elements count */
	&asn_SPC_SetTollDataRs_specs_1	/* Additional specs */
};
