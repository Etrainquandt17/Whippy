#ifndef SCN_SUBGAME_GUNSHOOT_CHARA_ICHARACONTROLLER_H
#define SCN_SUBGAME_GUNSHOOT_CHARA_ICHARACONTROLLER_H

#include "types.h"

namespace scn {
namespace subgame {
namespace gunshoot {
namespace chara {

class ICharaController {
public:
    virtual ~ICharaController();
    virtual void updateMain() = 0;
    virtual void updateUseGPU();
    virtual void updateDebug() = 0;
    virtual void draw() const;
};

}}}}  // namespace scn::subgame::gunshoot::chara

#endif
