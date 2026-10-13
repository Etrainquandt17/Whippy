#ifndef G3D_MINTWRAPNATIVE_H
#define G3D_MINTWRAPNATIVE_H

#include "mintvm/MintFuncProxy.h"
#include "mintvm/VMCore.h"
#include "std/new.h"

// TODO: the same templates are in hel/mint/WrapNative.h and mintglue/WrapNative.h; they belong in one header.

template <typename T>
struct mint_wrapNative_helper {
    mint_wrapNative_helper(T value) : mValue(value) {}

    T mValue;
};

#define MINT_ARG(type, index) (*reinterpret_cast<type*>(proxy->internal_getArg_addr(index)))

inline void mintCallWrappedFunc(void (*func)(), mintvm::MintFuncProxy*) {
    func();
}

template <typename A0>
void mintCallWrappedFunc(void (*func)(A0), mintvm::MintFuncProxy* proxy) {
    func(MINT_ARG(A0, 0));
}

template <typename A0, typename A1>
void mintCallWrappedFunc(void (*func)(A0, A1), mintvm::MintFuncProxy* proxy) {
    func(MINT_ARG(A0, 0), MINT_ARG(A1, 1));
}

template <typename A0, typename A1, typename A2>
void mintCallWrappedFunc(void (*func)(A0, A1, A2), mintvm::MintFuncProxy* proxy) {
    func(MINT_ARG(A0, 0), MINT_ARG(A1, 1), MINT_ARG(A2, 2));
}

template <typename R>
void mintCallWrappedFunc(R (*func)(), mintvm::MintFuncProxy* proxy) {
    proxy->useRetVal();
    new (proxy->internal_getRet_addr()) mint_wrapNative_helper<R>(func());
}

// The wrappers of methods copy the member pointer first: one that is not inlined keeps it in its own frame.

template <typename C>
void mintCallWrappedFunc(void (C::*func)() const, mintvm::MintFuncProxy* proxy) {
    void (C::*method)() const = func;
    proxy->useThis();
    (proxy->getThis<C>().*method)();
}

template <typename C, typename A0>
void mintCallWrappedFunc(void (C::*func)(A0) const, mintvm::MintFuncProxy* proxy) {
    void (C::*method)(A0) const = func;
    proxy->useThis();
    (proxy->getThis<C>().*method)(MINT_ARG(A0, 0));
}

template <typename C, typename A0, typename A1>
void mintCallWrappedFunc(void (C::*func)(A0, A1) const, mintvm::MintFuncProxy* proxy) {
    void (C::*method)(A0, A1) const = func;
    proxy->useThis();
    (proxy->getThis<C>().*method)(MINT_ARG(A0, 0), MINT_ARG(A1, 1));
}

template <typename C, typename A0, typename A1, typename A2>
void mintCallWrappedFunc(void (C::*func)(A0, A1, A2) const, mintvm::MintFuncProxy* proxy) {
    void (C::*method)(A0, A1, A2) const = func;
    proxy->useThis();
    (proxy->getThis<C>().*method)(MINT_ARG(A0, 0), MINT_ARG(A1, 1), MINT_ARG(A2, 2));
}

template <typename C, typename R>
void mintCallWrappedFunc(R (C::*func)() const, mintvm::MintFuncProxy* proxy) {
    R (C::*method)() const = func;
    proxy->useRetVal();
    proxy->useThis();
    new (proxy->internal_getRet_addr()) mint_wrapNative_helper<R>((proxy->getThis<C>().*method)());
}

#undef MINT_ARG

// Each binding is a class local to RegisterAll, in a block of its own because overloads share a name.
#define MINT_BIND(core, add, module, declaration, name, function) \
    { \
        struct Mint_##name##_0 { \
            static void Func(mintvm::MintFuncProxy& proxy) { \
                mintCallWrappedFunc(function, &proxy); \
            } \
        }; \
        (core).add(module, declaration, Mint_##name##_0::Func); \
    }

#define MINT_NATIVE_FUNCTION(core, module, declaration, name, function) \
    MINT_BIND(core, addNativeFunction, module, declaration, name, function)

#define MINT_NATIVE_POD_METHOD(core, type, declaration, name, function) \
    MINT_BIND(core, addNativePod_Method, type, declaration, name, function)

#endif
