#ifndef MINTVM_MINTSETTING_H
#define MINTVM_MINTSETTING_H

#include "mintvm/ExplicitSingleton.h"
#include "mintvm/MintAllocator.h"
#include "types.h"

namespace mintvm {

enum MintMsgKind {
    MINT_MSG_WARNING,
    MINT_MSG_ERROR,
    MINT_MSG_FATAL,
};

class MintSetting : public ExplicitSingleton<MintSetting> {
public:
    typedef void (*HaltCallback)();
    typedef void (*MessageCallback)(MintMsgKind kind, const char* message, const char* detail);

    MintSetting();
    ~MintSetting();

    void setVMAllocator(MintAllocator::AllocFunction alloc, MintAllocator::FreeFunction free) {
        mVMAllocator.set(alloc, free);
    }

    void setRunAllocator(MintAllocator::AllocFunction alloc, MintAllocator::FreeFunction free) {
        mRunAllocator.set(alloc, free);
    }

    void verify();
    void dump();

    static void messageCallbackDefault(MintMsgKind kind, const char* message, const char* detail);

    static const char* messageKindString(MintMsgKind kind);

    MintAllocator mVMAllocator;
    MintAllocator mRunAllocator;
    HaltCallback mHaltCallback;
    u32 _1C;
    MessageCallback mMessageCallback;
};

}

#endif
