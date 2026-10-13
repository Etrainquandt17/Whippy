#ifndef SCN_STEP_WEAPON_MANAGER_H
#define SCN_STEP_WEAPON_MANAGER_H

#include "scn/step/ocoll/TeamNo.h"
#include "types.h"
#include "util/ObjRefHandle.h"

namespace scn {
namespace step {
namespace weapon {

class Desc;
class Weapon;

// TODO: members and the other functions.
class Manager {
public:
    util::ObjRefHandle<Weapon> request(const Desc& desc);
    void reqDeadByTeamNo(ocoll::TeamNo teamNo);
    void reqDeadByTeamNoForBoss(ocoll::TeamNo teamNo);
};

}}}  // namespace scn::step::weapon

#endif
