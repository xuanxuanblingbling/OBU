#include "pathHistoryAPI.h"
#include "pathhistory.h"

int nHistoryCount = 0;
MSG_bsmPHused_st a_PHConciseDataBuffer[15];
PathHistory G_CLASS_PH_API;

int calcuPathHistoryApiC(MSG_bsmPHused_st pt)
{
    int ret = G_CLASS_PH_API.calcuPathHistory(pt);
    if (ret != -1 && ret != -2 && ret != 0)
    {
        nHistoryCount = G_CLASS_PH_API.a_PHConciseData.size();
        for (int i = 0; i < nHistoryCount; i++)
        {
            a_PHConciseDataBuffer[i] = G_CLASS_PH_API.a_PHConciseData[i];
        }
    }
    return ret;
}
