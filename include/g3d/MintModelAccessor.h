#ifndef G3D_MINTMODELACCESSOR_H
#define G3D_MINTMODELACCESSOR_H

namespace g3d {

class ModelAccessor;

namespace MintModelAccessor {

void RegisterForce(const ModelAccessor& obj);
void Unregister();
void SetVisibility(bool visible);

}}  // namespace g3d::MintModelAccessor

#endif
