#include "hel/mint/AddOnMathVector3.h"

#include "hel/common/Array.h"
#include "mintglue/VectorInline.h"

using hel::common::Array;
using hel::math::Vector3;

namespace hel {
namespace mint {

namespace {

Vector3& t_obj() {
    static Vector3 obj;
    return obj;
}

Vector3& t_slot(unsigned long index) {
    static Array<Vector3, 4> objs;
    return objs[index];
}

}

namespace AddOnMathVector3 {

const Vector3 Get() {
    return t_obj();
}

float GetX() {
    return t_obj().x;
}

float GetY() {
    return t_obj().y;
}

float GetZ() {
    return t_obj().z;
}

void SetXYZ(float x, float y, float z) {
    t_obj().x = x;
    t_obj().y = y;
    t_obj().z = z;
}

void Set(const Vector3& value) {
    t_obj() = value;
}

void SetX(float x) {
    t_obj().x = x;
}

void SetY(float y) {
    t_obj().y = y;
}

void SetZ(float z) {
    t_obj().z = z;
}

void Mul(float scale) {
    t_obj() *= scale;
}

void Div(float scale) {
    t_obj() /= scale;
}

void SlotLoad(unsigned long index) {
    t_obj() = t_slot(index);
}

void SlotSave(unsigned long index) {
    t_slot(index) = t_obj();
}

void SlotAdd(unsigned long index) {
    t_obj() += t_slot(index);
}

void SlotSub(unsigned long index) {
    t_obj() -= t_slot(index);
}

// Not in the split object: the original link folded it into nw4r::math::VEC3's constructor.
const Vector3 Create(float x, float y, float z) {
    return Vector3(x, y, z);
}

}

}}  // namespace hel::mint
