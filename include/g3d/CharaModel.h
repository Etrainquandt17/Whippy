#ifndef G3D_CHARAMODEL_H
#define G3D_CHARAMODEL_H

#include "g3d/ModelAccessor.h"
#include "g3d/ModelAnimAccessor.h"
#include "types.h"

namespace hel {
namespace math {
class Matrix34;
}}  // namespace hel::math

namespace g3d {

class CharaModelContext;
class ResFileAccessor;
class Root;

class CharaModel {
public:
    CharaModel(const CharaModelContext& context);
    ~CharaModel();

    ModelAccessor model();
    void setModelRTMtx(const hel::math::Matrix34& mtx);
    ModelAnimAccessor anim(u32 slot);
    void registerToRoot(Root& root);
    void updateFrame();
    void updateWorldMtxIfDirtyFlagOn();
    void updateWorldMtx();
    void setAnim(u32 slot, const ResFileAccessor& resFile, const char* name);

private:
    u32 _0[0x164 / 4];
};

}  // namespace g3d

#endif
