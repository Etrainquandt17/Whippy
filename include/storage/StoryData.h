#ifndef STORAGE_STORYDATA_H
#define STORAGE_STORYDATA_H

#include "scn/step/ChallengeKind.h"
#include "scn/step/LevelKind.h"
#include "types.h"

namespace storage {

class StoryData {
public:
    struct StageData {
        u8 _0;
        bool isSphereGet[5];
    };

    struct SphereUnlockData {
        bool unlocked;
        bool entered;
        bool executedDemo;
    };

    struct ChallengeData {
        int scoreNum;
        int medalKind;
        int scores[3];
    };

    // TODO: 8 bytes each, from 0xF4.
    struct LevelData {
        u32 _0;
        bool _4;
    };

    LevelData& levelData(scn::step::LevelKind level);
    ChallengeData& challengeData(scn::step::ChallengeKind kind);
    u32 sphereGetCount() const;

    u8 _0[0x8];
    StageData stageData[39];
    u8 _F2[0x42];
    // TODO: how many there are is not known.
    SphereUnlockData sphereUnlockData[1];
};

}  // namespace storage

#endif
