#ifndef SCN_STEP_CARRYITEM_ISTATE_H
#define SCN_STEP_CARRYITEM_ISTATE_H

#include "util/IState.h"

namespace scn {
namespace step {
namespace carryitem {

class IState : public util::IState {
public:
    // TODO: the five proc functions are IState's, which does not declare them yet.
    virtual ~IState();
};

}}}  // namespace scn::step::carryitem

#endif
