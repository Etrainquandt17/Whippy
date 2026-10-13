#ifndef SCN_CHALLENGERESULT_INFO_TOTALSCORE_H
#define SCN_CHALLENGERESULT_INFO_TOTALSCORE_H

#include "types.h"

namespace scn {
namespace challengeresult {
namespace info {

class TotalScore {
public:
    void updateFrame();
    void skip();
    void bonusSkipEffect();
};

}
}
}

#endif
