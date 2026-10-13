#ifndef SCN_SUBGAME_COMMON_UTIL_ACCESSPROTECTEDSINGLETON_H
#define SCN_SUBGAME_COMMON_UTIL_ACCESSPROTECTEDSINGLETON_H

namespace scn {
namespace subgame {
namespace common {
namespace util {

template <typename T>
class AccessProtectedSingleton {
public:
    static T* object_;
};

template <typename T>
class AccessProtectedSingletonAccessor {
public:
    virtual ~AccessProtectedSingletonAccessor();
};

}
}
}
}

#endif
