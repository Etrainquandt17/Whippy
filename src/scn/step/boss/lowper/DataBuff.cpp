#include "scn/step/boss/lowper/DataBuff.h"

#include "app/Random.h"

namespace scn {
namespace step {
namespace boss {
namespace lowper {

DataBuff::DataBuff() {}

DataBuff::~DataBuff() {}

void DataBuff::addSprinklerBulletSpeedData(f32 speed) {
    if (!mSprinklerBulletSpeedData.isFull()) {
        mSprinklerBulletSpeedData.add(speed);
    }
}

void DataBuff::clearSprinklerBulletSpeedData() {
    mSprinklerBulletSpeedData.clear();
}

bool DataBuff::isExistSprinklerBulletSpeedData() const {
    return mSprinklerBulletSpeedData.count() != 0;
}

f32 DataBuff::shiftSprinklerBulletSpeedData() {
    f32 speed = 0.0f;
    if (mSprinklerBulletSpeedData.count() != 0) {
        speed = mSprinklerBulletSpeedData[0];
        mSprinklerBulletSpeedData.removeAtIndex(0);
    }
    return speed;
}

void DataBuff::shuffleSprinklerBulletSpeedData() {
    hel::common::MutableArray<f32, 10> data;
    data = mSprinklerBulletSpeedData;
    mSprinklerBulletSpeedData.clear();
    while (data.count() != 0) {
        u32 index = app::Random::RandU32(data.count());
        mSprinklerBulletSpeedData.add(data[index]);
        data.removeAtIndex(index);
    }
}

void DataBuff::addBombFarBulletData(const BombFarBulletData& data) {
    mBombFarBulletData.add(data);
}

void DataBuff::clearBombFarBulletData() {
    mBombFarBulletData.clear();
}

u32 DataBuff::countBombFarBulletData() {
    return mBombFarBulletData.count();
}

DataBuff::BombFarBulletData DataBuff::getBombFarBulletData(u32 index) {
    return mBombFarBulletData[index];
}

u32 DataBuff::getMaxIntervalBombFarBulletData() {
    u32 max = 0;
    for (u32 i = 0; i < mBombFarBulletData.count(); i++) {
        if (mBombFarBulletData[i]._4 > max) {
            max = mBombFarBulletData[i]._4;
        }
    }
    return max;
}

void DataBuff::addVortexBulletSpeedData(f32 speed) {
    if (!mVortexBulletSpeedData.isFull()) {
        mVortexBulletSpeedData.add(speed);
    }
}

void DataBuff::clearVortexBulletSpeedData() {
    mVortexBulletSpeedData.clear();
}

f32 DataBuff::shiftVortexBulletSpeedData() {
    f32 speed = 0.0f;
    if (mVortexBulletSpeedData.count() != 0) {
        speed = mVortexBulletSpeedData[0];
        mVortexBulletSpeedData.removeAtIndex(0);
    }
    return speed;
}

bool DataBuff::isExistVortexBulletSpeedData() const {
    return mVortexBulletSpeedData.count() != 0;
}

void DataBuff::shuffleVortexBulletSpeedData() {
    hel::common::MutableArray<f32, 10> data;
    data = mVortexBulletSpeedData;
    mVortexBulletSpeedData.clear();
    while (data.count() != 0) {
        u32 index = app::Random::RandU32(data.count());
        mVortexBulletSpeedData.add(data[index]);
        data.removeAtIndex(index);
    }
}

}
}
}
}
