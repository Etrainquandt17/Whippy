#ifndef SCN_STEP_CHALLENGEKIND_H
#define SCN_STEP_CHALLENGEKIND_H

namespace scn {
namespace step {

// Named after the challenge names in ChallengeKindUtil's T_INFOS. 1, 4 and 8 have no entry there.
enum ChallengeKind {
    CHALLENGE_KIND_SWORD,
    CHALLENGE_KIND_1,
    CHALLENGE_KIND_WHIP,
    CHALLENGE_KIND_WATER,
    CHALLENGE_KIND_4,
    CHALLENGE_KIND_BOMB,
    CHALLENGE_KIND_WING,
    CHALLENGE_KIND_CARRY,
    CHALLENGE_KIND_8,
    CHALLENGE_KIND_HIGHJUMP,
    CHALLENGE_KIND_NUM,
};

}
}

#endif
