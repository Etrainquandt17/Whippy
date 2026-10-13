#include "scn/step/hero/MintFloaterRotCtrl.h"

#include "scn/step/hero/Hero.h"
#include "scn/step/hero/MintHero.h"
#include "scn/step/hero/FloaterRotCtrl.h"
#include "scn/step/hero/Model.h"

namespace scn {
namespace step {
namespace hero {

namespace {

FloaterRotCtrl& t_obj() {
    return MintHero::Obj().model().floaterRotCtrl();
}

}

namespace MintFloaterRotCtrl {

f32 GetRotV() {
    return t_obj().getRotV();
}

void InitRotV(f32 rot) {
    t_obj().initRotV(rot);
}

void SetRotVTarget(f32 rot) {
    t_obj().setRotVTarget(rot);
}

void ResetRotVTarget() {
    t_obj().resetRotVTarget();
}

void SetRotVIntpRate(f32 rate) {
    t_obj().setRotVIntpRate(rate);
}

void ResetRotVIntpRate() {
    t_obj().resetRotVIntpRate();
}

}
}
}
}
