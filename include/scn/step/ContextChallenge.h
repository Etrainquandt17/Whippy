#ifndef SCN_STEP_CONTEXTCHALLENGE_H
#define SCN_STEP_CONTEXTCHALLENGE_H

#include "scn/step/challenge/Score.h"
#include "types.h"

namespace scn {
namespace step {

class ContextChallenge {
public:
    static ContextChallenge Create();

    u32 _0;
    challenge::Score mScore;
    bool _88;
    bool _89;
};

}}  // namespace scn::step

#endif
