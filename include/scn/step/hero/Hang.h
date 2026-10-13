#ifndef SCN_STEP_HERO_HANG_H
#define SCN_STEP_HERO_HANG_H

#include "hel/math/Vector3.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {

// TODO: members; mParent is a hel::common::PointerWrapper<Hang>.
class Hang {
public:
    bool isExistParent() const { return mParent != 0; }
    void setCanHang(bool canHang);
    void setCanReceive(bool canReceive);
    void setIsHangNow(bool isHangNow);

    bool isHangNow() const { return mIsHangNow; }
    bool canHang() const;
    hel::math::Vector3 getRootPos() const;
    hel::math::Vector3 getConstraintOffsetChild() const;
    hel::math::Vector3 getConstraintPos() const;
    bool isParentRightDir() const;
    f32 getParentRotH() const;
    void unlinkParent();
    void unlinkChild();
    void setInterval(u32 interval);

    u32 _0[2];
    Hang* mParent;
    bool mCanReceive;
    bool mCanHang;
    bool mIsHangNow;
    u32 mInterval;
};

}
}
}

#endif
