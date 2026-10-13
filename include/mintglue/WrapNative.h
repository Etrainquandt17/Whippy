#ifndef MINTGLUE_WRAPNATIVE_H
#define MINTGLUE_WRAPNATIVE_H

#include "mintvm/MintFuncProxy.h"
#include "mintvm/VMCore.h"
#include "std/new.h"
#include "types.h"

// Each binding is a class local to the unit's AddOn, in a block of its own because overloads share a name.
#define MINT_NATIVE_FUNCTION(core, module, declaration, name, function) \
    { \
        struct Mint_##name##_0 { \
            static void Func(mintvm::MintFuncProxy& proxy) { \
                mintCallWrappedFunc(function, &proxy); \
            } \
        }; \
        (core).addNativeFunction(module, declaration, Mint_##name##_0::Func); \
    }

#define MINT_NATIVE_POD_METHOD(core, type, declaration, name, function) \
    { \
        struct Mint_##name##_0 { \
            static void Func(mintvm::MintFuncProxy& proxy) { \
                mintCallWrappedFunc(function, &proxy); \
            } \
        }; \
        (core).addNativePod_Method(type, declaration, Mint_##name##_0::Func); \
    }

// After the declaration come the class and the types of the constructor's parameters.
#define MINT_NATIVE_POD_CTOR(core, type, declaration, ...) \
    { \
        struct Mint_Ctor { \
            static void Func(mintvm::MintFuncProxy& proxy) { \
                mintCallWrappedCtor<__VA_ARGS__>(&proxy); \
            } \
        }; \
        (core).addNativePod_Method(type, declaration, Mint_Ctor::Func); \
    }

#define MINT_OFFSETOF(type, member) (reinterpret_cast<unsigned long>(&reinterpret_cast<type*>(0)->member))

template <typename T>
struct mint_wrapNative_helper {
    mint_wrapNative_helper(T value) : mValue(value) {}

    T mValue;
};

// With a reference for T the member is a reference, and reading it follows the pointer in the slot.
#define MINT_ARG(n) (reinterpret_cast<mint_wrapNative_helper<A##n>*>(proxy->internal_getArg_addr(n))->mValue)

inline void mintCallWrappedFunc(void (*func)(), mintvm::MintFuncProxy*) {
    func();
}

// TODO: name. Only this wrapper reads its argument through a function of its own: where it is expanded
// whole into a binding, the index and the register set get each other's registers without it.
template <typename T>
inline T mintArg(mintvm::MintFuncProxy* proxy, unsigned int n) {
    return reinterpret_cast<mint_wrapNative_helper<T>*>(proxy->internal_getArg_addr(n))->mValue;
}

template <typename A0>
void mintCallWrappedFunc(void (*func)(A0), mintvm::MintFuncProxy* proxy) {
    func(mintArg<A0>(proxy, 0));
}

template <typename A0, typename A1>
void mintCallWrappedFunc(void (*func)(A0, A1), mintvm::MintFuncProxy* proxy) {
    func(MINT_ARG(0), MINT_ARG(1));
}

template <typename A0, typename A1, typename A2>
void mintCallWrappedFunc(void (*func)(A0, A1, A2), mintvm::MintFuncProxy* proxy) {
    func(MINT_ARG(0), MINT_ARG(1), MINT_ARG(2));
}

template <typename A0, typename A1, typename A2, typename A3>
void mintCallWrappedFunc(void (*func)(A0, A1, A2, A3), mintvm::MintFuncProxy* proxy) {
    func(MINT_ARG(0), MINT_ARG(1), MINT_ARG(2), MINT_ARG(3));
}

template <typename A0, typename A1, typename A2, typename A3, typename A4>
void mintCallWrappedFunc(void (*func)(A0, A1, A2, A3, A4), mintvm::MintFuncProxy* proxy) {
    func(MINT_ARG(0), MINT_ARG(1), MINT_ARG(2), MINT_ARG(3), MINT_ARG(4));
}

template <typename A0, typename A1, typename A2, typename A3, typename A4, typename A5>
void mintCallWrappedFunc(void (*func)(A0, A1, A2, A3, A4, A5), mintvm::MintFuncProxy* proxy) {
    func(MINT_ARG(0), MINT_ARG(1), MINT_ARG(2), MINT_ARG(3), MINT_ARG(4), MINT_ARG(5));
}

