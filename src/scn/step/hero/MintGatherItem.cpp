#include "scn/step/hero/MintGatherItem.h"

#include "scn/step/hero/GatherItem.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/MintHero.h"

namespace scn {
namespace step {
namespace hero {

namespace {

GatherItem& t_obj() {
    return MintHero::Obj().gatherItem();
}

}

namespace MintGatherItem {

void Add(f32 left, f32 top, f32 right, f32 bottom) {
    t_obj().add(hel::geo::Rect(left, top, right, bottom));
}

void Clear() {
    t_obj().clear();
}

}}}}  // namespace scn::step::hero::MintGatherItem
