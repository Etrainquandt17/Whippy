#ifndef SCN_WMAP_HERO_INACTIVESTATE_H
#define SCN_WMAP_HERO_INACTIVESTATE_H

#include "util/IState.h"

namespace scn {
namespace wmap {
namespace hero {

class InactiveHero;

class IInactiveState : public util::IState {
public:
    virtual ~IInactiveState();
    virtual void proc();
};

namespace inactive {

// TODO: members of both.
class StateInit : public IInactiveState {
public:
    StateInit(InactiveHero* hero);
    virtual ~StateInit();
};

class StateSelect : public IInactiveState {
public:
    StateSelect(InactiveHero* hero, bool);
    virtual ~StateSelect();
};

}

}
}
}

#endif
