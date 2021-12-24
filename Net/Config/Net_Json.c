#include <stdint.h>
#include <stdio.h>
#include <fcntl.h>
#include "cJSON.h"
#include "Net_Json.h"

/********************************************
 * 函数名称：FN_readCanData
 * 描述：向文件中读数据
 * 函数参数：
 * ****************************************************************/
F2 FN_readCanData()
{
	F2 l_veh;
	FILE *fpread;
	long len = 0;
	char *l_buf = NULL; //初始化指针置空 08.31
	fpread = fopen("/mnt/APP/Config/obu/net/CanData.json", "rb");
	fseek(fpread, 0, SEEK_END);
	len = ftell(fpread);
	fseek(fpread, 0, SEEK_SET);
	l_buf = (char *)malloc(len + 1);
	fread(l_buf, 1, len, fpread);
	cJSON *l_root;

	if (fpread != NULL)
	{
		l_root = cJSON_Parse(l_buf);
		cJSON_Print(l_root);
		cJSON *l_item = cJSON_GetObjectItem(l_root, "fameHead");
		if (NULL != l_item)
		{
			memcpy(&l_veh.frameHead, &l_item->valueint, sizeof(l_veh.frameHead));
		}
		else
		{
			l_veh.frameHead = 0xFFFF;
		}
		l_item = cJSON_GetObjectItem(l_root, "frameNum");
		if (NULL != l_item)
		{
			memcpy(&l_veh.frameNum, &l_item->valueint, sizeof(l_veh.frameNum));
		}
		else
		{
			l_veh.frameNum = 0x01;
		}

		l_item = cJSON_GetObjectItem(l_root, "frameCMDT");
		if (NULL != l_item)
		{
			memcpy(&l_veh.frameCMDT, &l_item->valueint, sizeof(l_veh.frameCMDT));
		}
		else
		{
			l_veh.frameCMDT = 0xF2;
		}

		l_item = cJSON_GetObjectItem(l_root, "framSubCDMT");
		if (NULL != l_item)
		{
			memcpy(&l_veh.framSubCDMT, &l_item->valueint, sizeof(l_veh.framSubCDMT));
		}
		else
		{
			l_veh.framSubCDMT = 0x00;
		}

		l_item = cJSON_GetObjectItem(l_root, "frameStatus");
		if (NULL != l_item)
		{
			memcpy(&l_veh.frameStatus, &l_item->valueint, sizeof(l_veh.frameStatus));
		}
		else
		{
			l_veh.frameStatus = 0x01;
		}

		l_item = cJSON_GetObjectItem(l_root, "frameLen");
		if (NULL != l_item)
		{
			memcpy(&l_veh.frameLen, &l_item->valueint, sizeof(l_veh.frameLen));
		}
		else
		{
			l_veh.frameLen = 0x2F;
		}

		l_item = cJSON_GetObjectItem(l_root, "blockStats");
		if (NULL != l_item)
		{
			memcpy(&l_veh.blockState, &l_item->valueint, sizeof(l_veh.blockState));
		}
		else
		{
			l_veh.blockState = 0x00;
		}

		l_item = cJSON_GetObjectItem(l_root, "canFlag");
		if (NULL != l_item)
		{
			memcpy(&l_veh.canFlag, &l_item->valueint, sizeof(l_veh.canFlag));
		}
		else
		{
			l_veh.canFlag = 0x00;
		}

		l_item = cJSON_GetObjectItem(l_root, "speed");
		if (NULL != l_item)
		{
			memcpy(&l_veh.speed, &l_item->valueint, sizeof(l_veh.speed));
		}
		else
		{
			l_veh.speed = 0x00;
		}

		l_item = cJSON_GetObjectItem(l_root, "wheelTurn");
		if (NULL != l_item)
		{
			memcpy(&l_veh.wheelTurn, &l_item->valueint, sizeof(l_veh.wheelTurn));
		}
		else
		{
			l_veh.wheelTurn = 0x00;
		}

		l_item = cJSON_GetObjectItem(l_root, "exteriorLights");
		if (NULL != l_item)
		{
			memcpy(&l_veh.exteriorLights, &l_item->valueint, sizeof(l_veh.exteriorLights));
		}
		else
		{
			l_veh.exteriorLights = 0x00;
		}

		l_item = cJSON_GetObjectItem(l_root, "brakePedalStatus");
		if (NULL != l_item)
		{
			memcpy(&l_veh.brakePedalStatus, &l_item->valueint, sizeof(l_veh.brakePedalStatus));
		}
		else
		{
			l_veh.brakePedalStatus = 0x01;
		}

		l_item = cJSON_GetObjectItem(l_root, "tractionControlSystem");
		if (NULL != l_item)
		{
			memcpy(&l_veh.tractionControlSystem, &l_item->valueint, sizeof(l_veh.tractionControlSystem));
		}
		else
		{
			l_veh.tractionControlSystem = 0x00;
		}

		l_item = cJSON_GetObjectItem(l_root, "auxiliaryBrakeSystem");
		if (NULL != l_item)
		{
			memcpy(&l_veh.tractionControlStatus, &l_item->valueint, sizeof(l_veh.tractionControlStatus));
		}
		else
		{
			l_veh.tractionControlStatus = 0x00;
		}

		l_item = cJSON_GetObjectItem(l_root, "AntilockbrakeSystem");
		if (NULL != l_item)
		{
			memcpy(&l_veh.AntilockbrakeSystem, &l_item->valueint, sizeof(l_veh.AntilockbrakeSystem));
		}
		else
		{
			l_veh.AntilockbrakeSystem = 0x00;
		}

		l_item = cJSON_GetObjectItem(l_root, "bodyStabilitySystem");
		if (NULL != l_item)
		{
			memcpy(&l_veh.bodyStabilitySystem, &l_item->valueint, sizeof(l_veh.bodyStabilitySystem));
		}
		else
		{
			l_veh.bodyStabilitySystem = 0x00;
		}

		l_item = cJSON_GetObjectItem(l_root, "brakeAssistSystem");
		if (NULL != l_item)
		{
			memcpy(&l_veh.brakeAssistSystem, &l_item->valueint, sizeof(l_veh.brakeAssistSystem));
		}
		else
		{
			l_veh.brakeAssistSystem = 0x00;
		}

		l_item = cJSON_GetObjectItem(l_root, "tractionControlStatus");
		if (NULL != l_item)
		{
			memcpy(&l_veh.auxiliaryBrakeSystem, &l_item->valueint, sizeof(l_veh.auxiliaryBrakeSystem));
		}
		else
		{
			l_veh.auxiliaryBrakeSystem = 0x01;
		}

		l_item = cJSON_GetObjectItem(l_root, "basicVehicleClass");
		if (NULL != l_item)
		{
			memcpy(&l_veh.basicVehicleClass, &l_item->valueint, sizeof(l_veh.basicVehicleClass));
		}
		else
		{
			l_veh.basicVehicleClass = 0x3b;
		}

		l_item = cJSON_GetObjectItem(l_root, "check");
		if (NULL != l_item)
		{
			memcpy(&l_veh.check, &l_item->valueint, sizeof(l_veh.check));
		}
		else
		{
			l_veh.check = 0x00;
		}

		l_item = cJSON_GetObjectItem(l_root, "end");
		if (NULL != l_item)
		{
			memcpy(&l_veh.end, &l_item->valueint, sizeof(l_veh.end));
		}
		else
		{

			l_veh.end = 0xFF;
		}

		//			cJSON_Delete(l_item);
	}
	cJSON_Delete(l_root);
	free(l_buf);
	fclose(fpread);
	return l_veh;
}
/********************************************
 * 函数名称：FN_CreatCanDataJson
 * 描述：向文件中写数据
 * 函数参数：
 * ****************************************************************/
