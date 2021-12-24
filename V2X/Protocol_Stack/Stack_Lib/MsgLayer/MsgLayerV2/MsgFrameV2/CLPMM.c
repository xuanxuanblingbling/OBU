/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "Platooning"
 * 	found in "Platooning.asn"
 * 	`asn1c -gen-PER`
 */

#include "CLPMM.h"

static int
memb_id_constraint_1(const asn_TYPE_descriptor_t *td, const void *sptr,
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

static int
memb_pid_constraint_1(const asn_TYPE_descriptor_t *td, const void *sptr,
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
	
	if((size == 17)) {
		/* Constraint check succeeded */
		return 0;
	} else {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: constraint failed (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
}

static asn_oer_constraints_t asn_OER_memb_id_constr_3 CC_NOTUSED = {
	{ 0, 0 },
	8	/* (SIZE(8..8)) */};
static asn_per_constraints_t asn_PER_memb_id_constr_3 CC_NOTUSED = {
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	{ APC_CONSTRAINED,	 0,  0,  8,  8 }	/* (SIZE(8..8)) */,
	0, 0	/* No PER value map */
};
static asn_oer_constraints_t asn_OER_memb_pid_constr_5 CC_NOTUSED = {
	{ 0, 0 },
	17	/* (SIZE(17..17)) */};
static asn_per_constraints_t asn_PER_memb_pid_constr_5 CC_NOTUSED = {
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	{ APC_CONSTRAINED,	 0,  0,  17,  17 }	/* (SIZE(17..17)) */,
	0, 0	/* No PER value map */
};
asn_TYPE_member_t asn_MBR_CLPMM_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct CLPMM, msgCnt),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_MsgCount,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"msgCnt"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct CLPMM, id),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_OCTET_STRING,
		0,
		{ &asn_OER_memb_id_constr_3, &asn_PER_memb_id_constr_3,  memb_id_constraint_1 },
		0, 0, /* No default value */
		"id"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct CLPMM, secMark),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_DSecond,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"secMark"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct CLPMM, pid),
		(ASN_TAG_CLASS_CONTEXT | (3 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_OCTET_STRING,
		0,
		{ &asn_OER_memb_pid_constr_5, &asn_PER_memb_pid_constr_5,  memb_pid_constraint_1 },
		0, 0, /* No default value */
		"pid"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct CLPMM, role),
		(ASN_TAG_CLASS_CONTEXT | (4 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_RoleInPlatooning,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"role"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct CLPMM, status),
		(ASN_TAG_CLASS_CONTEXT | (5 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_StatusInPlatooning,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"status"
		},
	{ ATF_POINTER, 1, offsetof(struct CLPMM, leadingExt),
		(ASN_TAG_CLASS_CONTEXT | (6 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_MemberManagement,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"leadingExt"
		},
};
static const int asn_MAP_CLPMM_oms_1[] = { 6 };
static const ber_tlv_tag_t asn_DEF_CLPMM_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_CLPMM_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* msgCnt */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* id */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 }, /* secMark */
    { (ASN_TAG_CLASS_CONTEXT | (3 << 2)), 3, 0, 0 }, /* pid */
    { (ASN_TAG_CLASS_CONTEXT | (4 << 2)), 4, 0, 0 }, /* role */
    { (ASN_TAG_CLASS_CONTEXT | (5 << 2)), 5, 0, 0 }, /* status */
    { (ASN_TAG_CLASS_CONTEXT | (6 << 2)), 6, 0, 0 } /* leadingExt */
};
asn_SEQUENCE_specifics_t asn_SPC_CLPMM_specs_1 = {
	sizeof(struct CLPMM),
	offsetof(struct CLPMM, _asn_ctx),
	asn_MAP_CLPMM_tag2el_1,
	7,	/* Count of tags in the map */
	asn_MAP_CLPMM_oms_1,	/* Optional members */
	1, 0,	/* Root/Additions */
	7,	/* First extension addition */
};
asn_TYPE_descriptor_t asn_DEF_CLPMM = {
	"CLPMM",
	"CLPMM",
	&asn_OP_SEQUENCE,
	asn_DEF_CLPMM_tags_1,
	sizeof(asn_DEF_CLPMM_tags_1)
		/sizeof(asn_DEF_CLPMM_tags_1[0]), /* 1 */
	asn_DEF_CLPMM_tags_1,	/* Same as above */
	sizeof(asn_DEF_CLPMM_tags_1)
		/sizeof(asn_DEF_CLPMM_tags_1[0]), /* 1 */
	{ 0, 0, SEQUENCE_constraint },
	asn_MBR_CLPMM_1,
	7,	/* Elements count */
	&asn_SPC_CLPMM_specs_1	/* Additional specs */
};

