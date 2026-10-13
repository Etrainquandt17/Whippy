#ifndef MCOLL_DETAIL_DETECTARG_H
#define MCOLL_DETAIL_DETECTARG_H

#include "hel/math/Vector2.h"
#include "types.h"

namespace mcoll {
namespace detail {

class DetectArg {
public:
    DetectArg();

    hel::math::Vector2 velocity() const;
    void setVelocity(const hel::math::Vector2& velocity);
    u32 moveRetryCountMax() const;
    void setMoveRetryCountToZeroTime();
    void setMoveRetryCountToMultiTime();
    bool isPassThroughLand() const;
    void setIsPassThroughLand(bool isPass);
    void setIsGenerateFloorToOneSpaceGrid(bool isGenerate);
    void setIsGenerateFloorToTwoSpaceGrid(bool isGenerate);
    void setIsPassInvisibleLand(bool isPass);
    void setIsPassInvisibleWater(bool isPass);
    void setIsGroundMode(bool isGroundMode);
    void setIsPassCrystalWallLand(bool isPass);
    void setIsPassDamageLand(bool isPass);
    void setIsAfterMoveDetect(bool isAfterMove);

private:
    hel::math::Vector2 mVelocity;
    u32 mMoveRetryCountMax;
    bool mIsPassThroughLand;
    bool mIsGenerateFloorToOneSpaceGrid;
    bool mIsGenerateFloorToTwoSpaceGrid;
    bool mIsPassInvisibleLand;
    bool mIsPassInvisibleWater;
    bool mIsGroundMode;
    bool mIsPassCrystalWallLand;
    bool mIsPassDamageLand;
    bool mIsAfterMoveDetect;
};

}}  // namespace mcoll::detail

#endif
