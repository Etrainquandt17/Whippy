#ifndef SCN_WMAP_COMPONENT_H
#define SCN_WMAP_COMPONENT_H

#include "hel/common/ScopedPtr.h"
#include "storage/StoryMode.h"
#include "types.h"

namespace effect {
class StdRequestor;
}

namespace g3d {
class ResFileRepository;
}

namespace hid {
class RumbleManager;
}

namespace mem {
class AutoHeapExp;
}

namespace sfx {
class Fade;
class Manager;
}

namespace snd {
class SERequestor;
}

namespace storage {
class StoryData;
}

namespace scn {
namespace step {
class ContextHero;
}

namespace wmap {

class Camera;
class G3DRootSet;
class MapModelBg;
class MapModelRoute;
class RouteTrans;
class SceneStateChecker;
class UnlockManager;

namespace effect {
class Manager;
}

namespace hero {
class Manager;
}

namespace info {
class Manager;
}

class Component {
public:
    Component(const step::ContextHero& contextHero, storage::StoryMode storyMode);
    ~Component();

    mem::AutoHeapExp& heap() { return *mHeap; }
    g3d::ResFileRepository& resFileRepos() { return *mResFileRepos; }
    hid::RumbleManager& hidRumbleManager() { return *mHidRumbleManager; }
    sfx::Manager& sfxManager() { return *mSfxManager; }
    sfx::Fade& fade() { return *mFade; }
    G3DRootSet& g3dRootSet() { return *mG3DRootSet; }
    Camera& camera() { return *mCamera; }
    effect::Manager& effectManager() { return *mEffectManager; }
    info::Manager& infoManager() { return *mInfoManager; }
    hero::Manager& heroManager() { return *mHeroManager; }
    UnlockManager& unlockManager() { return *mUnlockManager; }
    MapModelBg& mapModelBg() { return *mMapModelBg; }
    MapModelRoute& mapModelRoute() { return *mMapModelRoute; }
    RouteTrans& routeTrans() { return *mRouteTrans; }
    SceneStateChecker& sceneStateChecker() { return *mSceneStateChecker; }

    hel::common::ScopedPtr<mem::AutoHeapExp> mHeap;
    hel::common::ScopedPtr<g3d::ResFileRepository> mResFileRepos;
    hel::common::ScopedPtr<hid::RumbleManager> mHidRumbleManager;
    hel::common::ScopedPtr<mem::AutoHeapExp> _C;
    hel::common::ScopedPtr<snd::SERequestor> _10;
    hel::common::ScopedPtr<sfx::Manager> mSfxManager;
    hel::common::ScopedPtr<sfx::Fade> mFade;
    hel::common::ScopedPtr<G3DRootSet> mG3DRootSet;
    hel::common::ScopedPtr<Camera> mCamera;
    hel::common::ScopedPtr<effect::Manager> mEffectManager;
    // TODO: one of these two is what effect() returns.
    hel::common::ScopedPtr< ::effect::StdRequestor> _28;
    hel::common::ScopedPtr< ::effect::StdRequestor> _2C;
    hel::common::ScopedPtr<info::Manager> mInfoManager;
    hel::common::ScopedPtr<hero::Manager> mHeroManager;
    hel::common::ScopedPtr<UnlockManager> mUnlockManager;
    hel::common::ScopedPtr<MapModelBg> mMapModelBg;
    hel::common::ScopedPtr<MapModelRoute> mMapModelRoute;
    hel::common::ScopedPtr<RouteTrans> mRouteTrans;
    hel::common::ScopedPtr<SceneStateChecker> mSceneStateChecker;
    storage::StoryMode mStoryMode;
    storage::StoryData* mStoryData;
};

}}  // namespace scn::wmap

#endif
