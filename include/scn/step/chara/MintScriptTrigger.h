#ifndef SCN_STEP_CHARA_MINTSCRIPTTRIGGER_H
#define SCN_STEP_CHARA_MINTSCRIPTTRIGGER_H

#include "types.h"

namespace scn {
namespace step {
namespace chara {

class ScriptTrigger;

namespace MintScriptTrigger {

void Register(ScriptTrigger& obj);
void Unregister(ScriptTrigger& obj);
void Set(u32 trigger);

}}}}  // namespace scn::step::chara::MintScriptTrigger

#endif
