#ifndef UTIL_STATECHANGER_H
#define UTIL_STATECHANGER_H

#include "hel/common/NonCopyable.h"
#include "std/new.h"
#include "types.h"
#include "util/IStateChanger.h"

namespace util {

class IState;
class IStateCallback;

// TODO: stands in for something not understood yet. setNextState takes its arguments by value (its symbols
// say so), and the original passes a hel::math::Vector3 temporary to it in place and copies it word by word
// only for the factory's constructor. This compiler makes one more copy for setNextState's own parameter.
// A call that names the argument type as a const reference avoids that copy; the factory holds the value.
template <typename T>
struct StateArgValue {
    typedef T Type;
};

template <typename T>
struct StateArgValue<const T&> {
    typedef T Type;
};

// TODO: the factories' constructors take their arguments by value: an out-of-line setNextState copies a
// description twice. Where a unit passes a Vector3 temporary and all of it is expanded, the original copies the
// vector once and leaves the second copy's slot unused. Only references give that here, so such a unit defines
// UTIL_STATECHANGER_FACTORY_ARGUMENTS_BY_REFERENCE ahead of its includes.
#ifdef UTIL_STATECHANGER_FACTORY_ARGUMENTS_BY_REFERENCE
#define UTIL_STATEFACTORY_ARGUMENT(T) const T&
#else
#define UTIL_STATEFACTORY_ARGUMENT(T) T
#endif

template <typename B>
class StateFactory {
public:
    StateFactory(void* buffer) : mBuffer(buffer) {}
    // Pure but defined: the vtable's slot is zero in the original.
    virtual ~StateFactory() = 0;
    virtual B* create() = 0;

protected:
    void* mBuffer;
};

template <typename B>
inline StateFactory<B>::~StateFactory() {}

template <typename B, typename S, typename A1>
class StateFactoryArg1 : public StateFactory<B> {
public:
    StateFactoryArg1(void* buffer, UTIL_STATEFACTORY_ARGUMENT(A1) a1) : StateFactory<B>(buffer), mArg1(a1) {}
    virtual B* create() { return new (this->mBuffer) S(mArg1); }

private:
    A1 mArg1;
};

template <typename B, typename S, typename A1, typename A2>
class StateFactoryArg2 : public StateFactory<B> {
public:
    StateFactoryArg2(void* buffer, UTIL_STATEFACTORY_ARGUMENT(A1) a1, UTIL_STATEFACTORY_ARGUMENT(A2) a2) : StateFactory<B>(buffer), mArg1(a1), mArg2(a2) {}
    virtual B* create() { return new (this->mBuffer) S(mArg1, mArg2); }

private:
    A1 mArg1;
    A2 mArg2;
};

template <typename B, typename S, typename A1, typename A2, typename A3>
class StateFactoryArg3 : public StateFactory<B> {
public:
    StateFactoryArg3(void* buffer, UTIL_STATEFACTORY_ARGUMENT(A1) a1, UTIL_STATEFACTORY_ARGUMENT(A2) a2, UTIL_STATEFACTORY_ARGUMENT(A3) a3) : StateFactory<B>(buffer), mArg1(a1), mArg2(a2), mArg3(a3) {}
    virtual B* create() { return new (this->mBuffer) S(mArg1, mArg2, mArg3); }

private:
    A1 mArg1;
    A2 mArg2;
    A3 mArg3;
};

template <typename B, typename S, typename A1, typename A2, typename A3, typename A4>
class StateFactoryArg4 : public StateFactory<B> {
public:
    StateFactoryArg4(void* buffer, UTIL_STATEFACTORY_ARGUMENT(A1) a1, UTIL_STATEFACTORY_ARGUMENT(A2) a2, UTIL_STATEFACTORY_ARGUMENT(A3) a3, UTIL_STATEFACTORY_ARGUMENT(A4) a4)
        : StateFactory<B>(buffer), mArg1(a1), mArg2(a2), mArg3(a3), mArg4(a4) {}
    virtual B* create() { return new (this->mBuffer) S(mArg1, mArg2, mArg3, mArg4); }

private:
    A1 mArg1;
    A2 mArg2;
    A3 mArg3;
    A4 mArg4;
};

template <typename B, typename S, typename A1, typename A2, typename A3, typename A4, typename A5>
class StateFactoryArg5 : public StateFactory<B> {
public:
    StateFactoryArg5(void* buffer, UTIL_STATEFACTORY_ARGUMENT(A1) a1, UTIL_STATEFACTORY_ARGUMENT(A2) a2, UTIL_STATEFACTORY_ARGUMENT(A3) a3, UTIL_STATEFACTORY_ARGUMENT(A4) a4, UTIL_STATEFACTORY_ARGUMENT(A5) a5)
        : StateFactory<B>(buffer), mArg1(a1), mArg2(a2), mArg3(a3), mArg4(a4), mArg5(a5) {}
    virtual B* create() { return new (this->mBuffer) S(mArg1, mArg2, mArg3, mArg4, mArg5); }

private:
    A1 mArg1;
    A2 mArg2;
    A3 mArg3;
    A4 mArg4;
    A5 mArg5;
};

class StateChangerBase : public IStateChanger {
public:
    StateChangerBase(IStateCallback& callback);
    virtual ~StateChangerBase();

