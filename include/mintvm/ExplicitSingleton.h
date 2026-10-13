#ifndef MINTVM_EXPLICITSINGLETON_H
#define MINTVM_EXPLICITSINGLETON_H

#include "mintvm/MintAssert.h"
#include "mintvm/NonCopyable.h"

namespace mintvm {

template <class T>
class ExplicitSingleton : public NonCopyable {
public:
    static bool IsExist() {
        return object_ != 0;
    }

    static T* Instance() {
        MINT_ASSERT("ExplicitSingleton.hpp", 33, object_);
        return object_;
    }

    static void SetInstance(T& object) {
        MINT_ASSERT("ExplicitSingleton.hpp", 51, !IsExist());
        object_ = &object;
    }

    static void UnsetInstance() {
        MINT_ASSERT("ExplicitSingleton.hpp", 62, IsExist());
        object_ = 0;
    }

    ExplicitSingleton() {
        MINT_ASSERT("ExplicitSingleton.hpp", 70, !object_);
    }

    ~ExplicitSingleton() {
        MINT_ASSERT("ExplicitSingleton.hpp", 76, !IsExist());
    }

private:
    static T* object_;
};

template <class T>
T* ExplicitSingleton<T>::object_;

}

#endif
