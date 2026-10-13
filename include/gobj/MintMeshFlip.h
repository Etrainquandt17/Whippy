#ifndef GOBJ_MINTMESHFLIP_H
#define GOBJ_MINTMESHFLIP_H

#include "types.h"

namespace gobj {

class MeshFlip;

namespace MintMeshFlip {

void Register(MeshFlip& obj);
void Unregister(MeshFlip& obj);
void Flip(u32 index);

}
}

#endif
