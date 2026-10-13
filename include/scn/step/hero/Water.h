#ifndef SCN_STEP_HERO_WATER_H
#define SCN_STEP_HERO_WATER_H

namespace hel {
namespace math {
class Vector2;
class Vector3;
}}  // namespace hel::math

namespace scn {
namespace step {
namespace hero {

class Water {
public:
    bool isInWater() const;
    void setForbidChangeState(bool isForbid);
    void setForbidEffect(bool isForbid);
    bool isOnSurface() const;
    hel::math::Vector3 getSurfaceUpVec(const hel::math::Vector2& pos) const;
    void requestBubble(const hel::math::Vector2& pos);
};

}}}  // namespace scn::step::hero

#endif
