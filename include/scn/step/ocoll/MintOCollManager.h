#ifndef SCN_STEP_OCOLL_MINTOCOLLMANAGER_H
#define SCN_STEP_OCOLL_MINTOCOLLMANAGER_H

namespace ocoll {

class Manager;

}

namespace scn {
namespace step {
namespace ocoll {
namespace MintOCollManager {

void Register(::ocoll::Manager& manager);
void Unregister(::ocoll::Manager& manager);
::ocoll::Manager& Ref();

}
}
}
}

#endif