uint32_t FN_WriteCanDataJson(F2 p_veh)
{
	cJSON *F2 = cJSON_CreateObject();
	cJSON_AddNumberToObject(F2, "fameHead", p_veh.frameHead);
	cJSON_AddNumberToObject(F2, "frameNum", p_veh.frameNum);
	cJSON_AddNumberToObject(F2, "frameCMDT", p_veh.frameCMDT);
	cJSON_AddNumberToObject(F2, "framSubCDMT", p_veh.framSubCDMT);
	cJSON_AddNumberToObject(F2, "frameStatus", p_veh.frameStatus);
	cJSON_AddNumberToObject(F2, "frameLen", p_veh.frameLen);
	cJSON_AddNumberToObject(F2, "blockStats", p_veh.blockState);
	cJSON_AddNumberToObject(F2, "canFlag", p_veh.canFlag);
	cJSON_AddNumberToObject(F2, "speed", p_veh.speed);
	cJSON_AddNumberToObject(F2, "wheelTurn", p_veh.wheelTurn);
	cJSON_AddNumberToObject(F2, "exteriorLights", p_veh.exteriorLights);
	cJSON_AddNumberToObject(F2, "brakePedalStatus", p_veh.brakePedalStatus);
	cJSON_AddNumberToObject(F2, "tractionControlSystem", p_veh.tractionControlSystem);
	cJSON_AddNumberToObject(F2, "auxiliaryBrakeSystem", p_veh.tractionControlStatus); //辅助制动系统
	cJSON_AddNumberToObject(F2, "AntilockbrakeSystem", p_veh.AntilockbrakeSystem);
	cJSON_AddNumberToObject(F2, "bodyStabilitySystem", p_veh.bodyStabilitySystem);
	cJSON_AddNumberToObject(F2, "brakeAssistSystem", p_veh.brakeAssistSystem);
	cJSON_AddNumberToObject(F2, "tractionControlStatus", p_veh.auxiliaryBrakeSystem); //牵引力控制系统状态
	cJSON_AddNumberToObject(F2, "basicVehicleClass", p_veh.basicVehicleClass);
	cJSON_AddNumberToObject(F2, "check", p_veh.check);
	cJSON_AddNumberToObject(F2, "end", p_veh.end);
	char *F2Str = cJSON_Print(F2);
	cJSON_Delete(F2);
	FILE *fp = fopen("/mnt/APP/Config/obu/net/CanData.json", "w");
	fwrite(F2Str, 1, strlen(F2Str), fp);
	fclose(fp);
	return 0;
}

