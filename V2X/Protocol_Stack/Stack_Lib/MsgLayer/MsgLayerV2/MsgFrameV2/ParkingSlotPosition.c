/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "PAM"
 * 	found in "PAM.asn"
 * 	`asn1c -gen-PER`
 */

#include "ParkingSlotPosition.h"

asn_TYPE_member_t asn_MBR_ParkingSlotPosition_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct ParkingSlotPosition, topLeft),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_PositionOffsetLLV,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"topLeft"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct ParkingSlotPosition, topRight),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_PositionOffsetLLV,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"topRight"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct ParkingSlotPosition, bottomLeft),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_PositionOffsetLLV,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"bottomLeft"
		},
};
static const ber_tlv_tag_t asn_DEF_ParkingSlotPosition_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_ParkingSlotPosition_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* topLeft */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* topRight */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 } /* bottomLeft */
};
asn_SEQUENCE_specifics_t asn_SPC_ParkingSlotPosition_specs_1 = {
	sizeof(struct ParkingSlotPosition),
	offsetof(struct ParkingSlotPosition, _asn_ctx),
	asn_MAP_ParkingSlotPosition_tag2el_1,
	3,	/* Count of tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	-1,	/* First extension addition */
};
asn_TYPE_descriptor_t asn_DEF_ParkingSlotPosition = {
	"ParkingSlotPosition",
	"ParkingSlotPosition",
	&asn_OP_SEQUENCE,
	asn_DEF_ParkingSlotPosition_tags_1,
	sizeof(asn_DEF_ParkingSlotPosition_tags_1)
		/sizeof(asn_DEF_ParkingSlotPosition_tags_1[0]), /* 1 */
	asn_DEF_ParkingSlotPosition_tags_1,	/* Same as above */
	sizeof(asn_DEF_ParkingSlotPosition_tags_1)
		/sizeof(asn_DEF_ParkingSlotPosition_tags_1[0]), /* 1 */
	{ 0, 0, SEQUENCE_constraint },
	asn_MBR_ParkingSlotPosition_1,
	3,	/* Elements count */
	&asn_SPC_ParkingSlotPosition_specs_1	/* Additional specs */
};

