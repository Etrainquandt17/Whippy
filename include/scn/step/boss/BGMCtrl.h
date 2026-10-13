#ifndef SCN_STEP_BOSS_BGMCTRL_H
#define SCN_STEP_BOSS_BGMCTRL_H

namespace scn {
namespace step {
namespace boss {

// TODO: members.
class BGMCtrl {
public:
    void update();
    void startBossDemo();
    void startBossBattleNormal();
    void startBossBattleGrandLowper();
    void startBossBattleLandia();
    void startBossBattleLast1();
    void startBossBattleLast2();
    void startBossDead();
    void readyBossBattleHRD3();
    void startBossBattleHRD3Phase1();
    void startBossBattleHRD3Phase2();
    void startBossBattleGalactaKnightPhase2();
    void endBossBattleLast1();
    void endBossBattleLast2();
};

}}}  // namespace scn::step::boss

#endif
