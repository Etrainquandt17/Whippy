#ifndef SCN_STEP_BOSS_GALACTAKNIGHT_THUNDERSPINECTRL_H
#define SCN_STEP_BOSS_GALACTAKNIGHT_THUNDERSPINECTRL_H

#define HEL_COMMON_MUTABLEARRAY_DESTRUCTOR_IN_CLASS
#define HEL_COMMON_MUTABLEARRAY_ADD_IN_CLASS
#define HEL_COMMON_MUTABLEARRAY_REMOVEATINDEX_IN_CLASS

#include "hel/common/MutableArray.h"
#include "types.h"
#include "util/ObjRefHandle.h"

namespace scn {
namespace step {
namespace boss {
namespace galactaknight {

}}  // namespace boss::galactaknight
namespace weapon {
class Weapon;
}
namespace boss {
class Boss;
namespace galactaknight {

class ThunderSpineCtrl {
public:
    struct ReqData {
        f32 _0;
    };

    ThunderSpineCtrl(Boss& boss);

    void add(const ReqData& data);
    ReqData pick();
    void clear();
    bool isEmpty() const;
    void request();
    void attack();
    void cleanup();

private:
    Boss& mBoss;
    hel::common::MutableArray<util::ObjRefHandle<weapon::Weapon>, 8> mWeapons;
    hel::common::MutableArray<ReqData, 8> mBuff;
};

}}}}  // namespace scn::step::boss::galactaknight

#endif
