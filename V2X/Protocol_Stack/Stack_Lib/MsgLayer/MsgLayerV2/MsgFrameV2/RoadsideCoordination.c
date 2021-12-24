/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "RSC"
 * 	found in "RSC.asn"
 * 	`asn1c -gen-PER`
 */

#include "RoadsideCoordination.h"

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
memb_coordinates_constraint_1(const asn_TYPE_descriptor_t *td, const void *sptr,
			asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	size_t size;
	
	if(!sptr) {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: value not given (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
	
	/* Determine the number of elements */
	size = _A_CSEQUENCE_FROM_VOID(sptr)->count;
	
	if((size >= 1 && size <= 16)) {
		/* Perform validation of the inner elements */
		return SEQUENCE_OF_constraint(td, sptr, ctfailcb, app_key);
	} else {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: constraint failed (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
}

static int
memb_laneCoordinates_constraint_1(const asn_TYPE_descriptor_t *td, const void *sptr,
			asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	size_t size;
	
	if(!sptr) {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: value not given (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
	
	/* Determine the number of elements */
	size = _A_CSEQUENCE_FROM_VOID(sptr)->count;
	
	if((size >= 1 && size <= 8)) {
		/* Perform validation of the inner elements */
		return SEQUENCE_OF_constraint(td, sptr, ctfailcb, app_key);
	} else {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: constraint failed (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
}

static asn_oer_constraints_t asn_OER_type_coordinates_constr_6 CC_NOTUSED = {
	{ 0, 0 },
	-1	/* (SIZE(1..16)) */};
static asn_per_constraints_t asn_PER_type_coordinates_constr_6 CC_NOTUSED = {
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	{ APC_CONSTRAINED,	 4,  4,  1,  16 }	/* (SIZE(1..16)) */,
	0, 0	/* No PER value map */
};
static asn_oer_constraints_t asn_OER_type_laneCoordinates_constr_8 CC_NOTUSED = {
	{ 0, 0 },
	-1	/* (SIZE(1..8)) */};
static asn_per_constraints_t asn_PER_type_laneCoordinates_constr_8 CC_NOTUSED = {
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	{ APC_CONSTRAINED,	 3,  3,  1,  8 }	/* (SIZE(1..8)) */,
	0, 0	/* No PER value map */
};
static asn_oer_constraints_t asn_OER_memb_id_constr_3 CC_NOTUSED = {
	{ 0, 0 },
	8	/* (SIZE(8..8)) */};
static asn_per_constraints_t asn_PER_memb_id_constr_3 CC_NOTUSED = {
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	{ APC_CONSTRAINED,	 0,  0,  8,  8 }	/* (SIZE(8..8)) */,
	0, 0	/* No PER value map */
};
static asn_oer_constraints_t asn_OER_memb_coordinates_constr_6 CC_NOTUSED = {
	{ 0, 0 },
	-1	/* (SIZE(1..16)) */};
static asn_per_constraints_t asn_PER_memb_coordinates_constr_6 CC_NOTUSED = {
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	{ APC_CONSTRAINED,	 4,  4,  1,  16 }	/* (SIZE(1..16)) */,
	0, 0	/* No PER value map */
};
static asn_oer_constraints_t asn_OER_memb_laneCoordinates_constr_8 CC_NOTUSED = {
	{ 0, 0 },
	-1	/* (SIZE(1..8)) */};
static asn_per_constraints_t asn_PER_memb_laneCoordinates_constr_8 CC_NOTUSED = {
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	{ APC_CONSTRAINED,	 3,  3,  1,  8 }	/* (SIZE(1..8)) */,
	0, 0	/* No PER value map */
};
static asn_TYPE_member_t asn_MBR_coordinates_6[] = {
	{ ATF_POINTER, 0, 0,
		(ASN_TAG_CLASS_UNIVERSAL | (16 << 2)),
		0,
		&asn_DEF_VehicleCoordination,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		""
		},
};
static const ber_tlv_tag_t asn_DEF_coordinates_tags_6[] = {
	(ASN_TAG_CLASS_CONTEXT | (4 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_SET_OF_specifics_t asn_SPC_coordinates_specs_6 = {
	sizeof(struct coordinates),
	offsetof(struct coordinates, _asn_ctx),
	0,	/* XER encoding is XMLDelimitedItemList */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_coordinates_6 = {
	"coordinates",
	"coordinates",
	&asn_OP_SEQUENCE_OF,
	asn_DEF_coordinates_tags_6,
	sizeof(asn_DEF_coordinates_tags_6)
		/sizeof(asn_DEF_coordinates_tags_6[0]) - 1, /* 1 */
	asn_DEF_coordinates_tags_6,	/* Same as above */
	sizeof(asn_DEF_coordinates_tags_6)
		/sizeof(asn_DEF_coordinates_tags_6[0]), /* 2 */
	{ &asn_OER_type_coordinates_constr_6, &asn_PER_type_coordinates_constr_6, SEQUENCE_OF_constraint },
	asn_MBR_coordinates_6,
	1,	/* Single element */
	&asn_SPC_coordinates_specs_6	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_laneCoordinates_8[] = {
	{ ATF_POINTER, 0, 0,
		(ASN_TAG_CLASS_UNIVERSAL | (16 << 2)),
		0,
		&asn_DEF_LaneCoordination,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		""
		},
};
static const ber_tlv_tag_t asn_DEF_laneCoordinates_tags_8[] = {
	(ASN_TAG_CLASS_CONTEXT | (5 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_SET_OF_specifics_t asn_SPC_laneCoordinates_specs_8 = {
	sizeof(struct laneCoordinates),
	offsetof(struct laneCoordinates, _asn_ctx),
	0,	/* XER encoding is XMLDelimitedItemList */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_laneCoordinates_8 = {
	"laneCoordinates",
	"laneCoordinates",
	&asn_OP_SEQUENCE_OF,
	asn_DEF_laneCoordinates_tags_8,
	sizeof(asn_DEF_laneCoordinates_tags_8)
		/sizeof(asn_DEF_laneCoordinates_tags_8[0]) - 1, /* 1 */
	asn_DEF_laneCoordinates_tags_8,	/* Same as above */
	sizeof(asn_DEF_laneCoordinates_tags_8)
		/sizeof(asn_DEF_laneCoordinates_tags_8[0]), /* 2 */
	{ &asn_OER_type_laneCoordinates_constr_8, &asn_PER_type_laneCoordinates_constr_8, SEQUENCE_OF_constraint },
	asn_MBR_laneCoordinates_8,
	1,	/* Single element */
	&asn_SPC_laneCoordinates_specs_8	/* Additional specs */
};

asn_TYPE_member_t asn_MBR_RoadsideCoordination_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct RoadsideCoordination, msgCnt),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_MsgCount,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"msgCnt"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct RoadsideCoordination, id),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_OCTET_STRING,
		0,
		{ &asn_OER_memb_id_constr_3, &asn_PER_memb_id_constr_3,  memb_id_constraint_1 },
		0, 0, /* No default value */
		"id"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct RoadsideCoordination, secMark),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_DSecond,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"secMark"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct RoadsideCoordination, refPos),
		(ASN_TAG_CLASS_CONTEXT | (3 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_Position3D,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"refPos"
		},
	{ ATF_POINTER, 2, offsetof(struct RoadsideCoordination, coordinates),
		(ASN_TAG_CLASS_CONTEXT | (4 << 2)),
		0,
		&asn_DEF_coordinates_6,
		0,
		{ &asn_OER_memb_coordinates_constr_6, &asn_PER_memb_coordinates_constr_6,  memb_coordinates_constraint_1 },
		0, 0, /* No default value */
		"coordinates"
		},
	{ ATF_POINTER, 1, offsetof(struct RoadsideCoordination, laneCoordinates),
		(ASN_TAG_CLASS_CONTEXT | (5 << 2)),
		0,
		&asn_DEF_laneCoordinates_8,
		0,
		{ &asn_OER_memb_laneCoordinates_constr_8, &asn_PER_memb_laneCoordinates_constr_8,  memb_laneCoordinates_constraint_1 },
		0, 0, /* No default value */
		"laneCoordinates"
		},
};
static const int asn_MAP_RoadsideCoordination_oms_1[] = { 4, 5 };
static const ber_tlv_tag_t asn_DEF_RoadsideCoordination_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_RoadsideCoordination_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* msgCnt */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* id */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 }, /* secMark */
    { (ASN_TAG_CLASS_CONTEXT | (3 << 2)), 3, 0, 0 }, /* refPos */
    { (ASN_TAG_CLASS_CONTEXT | (4 << 2)), 4, 0, 0 }, /* coordinates */
    { (ASN_TAG_CLASS_CONTEXT | (5 << 2)), 5, 0, 0 } /* laneCoordinates */
};
asn_SEQUENCE_specifics_t asn_SPC_RoadsideCoordination_specs_1 = {
	sizeof(struct RoadsideCoordination),
	offsetof(struct RoadsideCoordination, _asn_ctx),
	asn_MAP_RoadsideCoordination_tag2el_1,
	6,	/* Count of tags in the map */
	asn_MAP_RoadsideCoordination_oms_1,	/* Optional members */
	2, 0,	/* Root/Additions */
	6,	/* First extension addition */
};
asn_TYPE_descriptor_t asn_DEF_RoadsideCoordination = {
	"RoadsideCoordination",
	"RoadsideCoordination",
	&asn_OP_SEQUENCE,
	asn_DEF_RoadsideCoordination_tags_1,
	sizeof(asn_DEF_RoadsideCoordination_tags_1)
		/sizeof(asn_DEF_RoadsideCoordination_tags_1[0]), /* 1 */
	asn_DEF_RoadsideCoordination_tags_1,	/* Same as above */
	sizeof(asn_DEF_RoadsideCoordination_tags_1)
		/sizeof(asn_DEF_RoadsideCoordination_tags_1[0]), /* 1 */
	{ 0, 0, SEQUENCE_constraint },
	asn_MBR_RoadsideCoordination_1,
	6,	/* Elements count */
	&asn_SPC_RoadsideCoordination_specs_1	/* Additional specs */
};

