#ifndef HEL_MATH_DIRECTION3_H
#define HEL_MATH_DIRECTION3_H

#include "hel/math/Vector3.h"

namespace hel {
namespace math {

class Matrix34;

class Direction3 {
public:
    // TODO: inline in the original, as are the members of Front, Up and Left below the class. hel/math/Direction3.cpp
    // defines HEL_MATH_DIRECTION3_OUT_OF_LINE to get declarations: the place where it emits each depends on
    // functions of that unit which the link dropped.
#ifdef HEL_MATH_DIRECTION3_OUT_OF_LINE
    Direction3();
    Direction3& operator=(const Direction3& other);
#else
    Direction3& operator=(const Direction3& other) {
        if (this != &other) {
            mFront = other.mFront;
            mUp = other.mUp;
            mLeft = other.mLeft;
        }
        return *this;
    }

    Direction3() { *this = BASIS; }
#endif
    // TODO: inline in the original too; Direction3.cpp defines HEL_MATH_DIRECTION3_CONSTRUCTOR_OUT_OF_LINE to get
    // the declarations, for the same reason.
#ifdef HEL_MATH_DIRECTION3_CONSTRUCTOR_OUT_OF_LINE
    Direction3(const Direction3& other);
    Direction3(const Vector3& front, const Vector3& up, const Vector3& left);
#else
    Direction3(const Direction3& other) : mFront(other.mFront), mUp(other.mUp), mLeft(other.mLeft) {}
    Direction3(const Vector3& front, const Vector3& up, const Vector3& left) : mFront(front), mUp(up), mLeft(left) {}
#endif
    Direction3(const Matrix34& mtx);

    void set(const Vector3& a, const Vector3& b, const Vector3& c);
    void normalize();
    Vector3 globalPos(const Vector3& pos, const Vector3& origin) const;
    Vector3 globalVector(const Vector3& v) const;
    // TODO: declare unconditionally once hel/mint/AddOnMathDirection3.cpp casts the restructFrontUp it binds;
    // with this overload in sight its member pointer is ambiguous.
#ifdef HEL_MATH_DIRECTION3_CONSTRUCTOR_OUT_OF_LINE
    void restructFrontUp(const Vector3& front);
#endif

    class Front {
    public:
        Front(Direction3* direction) : mDirection(direction) {}

        bool permittedRestruct();
        void restruct();

    private:
        Direction3* mDirection;
    };

    class Up {
    public:
        Up(Direction3* direction) : mDirection(direction) {}

        bool permittedRestruct();
        void restruct();

    private:
        Direction3* mDirection;
    };

    class Left {
    public:
        Left(Direction3* direction) : mDirection(direction) {}

        bool permittedRestruct();
        void restruct();

    private:
        Direction3* mDirection;
    };

    // TODO: the name is a guess; the function is inlined wherever it is used.
    template <typename A, typename B>
    void restructWith() {
        A a(this);
        B b(this);
        if (a.permittedRestruct()) {
            b.restruct();
        } else {
            b.restruct();
            a.restruct();
        }
    }

    void restructFrontUp() { restructWith<Left, Up>(); }
    void restructFrontLeft() { restructWith<Up, Left>(); }
    void restructUpFront() { restructWith<Left, Front>(); }
    void restructUpLeft() { restructWith<Front, Left>(); }
    void restructLeftFront() { restructWith<Up, Front>(); }
    void restructLeftUp() { restructWith<Front, Up>(); }

    static const Direction3 BASIS;
    static const Direction3 FRONT_TO_RIGHT;
    static const Direction3 FRONT_TO_LEFT;

    Vector3 mFront;
    Vector3 mUp;
    Vector3 mLeft;
};

#ifndef HEL_MATH_DIRECTION3_OUT_OF_LINE
inline bool Direction3::Left::permittedRestruct() {
    Vector3 left = mDirection->mUp.permittedNormalizedCross(mDirection->mFront);
    if (left.isZero()) {
        return false;
    }
    mDirection->mLeft = left;
    return true;
}

// The front vector is read through a const path here and in permittedRestruct; without it the load moves.
inline void Direction3::Up::restruct() {
    mDirection->mUp = static_cast<const Vector3&>(mDirection->mFront).normalizedCross(mDirection->mLeft);
}

inline void Direction3::Left::restruct() {
    mDirection->mLeft = mDirection->mUp.normalizedCross(mDirection->mFront);
}

inline bool Direction3::Up::permittedRestruct() {
    Vector3 up = static_cast<const Vector3&>(mDirection->mFront).permittedNormalizedCross(mDirection->mLeft);
    if (up.isZero()) {
        return false;
    }
    mDirection->mUp = up;
    return true;
}

inline void Direction3::Front::restruct() {
    mDirection->mFront = mDirection->mLeft.normalizedCross(mDirection->mUp);
}

inline bool Direction3::Front::permittedRestruct() {
    Vector3 front = mDirection->mLeft.permittedNormalizedCross(mDirection->mUp);
    if (front.isZero()) {
        return false;
    }
    mDirection->mFront = front;
    return true;
}
#endif

}}  // namespace hel::math

#endif
