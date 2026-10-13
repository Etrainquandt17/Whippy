#define HEL_MATH_DIRECTION3_CONSTRUCTOR_OUT_OF_LINE
#define HEL_MATH_DIRECTION3_OUT_OF_LINE
#define HEL_MATH_MATRIX34_OUT_OF_LINE
#include "hel/math/Direction3.h"

#include "hel/math/Matrix34.h"
#include "mintglue/VectorInline.h"
#include "revolution/mtx.h"

namespace hel {
namespace math {

Direction3::Direction3(const Matrix34& mtx) {
    Vector3 front;
    Matrix34::MtxColVec(const_cast<f32 (*)[4]>(mtx.m), 2, reinterpret_cast<Vec*>(&front));
    front.normalize();
    Vector3 up;
    Matrix34::MtxColVec(const_cast<f32 (*)[4]>(mtx.m), 1, reinterpret_cast<Vec*>(&up));
    up.normalize();
    Vector3 left;
    Matrix34::MtxColVec(const_cast<f32 (*)[4]>(mtx.m), 0, reinterpret_cast<Vec*>(&left));
    left.normalize();
    set(front, up, left);
}

void Direction3::set(const Vector3& front, const Vector3& up, const Vector3& left) {
    mFront = front;
    mUp = up;
    mLeft = left;
}

void Direction3::normalize() {
    mFront.normalize();
    mUp.normalize();
    mLeft.normalize();
}

Matrix34::Matrix34(const Direction3& direction, const Vector3& pos) : m() {
    m[0][0] = direction.mLeft.x;
    m[1][0] = direction.mLeft.y;
    m[2][0] = direction.mLeft.z;
    m[0][1] = direction.mUp.x;
    m[1][1] = direction.mUp.y;
    m[2][1] = direction.mUp.z;
    m[0][2] = direction.mFront.x;
    m[1][2] = direction.mFront.y;
    m[2][2] = direction.mFront.z;
    m[0][3] = pos.x;
    m[1][3] = pos.y;
    m[2][3] = pos.z;
}

Vector3 Direction3::globalPos(const Vector3& pos, const Vector3& origin) const {
    Matrix34 mtx(*this, origin);
    return mtx.mul(pos);
}

Vector3 Direction3::globalVector(const Vector3& v) const {
    return globalPos(v, Vector3::ZERO);
}

Direction3::Direction3() {
    *this = BASIS;
}

Direction3::Direction3(const Direction3& other) : mFront(other.mFront), mUp(other.mUp), mLeft(other.mLeft) {}

Direction3::Direction3(const Vector3& front, const Vector3& up, const Vector3& left) : mFront(front), mUp(up), mLeft(left) {}

const Direction3 Direction3::BASIS = Direction3(Vector3(0.0f, 0.0f, 1.0f), Vector3(0.0f, 1.0f, 0.0f), Vector3(1.0f, 0.0f, 0.0f));
const Direction3 Direction3::FRONT_TO_RIGHT =
    Direction3(Vector3(1.0f, 0.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f), Vector3(0.0f, 0.0f, -1.0f));
const Direction3 Direction3::FRONT_TO_LEFT =
    Direction3(Vector3(-1.0f, 0.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f), Vector3(0.0f, 0.0f, 1.0f));

void Direction3::restructFrontUp(const Vector3& front) {
    mFront = front;
    restructFrontUp();
}

bool Direction3::Left::permittedRestruct() {
    Vector3 left = mDirection->mUp.permittedNormalizedCross(mDirection->mFront);
    if (left.isZero()) {
        return false;
    }
    mDirection->mLeft = left;
    return true;
}

void Direction3::Up::restruct() {
    // The front vector is read through a const path here and in permittedRestruct; without it the load moves.
    mDirection->mUp = static_cast<const Vector3&>(mDirection->mFront).normalizedCross(mDirection->mLeft);
}

void Direction3::Left::restruct() {
    mDirection->mLeft = mDirection->mUp.normalizedCross(mDirection->mFront);
}

bool Direction3::Up::permittedRestruct() {
    Vector3 up = static_cast<const Vector3&>(mDirection->mFront).permittedNormalizedCross(mDirection->mLeft);
    if (up.isZero()) {
        return false;
    }
    mDirection->mUp = up;
    return true;
}

void Direction3::Front::restruct() {
    mDirection->mFront = mDirection->mLeft.normalizedCross(mDirection->mUp);
}

bool Direction3::Front::permittedRestruct() {
    Vector3 front = mDirection->mLeft.permittedNormalizedCross(mDirection->mUp);
    if (front.isZero()) {
        return false;
    }
    mDirection->mFront = front;
    return true;
}

}}  // namespace hel::math
