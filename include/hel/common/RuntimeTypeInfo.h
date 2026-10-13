#ifndef HEL_COMMON_RUNTIMETYPEINFO_H
#define HEL_COMMON_RUNTIMETYPEINFO_H

namespace hel {
namespace common {

class RuntimeTypeInfo {
public:
    RuntimeTypeInfo(const RuntimeTypeInfo* parent, const char* name);

    // TODO: inline in the original; the body is in RuntimeTypeInfoInline.h until seq/SequenceWMapRoot.cpp can take it.
    bool isDerivedFrom(const RuntimeTypeInfo& other) const;

    static const char* NoName() { return "no name class"; }

private:
    const RuntimeTypeInfo* mParent;
    const char* mName;
};

// TODO: define this. Every unit that uses it has its own copy, with a static
// RuntimeTypeInfo whose parent is the info of T's base class.
template <typename T>
const RuntimeTypeInfo& RuntimeTypeInfoImpl();

namespace detail {

// TODO: how the original gets from T* to the info of T is not known.
template <typename T>
inline const RuntimeTypeInfo& TypeInfoFromPtr(T*) {
    return RuntimeTypeInfoImpl<T>();
}

}

template <typename T, typename U>
inline T DynamicCast(U* ptr) {
    const RuntimeTypeInfo& info = detail::TypeInfoFromPtr(static_cast<T>(0));
    if (ptr != 0 && ptr->GetRuntimeTypeInfo().isDerivedFrom(info)) {
        return static_cast<T>(ptr);
    }
    return 0;
}

template <typename T, typename U>
inline T& DynamicCastToRef(U* ptr) {
    return *DynamicCast<T*, U>(ptr);
}

}}  // namespace hel::common

#endif
