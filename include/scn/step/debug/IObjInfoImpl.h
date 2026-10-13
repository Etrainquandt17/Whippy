#ifndef SCN_STEP_DEBUG_IOBJINFOIMPL_H
#define SCN_STEP_DEBUG_IOBJINFOIMPL_H

#include "hel/common/FixedString.h"

namespace gobj {

class Anim;
class FootState;
class Location;
class Move;
class Script;

}

namespace util {

class IState;

}

namespace scn {
namespace step {

namespace chara {

class HitPoint;

}

namespace debug {

// TODO: the return types are guesses, except the name's; each is a pointer or a reference.
class IObjInfoImpl {
public:
    virtual ~IObjInfoImpl();
    virtual hel::common::FixedString<32> name() const = 0;
    virtual const gobj::Anim& anim() const = 0;
    virtual const gobj::FootState& footState() const = 0;
    virtual const chara::HitPoint& hitPoint() const = 0;
    virtual const gobj::Location& location() const = 0;
    virtual const gobj::Move& move() const = 0;
    virtual const gobj::Script& script() const = 0;
    virtual const util::IState& state() const = 0;
};

}
}
}

#endif
