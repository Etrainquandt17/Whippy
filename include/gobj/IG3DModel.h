#ifndef GOBJ_IG3DMODEL_H
#define GOBJ_IG3DMODEL_H

namespace g3d {
class ModelAccessor;
}

namespace gobj {

class IG3DModel {
public:
    virtual ~IG3DModel() {}
    virtual g3d::ModelAccessor g3dModel() = 0;
};

}  // namespace gobj

#endif
