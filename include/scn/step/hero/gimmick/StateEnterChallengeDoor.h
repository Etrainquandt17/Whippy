#ifndef SCN_STEP_HERO_GIMMICK_STATEENTERCHALLENGEDOOR_H
#define SCN_STEP_HERO_GIMMICK_STATEENTERCHALLENGEDOOR_H

#include "hel/math/Vector2.h"
#include "scn/step/ChallengeKind.h"
#include "types.h"
#include "util/IState.h"

namespace scn {
namespace step {
namespace hero {

class Hero;

namespace gimmick {

// TODO: members and the other virtual functions unknown; only what
// scn/step/gimmick/challengedoor/ChallengeDoor.cpp needs is declared.
class StateEnterChallengeDoor : public util::IState {
public:
    StateEnterChallengeDoor(Hero* hero, const hel::math::Vector2& pos, ChallengeKind kind, bool);
    virtual ~StateEnterChallengeDoor();

    static bool TryToChangeState(Hero* hero);
};

}}}}  // namespace scn::step::hero::gimmick

#endif
