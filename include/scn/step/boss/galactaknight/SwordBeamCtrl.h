#ifndef SCN_STEP_BOSS_GALACTAKNIGHT_SWORDBEAMCTRL_H
#define SCN_STEP_BOSS_GALACTAKNIGHT_SWORDBEAMCTRL_H

#define HEL_COMMON_MUTABLEARRAY_DESTRUCTOR_IN_CLASS
#define HEL_COMMON_MUTABLEARRAY_ADD_IN_CLASS
#define HEL_COMMON_MUTABLEARRAY_REMOVEATINDEX_IN_CLASS

#include "hel/common/MutableArray.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace galactaknight {

}
class Boss;
namespace galactaknight {

class SwordBeamCtrl {
public:
    struct ReqData {
        f32 _0;
        // Not a bool: the code tests it against zero before it is used as a number.
        u8 _4;
        bool _5;
        u32 mIndex;
    };

    SwordBeamCtrl(Boss& boss);

    void add(const ReqData& data);
    void clear();
    bool isEmpty() const;
    ReqData pick();
    void shuffleIndex();
    void requestOne();

private:
    Boss& mBoss;
    hel::common::MutableArray<ReqData, 12> mBuff;
};

}
}
}
}

#endif
