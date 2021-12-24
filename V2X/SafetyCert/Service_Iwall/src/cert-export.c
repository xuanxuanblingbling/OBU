#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "glib.h"
#include "cJSON.h"
#include "wj_log.h"
#include "common.h"

#define CERT_JSON_FILENAME  "./cert.json"

#define JSON_ALG_NODE   "algorithm"
#define JSON_FAC_NODE   "ca"
#define JSON_CA_NAME_NODE   "class"
#define JSON_STATUS_NODE    "status"
#define JSON_EX_TIME_NODE   "expirydata"
#define JSON_ST_TIME_NODE   "startdata"
#define JSON_SER_NUM_NODE   "serialnum"

enum {
    JSON_ALG_INDEX = 0,
    JSON_FAC_INDEX,
    JSON_CA_NAME_INDEX,
    JSON_EX_TIME_INDEX,
    JSON_ST_TIME_INDEX,
    JSON_SER_NUM_INDEX,
    JSON_STATUS_INDEX,
    JSON_INDEX_MAX
};


struct json_cert {
    int8_t *node_name;
    union {
        void *val;
        uint32_t i;
    } v;
};

static struct json_cert s_cert_json[JSON_INDEX_MAX] = {
    {JSON_ALG_NODE, {"SM2"}},
    {JSON_FAC_NODE, {"datang"}},
    {JSON_CA_NAME_NODE, {"Application certificate"}},
    {JSON_EX_TIME_NODE},
    {JSON_ST_TIME_NODE},
    {JSON_SER_NUM_NODE},
    {JSON_STATUS_NODE, {1}},
};

//"algorithm": "SM2",
//        "ca": "大唐CA",
//        "class": "应用证书",
//        "expirydata": "2020-06-25 13:31",
//        "serialnum": "2CEE193C188278EA3E437573",
//        "startdata": "2019-05-09 09:22",
//        "status": 1

int32_t write_cert_json_file(const int8_t *start_time, const int8_t *end_time, const int8_t *hash)
{
    cJSON *root = NULL;
    int8_t *out = NULL;
    int32_t i = 0;

    LogPrint(LOG_LEVEL_DEBUG, MODULE_NAME, "start:%s, end:%s", start_time, end_time);
    s_cert_json[JSON_ST_TIME_INDEX].v.val = (void *)start_time;
    s_cert_json[JSON_EX_TIME_INDEX].v.val = (void *)end_time;
    s_cert_json[JSON_SER_NUM_INDEX].v.val = (void *)hash;

    root =cJSON_CreateObject();
    if (NULL == root)
    {
        LogPrint(LOG_LEVEL_ERR, MODULE_NAME, "create json object failed");
        return -1;
    }

    for (i = 0; i < JSON_INDEX_MAX - 1; i++)
    {
        cJSON_AddStringToObject(root, s_cert_json[i].node_name, (int8_t *)s_cert_json[i].v.val);
    }

    cJSON_AddNumberToObject(root, s_cert_json[i].node_name, s_cert_json[i].v.i);
    out = cJSON_PrintUnformatted(root);

    cJSON_Delete(root);

    LogPrint(LOG_LEVEL_INFO, MODULE_NAME, "json:%s", out);

    if(0 == g_file_set_contents(CERT_JSON_FILENAME, out, strlen(out), NULL))
    {
        LogPrint(LOG_LEVEL_ERR, MODULE_NAME, "write json data to %s failed", CERT_JSON_FILENAME);
        cJSON_free(out);
        return -1;
    }

    cJSON_free(out);

    return 0;
}
