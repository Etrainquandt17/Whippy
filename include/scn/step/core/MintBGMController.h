#ifndef SCN_STEP_CORE_MINTBGMCONTROLLER_H
#define SCN_STEP_CORE_MINTBGMCONTROLLER_H

namespace scn {
namespace step {
namespace core {

class BGMController;

namespace MintBGMController {

void Register(BGMController& obj);
void Unregister(BGMController& obj);
void Request(int category, int id, bool flag);
void Unrequest(int category);
void Pause(int category);
void Unpause(int category);

}
}
}
}

#endif
