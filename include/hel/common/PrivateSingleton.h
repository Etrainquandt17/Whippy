#ifndef HEL_COMMON_PRIVATESINGLETON_H
#define HEL_COMMON_PRIVATESINGLETON_H

#include "hel/common/NonCopyable.h"

namespace hel {
namespace common {

template <typename T>
class PrivateSingleton : private NonCopyable {
protected:
    PrivateSingleton() { isExist_ = true; }
    ~PrivateSingleton() { isExist_ = false; }

private:
    static bool isExist_;
};

template <typename T>
bool PrivateSingleton<T>::isExist_;

}
}

#endif
