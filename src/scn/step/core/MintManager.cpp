#include "scn/step/core/MintManager.h"

namespace scn {
namespace step {
namespace core {

MintManager::MintManager()
    : mManager()
    , mEngine(mManager) {
    mEngine.addModuleBellow("App");
    mEngine.addModuleBellow("GObj");
    mEngine.addModuleBellow("HEL");
    mEngine.addModuleBellow("Scn.Step");
    mEngine.addModuleBellow("Snd");
}

MintManager::~MintManager() {}

mint::Engine& MintManager::engine() {
    return mEngine;
}

}}}  // namespace scn::step::core
