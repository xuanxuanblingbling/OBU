/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "Map"
 * 	found in "Map.asn"
 * 	`asn1c -gen-PER`
 */

#include "ST-Point.h"

static int
memb_s_axis_constraint_1(const asn_TYPE_descriptor_t *td, const void *sptr,
			asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	long value;
	
	if(!sptr) {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: value not given (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
	
	value = *(const long *)sptr;
	
	if((value >= -1024 && value <= 65535)) {
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
memb_t_axis_constraint_1(const asn_TYPE_descriptor_t *td, const void *sptr,
			asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	long value;
	
	if(!sptr) {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: value not given (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
	
	value = *(const long *)sptr;
	
	if((value >= -32768 && value <= 32767)) {
		/* Constraint check succeeded */
		return 0;
	} else {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: constraint failed (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
}

static asn_oer_constraints_t asn_OER_memb_s_axis_constr_2 CC_NOTUSED = {
	{ 4, 0 }	/* (-1024..65535) */,
	-1};
static asn_per_constraints_t asn_PER_memb_s_axis_constr_2 CC_NOTUSED = {
	{ APC_CONSTRAINED,	 17, -1, -1024,  65535 }	/* (-1024..65535) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_oer_constraints_t asn_OER_memb_t_axis_constr_3 CC_NOTUSED = {
	{ 2, 0 }	/* (-32768..32767) */,
	-1};
static asn_per_constraints_t asn_PER_memb_t_axis_constr_3 CC_NOTUSED = {
	{ APC_CONSTRAINED,	 16,  16, -32768,  32767 }	/* (-32768..32767) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
asn_TYPE_member_t asn_MBR_ST_Point_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct ST_Point, s_axis),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_NativeInteger,
		0,
		{ &asn_OER_memb_s_axis_constr_2, &asn_PER_memb_s_axis_constr_2,  memb_s_axis_constraint_1 },
		0, 0, /* No default value */
		"s-axis"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct ST_Point, t_axis),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_NativeInteger,
		0,
		{ &asn_OER_memb_t_axis_constr_3, &asn_PER_memb_t_axis_constr_3,  memb_t_axis_constraint_1 },
		0, 0, /* No default value */
		"t-axis"
		},
};
static const ber_tlv_tag_t asn_DEF_ST_Point_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_ST_Point_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* s-axis */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 } /* t-axis */
};
asn_SEQUENCE_specifics_t asn_SPC_ST_Point_specs_1 = {
	sizeof(struct ST_Point),
	offsetof(struct ST_Point, _asn_ctx),
	asn_MAP_ST_Point_tag2el_1,
	2,	/* Count of tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	2,	/* First extension addition */
};
asn_TYPE_descriptor_t asn_DEF_ST_Point = {
	"ST-Point",
	"ST-Point",
	&asn_OP_SEQUENCE,
	asn_DEF_ST_Point_tags_1,
	sizeof(asn_DEF_ST_Point_tags_1)
		/sizeof(asn_DEF_ST_Point_tags_1[0]), /* 1 */
	asn_DEF_ST_Point_tags_1,	/* Same as above */
	sizeof(asn_DEF_ST_Point_tags_1)
		/sizeof(asn_DEF_ST_Point_tags_1[0]), /* 1 */
	{ 0, 0, SEQUENCE_constraint },
	asn_MBR_ST_Point_1,
	2,	/* Elements count */
	&asn_SPC_ST_Point_specs_1	/* Additional specs */
};

