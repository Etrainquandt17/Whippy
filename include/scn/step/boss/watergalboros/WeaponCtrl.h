#ifndef SCN_STEP_BOSS_WATERGALBOROS_WEAPONCTRL_H
#define SCN_STEP_BOSS_WATERGALBOROS_WEAPONCTRL_H

#include "hel/common/MutableArray.h"
#include "hel/math/Vec2.h"
#include "hel/math/Vector2.h"
#include "scn/step/weapon/Kind.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace watergalboros {

}
class Boss;
namespace watergalboros {

class WeaponCtrl {
public:
    struct ReqData {
        int _0;
        hel::math::Vec2 _4;
    };

    WeaponCtrl(Boss& boss);

    void addReqData(const ReqData& data);
    void clearReqBuff();
    ReqData popReqData();
    bool isReqBuffEmpty();
    void request();
    void requestBase(weapon::Kind kind, hel::math::Vector2 pos, hel::math::Vector2 speed, u32 variation);

private:
    Boss& mBoss;
    hel::common::MutableArray<ReqData, 10> mReqBuff;
};

}}}}  // namespace scn::step::boss::watergalboros

#endif
