#ifndef SCN_STEP_CARRYITEM_PARAM_H
#define SCN_STEP_CARRYITEM_PARAM_H

#include "types.h"

namespace scn {
namespace step {
namespace carryitem {

class Param {
public:
    Param();
    ~Param();

private:
    u8 _0[0xA0];
};

}}}  // namespace scn::step::carryitem

#endif
