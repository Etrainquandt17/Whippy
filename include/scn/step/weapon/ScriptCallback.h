#ifndef SCN_STEP_WEAPON_SCRIPTCALLBACK_H
#define SCN_STEP_WEAPON_SCRIPTCALLBACK_H

#include "gobj/IScriptCallback.h"

namespace scn {
namespace step {
namespace weapon {

class Weapon;

class ScriptCallback : public gobj::IScriptCallback {
public:
    ScriptCallback(Weapon& weapon);
    virtual ~ScriptCallback();
    virtual void onScriptRequested(const gobj::Script& script, u32, u32);
    virtual void onScriptExecPre(const gobj::Script& script);
    virtual void onScriptExecPost(const gobj::Script& script);

private:
    Weapon& mObj;
};

}}}  // namespace scn::step::weapon

#endif
