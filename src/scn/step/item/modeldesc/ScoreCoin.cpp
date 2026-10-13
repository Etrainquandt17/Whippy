#include "scn/step/item/modeldesc/ScoreCoin.h"

#include "scn/step/item/ModelDescUtil.h"

namespace scn {
namespace step {
namespace item {
namespace modeldesc {

namespace ScoreCoin {

chara::ModelDesc& Create(u32 variation) {
    switch (static_cast<int>(variation)) {
    case 0:
    case 2:
    case 4:
        return ModelDescUtil::CreateGeneral<9, 0>("ScoreCoinS", "step/item/ScoreCoinS", "TopL");
    case 1:
    case 3:
    case 5:
        return ModelDescUtil::CreateGeneral<9, 1>("ScoreCoinB", "step/item/ScoreCoinB", "TopL");
    default:
        return ModelDescUtil::CreateGeneral<9, 0>("ScoreCoinS", "step/item/ScoreCoinS", "TopL");
    }
}

}

}}}}  // namespace scn::step::item::modeldesc
