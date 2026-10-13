#ifndef SCN_GOALGAME_JUMPBOARD_H
#define SCN_GOALGAME_JUMPBOARD_H

#include "types.h"

namespace scn {
namespace goalgame {

class JumpBoard {
public:
    void effectJumpBoard();

private:
    u8 _0[0x9F8];
    bool _9F8;
};

}}  // namespace scn::goalgame

#endif
