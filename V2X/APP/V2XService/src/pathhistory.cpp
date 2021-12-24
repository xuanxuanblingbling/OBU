#include "pathhistory.h"

PathHistory::PathHistory()
{
    nFlag = 0;
    dTotalDist = 0.0;
    dTotalDistLast = 0.0;
    flagCL = false;
    AllowableActualError = K_PHALLOWABLEERROR_M;
    a_PH.clear();
    a_PHConciseData.clear();
}
double PathHistory::calcuChordLength(const MSG_bsmPHused_st p_cPos1, const MSG_bsmPHused_st p_cPos2)
{
    double ret = 0.0;
    double long1 = p_cPos1.bsm_pos.n32long * M_PI / 180; //radian 2 degree
    double long2 = p_cPos2.bsm_pos.n32long * M_PI / 180;
    double lat1 = p_cPos1.bsm_pos.n32lat * M_PI / 180;
    double lat2 = p_cPos2.bsm_pos.n32lat * M_PI / 180;
    double a = lat1 - lat2;
    double b = long1 - long2;
    double s = 2 * asin(sqrt(pow(sin(a / 2.0), 2) + cos(lat1) * cos(lat2) * pow(sin(b / 2.0), 2)));
    s = s * REarthMeridian;
    ret = round(s * 10000) / 10000;
    return ret;
}
int PathHistory::deleteEleInArray()
{
    int i = 1;
    int numPH = a_PHConciseData.size();
    if (2 > numPH)
    {
        printf("deleteEleInArray failed.array count < 2.");
        return -1;
    }
    for (i = 0; i < numPH; i++)
    {
        a_PHConciseData[i] = a_PHConciseData[i + 1];
    }
    a_PHConciseData.pop_back();
    return 1;
}
int PathHistory::updateHistory(MSG_bsmPHused_st p_Pos)
{
    //check count
    int nPH3 = a_PH.size();
    if (3 < nPH3)
    {
        printf("updateHistory failed.p_a_PH count > 3.");
        return -1;
    }
    //addPos
    if (1 == nFlag)
    {
        if (3 == nPH3)
        {
            a_PH[1] = a_PH[2];
            a_PH[2] = p_Pos;
            nFlag = 0;
            return 1;
        }
        else
        {
            nFlag = 0;
            printf("update failed.only pre and next need to be update, but there is no enough p_a_PH.");
            return -1;
        }
    }
    if (3 == nPH3)
    {
        a_PH[0] = a_PH[1];
        a_PH[1] = a_PH[2];
        a_PH[2] = p_Pos;
        return 1;
    }
    while (3 > nPH3)
    {
        a_PH.push_back(p_Pos);
        nPH3 = a_PH.size();
        if (nPH3 == 3)
            return 1;
        else
            return 0;
    }
    return -2;
}
int PathHistory::calcuPathHistory(MSG_bsmPHused_st p_Pos)
{

    //init
    int retval = -1;
    //update a_PH or add a_PH until count=3
    int retUP = updateHistory(p_Pos);
    if (0 == retUP)
    {
        return 0;
    }
    if (-1 == retUP)
    {
        return -1;
    }
    //check number of p_nPHCountCur
    //calculate
    //step1:initial
    MSG_bsmPHused_st posStart = a_PH[0];
    MSG_bsmPHused_st posPrevs = a_PH[1];
    MSG_bsmPHused_st posNext = a_PH[2];

    double dIncrementDist = 0.0;
    double PH_ActualChordLength = 0.0;
    double PH_ActualError = 0.0;
    double dAngleDelta = 0.0;
    PH_EstimatedR = 0.0;

    if (0 == a_PHConciseData.size())
    {
        a_PHConciseData.push_back(posStart);
    }
    //step2:计算真实弦长
    PH_ActualChordLength = calcuChordLength(posStart, posNext);
    if (K_PH_CHORDLENGTHTHRESHOLD < PH_ActualChordLength)
    {
        PH_ActualError = AllowableActualError + 1;
        //goto step7
    }
    else
    {
        //step3:计算Pstarting 和 Pnext 与圆心连线所夹的角度ΔØ的值（弧度）
        double heading1 = posStart.bsm_heading;
        double heading2 = posNext.bsm_heading;
        dAngleDelta = abs(heading2 - heading1) * M_PI / 180;
        //step4:计算近似曲率半径PH_EstimatedR（米）
        if (K_PHSMALLDELTAPHI_R > dAngleDelta)
        {
            PH_ActualError = 0.0;
            PH_EstimatedR = K_PH_MAXESTIMATEDRADIUS;
            //goto step8
            nFlag = 1;
            retval = -4;
            return retval;
        }
        PH_EstimatedR = PH_ActualChordLength / (2 * sin(dAngleDelta / 2));
        //step5:计算Pstarting 和 Pnext两点之间的圆弧中间点到实际弦的垂直距离d的值
        double dDistMiddle2Chord = PH_EstimatedR * cos(dAngleDelta / 2);
        //step6:计算实际最大误差PH_ActualError
        PH_ActualError = PH_EstimatedR - dDistMiddle2Chord;
    }
    //step7：满足条件的点加入缓冲，且置flag为0.下次更新时全部更新start，pre，next
    if (AllowableActualError < PH_ActualError)
    {
        a_PHConciseData.push_back(posPrevs);
        int numPH = a_PHConciseData.size();
        nFlag = 0;
        //goto step9
        //step9：计算历史路径总距离，适当删减过期历史数据，直至历史路径总长小于历史数据总长最大值
        dIncrementDist = calcuChordLength(a_PHConciseData[numPH - 2], a_PHConciseData[numPH - 1]);
        dTotalDistLast = dTotalDist;
        dTotalDist = dTotalDist + dIncrementDist;
        while (K_PHDISTANCE_M < dTotalDist || nPHCount < numPH)
        {
            //删除底部数据
            dIncrementDist = calcuChordLength(a_PHConciseData[0], a_PHConciseData[1]);
            dTotalDist = dTotalDist - dIncrementDist;
            int retDel = deleteEleInArray();
            if (-1 == retDel)
            {
                printf("deleteEleInArray failed.from PathHistory.c");
                return -2;
            }
            numPH = a_PHConciseData.size();
        }
        retval = 1;
    }
    else //step8:不满足条件的不加入缓冲，且置flag为1.下次更新时只更新pre，next
    {
        nFlag = 1;
        retval = -3;
    }
    return retval;
}

