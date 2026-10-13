#include "scn/step/boss/ScriptCallback.h"

#include "scn/step/boss/Boss.h"
#include "scn/step/boss/ICustom.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"

namespace scn {
namespace step {
namespace boss {

ScriptCallback::ScriptCallback(Boss& boss) : mBoss(boss) {
    boss.model().registerScriptCallback(*this);
}

ScriptCallback::~ScriptCallback() {
    mBoss.model().unregisterScriptCallback(*this);
}

void ScriptCallback::onScriptRequested(const gobj::Script& script, u32, u32) {
    mBoss.model().rotCtrl().resetRotTarget();
    mBoss.custom()->onScriptRequested();
}

void ScriptCallback::onScriptExecPre(const gobj::Script& script) {
    Utility::MintRegister(mBoss);
}

void ScriptCallback::onScriptExecPost(const gobj::Script& script) {
    Utility::MintUnregister(mBoss);
}

}}}  // namespace scn::step::boss
