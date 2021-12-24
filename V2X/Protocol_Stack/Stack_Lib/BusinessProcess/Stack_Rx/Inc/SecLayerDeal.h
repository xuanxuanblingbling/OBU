#ifndef SECLAYER_SECLAYER_DEAL_H_
#define SECLAYER_SECLAYER_DEAL_H_

#ifdef __cplusplus
extern "C"
{
#endif

    void *SecLayer_Recv_ThreadProc(void *pArg);
    void *SecLayer_Recv_ThreadProcFunc(void *pArg);

#ifdef __cplusplus
}
#endif

#endif /* SECLAYER_SECLAYER_DEAL_H_ */
