#include <iostream>
#include "v2x-status.h"
int CheckV2xState()
{
    std::string cmd = "cv2x-config --get-v2x-status";
    FILE *fp = popen(cmd.c_str(), "r");
    if (fp == NULL)
    {
        return -1;
    }

    char buffer[512] = {0};
    fread(buffer, sizeof(char), 512, fp);
    pclose(fp);

    //parse string
    std::string str = buffer;
    const std::string target[2] = {"rx_status=", "tx_status="};
    int i = 0;
    for (i = 0; i < 2; i++)
    {
        std::size_t found = str.find(target[i]);
        if (found == std::string::npos)
        {
            return -2;
        }
        std::string result = str.substr(found + target[i].length(), 1);
        int k = std::atoi(result.c_str());
        if (k != 1 && i == 0)
        {
            //接收不正常
            return 1;
        }
        else if (k != 1 && i == 1)
        {
            //发送不正常
            return 2;
        }
    }

    return 0;
}