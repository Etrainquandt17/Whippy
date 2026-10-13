#ifndef SCN_STEP_CHALLENGE_PARAM_H
#define SCN_STEP_CHALLENGE_PARAM_H

#include "types.h"

namespace scn {
namespace step {
namespace challenge {

class Param {
public:
    struct CommonParam {
        u32 _0[11];
    };

    struct StageParam1 {
        u32 _0[10];
    };
};

}}}  // namespace scn::step::challenge

#endif
