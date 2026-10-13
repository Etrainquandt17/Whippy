#ifndef SCN_STEP_BOSS_LOWPER_BACKEFFECTCTRL_H
#define SCN_STEP_BOSS_LOWPER_BACKEFFECTCTRL_H

namespace scn {
namespace step {
namespace boss {

class Boss;

namespace lowper {

class BackEffectCtrl {
public:
    BackEffectCtrl(Boss& boss);
    ~BackEffectCtrl();

    void update();
    void request();
    void release();
    void onDead();

private:
    Boss& mBoss;
    bool mIsRequested;
    bool mIsDead;
};

}
}
}
}

#endif
