#ifndef SCN_STEP_GIMMICK_CHALLENGEDOOR_MINTCHALLENGEDOOR_H
#define SCN_STEP_GIMMICK_CHALLENGEDOOR_MINTCHALLENGEDOOR_H

namespace scn {
namespace step {
namespace gimmick {
namespace challengedoor {

class ChallengeDoor;

class MintChallengeDoor {
public:
    static void Register(ChallengeDoor& obj);
    static void Unregister(ChallengeDoor& obj);
    static ChallengeDoor& Obj();
};

}
}
}
}

#endif
