#ifndef GOBJ_MOVE_H
#define GOBJ_MOVE_H

#include "hel/math/Vector3.h"
#include "types.h"

namespace gobj {

class Location;
struct MoveParamAccel;
struct MoveParamDecel;
struct MoveParamFall;

class Move {
public:
    explicit Move(Location& location);

    hel::math::Vector3 velocity() const;
    void setVelocity(const hel::math::Vector3& velocity);
    void setSpeedH(f32 speed);
    void setSpeedV(f32 speed);
    void setSpeedD(f32 speed);
    void resetVelocity();
    void resetSpeedH();
    void resetSpeedV();
    void setMoveRate(f32 rate);
    void resetMoveRate();
    void accel(const hel::math::Vector3& dir, const MoveParamAccel& param);
    void decel(const MoveParamDecel& param);
    void groundAccel(bool isRight, const MoveParamAccel& param);
    void groundDecel(const MoveParamDecel& param);
    void airAccelFall(bool isRight, const MoveParamAccel& param, const MoveParamFall& fall);
    void airDecelFall(const MoveParamDecel& param, const MoveParamFall& fall);
    void updateLocation();

private:
    Location& mLocation;
    hel::math::Vector3 mVelocity;
    f32 mMoveRate;
};

}

#endif
