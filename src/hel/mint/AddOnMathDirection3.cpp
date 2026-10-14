#include "hel/mint/AddOnMathDirection3.h"

#include "hel/math/Direction3.h"
#include "hel/mint/AddOnMathVector3.h"
#include "hel/mint/WrapNative.h"

using hel::math::Direction3;
using hel::math::Vector3;

namespace hel {
namespace mint {

namespace {

Direction3& t_obj() {
    static Direction3 obj;
    return obj;
}

}

namespace AddOnMathDirection3 {

void RegisterAll(mintvm::VMCore& core) {
    core.addNativePod("HEL.Math.Direction3", sizeof(Direction3));
    core.addNativePod_Property("HEL.Math.Direction3", "left", MINT_OFFSETOF(Direction3, mLeft));
    core.addNativePod_Property("HEL.Math.Direction3", "up", MINT_OFFSETOF(Direction3, mUp));
    core.addNativePod_Property("HEL.Math.Direction3", "front", MINT_OFFSETOF(Direction3, mFront));
    MINT_NATIVE_POD_CTOR(
        core, "HEL.Math.Direction3", "void this(const ref HEL.Math.Vector3,const ref HEL.Math.Vector3,const ref HEL.Math.Vector3)",
        Direction3, const Vector3&, const Vector3&, const Vector3&
    );
    MINT_NATIVE_POD_METHOD(core, "HEL.Math.Direction3", "void restructFrontUp()", restructFrontUp, &Direction3::restructFrontUp);
    MINT_NATIVE_POD_METHOD(core, "HEL.Math.Direction3", "void restructFrontLeft()", restructFrontLeft, &Direction3::restructFrontLeft);
    MINT_NATIVE_POD_METHOD(core, "HEL.Math.Direction3", "void restructUpFront()", restructUpFront, &Direction3::restructUpFront);
    MINT_NATIVE_POD_METHOD(core, "HEL.Math.Direction3", "void restructUpLeft()", restructUpLeft, &Direction3::restructUpLeft);
    MINT_NATIVE_POD_METHOD(core, "HEL.Math.Direction3", "void restructLeftFront()", restructLeftFront, &Direction3::restructLeftFront);
    MINT_NATIVE_POD_METHOD(core, "HEL.Math.Direction3", "void restructLeftUp()", restructLeftUp, &Direction3::restructLeftUp);
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

Direction3 Get() {
    return t_obj();
}

void Set(const Direction3& value) {
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
    Set(Direction3::BASIS);
}

void SetFrontToRight() {
    Set(Direction3::FRONT_TO_RIGHT);
}

void SetFrontToLeft() {
    Set(Direction3::FRONT_TO_LEFT);
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

Direction3 Basis() {
    return Direction3::BASIS;
}

Direction3 Create(const Vector3& front, const Vector3& up, const Vector3& left) {
    return Direction3(front, up, left);
}

}

}}  // namespace hel::mint
