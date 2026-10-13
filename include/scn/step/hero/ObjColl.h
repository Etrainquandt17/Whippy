#ifndef SCN_STEP_HERO_OBJCOLL_H
#define SCN_STEP_HERO_OBJCOLL_H

#include "scn/step/chara/ObjColl.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {

class ObjColl {
public:
    void setBodyCollDefault();
    void setBodyCollBig();
    void setBodyCollSquat();
    void setBodyCollJump();
    void setBodyCollLandia();
    // TODO: the name is a guess.
    chara::ObjColl& objColl() { return mObjColl; }
    void setXlu();
    void unsetXlu();
    ::ocoll::Owner& owner();

private:
    u32 _0[2];
    chara::ObjColl mObjColl;
};

}
}
}

#endif
