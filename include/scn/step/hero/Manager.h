#ifndef SCN_STEP_HERO_MANAGER_H
#define SCN_STEP_HERO_MANAGER_H

#include "types.h"
#include "util/ObjRefHandle.h"

namespace hel {
namespace math {

class Vector3;

}
namespace geo {

class Rect;

}}  // namespace hel::geo

namespace scn {
namespace step {
namespace hero {

class BossDemoCtrl;
class ClearDanceSync;
class GeneralState;
class Hero;
class MoveLimitResponseCtrl;
class PiggybackTotalCtrl;

class Manager {
public:
    bool isExistPlayerInside(const hel::geo::Rect& rect) const;
    void clearOthersSuperAbility(u32 padChan);
    void incPauseDisableCount();
    void decPauseDisableCount();
    bool isUnlockLvMapDoorReadyAll() const;
    void setNextStateClearDance();
    void setSpreadHitStopCannon(u32 index, u32 frame);
    void setSpreadHitStopScrewSuper(u32 frame);
    BossDemoCtrl& bossDemoCtrl();
    ClearDanceSync& clearDanceSync();
    hel::math::Vector3 getNearestPlayerPos(const hel::math::Vector3& pos) const;
    util::ObjRefHandle<Hero> getNearestVisiblePlayer(const hel::math::Vector3& pos);
    hel::math::Vector3 getMainPlayerPos() const;
    hel::math::Vector3 getKeyCarryingNearestPlayerPos(const hel::math::Vector3& pos) const;
    u32 getPlayerCount() const;
    Hero& getPlayerByIndex(u32 index);
    Hero& getMainPlayer();
    util::ObjRefHandle<Hero> searchHeroFromObjCollOwnerID(u64 id);
    bool canShowWarpStarPanel() const;
    bool isSuperActionTime() const;
    hel::math::Vector3 getPlayerPosByIndex(u32 index) const;
    bool isBossDemoReady() const;
    void setClearDanceOffset(u32 index, const hel::math::Vector3& offset);
    MoveLimitResponseCtrl& moveLimitResponseCtrl();
    util::ObjRefHandle<Hero> searchHeroFromPadChan(u32 padChan);
    void setHidDisable();
    void setHidEnable();
    void setNextStateLandiaEscape(bool flag);
    void setSpaceJumpForce(const hel::geo::Rect& rect, const hel::math::Vector3& pos);
    void setSpaceJumpForceGivenPlayer(u32 index, const hel::geo::Rect& rect, const hel::math::Vector3& pos);
    void setNextStateDemoFallAll();
    void removeHero(u32 padChan);
    bool isClearDanceReadyAll() const;
    void setClearDanceReadyAllForce();
    void cureAll();
    hel::math::Vector3 getClearDancePos(u32 padChan);
    GeneralState& generalState();
    PiggybackTotalCtrl& piggybackTotalCtrl();
    void setPreventDamage();
    void setForbidInactiveHeroControl();
    void unsetForbidInactiveHeroControl();
};

}}}  // namespace scn::step::hero

#endif
