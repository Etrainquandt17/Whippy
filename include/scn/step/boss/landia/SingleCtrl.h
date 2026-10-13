#ifndef SCN_STEP_BOSS_LANDIA_SINGLECTRL_H
#define SCN_STEP_BOSS_LANDIA_SINGLECTRL_H

namespace scn {
namespace step {
namespace boss {

class Boss;

namespace landia {

// TODO: the other kinds.
enum SignalKind {
    SignalKind_GrandCrossNipRestart = 18
};

// TODO: members.
class SingleCtrl {
public:
    SingleCtrl(Boss& boss);

    void signal(SignalKind kind);
    bool flagActionEnd();
    void reqGrandCross(SignalKind kind);
    void setFireRainStarHitHeightSingleNum();
    void onFinishFormationPass();
    void generate();
    void dead();
    void generateStagingDead();
    void onDamage();
    void setFormationPassAnybodyWeaponHolding(bool flag);
    bool isFormationPassAnybodyWeaponHolding() const;
    bool isValid();
};

}
}
}
}

#endif
