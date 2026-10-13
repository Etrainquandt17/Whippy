#ifndef SCN_STEP_CHALLENGE_SCORE_H
#define SCN_STEP_CHALLENGE_SCORE_H

#include "scn/step/challenge/Param.h"
#include "types.h"

namespace scn {
namespace step {
namespace challenge {

class Score {
public:
    Score();

    int getTotalScore() const;
    void calcBonus();
    int medalKind() const;

private:
    Param::CommonParam mCommonParam;
    Param::StageParam1 mStageParam;
    u32 _54;
    u32 _58;
    u32 _5C;
    u32 _60;
    u32 _64;
    bool _68;
    bool _69;
    bool _6A;
    u32 _6C;
    u32 _70;
    u32 _74;
    bool _78;
    bool _79;
    u32 _7C;
    bool _80;
};

}
}
}

#endif
