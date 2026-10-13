#ifndef MINTVM_VMKEY_H
#define MINTVM_VMKEY_H

#include "mintvm/TmpSymbol.h"
#include "mintvm/stdc.h"
#include "types.h"

namespace mintvm {

class VMKey {
public:
    VMKey(const char* ns, const char* name);
    VMKey(const VMKey& other);
    ~VMKey();

    void setNs(const char* ns);
    void setName(const char* name);

    // "void f(int)" is filed as "f(int)".
    static const char* skipReturnType(const char* declaration) {
        int paren = TmpSymbol::find(declaration, '(');
        if (paren != -1) {
            const char* p;
            int space = -1;
            for (p = declaration; p < declaration + paren; p++) {
                if (*p == ' ') {
                    space = p - declaration;
                }
            }
            if (space != -1) {
                declaration = &declaration[space + 1];
            }
        }
        return declaration;
    }

    static int compare(const char* a, const char* b) {
        return strcmp(a, b);
    }

    bool operator<(const VMKey& other) const {
        return isLess(other);
    }

    // Shorter keys sort first. The result is converted to bool once more by the caller.
    int isLess(const VMKey& other) const {
        if (mNsLength != other.mNsLength) {
            return mNsLength - other.mNsLength < 0;
        }
        if (mNameLength != other.mNameLength) {
            return mNameLength - other.mNameLength < 0;
        }
        int result = compare(mName, other.mName);
        if (result == 0) {
            return compare(mNs, other.mNs) < 0;
        }
        return result < 0;
    }

    const char* ns() const {
        return mNs;
    }

    const char* name() const {
        return mName;
    }

    VMKey moduleKey() const {
        return VMKey(mNs, "");
    }

    TmpSymbol tmpSymbol() const {
        return TmpSymbol(mNs, ".", mName);
    }

    const char* mNs;
    const char* mName;
    u16 mNsLength;
    u16 mNameLength;
};

inline VMKey::VMKey(const char* ns, const char* name)
    : mNs(0)
    , mName(0)
    , mNsLength(0)
    , mNameLength(0) {
    setNs(ns);
    setName(skipReturnType(name));
}

inline VMKey::VMKey(const VMKey& other)
    : mNs(other.mNs)
    , mName(other.mName)
    , mNsLength(other.mNsLength)
    , mNameLength(other.mNameLength) {}

inline VMKey::~VMKey() {}

inline void VMKey::setNs(const char* ns) {
    mNs = ns;
    mNsLength = strlen(ns);
}

inline void VMKey::setName(const char* name) {
    mName = name;
    mNameLength = strlen(name);
}

}  // namespace mintvm

#endif
