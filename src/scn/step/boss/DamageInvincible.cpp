#include "scn/step/boss/DamageInvincible.h"

#include "scn/step/chara/DamageInfo.h"

namespace scn {
namespace step {
namespace boss {

namespace {

struct FrameByDamage {
    u32 mDamage;
    u32 mFrame;
};

FrameByDamage T_FRAME_BY_DAMAGE_TABLE[] = {
    { 35, 36 }, { 25, 28 }, { 20, 20 }, { 11, 16 }, { 6, 12 }, { 1, 8 }, { 0, 0 },
};

}

DamageInvincible::DamageInvincible(Boss& boss) : mBoss(boss), mFrame(0) {}

void DamageInvincible::update() {
    if (mFrame != 0) {
        mFrame--;
    }
}

void DamageInvincible::setByDamage(const chara::DamageInfo& info) {
    u32 damage = info.data().mDamage;
    if (info.attackType() == 0x257) {
        return;
    }
    u32 frame = 0;
    for (u32 i = 0; i < 7; i++) {
        if (damage >= T_FRAME_BY_DAMAGE_TABLE[i].mDamage) {
            frame = T_FRAME_BY_DAMAGE_TABLE[i].mFrame;
            break;
        }
    }
    if (frame > mFrame) {
        mFrame = frame;
    }
}

void DamageInvincible::cancel() {
    mFrame = 0;
}

bool DamageInvincible::isInvincible(const chara::DamageInfo& info) const {
    if (info.data()._48) {
        return false;
    }
    int type = info.attackType();
    if ((type >= 0x107 && type <= 0x10A) || (type >= 0x104 && type <= 0x105)) {
        return false;
    }
    return isInvincible();
}

bool DamageInvincible::isInvincible() const {
    return mFrame != 0;
}

u32 DamageInvincible::getFrame() const {
    return mFrame;
}

}}}  // namespace scn::step::boss