template <typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
void mintCallWrappedFunc(void (*func)(A0, A1, A2, A3, A4, A5, A6), mintvm::MintFuncProxy* proxy) {
    func(MINT_ARG(0), MINT_ARG(1), MINT_ARG(2), MINT_ARG(3), MINT_ARG(4), MINT_ARG(5), MINT_ARG(6));
}

template <typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7>
void mintCallWrappedFunc(void (*func)(A0, A1, A2, A3, A4, A5, A6, A7), mintvm::MintFuncProxy* proxy) {
    func(MINT_ARG(0), MINT_ARG(1), MINT_ARG(2), MINT_ARG(3), MINT_ARG(4), MINT_ARG(5), MINT_ARG(6), MINT_ARG(7));
}

template <typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8>
void mintCallWrappedFunc(void (*func)(A0, A1, A2, A3, A4, A5, A6, A7, A8), mintvm::MintFuncProxy* proxy) {
    func(MINT_ARG(0), MINT_ARG(1), MINT_ARG(2), MINT_ARG(3), MINT_ARG(4), MINT_ARG(5), MINT_ARG(6), MINT_ARG(7), MINT_ARG(8));
}

template <typename R>
void mintCallWrappedFunc(R (*func)(), mintvm::MintFuncProxy* proxy) {
    proxy->useRetVal();
    new (proxy->internal_getRet_addr()) mint_wrapNative_helper<R>(func());
}

template <typename R, typename A0>
void mintCallWrappedFunc(R (*func)(A0), mintvm::MintFuncProxy* proxy) {
    proxy->useRetVal();
    new (proxy->internal_getRet_addr()) mint_wrapNative_helper<R>(func(MINT_ARG(0)));
}

template <typename R, typename A0, typename A1>
void mintCallWrappedFunc(R (*func)(A0, A1), mintvm::MintFuncProxy* proxy) {
    proxy->useRetVal();
    new (proxy->internal_getRet_addr()) mint_wrapNative_helper<R>(func(MINT_ARG(0), MINT_ARG(1)));
}

template <typename R, typename A0, typename A1, typename A2>
void mintCallWrappedFunc(R (*func)(A0, A1, A2), mintvm::MintFuncProxy* proxy) {
    proxy->useRetVal();
    new (proxy->internal_getRet_addr()) mint_wrapNative_helper<R>(func(MINT_ARG(0), MINT_ARG(1), MINT_ARG(2)));
}

template <typename R, typename A0, typename A1, typename A2, typename A3>
void mintCallWrappedFunc(R (*func)(A0, A1, A2, A3), mintvm::MintFuncProxy* proxy) {
    proxy->useRetVal();
    new (proxy->internal_getRet_addr()) mint_wrapNative_helper<R>(func(MINT_ARG(0), MINT_ARG(1), MINT_ARG(2), MINT_ARG(3)));
}

template <typename C>
void mintCallWrappedFunc(void (C::*func)(), mintvm::MintFuncProxy* proxy) {
    void (C::*copy)() = func;
    proxy->useThis();
    (proxy->getThis<C>().*copy)();
}

template <typename C, typename A0>
void mintCallWrappedFunc(void (C::*func)(A0), mintvm::MintFuncProxy* proxy) {
    void (C::*copy)(A0) = func;
    proxy->useThis();
    (proxy->getThis<C>().*copy)(MINT_ARG(0));
}

template <typename C, typename A0, typename A1>
void mintCallWrappedFunc(void (C::*func)(A0, A1), mintvm::MintFuncProxy* proxy) {
    void (C::*copy)(A0, A1) = func;
    proxy->useThis();
    (proxy->getThis<C>().*copy)(MINT_ARG(0), MINT_ARG(1));
}

template <typename C, typename A0, typename A1, typename A2>
void mintCallWrappedFunc(void (C::*func)(A0, A1, A2), mintvm::MintFuncProxy* proxy) {
    void (C::*copy)(A0, A1, A2) = func;
    proxy->useThis();
    (proxy->getThis<C>().*copy)(MINT_ARG(0), MINT_ARG(1), MINT_ARG(2));
}

