#ifndef SCN_STEP_BOSS_OBJINFOIMPL_H
#define SCN_STEP_BOSS_OBJINFOIMPL_H

#include "scn/step/debug/IObjInfoImpl.h"

namespace scn {
namespace step {
namespace boss {

class Boss;

class ObjInfoImpl : public debug::IObjInfoImpl {
public:
    ObjInfoImpl(Boss& boss);
    virtual ~ObjInfoImpl();
    virtual hel::common::FixedString<32> name() const;
    virtual const gobj::Anim& anim() const;
    virtual const gobj::FootState& footState() const;
    virtual const chara::HitPoint& hitPoint() const;
    virtual const gobj::Location& location() const;
    virtual const gobj::Move& move() const;
    virtual const gobj::Script& script() const;
    virtual const util::IState& state() const;

private:
    Boss& mBoss;
};

}
}
}

#endif
