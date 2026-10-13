#ifndef SCN_SUBGAME_GUNSHOOT_ENEMY_DAMAGEANIMATOR_H
#define SCN_SUBGAME_GUNSHOOT_ENEMY_DAMAGEANIMATOR_H

#include "g3d/ModelAnimAccessor.h"
#include "scn/subgame/gunshoot/enemy/AnimParam.h"
#include "scn/subgame/gunshoot/enemy/AnimatorTarget.h"
#include "scn/subgame/gunshoot/enemy/HitAttribute.h"
#include "types.h"
#include "util/FrameCounter.h"

namespace scn {
namespace subgame {
namespace gunshoot {

namespace chara {
class StageConstant;
}

namespace enemy {

class PlayListSetController;

class DamageAnimator {
public:
    DamageAnimator(const chara::StageConstant& stageConstant, AnimatorTarget target);
    ~DamageAnimator();

    void initialize(HitAttribute attribute);
    void initializeForStun();
    void initializeForClimaxEx();
    void initPlayListSet(PlayListSetController& playListSet);
    void resume(bool damage);
    void resumeForStun();
    void resumeForClimaxEx();
    void updateMain();
    bool isEnd() const;
    void startDamage();
    void startDamageForStun();
    void startDamageForClimaxEx();
    void startPlayListIfNecessary(int index);

private:
    int _0;
    AnimParam mAnimParam;
    AnimatorTarget mTarget;
    HitAttribute mHitAttribute;
    g3d::ModelAnimAccessor _D30;
    bool mIsStun;
    bool mIsClimaxEx;
    util::FrameCounter mCounter;
    PlayListSetController* mPlayListSet;
};

}}}}  // namespace scn::subgame::gunshoot::enemy

#endif
