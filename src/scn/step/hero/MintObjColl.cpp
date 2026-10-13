#include "scn/step/hero/MintObjColl.h"

#include "scn/step/hero/Hero.h"
#include "scn/step/hero/MintHero.h"
#include "scn/step/hero/ObjColl.h"

namespace scn {
namespace step {
namespace hero {

namespace {

ObjColl& t_obj() {
    return MintHero::Obj().objColl();
}

}

namespace MintObjColl {

void SetBodyCollDefault() {
    t_obj().setBodyCollDefault();
}

void SetBodyCollBig() {
    t_obj().setBodyCollBig();
}

void SetBodyCollSquat() {
    t_obj().setBodyCollSquat();
}

void SetBodyCollJump() {
    t_obj().setBodyCollJump();
}

}
}
}
}
