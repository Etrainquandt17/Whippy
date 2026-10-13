#ifndef SCN_STEP_CHARA_MINTSHAKE_H
#define SCN_STEP_CHARA_MINTSHAKE_H

namespace scn {
namespace step {
namespace chara {

class Shake;

namespace MintShake {

void Register(Shake& obj);
void Unregister(Shake& obj);
void Request(int kind);

}
}
}
}

#endif
