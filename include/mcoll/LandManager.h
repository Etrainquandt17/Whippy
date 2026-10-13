#ifndef MCOLL_LANDMANAGER_H
#define MCOLL_LANDMANAGER_H

#include "types.h"

namespace hel {
namespace math {
class Vector2;
}
}

namespace mcoll {

namespace detail {
class DetectArg;
class DetectResult;
}

class LandManager {
public:
    detail::DetectResult rayCheck(const hel::math::Vector2& pos, const detail::DetectArg& arg) const;
    bool isExistLand(const hel::math::Vector2& pos) const;
    bool isExistMoveLand(const hel::math::Vector2& pos) const;
    bool isExistMoveLandInitialPlacement(const hel::math::Vector2& pos) const;
    bool isWaterGrid(const hel::math::Vector2& pos) const;
    void setIsExistGimmickBlock(u32 x, u32 y, bool isExist);
    void setIsExistFireBlock(u32 x, u32 y, bool isExist);
    void setIsExistIceBlock(u32 x, u32 y, bool isExist);
    void setIsExistIronBlockLand(u32 x, u32 y, bool isExist);
    void setIsExistSnowBlockLand(u32 x, u32 y, bool isExist);
    void setIsExistGrassBlockLand(u32 x, u32 y, bool isExist);
    void setIsExistStoneBlockLand(u32 x, u32 y, bool isExist);
    void setIsExistWoodBlockLand(u32 x, u32 y, bool isExist);
    u32 gridWidth() const;
};

}

#endif
