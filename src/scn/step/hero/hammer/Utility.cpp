#include "scn/step/hero/hammer/Utility.h"
#include "gobj/Target.h"
#include "hel/geo2d/Edge.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "mcoll/LandManager.h"
#include "mcoll/detail/CollideTarget.h"
#include "mcoll/detail/CollidedInfo.h"
#include "mcoll/detail/CollidedLog.h"
#include "mcoll/detail/DetectArg.h"
#include "mcoll/detail/DetectResult.h"
#include "scn/step/Component.h"
#include "scn/step/chara/Location.h"
#include "scn/step/debug/GeneralDrawer.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/map/LandManager.h"

namespace scn {
namespace step {
namespace hero {
namespace hammer {

bool Utility::IsHitFrontFloor(Hero& hero) {
    f32 sign = hero.target().getSign();
    hel::math::Vector2 pos =
        static_cast<const Hero&>(hero).location().pos().getXY() + hel::math::Vector2(0.4f * sign, 0.9f);
    hel::math::Vector2 velocity(0.8f * sign, -1.0f);
    mcoll::detail::DetectArg arg;
    arg.setVelocity(velocity);
    arg.setIsPassInvisibleLand(true);
    mcoll::detail::DetectResult result = hero.comp().mapLandManager().native().rayCheck(pos, arg);
    hero.comp().debugGeneralDrawer().addArrow(pos, pos + velocity);
    if (result.collidedLogCount() != 0) {
        mcoll::detail::CollidedInfo info = result.collidedLog(0).info();
        hel::geo2d::Edge edge = info.collideTarget().edge();
        hel::math::Vector2 normal = edge._10;
        if (0.0f == normal.y) {
            return false;
        }
        return true;
    }
    return false;
}

}}}}  // namespace scn::step::hero::hammer