bool PathHistory::judgeCurve()
{
    if (nPHCount == a_PHConciseData.size())
    {
        double delta = dTotalDist - dTotalDistLast;
        if (delta < -1)
            flagCL = true;
        else if (delta > 1)
        {
            flagCL = false;
        }
    }
    else
    {
        double R = getEstimateR();
        if (R < 100)
            flagCL = true;
        else
        {
            flagCL = false;
        }
    }

    return flagCL;
}
MSG_bsmPHused_st PathHistory::getPathHistory()
{
    int numPH = a_PHConciseData.size();
    MSG_bsmPHused_st p_PosPre = a_PHConciseData[numPH - 1];
    return p_PosPre;
}

MSG_bsmPHused_st PathHistory::getLastGPS()
{
    MSG_bsmPHused_st p_PosLast = a_PH[1];
    return p_PosLast;
}

//std::vector<PointGPSsimplify> PathHistory::convert2Presentation()
//{
//        std::vector<PointGPSsimplify> gpsSC;
//        gpsSC.clear();
//        int numPH=a_PHConciseData.size();
//        for(int i=0;i<numPH;i++)
//        {
//            PointGPSsimplify Pos;
//            Pos.x = a_PHConciseData[i].bsm_pos.pos_lon;
//            Pos.y = a_PHConciseData[i].bsm_pos.pos_lat;
//            Pos.speed = a_PHConciseData[i].bsm_speed;
//            Pos.heading = a_PHConciseData[i].bsm_heading;
//            gpsSC.push_back(Pos);
//        }
//        return gpsSC;
//}

std::vector<MSG_bsmPHused_st> PathHistory::getPathHistorySeries()
{
    //    std::vector<PointPH> gpsSC;
    //    gpsSC.clear();
    //    int numPH=a_PHConciseDataBuffer.size();
    //    for(int i=0;i<numPH;i++)
    //    {
    //        PointPH Pos = a_PHConciseDataBuffer[i];
    //        gpsSC.push_back(Pos);
    //    }
    //    return gpsSC;
    return a_PHConciseData;
}
