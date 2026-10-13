#ifndef GOBJ_MINTFOOTSTATE_H
#define GOBJ_MINTFOOTSTATE_H

namespace gobj {

class FootState;

namespace MintFootState {

void Register(FootState& obj);
void Unregister(FootState& obj);
bool IsGround();
bool IsAir();

}
}

#endif
