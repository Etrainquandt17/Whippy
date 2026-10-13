#ifndef SCN_STEP_ITEM_ISTATE_H
#define SCN_STEP_ITEM_ISTATE_H

#include "util/IState.h"

namespace scn {
namespace step {
namespace item {

class IState : public util::IState {
public:
    // TODO: the other virtual functions.
    virtual ~IState();
};

}}}  // namespace scn::step::item

#endif
