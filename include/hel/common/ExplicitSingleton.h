#ifndef HEL_COMMON_EXPLICITSINGLETON_H
#define HEL_COMMON_EXPLICITSINGLETON_H

#include "hel/common/NonCopyable.h"

namespace hel {
namespace common {

// The object registers itself in the body of its constructor and takes itself out in the body of its
// destructor, which is why the store comes after the members are built and ahead of their destructors.
// TODO: Object, SetInstance and UnsetInstance are always expanded. The names are guesses, the last two after
// mintvm::ExplicitSingleton.
template <typename T>
class ExplicitSingleton : private NonCopyable {
public:
    static bool IsExist() { return object_ != 0; }

    // Two calls in one expression read the pointer once, which two uses of object_ do not
    // (file::FileManager's constructor).
    static T& Object() { return *object_; }

    static void SetInstance(T& object) { object_ = &object; }
    static void UnsetInstance() { object_ = 0; }

    static T* object_;

protected:
    ExplicitSingleton() {}
    ~ExplicitSingleton() {}
};

template <typename T>
T* ExplicitSingleton<T>::object_;

}}  // namespace hel::common

#endif
