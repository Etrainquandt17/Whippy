#ifndef SCN_STEP_BOSS_ISTATE_H
#define SCN_STEP_BOSS_ISTATE_H

#include "util/IState.h"

namespace scn {
namespace step {
namespace boss {

class IState : public util::IState {
public:
    // TODO: the other virtual functions.
    virtual ~IState();
};

}
}
}

#endif
