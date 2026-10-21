#ifndef SCN_CHALLENGERESULT_SCENECHALLENGERESULT_H
#define SCN_CHALLENGERESULT_SCENECHALLENGERESULT_H

#include "scn/challengeresult/effect/Manager.h"
#include "scn/challengeresult/info/Manager.h"
#include "scn/step/ChallengeKind.h"
#include "scn/step/ContextChallenge.h"
#include "sfx/Fade.h"
#include "storage/StoryData.h"
#include "types.h"
#include "util/FrameCounter.h"

namespace scn {
namespace challengeresult {

class SceneChallengeResult {
public:
    class Recipe {
    public:
        static Recipe Create(step::ChallengeKind kind, bool isExtraMode, step::ContextChallenge context,
                             storage::StoryData::ChallengeData data);

        Recipe(const Recipe& other);

    private:
        u32 _0[0x2A];
    };

    struct Result {
        bool _0;
        bool _1;
    };

    SceneChallengeResult(const Recipe& recipe);

    Result result();

    void updateMain();

private:
    u8 _0[0x154];
    effect::Manager mEffect;
    int mState;
    u8 _320[0x3B0 - 0x320];
    // TODO: util::PlacementNew<info::Manager>, whose access to the object is
    // inline here; util/PlacementNew.h has none yet.
    info::Manager* mInfo;
    u8 _3B4[sizeof(info::Manager)];
    util::FrameCounter mCounter;
    sfx::Fade mFade;
    u32 _5B64[(0x5C80 - 0x5B64) / 4];
    bool _5C80;
    bool _5C81;
};

}}  // namespace scn::challengeresult

#endif
