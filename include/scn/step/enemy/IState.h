#ifndef SCN_STEP_ENEMY_ISTATE_H
#define SCN_STEP_ENEMY_ISTATE_H

#include "util/IState.h"

namespace scn {
namespace step {
namespace enemy {

class IState : public util::IState {
public:
    // TODO: the other virtual functions.
    virtual ~IState();
};

}}}  // namespace scn::step::enemy

#endif
