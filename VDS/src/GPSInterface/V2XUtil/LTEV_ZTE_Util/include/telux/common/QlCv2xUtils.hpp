#ifndef QLCV2XUTILS_HPP
#define QLCV2XUTILS_HPP
#include <memory>
#include "qmi/QlApQmiClient.hpp"
#include "QlCrypt.hpp"

namespace telux {
namespace common {

class QlCv2xUtils {
public:
  static QlCv2xUtils &getInstance();
  bool Auth();
  ~QlCv2xUtils();
  
private:
  QlCv2xUtils();
  QlCv2xUtils(const QlCv2xUtils &) = delete;
  QlCv2xUtils &operator=(const QlCv2xUtils &) = delete;

  bool authed;
  QlCrypt crypt;
  std::shared_ptr<telux::qmi::QlApQmiClient> qlApQmiClient_ = nullptr;
};

}
}
#endif //QLCV2XUTILS_HPP

