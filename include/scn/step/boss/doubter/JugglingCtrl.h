#ifndef SCN_STEP_BOSS_DOUBTER_JUGGLINGCTRL_H
#define SCN_STEP_BOSS_DOUBTER_JUGGLINGCTRL_H

#include "g3d/NodeAccessor.h"
#include "hel/common/Array.h"
#include "hel/common/MutableArray.h"
#include "scn/step/boss/doubter/AnimKind.h"
#include "scn/step/enemy/Accessor.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace doubter {

}
class Boss;
namespace doubter {

class JugglingCtrl {
public:
    struct ReqData {
        u32 _0;
    };

    JugglingCtrl(Boss& boss);
    void update();
    void setIsActive(bool isActive);
    void inactivateEnf();
    bool isActive() const;
    void clearHandSubAnim();
    void requestJugglingThrowSE(u32 index);
    void requestJugglingCatchSE(u32 index);
    g3d::NodeAccessor getFollowNode(u32 index);
    void addReqData(const ReqData& data);
    void reqEnemy();
    bool isHoldEnemy();
    void signalAllEnemyPrepare();
    void signalAllEnemyPrepare2();
    void signalEnemyShot();
    void signalEnemyShotRand();
    void signalEnemyFastShotRand();
    void signalEnemySearchShotRand();
    void signalAllEnemyShot2();
    void unlinkEnemy(enemy::Enemy& enemy);
    void clearReqData();
    bool isHoldHero();
    void setDamageHero();
    void shotPrepareHero();
    void shotHero();
    void resetFollowIndex();

private:
    void setHandSubAnim(AnimKind kind);
    void reqEnemyIN(u32 index);

    Boss& mBoss;
    hel::common::MutableArray<ReqData, 3> mReqData;
    hel::common::Array<enemy::Accessor, 3> mEnemies;
    bool mIsActive;
    u32 mFollowIndex;
    AnimKind mHandSubAnim;
};

}}}}  // namespace scn::step::boss::doubter

#endif
