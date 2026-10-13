#ifndef SCN_STEP_BOSS_LOWPER_DATABUFF_H
#define SCN_STEP_BOSS_LOWPER_DATABUFF_H

#define HEL_COMMON_MUTABLEARRAY_DESTRUCTOR_IN_CLASS
#define HEL_COMMON_MUTABLEARRAY_ADD_IN_CLASS
#define HEL_COMMON_MUTABLEARRAY_REMOVEATINDEX_IN_CLASS

#include "hel/common/MutableArray.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace lowper {

class DataBuff {
public:
    struct BombFarBulletData {
        f32 _0;
        u32 _4;
    };

    DataBuff();
    ~DataBuff();
    void addSprinklerBulletSpeedData(f32 speed);
    void clearSprinklerBulletSpeedData();
    bool isExistSprinklerBulletSpeedData() const;
    f32 shiftSprinklerBulletSpeedData();
    void shuffleSprinklerBulletSpeedData();
    void addBombFarBulletData(const BombFarBulletData& data);
    void clearBombFarBulletData();
    u32 countBombFarBulletData();
    BombFarBulletData getBombFarBulletData(u32 index);
    u32 getMaxIntervalBombFarBulletData();
    void addVortexBulletSpeedData(f32 speed);
    void clearVortexBulletSpeedData();
    f32 shiftVortexBulletSpeedData();
    bool isExistVortexBulletSpeedData() const;
    void shuffleVortexBulletSpeedData();

private:
    hel::common::MutableArray<f32, 10> mSprinklerBulletSpeedData;
    hel::common::MutableArray<BombFarBulletData, 5> mBombFarBulletData;
    hel::common::MutableArray<f32, 10> mVortexBulletSpeedData;
};

}}}}  // namespace scn::step::boss::lowper

#endif
