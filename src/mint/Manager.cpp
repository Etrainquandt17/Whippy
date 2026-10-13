#include "mint/Manager.h"

#include "revolution/os/OSError.h"

namespace mint {

namespace {

void t_Halt() {
    OSPanic("Manager.cpp", 19, "Halt on Mint.");
}

void t_MessageCallBack(mintvm::MintMsgKind, const char*, const char*) {}

}

Manager::Manager() : mSetting(), mHeap(mSetting), mArchive() {
    mSetting.mHaltCallback = t_Halt;
    mSetting.mMessageCallback = t_MessageCallBack;
    mSetting.verify();
}

Manager::~Manager() {}

const ScriptArchive& Manager::scriptArchive() const {
    return mArchive;
}

}
