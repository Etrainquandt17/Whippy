#ifndef G3D_MODELACCESSOR_H
#define G3D_MODELACCESSOR_H

#include "types.h"

namespace g3d {

class MaterialAccessor;
class NodeAccessor;

class ModelAccessor {
public:
    ModelAccessor();
    ~ModelAccessor();

    ModelAccessor& operator=(const ModelAccessor& other);

    void setVisibility(bool visible) const;
    NodeAccessor nodeByName(const char* name) const;
    MaterialAccessor materialByName(const char* name) const;
    bool isVisible() const;

private:
    u8 _0[0x10];
};

}  // namespace g3d

#endif
