#ifndef SCN_SUBGAME_GUNSHOOT_INPUT_ACCESSOR_H
#define SCN_SUBGAME_GUNSHOOT_INPUT_ACCESSOR_H

#include "hel/math/Vector2.h"
#include "types.h"

namespace scn {
namespace subgame {
namespace gunshoot {
namespace input {

class Accessor {
public:
    hel::math::Vector2 dpdPos() const;

private:
    u32 _0;
    u32 _4;
};

}}}}  // namespace scn::subgame::gunshoot::input

#endif
