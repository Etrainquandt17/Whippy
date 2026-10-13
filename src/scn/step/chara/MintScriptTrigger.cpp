#include "scn/step/chara/MintScriptTrigger.h"

#include "hel/common/PointerWrapper.h"
#include "scn/step/chara/ScriptTrigger.h"

namespace scn {
namespace step {
namespace chara {

namespace {

hel::common::PointerWrapper<ScriptTrigger> t_obj;

}

namespace MintScriptTrigger {

void Register(ScriptTrigger& obj) {
    t_obj.set(obj);
}

void Unregister(ScriptTrigger&) {
    t_obj.reset();
}

void Set(u32 trigger) {
    t_obj->set(trigger);
}

}}}}  // namespace scn::step::chara::MintScriptTrigger
