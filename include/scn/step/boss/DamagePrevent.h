#ifndef SCN_STEP_BOSS_DAMAGEPREVENT_H
#define SCN_STEP_BOSS_DAMAGEPREVENT_H

#include "hel/common/MutableArray.h"
#include "scn/step/ocoll/AttackType.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {

class Boss;

class DamagePrevent {
public:
    struct PreventTargetData {
        PreventTargetData() {}
        PreventTargetData(ocoll::AttackType type, f32 rate) : mType(type), mRate(rate) {}

        ocoll::AttackType mType;
        f32 mRate;
    };

    DamagePrevent(Boss& boss);
    ~DamagePrevent();

    u32 calcDamage(u32 damage, ocoll::AttackType type);
    void addPreventTarget(ocoll::AttackType type, f32 rate);
    void removePreventTarget(ocoll::AttackType type);

private:
    Boss& mBoss;
    hel::common::MutableArray<PreventTargetData, 16> mTargets;
};

}}}  // namespace scn::step::boss

#endif
