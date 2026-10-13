#ifndef SCN_STEP_CHARA_WATER_H
#define SCN_STEP_CHARA_WATER_H

namespace hel {
namespace math {

class Vector2;

}}  // namespace hel::math

namespace scn {
namespace step {
namespace chara {

// TODO: members and the other functions.
class Water {
public:
    bool isInWater() const;
    void setForbidEffect(bool isForbid);
    void setUseCallback(bool flag);
    bool isPosInWater(const hel::math::Vector2& offset) const;
};

}}}  // namespace scn::step::chara

#endif
