#ifndef HEL_COMMON_NONCOPYABLE_H
#define HEL_COMMON_NONCOPYABLE_H

namespace hel {
namespace common {

class NonCopyable {
protected:
    NonCopyable() {}
    // The original link folded this into hel::geo::Rect::~Rect, which is what callers name.
    ~NonCopyable();

private:
    NonCopyable(const NonCopyable&);
    NonCopyable& operator=(const NonCopyable&);
};

}}  // namespace hel::common

#endif
