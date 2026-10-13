#include "scn/step/weapon/ScriptCallback.h"

#include "scn/step/chara/Model.h"
#include "scn/step/weapon/Weapon.h"

namespace scn {
namespace step {
namespace weapon {

ScriptCallback::ScriptCallback(Weapon& weapon) : mObj(weapon) {
    weapon.model().registerScriptCallback(*this);
}

ScriptCallback::~ScriptCallback() {
    mObj.model().unregisterScriptCallback(*this);
}

void ScriptCallback::onScriptRequested(const gobj::Script& script, u32, u32) {}

void ScriptCallback::onScriptExecPre(const gobj::Script& script) {}

void ScriptCallback::onScriptExecPost(const gobj::Script& script) {}

}}}  // namespace scn::step::weapon
