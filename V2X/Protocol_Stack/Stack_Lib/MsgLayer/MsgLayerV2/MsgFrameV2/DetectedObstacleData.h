/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "SensorSharing"
 * 	found in "SensorSharing.asn"
 * 	`asn1c -gen-PER`
 */

#ifndef	_DetectedObstacleData_H_
#define	_DetectedObstacleData_H_


#include <asn_application.h>

/* Including external dependencies */
#include "ObstacleType.h"
#include "Confidence.h"
#include <NativeInteger.h>
#include "SourceType.h"
#include "DSecond.h"
#include "PositionOffsetLLV.h"
#include "PositionConfidenceSet.h"
#include "Speed.h"
#include "SpeedConfidence.h"
#include "Heading.h"
#include "HeadingConfidence.h"
#include "ObjectSize.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct AccelerationSet4Way;
struct ObjectSizeConfidence;
struct Polygon;

/* DetectedObstacleData */
typedef struct DetectedObstacleData {
	ObstacleType_t	 obsType;
	Confidence_t	*objTypeConfidence	/* OPTIONAL */;
	long	 obsId;
	SourceType_t	 source;
	DSecond_t	 secMark;
	PositionOffsetLLV_t	 pos;
	PositionConfidenceSet_t	 posConfidence;
	Speed_t	 speed;
	SpeedConfidence_t	*speedCfd	/* OPTIONAL */;
	Heading_t	 heading;
	HeadingConfidence_t	*headingCfd	/* OPTIONAL */;
	Speed_t	*verSpeed	/* OPTIONAL */;
	SpeedConfidence_t	*verSpeedConfidence	/* OPTIONAL */;
	struct AccelerationSet4Way	*accelSet	/* OPTIONAL */;
	ObjectSize_t	 size;
	struct ObjectSizeConfidence	*objSizeConfidence	/* OPTIONAL */;
	long	*tracking	/* OPTIONAL */;
	struct Polygon	*polygon	/* OPTIONAL */;
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} DetectedObstacleData_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_DetectedObstacleData;
extern asn_SEQUENCE_specifics_t asn_SPC_DetectedObstacleData_specs_1;
extern asn_TYPE_member_t asn_MBR_DetectedObstacleData_1[18];

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "AccelerationSet4Way.h"
#include "ObjectSizeConfidence.h"
#include "Polygon.h"

#endif	/* _DetectedObstacleData_H_ */
#include <asn_internal.h>
