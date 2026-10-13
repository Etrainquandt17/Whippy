#ifndef GOBJ_ISCRIPTCALLBACK_H
#define GOBJ_ISCRIPTCALLBACK_H

#include "types.h"

namespace gobj {

class Script;

class IScriptCallback {
public:
    virtual ~IScriptCallback();
    virtual void onScriptRequested(const Script& script, u32, u32) = 0;
    virtual void onScriptExecPre(const Script& script) = 0;
    virtual void onScriptExecPost(const Script& script) = 0;
};

}

#endif
