#ifndef SCN_TITLE_MINTMANAGER_H
#define SCN_TITLE_MINTMANAGER_H

#include "mint/Engine.h"
#include "mint/Manager.h"

namespace scn {
namespace title {

class MintManager {
public:
    MintManager();

private:
    mint::Manager mManager;
    mint::Engine mEngine;
};

}}  // namespace scn::title

#endif
