#ifndef PATHHISTORY_H
#define PATHHISTORY_H

#include "pathHistoryAPI.h"
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

#define REarthMeridian 6372795.477598
//地球半径（米）在子午线处的长度
#define K_PH_CHORDLENGTHTHRESHOLD 210.0
//弦长阈值（米）
#define K_PHSMALLDELTAPHI_R 0.02
//曲率对应角阈值（弧度）
#define K_PH_MAXESTIMATEDRADIUS 0x7FFFFF
//最大曲率半径（米）
#define K_PHDISTANCE_M 200
//历史路径总距离最大值 （米）
#define K_PHALLOWABLEERROR_M 1
//dist rad to chord
#define nPHCount 5

class PathHistory
{
public:
    int nFlag;
    double dTotalDist;
    double dTotalDistLast;
    double deltaTotalD;
    double AllowableActualError;
    double PH_EstimatedR;
    bool flagCL;
    vector<MSG_bsmPHused_st> a_PH;
    vector<MSG_bsmPHused_st> a_PHConciseData;

    PathHistory();
    ~PathHistory() {}
    void setAE(double AE) { AllowableActualError = AE; }
    double calcuChordLength(const MSG_bsmPHused_st p_cPos1, const MSG_bsmPHused_st p_cPos2);

    int deleteEleInArray();

    int updateHistory(MSG_bsmPHused_st p_Pos);

    int calcuPathHistory(MSG_bsmPHused_st p_Pos);
    bool judgeCurve();
    MSG_bsmPHused_st getPathHistory();
    MSG_bsmPHused_st getLastGPS();
    double getEstimateR() { return PH_EstimatedR; }
    double getTotalDist() { return dTotalDist; }
    //    std::vector<PointGPSsimplify> convert2Presentation();
    std::vector<MSG_bsmPHused_st> getPathHistorySeries();
};

#endif // PATHHISTORY_H
