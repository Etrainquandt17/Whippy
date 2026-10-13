#ifndef NW4R_G3D_RES_RESCOMMON_H
#define NW4R_G3D_RES_RESCOMMON_H

#include "nw4r/db/assert.h"
#include "types.h"

namespace nw4r {
namespace g3d {

template <typename T>
class ResCommon {
public:
    explicit ResCommon(void* pData) : mpData(static_cast<T*>(pData)) {}
    explicit ResCommon(const void* pData) : mpData(static_cast<const T*>(pData)) {}

    bool IsValid() const { return mpData != 0; }

    T* ptr() { return mpData; }
    const T* ptr() const { return mpData; }

    T& ref() {
        NW4R_ASSERT_PTR_AT("g3d_rescommon_ac.h", 140, mpData);
        return *mpData;
    }
    const T& ref() const {
        NW4R_ASSERT_PTR_AT("g3d_rescommon_ac.h", 143, mpData);
        return *mpData;
    }

    template <typename PTR_T>
    PTR_T* ofs_to_ptr(s32 ofs) {
        u8* pPtr = reinterpret_cast<u8*>(mpData);
        if (ofs != 0) {
            return reinterpret_cast<PTR_T*>(pPtr + ofs);
        }
        return 0;
    }
    template <typename PTR_T>
    const PTR_T* ofs_to_ptr(s32 ofs) const {
        const u8* pPtr = reinterpret_cast<const u8*>(mpData);
        if (ofs != 0) {
            return reinterpret_cast<const PTR_T*>(pPtr + ofs);
        }
        return 0;
    }

    // Defined below the class: an instance is then emitted at the end of a unit and called, as the original does.
    template <typename OBJ_T>
    OBJ_T ofs_to_obj(s32 ofs);
    template <typename OBJ_T>
    const OBJ_T ofs_to_obj(s32 ofs) const {
        const u8* pPtr = reinterpret_cast<const u8*>(mpData);
        if (ofs != 0) {
            return OBJ_T(const_cast<u8*>(pPtr + ofs));
        }
        return OBJ_T(0);
    }

private:
    T* mpData;
};

template <typename T>
template <typename OBJ_T>
OBJ_T ResCommon<T>::ofs_to_obj(s32 ofs) {
    u8* pPtr = reinterpret_cast<u8*>(mpData);
    if (ofs != 0) {
        return OBJ_T(pPtr + ofs);
    }
    return OBJ_T(0);
}

}
}

#endif
