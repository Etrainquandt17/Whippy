#ifndef INFO_UTIL_H
#define INFO_UTIL_H

#include "scn/step/hero/AbilityKind.h"
#include "scn/step/hero/Kind.h"
#include "types.h"

namespace hel {
namespace math {
class Vector2;
}}  // namespace hel::math

namespace lyt {
class Layout;
class PaneAccessor;
}

namespace info {

const wchar_t* abilityName(scn::step::hero::AbilityKind kind);
f32 CalcStringWidth(const wchar_t* str, const lyt::PaneAccessor& pane);
void selectHeroPane(lyt::Layout& layout, scn::step::hero::Kind kind);
void selectHeroPaneByAction(lyt::Layout& layout, scn::step::hero::Kind kind);
bool hitTest(const lyt::PaneAccessor& pane, const hel::math::Vector2& a, const hel::math::Vector2& b);

}  // namespace info

#endif
