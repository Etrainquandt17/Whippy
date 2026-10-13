#ifndef SCN_STEP_BOSS_SCRIPTCALLBACK_H
#define SCN_STEP_BOSS_SCRIPTCALLBACK_H

#include "gobj/IScriptCallback.h"

namespace scn {
namespace step {
namespace boss {

class Boss;

class ScriptCallback : public gobj::IScriptCallback {
public:
    ScriptCallback(Boss& boss);
    virtual ~ScriptCallback();
    virtual void onScriptRequested(const gobj::Script& script, u32, u32);
    virtual void onScriptExecPre(const gobj::Script& script);
    virtual void onScriptExecPost(const gobj::Script& script);

private:
    Boss& mBoss;
};

}}}  // namespace scn::step::boss

#endif
