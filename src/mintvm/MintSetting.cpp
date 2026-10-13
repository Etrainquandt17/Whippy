#include "mintvm/MintSetting.h"

#include "mintvm/stdc.h"

namespace mintvm {

MintSetting::MintSetting()
    : mHaltCallback(0)
    , _1C(0x40)
    , mMessageCallback(messageCallbackDefault) {
    SetInstance(*this);
}

MintSetting::~MintSetting() {
    UnsetInstance();
}

void MintSetting::verify() {
    mVMAllocator.verify();
    mRunAllocator.verify();
    MINT_ASSERT("MintSetting.cpp", 49, mHaltCallback);
}

void MintSetting::dump() {
    printf("--- MintSetting ---\n");
    printf("[vmAllocator]  alloc: %x, free: %x\n", mVMAllocator.mAlloc, mVMAllocator.mFree);
    printf("[runAllocator] alloc: %x, free: %x\n", mRunAllocator.mAlloc, mRunAllocator.mFree);
}

void MintSetting::messageCallbackDefault(MintMsgKind kind, const char* message, const char* detail) {
    const char* kindString = messageKindString(kind);
    printf("*************************************************\n");
    printf("* [Mint][%s] %s\n", kindString, message);
    printf("* ----------------------\n");
    printf("* %s\n", detail);
    printf("*************************************************\n");
}

const char* MintSetting::messageKindString(MintMsgKind kind) {
    static const char* table[] = {"Warning", "Error", "Fatal"};
    return table[kind];
}

}
