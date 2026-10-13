#ifndef SCN_STEP_ENEMY_VACUUMRECEIVER_H
#define SCN_STEP_ENEMY_VACUUMRECEIVER_H

#include "hel/math/Vector2.h"
#include "types.h"

namespace hel {
namespace geo {

class Rect;

}}  // namespace hel::geo

namespace scn {
namespace step {
namespace enemy {

class Enemy;

// TODO: members and the other functions.
class VacuumReceiver {
public:
    VacuumReceiver(Enemy& enemy);
    ~VacuumReceiver();

    void setIsValid(bool isValid);
    void unsetSyncReceiver();
    void procAnim();
    void setEndVacuumed();
    hel::math::Vector2 getAttackerPos() const;
    bool isResist() const;
    hel::math::Vector2 getResistAttackerPos() const;
    u32 getResistLevelTotal();
    void setResistLevel(u32 level);
    void setResistLevelInterim(u32 level, u32 frame);
    void setResistLevelStep(u32 step);
    void clearResistLevelStep();
    void setCustomCollideRect(const hel::geo::Rect& rect);
};

}}}  // namespace scn::step::enemy

#endif
