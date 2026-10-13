#ifndef SCN_CHALLENGERESULT_INFO_MANAGER_H
#define SCN_CHALLENGERESULT_INFO_MANAGER_H

#include "scn/challengeresult/info/ResultLyt.h"
#include "types.h"

namespace scn {
namespace challengeresult {
namespace info {

class Manager {
public:
    void procAnim();
    void procReadyToRender();

    u8 _0[0x384];
    ResultLyt mResultLyt;
    u8 _5670[0x5784 - 0x5670];
};

}}}  // namespace scn::challengeresult::info

#endif
