#include "scn/step/boss/goliath/LandCtrl.h"

#include "gobj/Target.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/chara/Location.h"

namespace scn {
namespace step {
namespace boss {
namespace goliath {

namespace {

struct LandData {
    f32 mFloorY;
    f32 mWidth;
    f32 mBump;
    f32 mWallDepth;
};

const LandData T_LAND_DATA[6] = {
    { 0.0f, 17.0f, 0.0f, 0.0f },   { -18.0f, 17.0f, 0.0f, 0.0f },  { -36.0f, 15.0f, 0.0f, 0.0f },
    { -54.0f, 17.0f, 1.0f, 0.0f }, { -72.0f, 13.0f, 1.0f, -1.5f }, { -90.0f, 11.0f, 0.0f, 0.0f },
};

}

LandCtrl::LandCtrl(Boss& boss) : mBoss(boss), mLevel(0), mCenterX(0.0f) {
    mCenterX = boss.basePos().x - 2.0f;
}

f32 LandCtrl::getFloorY() const {
    return T_LAND_DATA[mLevel].mFloorY + mBoss.basePos().y;
}

f32 LandCtrl::getFloorYWithBump() const {
    return T_LAND_DATA[mLevel].mBump + getFloorY();
}

f32 LandCtrl::getWidth() const {
    return T_LAND_DATA[mLevel].mWidth;
}

f32 LandCtrl::getWallDepth() const {
    return T_LAND_DATA[mLevel].mWallDepth;
}

f32 LandCtrl::getCenterX() const {
    return mCenterX;
}

f32 LandCtrl::getOppositeWallX() const {
    f32 sign = mBoss.location().pos().x < getCenterX() ? 1.0f : -1.0f;
    f32 centerX = getCenterX();
    f32 width = getWidth();
    return centerX + width * (0.5f * sign);
}

f32 LandCtrl::getFaceToFaceWallX() const {
    return getCenterX() + 0.5f * mBoss.target().getSign() * getWidth();
}

f32 LandCtrl::getAdjustX(f32 x, f32 margin) const {
    f32 min = margin + (getCenterX() - 0.5f * getWidth());
    f32 max = getCenterX() + 0.5f * getWidth() - margin;
    if (max <= min) {
        return getCenterX();
    }
    if (x > max) {
        return max;
    }
    if (x < min) {
        return min;
    }
    return x;
}

int LandCtrl::getLevel() const {
    return mLevel;
}

bool LandCtrl::isMaxLevel() const {
    return mLevel == 5;
}

int LandCtrl::getMaxLevelOnBattle() const {
    return 4;
}

void LandCtrl::levelUp() {
    static const u32 maxLevel = 5;
    if (mLevel < maxLevel) {
        mLevel++;
    }
}

}}}}  // namespace scn::step::boss::goliath
