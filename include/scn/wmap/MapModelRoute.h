#ifndef SCN_WMAP_MAPMODELROUTE_H
#define SCN_WMAP_MAPMODELROUTE_H

#include "effect/StdRequestor.h"
#include "g3d/ResFileAccessor.h"
#include "g3d/StdModel.h"
#include "mem/ExplicitAutoDeleteArray.h"
#include "scn/step/LevelKind.h"
#include "scn/wmap/ItemKind.h"
#include "scn/wmap/MapKind.h"
#include "scn/wmap/MapModelRouteEffect.h"
#include "scn/wmap/UnlockKind.h"
#include "types.h"

namespace g3d {
class Root;
}

namespace scn {
namespace wmap {

class Component;

class MapModelRoute {
public:
    MapModelRoute(Component& component);
    ~MapModelRoute();

    void procAnim();
    void registerToRoot(g3d::Root& root);
    void setMapKind(MapKind kind);
    void setWaitItem(ItemKind item);
    void onMove();
    void startUnlockAnim(step::LevelKind level);
    bool isEndUnlockAnim() const;

private:
    g3d::StdModel& mfGetModel();
    g3d::StdModel& mfGetModel(MapKind kind);
    g3d::ResFileAccessor& mfGetResFile(MapKind kind);
    bool mfIsEndAllUnlockAnim();
    void mfStartUnlockAnim();
    void mfStartWaitAnim(UnlockKind kind);

    Component& mComponent;
    g3d::ResFileAccessor _4;
    g3d::ResFileAccessor _8;
    g3d::StdModel _C;
    g3d::StdModel _1B8;
    effect::StdRequestor mEffect;
    MapKind mMapKind;
    UnlockKind _384;
    step::LevelKind _388;
    step::LevelKind _38C;
    u32 _390;
    mem::ExplicitAutoDeleteArray<MapModelRouteEffect, 8> mEffects;
    int _3BC;
};

}}  // namespace scn::wmap

#endif
