#include "mintglue/HEL__Math__Vector3.h"

#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "hel/mint/AddOnMathVector3.h"
#include "mintglue/VectorInline.h"
#include "mintglue/WrapNative.h"

using hel::math::Vector2;
using hel::math::Vector3;
using namespace hel::mint;

namespace mintglue {
namespace HEL__Math__Vector3 {

void AddOn(mintvm::VMCore& core) {
    core.addNativePod("HEL.Math.Vector3", sizeof(Vector3));
    core.addNativePod_Property("HEL.Math.Vector3", "x", MINT_OFFSETOF(Vector3, x));
    core.addNativePod_Property("HEL.Math.Vector3", "y", MINT_OFFSETOF(Vector3, y));
    core.addNativePod_Property("HEL.Math.Vector3", "z", MINT_OFFSETOF(Vector3, z));
    MINT_NATIVE_POD_CTOR(core, "HEL.Math.Vector3", "void this(float,float,float)", Vector3, f32, f32, f32);
    MINT_NATIVE_POD_METHOD(core, "HEL.Math.Vector3", "void set(float,float,float)", set, &Vector3::set);
    MINT_NATIVE_POD_METHOD(core, "HEL.Math.Vector3", "bool isZeroLoose(float)const", isZeroLoose, &Vector3::isZeroLoose);
    MINT_NATIVE_POD_METHOD(core, "HEL.Math.Vector3", "bool isZeroStrict()const", isZeroStrict, &Vector3::isZeroStrict);
    MINT_NATIVE_POD_METHOD(core, "HEL.Math.Vector3", "bool isZero()const", isZero, &Vector3::isZero);
    MINT_NATIVE_POD_METHOD(core, "HEL.Math.Vector3", "void opAddAssign(const ref HEL.Math.Vector3)", opAddAssign, (void (Vector3::*)(const Vector3&))&Vector3::operator+=);
    MINT_NATIVE_POD_METHOD(core, "HEL.Math.Vector3", "void opSubAssign(const ref HEL.Math.Vector3)", opSubAssign, (void (Vector3::*)(const Vector3&))&Vector3::operator-=);
    MINT_NATIVE_POD_METHOD(core, "HEL.Math.Vector3", "void opMulAssign(float)", opMulAssign, (void (Vector3::*)(f32))&Vector3::operator*=);
    MINT_NATIVE_POD_METHOD(core, "HEL.Math.Vector3", "void opDivAssign(float)", opDivAssign, (void (Vector3::*)(f32))&Vector3::operator/=);
    MINT_NATIVE_POD_METHOD(core, "HEL.Math.Vector3", "HEL.Math.Vector3 opAdd(const ref HEL.Math.Vector3)const", opAdd, &Vector3::operator+);
    MINT_NATIVE_POD_METHOD(core, "HEL.Math.Vector3", "HEL.Math.Vector3 opSub(const ref HEL.Math.Vector3)const", opSub, (Vector3 (Vector3::*)(const Vector3&) const)&Vector3::operator-);
    MINT_NATIVE_POD_METHOD(core, "HEL.Math.Vector3", "HEL.Math.Vector3 opMul(float)const", opMul, &Vector3::operator*);
    MINT_NATIVE_POD_METHOD(core, "HEL.Math.Vector3", "HEL.Math.Vector3 opDiv(float)const", opDiv, &Vector3::operator/);
    MINT_NATIVE_POD_METHOD(core, "HEL.Math.Vector3", "HEL.Math.Vector2 getXY()const", getXY, &Vector3::getXY);
    MINT_NATIVE_POD_METHOD(core, "HEL.Math.Vector3", "HEL.Math.Vector2 getXZ()const", getXZ, &Vector3::getXZ);
    MINT_NATIVE_POD_METHOD(core, "HEL.Math.Vector3", "HEL.Math.Vector2 getYX()const", getYX, &Vector3::getYX);
    MINT_NATIVE_POD_METHOD(core, "HEL.Math.Vector3", "HEL.Math.Vector2 getYZ()const", getYZ, &Vector3::getYZ);
    MINT_NATIVE_POD_METHOD(core, "HEL.Math.Vector3", "HEL.Math.Vector2 getZX()const", getZX, &Vector3::getZX);
    MINT_NATIVE_POD_METHOD(core, "HEL.Math.Vector3", "HEL.Math.Vector2 getZY()const", getZY, &Vector3::getZY);
    MINT_NATIVE_FUNCTION(core, "HEL.Math.Vector3", "const HEL.Math.Vector3 Get()", Get, &AddOnMathVector3::Get);
    MINT_NATIVE_FUNCTION(core, "HEL.Math.Vector3", "float GetX()", GetX, &AddOnMathVector3::GetX);
    MINT_NATIVE_FUNCTION(core, "HEL.Math.Vector3", "float GetY()", GetY, &AddOnMathVector3::GetY);
    MINT_NATIVE_FUNCTION(core, "HEL.Math.Vector3", "float GetZ()", GetZ, &AddOnMathVector3::GetZ);
    MINT_NATIVE_FUNCTION(core, "HEL.Math.Vector3", "void Set(const ref HEL.Math.Vector3)", Set, &AddOnMathVector3::Set);
    MINT_NATIVE_FUNCTION(core, "HEL.Math.Vector3", "void SetXYZ(float,float,float)", SetXYZ, &AddOnMathVector3::SetXYZ);
    MINT_NATIVE_FUNCTION(core, "HEL.Math.Vector3", "void SetX(float)", SetX, &AddOnMathVector3::SetX);
    MINT_NATIVE_FUNCTION(core, "HEL.Math.Vector3", "void SetY(float)", SetY, &AddOnMathVector3::SetY);
    MINT_NATIVE_FUNCTION(core, "HEL.Math.Vector3", "void SetZ(float)", SetZ, &AddOnMathVector3::SetZ);
    MINT_NATIVE_FUNCTION(core, "HEL.Math.Vector3", "void Mul(float)", Mul, &AddOnMathVector3::Mul);
    MINT_NATIVE_FUNCTION(core, "HEL.Math.Vector3", "void Div(float)", Div, &AddOnMathVector3::Div);
    MINT_NATIVE_FUNCTION(core, "HEL.Math.Vector3", "void SlotLoad(int)", SlotLoad, (void (*)(int))&AddOnMathVector3::SlotLoad);
    MINT_NATIVE_FUNCTION(core, "HEL.Math.Vector3", "void SlotSave(int)", SlotSave, (void (*)(int))&AddOnMathVector3::SlotSave);
    MINT_NATIVE_FUNCTION(core, "HEL.Math.Vector3", "void SlotAdd(int)", SlotAdd, (void (*)(int))&AddOnMathVector3::SlotAdd);
    MINT_NATIVE_FUNCTION(core, "HEL.Math.Vector3", "void SlotSub(int)", SlotSub, (void (*)(int))&AddOnMathVector3::SlotSub);
    MINT_NATIVE_FUNCTION(core, "HEL.Math.Vector3", "const HEL.Math.Vector3 Create(float,float,float)", Create, &AddOnMathVector3::Create);
}

}
}
