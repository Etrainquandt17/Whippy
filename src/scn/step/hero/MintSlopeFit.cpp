#include "scn/step/hero/MintSlopeFit.h"

#include "scn/step/hero/Hero.h"
#include "scn/step/hero/MintHero.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/SlopeFit.h"

namespace scn {
namespace step {
namespace hero {

namespace {

SlopeFit& t_obj() {
    return MintHero::Obj().model().slopeFit();
}

}

namespace MintSlopeFit {

void SetValid(bool valid) {
    t_obj().setValid(valid);
}

void SetIntpRate(f32 rate) {
    t_obj().setIntpRate(rate);
}

void SetAffectRate(f32 rate) {
    t_obj().setAffectRate(rate);
}

}}}}  // namespace scn::step::hero::MintSlopeFit
