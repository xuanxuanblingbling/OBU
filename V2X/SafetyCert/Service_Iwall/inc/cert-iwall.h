#ifndef CERT_IWALL_H
#define CERT_IWALL_H


extern int32_t ImportCertificate();
extern int32_t Apply_PseudonymCert();

extern int Get_ImportCertStatus(char *FileName);
extern int Set_ImportCertStatus(char *FileName, int status);
#endif