#ifndef SCN_STEP_CARRYITEM_SCRIPTCALLBACK_H
#define SCN_STEP_CARRYITEM_SCRIPTCALLBACK_H

#include "gobj/IScriptCallback.h"

namespace scn {
namespace step {
namespace carryitem {

class CarryItem;

class ScriptCallback : public gobj::IScriptCallback {
public:
    ScriptCallback(CarryItem& carryItem);
    virtual ~ScriptCallback();
    virtual void onScriptRequested(const gobj::Script& script, u32, u32);
    virtual void onScriptExecPre(const gobj::Script& script);
    virtual void onScriptExecPost(const gobj::Script& script);

private:
    CarryItem& mObj;
};

}}}  // namespace scn::step::carryitem

#endif
