#include "scn/step/boss/whispy/StateAppear.h"

#include "scn/step/Component.h"
#include "scn/step/boss/BGMCtrl.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Invincible.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/whispy/StateWait.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ScriptTrigger.h"
#include "scn/step/hero/Manager.h"

namespace scn {
namespace step {
namespace boss {
namespace whispy {

StateAppear::StateAppear(Boss* boss) : StateBase(boss), mIsWaitDemoReady(true), mIsGameStarted(false), mIsBgmStarted(false) {
    obj().invincible().setPermNoFlash();
    obj().bgmCtrl().startBossDemo();
    if (Utility::IsStagingFirstAppear(obj())) {
        Utility::StagingFirstAppearStart(obj());
    } else {
        obj().model().reqScript(1);
        mIsWaitDemoReady = false;
    }
}

StateAppear::~StateAppear() {}

void StateAppear::procAnim() {
    if (Utility::IsStagingFirstAppear(obj()) && Utility::IsAppearDemoCancelRequested(obj())) {
        startGame();
        startBgm();
        obj().stateChanger().setNextState<StateWait, Boss*>(objPtr());
        return;
    }
    if (mIsWaitDemoReady) {
        if (obj().comp().heroManager().isBossDemoReady()) {
            mIsWaitDemoReady = false;
            obj().model().reqScript(0x16);
        }
    } else {
        if (obj().scriptTrigger().get(0)) {
            startGame();
        }
        if (obj().scriptTrigger().get(1)) {
            startBgm();
        }
        if (obj().model().isAllEnd()) {
            obj().stateChanger().setNextState<StateWait, Boss*>(objPtr());
        }
    }
}

void StateAppear::procMove() {}

void StateAppear::procFixPos() {}

void StateAppear::startGame() {
    if (!mIsGameStarted) {
        mIsGameStarted = true;
        Utility::AppearBossPanel(obj());
        if (Utility::IsStagingFirstAppear(obj())) {
            Utility::StagingFirstAppearEnd(obj());
        }
    }
}

void StateAppear::startBgm() {
    if (!mIsBgmStarted) {
        mIsBgmStarted = true;
        obj().bgmCtrl().startBossBattleNormal();
    }
}

}
}
}
}
