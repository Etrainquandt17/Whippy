#ifndef SCN_STEP_WEAPON_WATERUNDERWATER_STATEWARP_H
#define SCN_STEP_WEAPON_WATERUNDERWATER_STATEWARP_H

#include "scn/step/weapon/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace weapon {
namespace waterunderwater {

class StateWarp : public StateBase {
public:
    StateWarp(Weapon* weapon);
    virtual ~StateWarp();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
    virtual void procObjCollReact();
};

}}}}  // namespace scn::step::weapon::waterunderwater

#endif
