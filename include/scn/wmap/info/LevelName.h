#ifndef SCN_WMAP_INFO_LEVELNAME_H
#define SCN_WMAP_INFO_LEVELNAME_H

#include "hel/math/Vector3.h"
#include "mem/ExplicitScopedPtr.h"
#include "scn/step/LevelKind.h"
#include "scn/wmap/ItemKind.h"
#include "types.h"

namespace info {
namespace common {
class WiiButton;
}
}

namespace hel {
namespace math {
class Matrix44;
}
}

namespace lyt {
class Layout;
}

namespace scn {
namespace wmap {

class Component;

namespace info {

class LevelName {
public:
    LevelName(Component& component);

    void procAnim();
    void updateScreenPos(const hel::math::Matrix44& view);
    void procReadyToRender();
    void draw();
    void init(ItemKind item, const hel::math::Vector3& pos);
    void setItem(ItemKind item, const hel::math::Vector3& pos);
    void open();
    void onMoveStart();
    void onMoveEnd();
    void on1Pushed();
    void on2Pushed();

private:
    void mfStartLevel(step::LevelKind level, bool skip);
    void mfStartShip(bool skip);
    void mfUpdateVisibility();
    void mfToOpen();
    void mfToClose();
    bool mfCanMoveToHalcandra() const;

    Component& mComponent;
    mem::ExplicitScopedPtr<lyt::Layout> _4;
    mem::ExplicitScopedPtr<lyt::Layout> _C;
    mem::ExplicitScopedPtr< ::info::common::WiiButton> _14;
    mem::ExplicitScopedPtr< ::info::common::WiiButton> _1C;
    mem::ExplicitScopedPtr< ::info::common::WiiButton> _24;
    mem::ExplicitScopedPtr< ::info::common::WiiButton> _2C;
    hel::math::Vector3 _34;
    bool _40;
    ItemKind mItemKind;
    hel::math::Vector3 _48;
    bool _54;
    int _58;
    bool _5C;
    bool _5D;
    bool _5E;
};

}
}
}

#endif
