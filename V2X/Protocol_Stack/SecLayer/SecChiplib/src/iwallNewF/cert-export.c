#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "glib.h"
#include "cJSON.h"
#include "wj_log.h"
#include "common.h"
#include "Chip_iwallNewF.h"
#define CERT_JSON_FILENAME "/mnt/APP/Config/Cert_Info.json"

#define JSON_ALG_NODE "algorithm"
#define JSON_FAC_NODE "ca"
#define JSON_CA_NAME_NODE "class"
#define JSON_STATUS_NODE "status"
#define JSON_EX_TIME_NODE "expirydata"
#define JSON_ST_TIME_NODE "startdata"
#define JSON_SER_NUM_NODE "serialnum"
#define JSON_CERT_PATH_NODE "path"
#define JSON_CERT_ID_NODE "id"

enum
{
    JSON_ALG_INDEX = 0, /*初始化json节点内容时使用的数组索引*/
    JSON_FAC_INDEX,
    JSON_CA_NAME_INDEX,
    JSON_EX_TIME_INDEX,
    JSON_ST_TIME_INDEX,
    JSON_SER_NUM_INDEX,
    JSON_PATH_INDEX,
    JSON_STATUS_INDEX,
    JSON_ID_INDEX,
    JSON_INDEX_MAX
};

struct json_cert
{
    // int8_t *node_name;
    char *node_name;
    union
    {
        void *val;
        uint32_t i;
    } v;
};

static struct json_cert s_cert_json[JSON_INDEX_MAX] = {
    {JSON_ALG_NODE, {"SM2"}},
    {JSON_FAC_NODE, {"iwall"}},
    {JSON_CA_NAME_NODE, {"Application certificate"}},
    {JSON_EX_TIME_NODE},
    {JSON_ST_TIME_NODE},
    {JSON_SER_NUM_NODE},
    {JSON_CERT_PATH_NODE},
    {JSON_STATUS_NODE},
    {JSON_CERT_ID_NODE},
};

//"algorithm": "SM2",
//        "ca": "大唐CA",
//        "class": "应用证书",
//        "expirydata": "2020-06-25 13:31",
//        "serialnum": "2CEE193C188278EA3E437573",
//        "startdata": "2019-05-09 09:22",
//        "status": 1

int32_t write_cert_json_file(const int8_t *start_time, const int8_t *end_time, const int8_t *hash,
                             const int8_t *path_name, const int8_t *json_path_name)
{
    cJSON *root = NULL;
    cJSON *arr = NULL;
    int8_t *out = NULL;
    int32_t i = 0;

    LogPrint(LOG_LEVEL_DEBUG, MODULE_NAME, "start:%s, end:%s", start_time, end_time);
    s_cert_json[JSON_ST_TIME_INDEX].v.val = (void *)start_time;
    s_cert_json[JSON_EX_TIME_INDEX].v.val = (void *)end_time;
    s_cert_json[JSON_SER_NUM_INDEX].v.val = (void *)"AA";
    s_cert_json[JSON_PATH_INDEX].v.val = (void *)path_name;
    s_cert_json[JSON_STATUS_INDEX].v.i = 1;
    s_cert_json[JSON_ID_INDEX].v.i = 1;

    arr = cJSON_CreateArray();
    if (NULL == arr)
    {
        LogPrint(LOG_LEVEL_ERR, MODULE_NAME, "create json arr object failed");
        return -1;
    }

    root = cJSON_CreateObject();
    if (NULL == root)
    {
        LogPrint(LOG_LEVEL_ERR, MODULE_NAME, "create json object failed");
        return -1;
    }

    cJSON_AddItemToArray(arr, root);

    for (i = 0; i < JSON_INDEX_MAX - 2; i++)
    {
        cJSON_AddStringToObject(root, (const char *)s_cert_json[i].node_name, (const char *)s_cert_json[i].v.val);
    }

    for (i = 0; i < JSON_INDEX_MAX; i++)
    {
        cJSON_AddNumberToObject(root, (const char *)s_cert_json[i].node_name, s_cert_json[i].v.i);
    }

    out = (int8_t *)cJSON_PrintUnformatted(arr);

    cJSON_Delete(arr);

    LogPrint(LOG_LEVEL_DEBUG, MODULE_NAME, "json:%s", out);

    if ((0 == g_file_set_contents((const gchar *)json_path_name, (const gchar *)out, (gssize)strlen((const char *)out), NULL)))
    {
        LogPrint(LOG_LEVEL_ERR, MODULE_NAME, "write json data to %s failed", CERT_JSON_FILENAME);
        cJSON_free(out);
        return -1;
    }

    cJSON_free(out);

    return 0;
}
