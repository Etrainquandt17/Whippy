#ifndef SCN_STEP_HERO_NURURI_H
#define SCN_STEP_HERO_NURURI_H

#include "hel/math/Vector2.h"

namespace nururi {
class Nururi;
}

namespace scn {
namespace step {
namespace hero {

// TODO: members.
class Nururi {
public:
    void setValid(bool isValid);
    void setValid(bool isValid, u32 frame);
    void setCanNururi(bool canNururi);
    hel::math::Vector2 getNururiDir() const;
    void changeSetting(const hel::math::Vector2& dir, f32, f32);
    ::nururi::Nururi& nururi();
};

}}}  // namespace scn::step::hero

#endif
