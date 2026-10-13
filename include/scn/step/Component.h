#ifndef SCN_STEP_COMPONENT_H
#define SCN_STEP_COMPONENT_H

namespace g3d {
class ResFileRepository;
}

namespace ocoll {
class Manager;
}

namespace scn {
namespace step {

class Context;

namespace bg {
class Manager;
}
namespace arena {
class Manager;
}
namespace boss {
class Manager;
}
namespace camera {
class CameraController;
class CameraAccessor;
class MainCamera;
}
namespace carryitem {
class Manager;
}
namespace core {
class AreaOperation;
class BGMController;
class G3DRootSet;
class MintManager;
class PermEffect;
class PauseTrigger;
class PermSoundSE;
class SceneChanger;
}
namespace item {
class Manager;
}
namespace debug {
class GeneralDrawer;
class ObjInfoRepos;
}
namespace enemy {
class Manager;
}
namespace gimmick {
class Manager;
}
namespace hero {
class Manager;
}
namespace info {
class Manager;
}
namespace map {
class DataFile;
class LandManager;
class MemManager;
}
namespace spstop {
class Manager;
}
namespace ostop {
class Manager;
}
namespace sfx {
class BGFade;
class CinemaScope;
class Manager;
class ScreenFade;
class SuperFade;
class SuperBackPicture;
class Wipe;
}
namespace weapon {
class Manager;
}

class Component {
public:
    info::Manager& infoManager();
    camera::CameraController& cameraController() const;
    ::ocoll::Manager& objCollManager();
    map::MemManager& mapMemManager();
    map::DataFile& mapDataFile() const;
    map::LandManager& mapLandManager();
    gimmick::Manager& gimmickManager();
    carryitem::Manager& carryItemManager();
    camera::MainCamera& mainCamera() const;
    Context& context() const;
    g3d::ResFileRepository& resFileRepos();
    core::MintManager& mintManager();
    hero::Manager& heroManager();
    item::Manager& itemManager();
    core::PermEffect& permEffect();
    spstop::Manager& superStopManager();
    ostop::Manager& objStopManager();
    sfx::CinemaScope& cinemaScope();
    sfx::SuperFade& superFade();
    camera::CameraAccessor& cameraAccessor() const;
    sfx::BGFade& bgFade();
    core::BGMController& bgmController();
    bg::Manager& mapDecorationManager();
    enemy::Manager& enemyManager();
    debug::GeneralDrawer& debugGeneralDrawer();
    boss::Manager& bossManager();
    core::PermSoundSE& permSoundSE();
    sfx::ScreenFade& screenFade();
    sfx::Manager& sfxManager();
    debug::ObjInfoRepos& debugObjInfoRepos();
    core::PauseTrigger& pauseTrigger();
    core::SceneChanger& sceneChanger();
    arena::Manager& arenaManager();
    weapon::Manager& weaponManager();
    core::AreaOperation& areaOperation();
    sfx::Wipe& wipe();
    sfx::SuperBackPicture& superBackPicture();
    core::G3DRootSet& g3dRootSet();
};

}
}

#endif
