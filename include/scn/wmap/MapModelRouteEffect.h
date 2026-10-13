#ifndef SCN_WMAP_MAPMODELROUTEEFFECT_H
#define SCN_WMAP_MAPMODELROUTEEFFECT_H

#include "effect/StdRequestor.h"
#include "g3d/ResFileAccessor.h"
#include "g3d/StdModel.h"
#include "scn/wmap/MapModelRouteKind.h"
#include "types.h"

namespace scn {
namespace wmap {

class Component;

class MapModelRouteEffect {
public:
    MapModelRouteEffect(Component& component, MapModelRouteKind kind);
    ~MapModelRouteEffect();

    void procAnim();
    void appear(bool flag);
    void disappear();
    bool isAnimEnd() const;
    void restartIfAppear();

private:
    const char* mfGetResFileName() const;
    const char* mfGetTopLName() const;
    u32 mfGetEffectKind() const;
    void mfStart();

    Component& mComponent;
    MapModelRouteKind mKind;
    bool _8;
    bool _9;
    g3d::ResFileAccessor mResFile;
    g3d::StdModel mModel;
    effect::StdRequestor mEffect;
};

}}  // namespace scn::wmap

#endif
