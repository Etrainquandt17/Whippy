#ifndef SCN_STEP_BOSS_WHISPY_DAMAGEEYECTRL_H
#define SCN_STEP_BOSS_WHISPY_DAMAGEEYECTRL_H

namespace scn {
namespace step {
namespace boss {
namespace whispy {

}

class Boss;

namespace whispy {

class DamageEyeCtrl {
public:
    DamageEyeCtrl(Boss& boss);

    void update();
    void set();

private:
    Boss& mBoss;
    bool mIsSet;
};

}
}
}
}

#endif
