#ifndef SCN_CHALLENGERESULT_INFO_RESULTLYT_H
#define SCN_CHALLENGERESULT_INFO_RESULTLYT_H

#include "lyt/Layout.h"
#include "scn/challengeresult/info/TotalScore.h"
#include "types.h"
#include "util/FrameCounter.h"

namespace scn {
namespace challengeresult {
namespace info {

class ResultLyt {
public:
    bool isAnimEnd() const;
    void updateFrame();
    void updateFrame1();
    void stateStart();
    void stateCountUp();
    void stateCountWait();
    void stateTimeBonus();
    void stateBonus();

    // The Korean version has 0x194 bytes more somewhere before the three flags.
#ifdef VERSION_SUKK01
    enum { EXTRA = 0x194 };
#else
    enum { EXTRA = 0 };
#endif

    u8 _0[0x8];
    int mState;
    u8 _C[0x4];
    util::FrameCounter _10;
    lyt::Layout _18;
    u8 _1A8[0x660 - 0x1A8];
    TotalScore _660;
    u8 _661[0x52E8 + EXTRA - 0x661];
    bool _52E8;
    bool _52E9;
    bool _52EA;
};

}}}  // namespace scn::challengeresult::info

#endif
