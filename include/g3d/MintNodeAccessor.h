#ifndef G3D_MINTNODEACCESSOR_H
#define G3D_MINTNODEACCESSOR_H

namespace g3d {

class NodeAccessor;

namespace MintNodeAccessor {

void RegisterForce(const NodeAccessor& obj);
void Unregister();
void LoadWorldTrans();
void LoadWorldRotate();
void LoadWorldScale();
bool IsVisible();
void SetVisibility(bool visible);
void SetVisibilityBelow(bool visible);

}
}

#endif
