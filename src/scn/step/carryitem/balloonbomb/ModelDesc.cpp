#include "scn/step/carryitem/balloonbomb/ModelDesc.h"

#include "scn/step/carryitem/ModelDescUtil.h"

namespace scn {
namespace step {
namespace carryitem {
namespace balloonbomb {

namespace ModelDesc {

chara::ModelDesc& Create() {
    return ModelDescUtil::CreateGeneral<6, 0>("BalloonBomb", "step/item/BalloonBomb", "TopL");
}

}

}}}}  // namespace scn::step::carryitem::balloonbomb
