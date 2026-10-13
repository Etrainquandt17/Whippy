#include "mintglue/HEL__Math__Vector2.h"

#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "mintglue/VectorInline.h"
#include "mintglue/WrapNative.h"

using hel::math::Vector2;
using hel::math::Vector3;

namespace mintglue {
namespace HEL__Math__Vector2 {

void AddOn(mintvm::VMCore& core) {
    core.addNativePod("HEL.Math.Vector2", sizeof(Vector2));
    core.addNativePod_Property("HEL.Math.Vector2", "x", MINT_OFFSETOF(Vector2, x));
    core.addNativePod_Property("HEL.Math.Vector2", "y", MINT_OFFSETOF(Vector2, y));
    MINT_NATIVE_POD_CTOR(core, "HEL.Math.Vector2", "void this(float,float)", Vector2, f32, f32);
    MINT_NATIVE_POD_METHOD(core, "HEL.Math.Vector2", "void set(float,float)", set, &Vector2::set);
    MINT_NATIVE_POD_METHOD(core, "HEL.Math.Vector2", "bool isZeroLoose(float)const", isZeroLoose, &Vector2::isZeroLoose);
    MINT_NATIVE_POD_METHOD(core, "HEL.Math.Vector2", "bool isZeroStrict()const", isZeroStrict, &Vector2::isZeroStrict);
    MINT_NATIVE_POD_METHOD(core, "HEL.Math.Vector2", "bool isZero()const", isZero, &Vector2::isZero);
    MINT_NATIVE_POD_METHOD(core, "HEL.Math.Vector2", "void opAddAssign(const ref HEL.Math.Vector2)", opAddAssign, (void (Vector2::*)(const Vector2&))&Vector2::operator+=);
    MINT_NATIVE_POD_METHOD(core, "HEL.Math.Vector2", "void opSubAssign(const ref HEL.Math.Vector2)", opSubAssign, (void (Vector2::*)(const Vector2&))&Vector2::operator-=);
    MINT_NATIVE_POD_METHOD(core, "HEL.Math.Vector2", "void opMulAssign(float)", opMulAssign, (void (Vector2::*)(f32))&Vector2::operator*=);
    MINT_NATIVE_POD_METHOD(core, "HEL.Math.Vector2", "void opDivAssign(float)", opDivAssign, (void (Vector2::*)(f32))&Vector2::operator/=);
    MINT_NATIVE_POD_METHOD(core, "HEL.Math.Vector2", "HEL.Math.Vector2 opAdd(const ref HEL.Math.Vector2)const", opAdd, &Vector2::operator+);
    MINT_NATIVE_POD_METHOD(core, "HEL.Math.Vector2", "HEL.Math.Vector2 opSub(const ref HEL.Math.Vector2)const", opSub, (Vector2 (Vector2::*)(const Vector2&) const)&Vector2::operator-);
    MINT_NATIVE_POD_METHOD(core, "HEL.Math.Vector2", "HEL.Math.Vector2 opMul(float)const", opMul, &Vector2::operator*);
    MINT_NATIVE_POD_METHOD(core, "HEL.Math.Vector2", "HEL.Math.Vector2 opDiv(float)const", opDiv, &Vector2::operator/);
    MINT_NATIVE_POD_METHOD(core, "HEL.Math.Vector2", "HEL.Math.Vector3 toVector3()const", toVector3, &Vector2::toVector3);
    MINT_NATIVE_POD_METHOD(core, "HEL.Math.Vector2", "HEL.Math.Vector3 toVector3XOY()const", toVector3XOY, &Vector2::toVector3XOY);
}

}}  // namespace mintglue::HEL__Math__Vector2
