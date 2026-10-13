#ifndef SCN_CHALLENGERESULT_EFFECT_MANAGER_H
#define SCN_CHALLENGERESULT_EFFECT_MANAGER_H

#include "types.h"

namespace scn {
namespace challengeresult {
namespace effect {

class Manager {
public:
    void procAnim();
    void procReadyToRender();

private:
    u8 _0[0x31C - 0x154];
};

}}}  // namespace scn::challengeresult::effect

#endif
