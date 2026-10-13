#include "util/StateChanger.h"

#include "util/IState.h"
#include "util/IStateCallback.h"

namespace util {

StateChangerBase::StateChangerBase(IStateCallback& callback)
    : mCallback(&callback)
    , mState(0)
    , mNextStateFactory(0)
    , mFactoryBuffer() {}

StateChangerBase::~StateChangerBase() {
    reset();
}

void StateChangerBase::changeStateIfPossible() {
    if (hasNextState()) {
        changeState();
    }
}

bool StateChangerBase::hasNextState() const {
    return mNextStateFactory != 0;
}

IState& StateChangerBase::currentStateRef() {
    return *mState;
}

const IState& StateChangerBase::currentStateRef() const {
    return *mState;
}

void StateChangerBase::changeState() {
    if (mState != 0) {
        releaseCurrentState();
    }
    mCallback->onStateChanged(*this);
    mState = mNextStateFactory->create();
    releaseNextStateFactory();
}

void StateChangerBase::reset() {
    if (mNextStateFactory != 0) {
        releaseNextStateFactory();
    }
    if (mState != 0) {
        releaseCurrentState();
    }
}

void StateChangerBase::releaseCurrentState() {
    mState->~IState();
    mState = 0;
}

void StateChangerBase::releaseNextStateFactory() {
    mNextStateFactory->~StateFactory<IState>();
    mNextStateFactory = 0;
}

void StateChangerBase::onSetNextStateFactory() {
    if (mNextStateFactory == 0) {
        return;
    }
    releaseNextStateFactory();
}

}  // namespace util
