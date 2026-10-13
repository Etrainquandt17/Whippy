#ifndef GFX_EASYRENDER3D_H
#define GFX_EASYRENDER3D_H

#include "revolution/gx/GXStruct.h"
#include "types.h"

namespace hel {
namespace math {
class Matrix34;
}}  // namespace hel::math

namespace hel {
namespace math {
class Matrix44;
}}  // namespace hel::math

namespace hel {
namespace math {
class Vector3;
}}  // namespace hel::math

namespace gfx {

class EasyRender3D {
public:
    static void SetupGX(const hel::math::Matrix44& projMtx, bool);
    static void SetViewMtx(const hel::math::Matrix34& mtx);
    static void LoadPosMtx(const hel::math::Matrix34& mtx);
    static void SetColor(const GXColor& color);
    static void DrawLine(const hel::math::Matrix34& mtx, const hel::math::Vector3&, const hel::math::Vector3&, f32);
    static void DrawTriangleFill(const hel::math::Matrix34& mtx, const hel::math::Vector3&, const hel::math::Vector3&, const hel::math::Vector3&);
    static void DrawQuadFill(const hel::math::Matrix34& mtx, const hel::math::Vector3&, const hel::math::Vector3&, const hel::math::Vector3&, const hel::math::Vector3&);
    static void DrawCircleFill(const hel::math::Matrix34& mtx, f32, f32, const hel::math::Vector3&, const hel::math::Vector3&);
    static void DrawCapsule2DFill(const hel::math::Matrix34& mtx, f32, f32, f32, const hel::math::Vector3&, const hel::math::Vector3&);
    static void DrawStarFill(const hel::math::Matrix34& mtx, f32, f32, f32, const hel::math::Vector3&, const hel::math::Vector3&);
};

}  // namespace gfx

#endif
