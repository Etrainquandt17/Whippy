#ifndef MINTVM_NONCOPYABLE_H
#define MINTVM_NONCOPYABLE_H

namespace mintvm {

class NonCopyable {
public:
    NonCopyable() {}
    ~NonCopyable() {}

private:
    NonCopyable(const NonCopyable&);
    NonCopyable& operator=(const NonCopyable&);
};

}  // namespace mintvm

#endif
