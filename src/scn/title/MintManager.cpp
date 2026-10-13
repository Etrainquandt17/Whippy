#include "scn/title/MintManager.h"

namespace scn {
namespace title {

MintManager::MintManager()
    : mManager()
    , mEngine(mManager) {
    mEngine.addModuleBellow("App");
    mEngine.addModuleBellow("GObj");
    mEngine.addModuleBellow("HEL");
    mEngine.addModuleBellow("Scn.Title");
    mEngine.addModuleBellow("Snd");
}

}}  // namespace scn::title
