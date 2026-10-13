#include "scn/step/boss/Handicap.h"

#include "scn/step/Component.h"
#include "scn/step/DebugStepSettingProxy.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Manager.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/chara/HitPoint.h"

namespace scn {
namespace step {
namespace boss {

namespace {

const f32 T_HP_RATE_TABLE[] = { 1.0f, 0.97f, 0.91f, 0.88f, 0.82f, 0.74f, 0.62f };

}

Handicap::Handicap(Boss& boss) : mBoss(boss) {}

void Handicap::setup() {
    if (Utility::IsBossMBoss(mBoss.kind())) {
        return;
    }
    mBoss.comp().bossManager().setRetryBossKind(mBoss.kind());
    u32 count = mBoss.comp().bossManager().getRetryBossCount(mBoss.kind());
    if (count >= 7) {
        count = 6;
    }
    f32 rate = T_HP_RATE_TABLE[count];
    if (Utility::IsArena(mBoss)) {
        rate = 0.75f;
    }
    f32 hitPoint = mBoss.hitPoint().getMax();
    hitPoint *= rate;
    mBoss.hitPoint().init(hitPoint);
    DebugStepSettingProxy::GetAlertInfoBossHandicapMonitor();
}

}}}  // namespace scn::step::boss
