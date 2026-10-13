#ifndef SCN_STEP_BOSS_METALGENERAL_STATEBOMBJOINT_H
#define SCN_STEP_BOSS_METALGENERAL_STATEBOMBJOINT_H

#include "scn/step/boss/StateBase.h"

namespace scn {
namespace step {
namespace boss {
namespace metalgeneral {

class StateBombJoint : public StateBase {
public:
    // TODO: name the kinds.
    enum JointKind {
        JOINT_KIND_0,
        JOINT_KIND_1,
    };

    StateBombJoint(Boss* boss, JointKind kind);
    virtual ~StateBombJoint();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    JointKind mKind;
};

}
}
}
}

#endif
