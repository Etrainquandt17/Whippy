#include "scn/step/spstop/Manager.h"

namespace scn {
namespace step {
namespace spstop {

Manager::Manager() : mIsRequested(false), mIsStopped(false) {}

Manager::~Manager() {}

bool Manager::isStopped() const {
    return mIsStopped;
}

void Manager::requestSuperStop() {
    mIsRequested = true;
}

void Manager::unrequestSuperStop() {
    mIsRequested = false;
}

void Manager::update() {
    if (mIsRequested != mIsStopped) {
        mIsStopped = mIsRequested;
        if (mIsRequested) {
            for (u32 i = 0; i < mReceivers.count(); i++) {
                mReceivers[i]->onSuperStopStarted(*this);
            }
        } else {
            for (u32 i = mReceivers.count(); i != 0; i--) {
                mReceivers[i - 1]->onSuperStopFinished(*this);
            }
        }
    }
}

void Manager::registerEventReceiver(IEventReceiver& receiver) {
    mReceivers.add(&receiver);
    if (mIsStopped) {
        receiver.onSuperStopStarted(*this);
    }
}

void Manager::unregisterEventReceiver(IEventReceiver& receiver) {
    mReceivers.erase(mReceivers.find(&receiver));
}

}}}  // namespace scn::step::spstop
