#ifndef SCN_STEP_CORE_MINTMANAGER_H
#define SCN_STEP_CORE_MINTMANAGER_H

#include "mint/Engine.h"
#include "mint/Manager.h"

namespace scn {
namespace step {
namespace core {

class MintManager {
public:
    MintManager();
    ~MintManager();

    mint::Engine& engine();

private:
    mint::Manager mManager;
    mint::Engine mEngine;
};

}
}
}

#endif
