#include "scn/step/carryitem/lockkey/ModelDesc.h"

#include "scn/step/carryitem/ModelDescUtil.h"

namespace scn {
namespace step {
namespace carryitem {
namespace lockkey {

namespace ModelDesc {

chara::ModelDesc& Create() {
    return ModelDescUtil::CreateGeneral<1, 0>("LockKey", "step/item/LockKey", "TopL");
}

}

}}}}  // namespace scn::step::carryitem::lockkey