    void reset();
    void changeStateIfPossible();
    bool hasNextState() const;
    IState& currentStateRef();
    const IState& currentStateRef() const;

protected:
    void changeState();
    void releaseCurrentState();
    void releaseNextStateFactory();
    void onSetNextStateFactory();

    IStateCallback* mCallback;
    IState* mState;
    StateFactory<IState>* mNextStateFactory;
    u8 mFactoryBuffer[0x80];
};

template <typename T, int N>
class StateChanger : public StateChangerBase {
public:
    StateChanger(IStateCallback& callback) : StateChangerBase(callback), mStateBuffer() {}
    ~StateChanger();

    template <typename S, typename A1>
    void setNextState(A1 a1) {
        typedef typename StateArgValue<A1>::Type V1;
        onSetNextStateFactory();
        mNextStateFactory = new (mFactoryBuffer) StateFactoryArg1<IState, S, V1>(mStateBuffer, a1);
    }

    template <typename S, typename A1, typename A2>
    void setNextState(A1 a1, A2 a2) {
        typedef typename StateArgValue<A1>::Type V1;
        typedef typename StateArgValue<A2>::Type V2;
        onSetNextStateFactory();
        mNextStateFactory = new (mFactoryBuffer) StateFactoryArg2<IState, S, V1, V2>(mStateBuffer, a1, a2);
    }

    template <typename S, typename A1, typename A2, typename A3>
    void setNextState(A1 a1, A2 a2, A3 a3) {
        typedef typename StateArgValue<A1>::Type V1;
        typedef typename StateArgValue<A2>::Type V2;
        typedef typename StateArgValue<A3>::Type V3;
        onSetNextStateFactory();
        mNextStateFactory = new (mFactoryBuffer) StateFactoryArg3<IState, S, V1, V2, V3>(mStateBuffer, a1, a2, a3);
    }

    template <typename S, typename A1, typename A2, typename A3, typename A4>
    void setNextState(A1 a1, A2 a2, A3 a3, A4 a4) {
        typedef typename StateArgValue<A1>::Type V1;
        typedef typename StateArgValue<A2>::Type V2;
        typedef typename StateArgValue<A3>::Type V3;
        typedef typename StateArgValue<A4>::Type V4;
        onSetNextStateFactory();
        mNextStateFactory = new (mFactoryBuffer) StateFactoryArg4<IState, S, V1, V2, V3, V4>(mStateBuffer, a1, a2, a3, a4);
    }

    template <typename S, typename A1, typename A2, typename A3, typename A4, typename A5>
    void setNextState(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5) {
        typedef typename StateArgValue<A1>::Type V1;
        typedef typename StateArgValue<A2>::Type V2;
        typedef typename StateArgValue<A3>::Type V3;
        typedef typename StateArgValue<A4>::Type V4;
        typedef typename StateArgValue<A5>::Type V5;
        onSetNextStateFactory();
        mNextStateFactory =
            new (mFactoryBuffer) StateFactoryArg5<IState, S, V1, V2, V3, V4, V5>(mStateBuffer, a1, a2, a3, a4, a5);
    }

private:
    u8 mStateBuffer[N];
};

}

#endif
