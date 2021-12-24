/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "Map"
 * 	found in "Map.asn"
 * 	`asn1c -gen-PER`
 */

#ifndef	_LaneEx_H_
#define	_LaneEx_H_


#include <asn_application.h>

/* Including external dependencies */
#include "LaneRefID.h"
#include "LaneWidth.h"
#include "AllowedManeuvers.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct LaneAttributes;
struct ConnectsToExList;
struct SpeedLimitList;
struct STPointList;
struct LaneLineType;

/* LaneEx */
typedef struct LaneEx {
	LaneRefID_t	 laneRefID;
	LaneWidth_t	*laneWidth	/* OPTIONAL */;
	struct LaneAttributes	*laneAttributes	/* OPTIONAL */;
	AllowedManeuvers_t	*maneuvers	/* OPTIONAL */;
	struct ConnectsToExList	*connectsTo_ex	/* OPTIONAL */;
	struct SpeedLimitList	*speedLimits	/* OPTIONAL */;
	struct STPointList	*st_points	/* OPTIONAL */;
	struct LaneLineType	*laneLineType	/* OPTIONAL */;
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} LaneEx_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_LaneEx;
extern asn_SEQUENCE_specifics_t asn_SPC_LaneEx_specs_1;
extern asn_TYPE_member_t asn_MBR_LaneEx_1[8];

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "LaneAttributes.h"
#include "ConnectsToExList.h"
#include "SpeedLimitList.h"
#include "STPointList.h"
#include "LaneLineType.h"

#endif	/* _LaneEx_H_ */
#include <asn_internal.h>
