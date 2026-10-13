#ifndef SCN_STEP_BOSS_ZANKIBBLE_ENEMYCTRL_H
#define SCN_STEP_BOSS_ZANKIBBLE_ENEMYCTRL_H

#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/enemy/Accessor.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace zankibble {

class EnemyCtrl {
public:
    enum CutterKind {
        CUTTER_KIND_STRAIGHT,
        CUTTER_KIND_CIRCLE,
        CUTTER_KIND_BACK_CIRCLE,
        CUTTER_KIND_SLANT,
    };

    EnemyCtrl(Boss& boss);

    void request(CutterKind kind, hel::math::Vector2 pos, hel::math::Vector3 velocity, bool isReverse);
    void caughtSignal();
    bool isCaught();
    bool isHoldCatchWaitCutter();

private:
    Boss& mBoss;
    enemy::Accessor mCutter;
    bool mIsCaught;
};

}}}}  // namespace scn::step::boss::zankibble

#endif
