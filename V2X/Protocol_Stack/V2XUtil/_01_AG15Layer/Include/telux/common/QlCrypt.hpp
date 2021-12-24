#ifndef QLCRYPT_HPP
#define QLCRYPT_HPP

namespace telux {
namespace common {

class QlCrypt {
public:
  QlCrypt();
  ~QlCrypt();

  int EncryptSha512(char* plain_str, const char *salt_code, char* encrypted_str, int encrypted_buff_len); 
  char* GenerateKey(char* key, int len);
};

}
}
#endif //QLCRYPT_HPP


