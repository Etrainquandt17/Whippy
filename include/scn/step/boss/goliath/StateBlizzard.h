#ifndef SCN_STEP_BOSS_GOLIATH_STATEBLIZZARD_H
#define SCN_STEP_BOSS_GOLIATH_STATEBLIZZARD_H

#define HEL_COMMON_MUTABLEARRAY_DESTRUCTOR_IN_CLASS
#define HEL_COMMON_MUTABLEARRAY_ADD_IN_CLASS
#define HEL_COMMON_MUTABLEARRAY_REMOVEATINDEX_IN_CLASS

#include "hel/common/Array.h"
#include "hel/common/MutableArray.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/goliath/BlizzardDesc.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace goliath {

class StateBlizzard : public StateBase {
public:
    struct BlizzardReqData {
        BlizzardReqData() {}

        f32 mAngle;
        bool mIsReverse;
    };

    StateBlizzard(Boss* boss, const BlizzardDesc& desc);
    virtual ~StateBlizzard();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    void addBlizzardReqData(f32 angle, bool isReverse);

    hel::common::MutableArray<BlizzardReqData, 8> mReqData;
    u32 mIndex;
};

}}}}  // namespace scn::step::boss::goliath

#endif
