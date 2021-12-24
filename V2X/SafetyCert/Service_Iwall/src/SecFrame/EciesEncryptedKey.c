/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "SecMsg"
 *     found in "SecMsg.asn"
 *     `asn1c -gen-PER`
 */

#include "EciesEncryptedKey.h"

static int
memb_c_constraint_1(const asn_TYPE_descriptor_t *td, const void *sptr,
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

    if((size == 16)) {
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
memb_t_constraint_1(const asn_TYPE_descriptor_t *td, const void *sptr,
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

    if((size == 32)) {
        /* Constraint check succeeded */
        return 0;
    } else {
        ASN__CTFAIL(app_key, td, sptr,
            "%s: constraint failed (%s:%d)",
            td->name, __FILE__, __LINE__);
        return -1;
    }
}

static asn_oer_constraints_t asn_OER_memb_c_constr_4 CC_NOTUSED = {
    { 0, 0 },
    16    /* (SIZE(16..16)) */};
static asn_per_constraints_t asn_PER_memb_c_constr_4 CC_NOTUSED = {
    { APC_UNCONSTRAINED,    -1, -1,  0,  0 },
    { APC_CONSTRAINED,     0,  0,  16,  16 }    /* (SIZE(16..16)) */,
    0, 0    /* No PER value map */
};
static asn_oer_constraints_t asn_OER_memb_t_constr_5 CC_NOTUSED = {
    { 0, 0 },
    32    /* (SIZE(32..32)) */};
static asn_per_constraints_t asn_PER_memb_t_constr_5 CC_NOTUSED = {
    { APC_UNCONSTRAINED,    -1, -1,  0,  0 },
    { APC_CONSTRAINED,     0,  0,  32,  32 }    /* (SIZE(32..32)) */,
    0, 0    /* No PER value map */
};
asn_TYPE_member_t asn_MBR_EciesEncryptedKey_1[] = {
    { ATF_NOFLAGS, 0, offsetof(struct EciesEncryptedKey, eccCcurve),
        (ASN_TAG_CLASS_CONTEXT | (0 << 2)),
        -1,    /* IMPLICIT tag at current level */
        &asn_DEF_EccCurve,
        0,
        { 0, 0, 0 },
        0, 0, /* No default value */
        "eccCcurve"
        },
    { ATF_NOFLAGS, 0, offsetof(struct EciesEncryptedKey, v),
        (ASN_TAG_CLASS_CONTEXT | (1 << 2)),
        +1,    /* EXPLICIT tag at current level */
        &asn_DEF_ECCPoint,
        0,
        { 0, 0, 0 },
        0, 0, /* No default value */
        "v"
        },
    { ATF_NOFLAGS, 0, offsetof(struct EciesEncryptedKey, c),
        (ASN_TAG_CLASS_CONTEXT | (2 << 2)),
        -1,    /* IMPLICIT tag at current level */
        &asn_DEF_OCTET_STRING,
        0,
        { &asn_OER_memb_c_constr_4, &asn_PER_memb_c_constr_4,  memb_c_constraint_1 },
        0, 0, /* No default value */
        "c"
        },
    { ATF_NOFLAGS, 0, offsetof(struct EciesEncryptedKey, t),
        (ASN_TAG_CLASS_CONTEXT | (3 << 2)),
        -1,    /* IMPLICIT tag at current level */
        &asn_DEF_OCTET_STRING,
        0,
        { &asn_OER_memb_t_constr_5, &asn_PER_memb_t_constr_5,  memb_t_constraint_1 },
        0, 0, /* No default value */
        "t"
        },
};
static const ber_tlv_tag_t asn_DEF_EciesEncryptedKey_tags_1[] = {
    (ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_EciesEncryptedKey_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* eccCcurve */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* v */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 }, /* c */
    { (ASN_TAG_CLASS_CONTEXT | (3 << 2)), 3, 0, 0 } /* t */
};
asn_SEQUENCE_specifics_t asn_SPC_EciesEncryptedKey_specs_1 = {
    sizeof(struct EciesEncryptedKey),
    offsetof(struct EciesEncryptedKey, _asn_ctx),
    asn_MAP_EciesEncryptedKey_tag2el_1,
    4,    /* Count of tags in the map */
    0, 0, 0,    /* Optional elements (not needed) */
    -1,    /* First extension addition */
};
asn_TYPE_descriptor_t asn_DEF_EciesEncryptedKey = {
    "EciesEncryptedKey",
    "EciesEncryptedKey",
    &asn_OP_SEQUENCE,
    asn_DEF_EciesEncryptedKey_tags_1,
    sizeof(asn_DEF_EciesEncryptedKey_tags_1)
        /sizeof(asn_DEF_EciesEncryptedKey_tags_1[0]), /* 1 */
    asn_DEF_EciesEncryptedKey_tags_1,    /* Same as above */
    sizeof(asn_DEF_EciesEncryptedKey_tags_1)
        /sizeof(asn_DEF_EciesEncryptedKey_tags_1[0]), /* 1 */
    { 0, 0, SEQUENCE_constraint },
    asn_MBR_EciesEncryptedKey_1,
    4,    /* Elements count */
    &asn_SPC_EciesEncryptedKey_specs_1    /* Additional specs */
};

