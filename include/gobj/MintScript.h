#ifndef GOBJ_MINTSCRIPT_H
#define GOBJ_MINTSCRIPT_H

#include "types.h"

namespace gobj {

class Script;

namespace MintScript {

void Register(Script& obj);
void Unregister(Script& obj);
u32 PrevScriptIndex();

}
}

#endif