template <typename C, typename A0>
void mintCallWrappedFunc(void (C::*func)(A0) const, mintvm::MintFuncProxy* proxy) {
    void (C::*copy)(A0) const = func;
    proxy->useThis();
    (proxy->getThis<C>().*copy)(MINT_ARG(0));
}

template <typename C>
void mintCallWrappedFunc(void (C::*func)() const, mintvm::MintFuncProxy* proxy) {
    void (C::*copy)() const = func;
    proxy->useThis();
    (proxy->getThis<C>().*copy)();
}

template <typename C, typename A0, typename A1>
void mintCallWrappedFunc(void (C::*func)(A0, A1) const, mintvm::MintFuncProxy* proxy) {
    void (C::*copy)(A0, A1) const = func;
    proxy->useThis();
    (proxy->getThis<C>().*copy)(MINT_ARG(0), MINT_ARG(1));
}

template <typename C, typename A0, typename A1, typename A2>
void mintCallWrappedFunc(void (C::*func)(A0, A1, A2) const, mintvm::MintFuncProxy* proxy) {
    void (C::*copy)(A0, A1, A2) const = func;
    proxy->useThis();
    (proxy->getThis<C>().*copy)(MINT_ARG(0), MINT_ARG(1), MINT_ARG(2));
}

template <typename C, typename A0, typename A1, typename A2, typename A3>
void mintCallWrappedFunc(void (C::*func)(A0, A1, A2, A3) const, mintvm::MintFuncProxy* proxy) {
    void (C::*copy)(A0, A1, A2, A3) const = func;
    proxy->useThis();
    (proxy->getThis<C>().*copy)(MINT_ARG(0), MINT_ARG(1), MINT_ARG(2), MINT_ARG(3));
}

template <typename C, typename A0, typename A1, typename A2, typename A3, typename A4>
void mintCallWrappedFunc(void (C::*func)(A0, A1, A2, A3, A4) const, mintvm::MintFuncProxy* proxy) {
    void (C::*copy)(A0, A1, A2, A3, A4) const = func;
    proxy->useThis();
    (proxy->getThis<C>().*copy)(MINT_ARG(0), MINT_ARG(1), MINT_ARG(2), MINT_ARG(3), MINT_ARG(4));
}

// TODO: the name of the constructor wrapper is a guess; every use is inlined.
template <typename C, typename A0, typename A1>
inline void mintCallWrappedCtor(mintvm::MintFuncProxy* proxy) {
    proxy->useThis();
    new (&proxy->getThis<C>()) C(MINT_ARG(0), MINT_ARG(1));
}

template <typename C, typename A0, typename A1, typename A2>
inline void mintCallWrappedCtor(mintvm::MintFuncProxy* proxy) {
    proxy->useThis();
    new (&proxy->getThis<C>()) C(MINT_ARG(0), MINT_ARG(1), MINT_ARG(2));
}

template <typename C, typename R>
void mintCallWrappedFunc(R (C::*func)(), mintvm::MintFuncProxy* proxy) {
    R (C::*copy)() = func;
    proxy->useRetVal();
    proxy->useThis();
    new (proxy->internal_getRet_addr()) mint_wrapNative_helper<R>((proxy->getThis<C>().*copy)());
}

template <typename C, typename R>
void mintCallWrappedFunc(R (C::*func)() const, mintvm::MintFuncProxy* proxy) {
    R (C::*copy)() const = func;
    proxy->useRetVal();
    proxy->useThis();
    new (proxy->internal_getRet_addr()) mint_wrapNative_helper<R>((proxy->getThis<C>().*copy)());
}

template <typename C, typename R, typename A0>
void mintCallWrappedFunc(R (C::*func)(A0) const, mintvm::MintFuncProxy* proxy) {
    R (C::*copy)(A0) const = func;
    proxy->useRetVal();
    proxy->useThis();
    new (proxy->internal_getRet_addr()) mint_wrapNative_helper<R>((proxy->getThis<C>().*copy)(MINT_ARG(0)));
}

#endif
