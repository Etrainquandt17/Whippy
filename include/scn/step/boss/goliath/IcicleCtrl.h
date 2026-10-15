#ifndef SCN_STEP_BOSS_GOLIATH_ICICLECTRL_H
#define SCN_STEP_BOSS_GOLIATH_ICICLECTRL_H

#define HEL_COMMON_MUTABLEARRAY_DESTRUCTOR_IN_CLASS
#define HEL_COMMON_MUTABLEARRAY_ADD_IN_CLASS
#define HEL_COMMON_MUTABLEARRAY_REMOVEATINDEX_IN_CLASS

#include "hel/common/Array.h"
#include "hel/common/MutableArray.h"
#include "types.h"
#include "util/ObjRefHandle.h"

namespace scn {
namespace step {
namespace boss {
namespace goliath {

}}  // namespace boss::goliath
namespace enemy {
class Enemy;
}
namespace boss {
class Boss;
namespace goliath {

class IcicleCtrl {
public:
    IcicleCtrl(Boss& boss);

    void updateRequest();
    void startRequest();
    void request(f32 x);
    void down();
    void fall();
    void cleanup();

private:
    Boss& mBoss;
    hel::common::MutableArray<util::ObjRefHandle<enemy::Enemy>, 8> mIcicles;
    hel::common::MutableArray<f32, 8> mRequests;
};

}}}}  // namespace scn::step::boss::goliath

#endif