/********************************************
 * 函数名称：FN_readRampIntoData
 * 描述：向文件中读数据
 * 函数参数：
 * ****************************************************************/
F5 FN_readRampIntoData()
{
	F5 l_ramp_into;
	FILE *fpread;
	long len = 0;
	char *l_buf = NULL; //初始化指针置空 08.31
	fpread = fopen("/mnt/APP/Config/obu/net/RampInto.json", "rb");
	fseek(fpread, 0, SEEK_END);
	len = ftell(fpread);
	fseek(fpread, 0, SEEK_SET);
	l_buf = (char *)malloc(len + 1);
	fread(l_buf, 1, len, fpread);
	cJSON *l_root;

	if (fpread != NULL)
	{
		l_root = cJSON_Parse(l_buf);
		cJSON_Print(l_root);
		cJSON *l_item = cJSON_GetObjectItem(l_root, "fameHead");
		memcpy(&l_ramp_into.frameHead, &l_item->valueint, sizeof(l_ramp_into.frameHead));
		l_item = cJSON_GetObjectItem(l_root, "frameNum");
		memcpy(&l_ramp_into.frameNum, &l_item->valueint, sizeof(l_ramp_into.frameNum));
		l_item = cJSON_GetObjectItem(l_root, "frameCMDT");
		memcpy(&l_ramp_into.frameCMDT, &l_item->valueint, sizeof(l_ramp_into.frameCMDT));
		l_item = cJSON_GetObjectItem(l_root, "framSubCDMT");
		memcpy(&l_ramp_into.framSubCDMT, &l_item->valueint, sizeof(l_ramp_into.framSubCDMT));
		l_item = cJSON_GetObjectItem(l_root, "frameStatus");
		memcpy(&l_ramp_into.frameStatus, &l_item->valueint, sizeof(l_ramp_into.frameStatus));
		l_item = cJSON_GetObjectItem(l_root, "frameLen");
		memcpy(&l_ramp_into.frameLen, &l_item->valueint, sizeof(l_ramp_into.frameLen));
		l_item = cJSON_GetObjectItem(l_root, "request_status");
		memcpy(&l_ramp_into.request_status, &l_item->valueint, sizeof(l_ramp_into.request_status));
		l_item = cJSON_GetObjectItem(l_root, "driving_status");
		memcpy(&l_ramp_into.driving_status, &l_item->valueint, sizeof(l_ramp_into.driving_status));
		l_item = cJSON_GetObjectItem(l_root, "driving_request");
		memcpy(&l_ramp_into.driving_request, &l_item->valueint, sizeof(l_ramp_into.driving_request));
		l_item = cJSON_GetObjectItem(l_root, "target_lane");
		memcpy(&l_ramp_into.target_lane, &l_item->valueint, sizeof(l_ramp_into.target_lane));
		l_item = cJSON_GetObjectItem(l_root, "request_target");
		memcpy(&l_ramp_into.request_target, &l_item->valueint, sizeof(l_ramp_into.request_target));
		l_item = cJSON_GetObjectItem(l_root, "device_id");
		memcpy(&l_ramp_into.device_id, &l_item->valueint, sizeof(l_ramp_into.device_id));
		l_item = cJSON_GetObjectItem(l_root, "request_start_time");
		memcpy(&l_ramp_into.request_start_time, &l_item->valueint, sizeof(l_ramp_into.request_start_time));
		l_item = cJSON_GetObjectItem(l_root, "request_end_time");
		memcpy(&l_ramp_into.request_end_time, &l_item->valueint, sizeof(l_ramp_into.request_end_time));
		l_item = cJSON_GetObjectItem(l_root, "check");
		memcpy(&l_ramp_into.check, &l_item->valueint, sizeof(l_ramp_into.check));
		l_item = cJSON_GetObjectItem(l_root, "end");
		memcpy(&l_ramp_into.end, &l_item->valueint, sizeof(l_ramp_into.end));
		//			cJSON_Delete(l_item);
	}
	cJSON_Delete(l_root);
	free(l_buf);
	fclose(fpread);
	return l_ramp_into;
}
/********************************************
 * 函数名称：FN_CreatRampIntoDataJson
 * 描述：向文件中写数据
 * 函数参数：
 * ****************************************************************/
