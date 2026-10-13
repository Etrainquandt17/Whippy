#include "scn/step/carryitem/ScriptCallback.h"

#include "scn/step/carryitem/CarryItem.h"
#include "scn/step/chara/Model.h"

namespace scn {
namespace step {
namespace carryitem {

ScriptCallback::ScriptCallback(CarryItem& carryItem)
    : mObj(carryItem) {
    carryItem.model().registerScriptCallback(*this);
}

ScriptCallback::~ScriptCallback() {
    mObj.model().unregisterScriptCallback(*this);
}

void ScriptCallback::onScriptRequested(const gobj::Script& script, u32, u32) {}

void ScriptCallback::onScriptExecPre(const gobj::Script& script) {}

void ScriptCallback::onScriptExecPost(const gobj::Script& script) {}

}}}  // namespace scn::step::carryitem
