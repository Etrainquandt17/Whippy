#include "hel/mint/AddOnMathDirection3.h"

#include "hel/math/Direction3.h"
#include "hel/mint/AddOnMathVector3.h"
#include "hel/mint/WrapNative.h"

namespace hel {
namespace mint {

namespace {

hel::math::Direction3& t_obj() {
    static hel::math::Direction3 obj;
    return obj;
}

}

namespace AddOnMathDirection3 {

void RegisterAll(mintvm::VMCore& core) {
    core.addNativePod("HEL.Math.Direction3", sizeof(hel::math::Direction3));
    core.addNativePod_Property("HEL.Math.Direction3", "left", MINT_OFFSETOF(hel::math::Direction3, mLeft));
    core.addNativePod_Property("HEL.Math.Direction3", "up", MINT_OFFSETOF(hel::math::Direction3, mUp));
    core.addNativePod_Property("HEL.Math.Direction3", "front", MINT_OFFSETOF(hel::math::Direction3, mFront));
    MINT_NATIVE_POD_CTOR(
        core, "HEL.Math.Direction3", "void this(const ref HEL.Math.Vector3,const ref HEL.Math.Vector3,const ref HEL.Math.Vector3)",
        hel::math::Direction3, const hel::math::Vector3&, const hel::math::Vector3&, const hel::math::Vector3&
    );
    MINT_NATIVE_POD_METHOD(core, "HEL.Math.Direction3", "void restructFrontUp()", restructFrontUp, &hel::math::Direction3::restructFrontUp);
    MINT_NATIVE_POD_METHOD(core, "HEL.Math.Direction3", "void restructFrontLeft()", restructFrontLeft, &hel::math::Direction3::restructFrontLeft);
    MINT_NATIVE_POD_METHOD(core, "HEL.Math.Direction3", "void restructUpFront()", restructUpFront, &hel::math::Direction3::restructUpFront);
    MINT_NATIVE_POD_METHOD(core, "HEL.Math.Direction3", "void restructUpLeft()", restructUpLeft, &hel::math::Direction3::restructUpLeft);
    MINT_NATIVE_POD_METHOD(core, "HEL.Math.Direction3", "void restructLeftFront()", restructLeftFront, &hel::math::Direction3::restructLeftFront);
    MINT_NATIVE_POD_METHOD(core, "HEL.Math.Direction3", "void restructLeftUp()", restructLeftUp, &hel::math::Direction3::restructLeftUp);
    MINT_NATIVE_FUNCTION(core, "HEL.Math.Direction3", "void LoadLeft()", LoadLeft, LoadLeft);
    MINT_NATIVE_FUNCTION(core, "HEL.Math.Direction3", "void LoadUp()", LoadUp, LoadUp);
    MINT_NATIVE_FUNCTION(core, "HEL.Math.Direction3", "void LoadFront()", LoadFront, LoadFront);
    MINT_NATIVE_FUNCTION(core, "HEL.Math.Direction3", "void StoreLeft()", StoreLeft, StoreLeft);
    MINT_NATIVE_FUNCTION(core, "HEL.Math.Direction3", "void StoreUp()", StoreUp, StoreUp);
    MINT_NATIVE_FUNCTION(core, "HEL.Math.Direction3", "void StoreFront()", StoreFront, StoreFront);
    MINT_NATIVE_FUNCTION(core, "HEL.Math.Direction3", "void SetBasis()", SetBasis, SetBasis);
    MINT_NATIVE_FUNCTION(core, "HEL.Math.Direction3", "void SetFrontToRight()", SetFrontToRight, SetFrontToRight);
    MINT_NATIVE_FUNCTION(core, "HEL.Math.Direction3", "void SetFrontToLeft()", SetFrontToLeft, SetFrontToLeft);
    MINT_NATIVE_FUNCTION(core, "HEL.Math.Direction3", "void RestructFrontUp()", RestructFrontUp, RestructFrontUp);
    MINT_NATIVE_FUNCTION(core, "HEL.Math.Direction3", "void RestructFrontLeft()", RestructFrontLeft, RestructFrontLeft);
    MINT_NATIVE_FUNCTION(core, "HEL.Math.Direction3", "void RestructUpFront()", RestructUpFront, RestructUpFront);
    MINT_NATIVE_FUNCTION(core, "HEL.Math.Direction3", "void RestructUpLeft()", RestructUpLeft, RestructUpLeft);
    MINT_NATIVE_FUNCTION(core, "HEL.Math.Direction3", "void RestructLeftFront()", RestructLeftFront, RestructLeftFront);
    MINT_NATIVE_FUNCTION(core, "HEL.Math.Direction3", "void RestructLeftUp()", RestructLeftUp, RestructLeftUp);
    MINT_NATIVE_FUNCTION(core, "HEL.Math.Direction3", "HEL.Math.Direction3 Get()", Get, Get);
    MINT_NATIVE_FUNCTION(core, "HEL.Math.Direction3", "void Set(HEL.Math.Direction3)", Set, Set);
    MINT_NATIVE_FUNCTION(core, "HEL.Math.Direction3", "HEL.Math.Direction3 Basis()", Basis, Basis);
    MINT_NATIVE_FUNCTION(
        core, "HEL.Math.Direction3",
        "HEL.Math.Direction3 Create(const ref HEL.Math.Vector3,const ref HEL.Math.Vector3,const ref HEL.Math.Vector3)", Create, Create
    );
}

hel::math::Direction3 Get() {
    return t_obj();
}

void Set(const hel::math::Direction3& value) {
    t_obj() = value;
}

void LoadLeft() {
    t_obj().mLeft = AddOnMathVector3::Get();
}

void LoadUp() {
    t_obj().mUp = AddOnMathVector3::Get();
}

void LoadFront() {
    t_obj().mFront = AddOnMathVector3::Get();
}

void StoreLeft() {
    AddOnMathVector3::Set(t_obj().mLeft);
}

void StoreUp() {
    AddOnMathVector3::Set(t_obj().mUp);
}

void StoreFront() {
    AddOnMathVector3::Set(t_obj().mFront);
}

void SetBasis() {
    Set(hel::math::Direction3::BASIS);
}

void SetFrontToRight() {
    Set(hel::math::Direction3::FRONT_TO_RIGHT);
}

void SetFrontToLeft() {
    Set(hel::math::Direction3::FRONT_TO_LEFT);
}

void RestructFrontUp() {
    t_obj().restructFrontUp();
}

void RestructFrontLeft() {
    t_obj().restructFrontLeft();
}

void RestructUpFront() {
    t_obj().restructUpFront();
}

void RestructUpLeft() {
    t_obj().restructUpLeft();
}

void RestructLeftFront() {
    t_obj().restructLeftFront();
}

void RestructLeftUp() {
    t_obj().restructLeftUp();
}

hel::math::Direction3 Basis() {
    return hel::math::Direction3::BASIS;
}

hel::math::Direction3 Create(const hel::math::Vector3& front, const hel::math::Vector3& up, const hel::math::Vector3& left) {
    return hel::math::Direction3(front, up, left);
}

}

}}  // namespace hel::mint
