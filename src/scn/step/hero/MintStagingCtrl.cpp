#include "scn/step/hero/MintStagingCtrl.h"

#include "mintglue/VectorInline.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/MintHero.h"
#include "scn/step/hero/StagingCtrl.h"

using hel::math::Vector2;

namespace scn {
namespace step {
namespace hero {

namespace {

StagingCtrl& t_obj() {
    return MintHero::Obj().stagingCtrl();
}

}

namespace MintStagingCtrl {

void SetZoom(f32 x, f32 y, f32 rate) {
    t_obj().setZoom(Vector2(x, y), rate);
}

void SetZoom(f32 rate) {
    t_obj().setZoom(rate);
}

void UnsetZoom() {
    t_obj().unsetZoom();
}

void SetCamRot(f32 x, f32 y) {
    t_obj().setCamRot(x, y);
}

void UnsetCamRot() {
    t_obj().unsetCamRot();
}

}}}}  // namespace scn::step::hero::MintStagingCtrl
