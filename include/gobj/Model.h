#ifndef GOBJ_MODEL_H
#define GOBJ_MODEL_H

#include "gobj/IG3DModel.h"
#include "hel/math/Vector3.h"

namespace g3d {
class Root;
}

namespace hel {
namespace math {
class Matrix34;
}}  // namespace hel::math

namespace gobj {

class NodeRepos;

// TODO: size and members. A g3d::CharaModel sits at 4.
class Model : public IG3DModel {
public:
    virtual ~Model();
    virtual g3d::ModelAccessor g3dModel();

    void registerToRoot(g3d::Root& root);
    const NodeRepos& nodes() const;
    hel::math::Vector3 scale() const;
    void setScale(const hel::math::Vector3& scale);
    void setRotateMtx(const hel::math::Matrix34& mtx);
    void updateWorldMtx();
};

}  // namespace gobj

#endif