uint32_t FN_CreatRampIntoDataJson(F5 p_ramp_into)
{
	cJSON *F5 = cJSON_CreateObject();
	cJSON_AddNumberToObject(F5, "fameHead", p_ramp_into.frameHead);
	cJSON_AddNumberToObject(F5, "frameNum", p_ramp_into.frameNum);
	cJSON_AddNumberToObject(F5, "frameCMDT", p_ramp_into.frameCMDT);
	cJSON_AddNumberToObject(F5, "framSubCDMT", p_ramp_into.framSubCDMT);
	cJSON_AddNumberToObject(F5, "frameStatus", p_ramp_into.frameStatus);
	cJSON_AddNumberToObject(F5, "frameLen", p_ramp_into.frameLen);
	cJSON_AddNumberToObject(F5, "request_status", p_ramp_into.request_status);
	cJSON_AddNumberToObject(F5, "driving_status", p_ramp_into.driving_status);
	cJSON_AddNumberToObject(F5, "driving_request", p_ramp_into.driving_request);
	cJSON_AddNumberToObject(F5, "target_lane", p_ramp_into.target_lane);
	cJSON_AddNumberToObject(F5, "request_target", p_ramp_into.request_target);
	cJSON_AddStringToObject(F5, "device_id", p_ramp_into.device_id);
	cJSON_AddNumberToObject(F5, "request_start_time", p_ramp_into.request_start_time);
	cJSON_AddNumberToObject(F5, "request_end_time", p_ramp_into.request_end_time);
	cJSON_AddNumberToObject(F5, "check", p_ramp_into.check);
	cJSON_AddNumberToObject(F5, "end", p_ramp_into.end);
	char *F5Str = cJSON_Print(F5);
	cJSON_Delete(F5);
	FILE *fp = fopen("/mnt/APP/Config/obu/net/RampInto.json", "w");
	fwrite(F5Str, 1, strlen(F5Str), fp);
	fclose(fp);
	return 0;
}
