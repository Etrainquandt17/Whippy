#ifndef SCN_STEP_BOSS_LOWPER_STATEFREEZEATTACKSPINE_H
#define SCN_STEP_BOSS_LOWPER_STATEFREEZEATTACKSPINE_H

#include "hel/common/Array.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/weapon/Weapon.h"
#include "types.h"
#include "util/ObjRefHandle.h"

namespace scn {
namespace step {
namespace boss {
namespace lowper {

class StateFreezeAttackSpine : public StateBase {
public:
    StateFreezeAttackSpine(Boss* boss, u32 frame);
    virtual ~StateFreezeAttackSpine();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    void reqIceSpine();
    void shotIceSpine();
    u32 mFrame;
    u32 mCount;
    hel::common::Array<util::ObjRefHandle<weapon::Weapon>, 4> mWeapons;
};

}}}}  // namespace scn::step::boss::lowper

#endif
