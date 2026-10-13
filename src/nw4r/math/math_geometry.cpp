#include "nw4r/math.h"

#include <ss/algorithm>

namespace nw4r {
namespace math {


namespace detail {

f32 epsilon = 0.0001f;

} // namespace detail

void PLANE::Set(const VEC3* p0, const VEC3* p1, const VEC3* p2) {
    VEC3 v0, v1, v2;

    VEC3Sub(&v0, p2, p0);
    VEC3Sub(&v1, p1, p0);
    VEC3Normalize(&n, VEC3Cross(&v2, &v0, &v1));
    d = -VEC3Dot(&n, p0);
}

void AABB::Set(const VEC3* pPoints, unsigned int num) {
    min = pPoints[0];
    max = pPoints[0];

    for (unsigned int i = 1; i < num; i++) {
        if (pPoints[i].x < min.x) {
            min.x = pPoints[i].x;
        } else if (pPoints[i].x > max.x) {
            max.x = pPoints[i].x;
        }

        if (pPoints[i].y < min.y) {
            min.y = pPoints[i].y;
        } else if (pPoints[i].y > max.y) {
            max.y = pPoints[i].y;
        }

        if (pPoints[i].z < min.z) {
            min.z = pPoints[i].z;
        } else if (pPoints[i].z > max.z) {
            max.z = pPoints[i].z;
        }
    }
}

void AABB::Set(const AABB* pBox, const MTX34* pMtx) {
    f32 x0, y0, z0;
    f32 x1, y1, z1;
    f32 a0, a1;
    f32 b0, b1;

    x0 = pMtx->_00 * pBox->min.x + pMtx->_03;
    x1 = pMtx->_00 * pBox->max.x + pMtx->_03;

    a0 = pMtx->_01 * pBox->min.y;
    a1 = pMtx->_01 * pBox->max.y;

    b0 = pMtx->_02 * pBox->min.z;
    b1 = pMtx->_02 * pBox->max.z;

    if (x0 > x1) {
        std::swap(x0, x1);
    }

    if (a0 < a1) {
        x0 += a0;
        x1 += a1;
    } else {
        x0 += a1;
        x1 += a0;
    }

    if (b0 < b1) {
        x0 += b0;
        x1 += b1;
    } else {
        x0 += b1;
        x1 += b0;
    }

    y0 = pMtx->_10 * pBox->min.x + pMtx->_13;
    y1 = pMtx->_10 * pBox->max.x + pMtx->_13;

    a0 = pMtx->_11 * pBox->min.y;
    a1 = pMtx->_11 * pBox->max.y;

    b0 = pMtx->_12 * pBox->min.z;
    b1 = pMtx->_12 * pBox->max.z;

    if (y0 > y1) {
        std::swap(y0, y1);
    }

    if (a0 < a1) {
        y0 += a0;
        y1 += a1;
    } else {
        y0 += a1;
        y1 += a0;
    }

    if (b0 < b1) {
        y0 += b0;
        y1 += b1;
    } else {
        y0 += b1;
        y1 += b0;
    }

    z0 = pMtx->_20 * pBox->min.x + pMtx->_23;
    z1 = pMtx->_20 * pBox->max.x + pMtx->_23;

    a0 = pMtx->_21 * pBox->min.y;
    a1 = pMtx->_21 * pBox->max.y;

    b0 = pMtx->_22 * pBox->min.z;
    b1 = pMtx->_22 * pBox->max.z;

    if (z0 > z1) {
        std::swap(z0, z1);
    }

    if (a0 < a1) {
        z0 += a0;
        z1 += a1;
    } else {
        z0 += a1;
        z1 += a0;
    }

    if (b0 < b1) {
        z0 += b0;
        z1 += b1;
    } else {
        z0 += b1;
        z1 += b0;
    }

    min.x = x0;
    min.y = y0;
    min.z = z0;

    max.x = x1;
    max.y = y1;
    max.z = z1;
}

// Dropped by the link, so this is a reconstruction that was never compared.
// It is here for the two constants it leaves in front of the others.
void SPHERE::Set(const VEC3* pPoints, unsigned int num) {
    AABB box;
    box.Set(pPoints, num);
    VEC3Lerp(&C, &box.min, &box.max, 0.5f);

    f32 maxDistSq = 0.0f;

    for (unsigned int i = 0; i < num; i++) {
        f32 distSq = VEC3DistSq(&C, &pPoints[i]);

        if (distSq > maxDistSq) {
            maxDistSq = distSq;
        }
    }

    r = FSqrt(maxDistSq);
}

void FRUSTUM::Set(f32 fovy, f32 aspect, f32 n, f32 f, const MTX34& rCamMtx) {
    f32 tan = TanDeg(fovy * 0.5f);
    f32 ny = tan * n;
    f32 nx = ny * aspect;
    Set(ny, -ny, -nx, nx, n, f, rCamMtx);
}

void FRUSTUM::Set(f32 t, f32 b, f32 l, f32 r, f32 n, f32 f,
                  const MTX34& rCamMtx) {
    MTX34 invcam;
    MTX34Inv(&invcam, &rCamMtx);
    MTX34Copy(&mCamMtx, &rCamMtx);

    VEC3 p0(0.0f, 0.0f, 0.0f);
    VEC3 p[POINT_MAX];

    f32 f_n = f / n;

    p[POINT_NEAR_TL].x = l;
    p[POINT_NEAR_TL].y = t;
    p[POINT_NEAR_TL].z = -n;

    p[POINT_NEAR_TR].x = r;
    p[POINT_NEAR_TR].y = t;
    p[POINT_NEAR_TR].z = -n;

    p[POINT_NEAR_BR].x = r;
    p[POINT_NEAR_BR].y = b;
    p[POINT_NEAR_BR].z = -n;

    p[POINT_NEAR_BL].x = l;
    p[POINT_NEAR_BL].y = b;
    p[POINT_NEAR_BL].z = -n;

    p[POINT_FAR_TL].x = f_n * l;
    p[POINT_FAR_TL].y = f_n * t;
    p[POINT_FAR_TL].z = -f;

    p[POINT_FAR_TR].x = f_n * r;
    p[POINT_FAR_TR].y = f_n * t;
    p[POINT_FAR_TR].z = -f;

    p[POINT_FAR_BR].x = f_n * r;
    p[POINT_FAR_BR].y = f_n * b;
    p[POINT_FAR_BR].z = -f;

    p[POINT_FAR_BL].x = f_n * l;
    p[POINT_FAR_BL].y = f_n * b;
    p[POINT_FAR_BL].z = -f;

    mNearZ = -n;
    mFarZ = -f;

    mPlaneL.Set(&p0, &p[POINT_NEAR_BL], &p[POINT_NEAR_TL]);
    mPlaneR.Set(&p0, &p[POINT_NEAR_TR], &p[POINT_NEAR_BR]);
    mPlaneT.Set(&p0, &p[POINT_NEAR_TL], &p[POINT_NEAR_TR]);
    mPlaneB.Set(&p0, &p[POINT_NEAR_BR], &p[POINT_NEAR_BL]);

    for (int i = 0; i < POINT_MAX; i++) {
        VEC3TransformCoord(&p[i], &invcam, &p[i]);
    }

    VEC3TransformCoord(&p0, &invcam, &p0);
    mBox.Set(p, POINT_MAX);

    // clang-format off
    mPlanes[PLANE_L].Set(&p0,               &p[POINT_NEAR_BL], &p[POINT_NEAR_TL]);
    mPlanes[PLANE_R].Set(&p0,               &p[POINT_NEAR_TR], &p[POINT_NEAR_BR]);
    mPlanes[PLANE_N].Set(&p[POINT_NEAR_TL], &p[POINT_NEAR_TR], &p[POINT_NEAR_BR]);
    mPlanes[PLANE_F].Set(&p[POINT_FAR_TL],  &p[POINT_FAR_BL],  &p[POINT_FAR_BR]);
    mPlanes[PLANE_T].Set(&p0,               &p[POINT_NEAR_TL], &p[POINT_NEAR_TR]);
    mPlanes[PLANE_B].Set(&p0,               &p[POINT_NEAR_BR], &p[POINT_NEAR_BL]);
    // clang-format on
}

f32 DistSqSegment3ToSegment3(const SEGMENT3* pS1, const SEGMENT3* pS2, f32* pS,
                             f32* pT) {
    VEC3 u = pS1->P1 - pS1->P0;
    VEC3 v = pS2->P1 - pS2->P0;
    VEC3 w = pS1->P0 - pS2->P0;

    f32 a = VEC3LenSq(&u);
    f32 b = VEC3Dot(&u, &v);
    f32 c = VEC3LenSq(&v);
    f32 d = VEC3Dot(&u, &w);
    f32 e = VEC3Dot(&v, &w);

    f32 D = a * c - b * b;
    f32 sc, sN, sD = D;
    f32 tc, tN, tD = D;

    if (D < detail::epsilon) {
        sN = 0.0f;
        sD = 1.0f;
        tN = e;
        tD = c;
    } else {
        sN = b * e - c * d;
        tN = a * e - b * d;

        if (sN < 0.0f) {
            sN = 0.0f;
            tN = e;
            tD = c;
        } else if (sN > sD) {
            sN = sD;
            tN = e + b;
            tD = c;
        }
    }

    if (tN < 0.0) {
        tN = 0.0f;

        if (-d < 0.0f) {
            sN = 0.0f;
        } else if (-d > a) {
            sN = sD;
        } else {
            sN = -d;
            sD = a;
        }
    } else if (tN > tD) {
        tN = tD;

        if (-d + b < 0.0f) {
            sN = 0.0f;
        } else if (-d + b > a) {
            sN = sD;
        } else {
            sN = -d + b;
            sD = a;
        }
    }

    sc = FAbs(sN) < detail::epsilon ? 0.0f : sN / sD;
    tc = FAbs(tN) < detail::epsilon ? 0.0f : tN / tD;

    if (pS != NULL) {
        *pS = sc;
    }

    if (pT != NULL) {
        *pT = tc;
    }

    VEC3 dP = w + u * sc - v * tc;
    return VEC3LenSq(&dP);
}

IntersectionResult IntersectionLine3Sphere(const LINE3* pLine,
                                           const SPHERE* pSphere, f32* pT0,
                                           f32* pT1) {
    VEC3 PmC;
    f32 b, c, D;

    VEC3Sub(&PmC, &pLine->P, &pSphere->C);

    b = 2.0f * VEC3Dot(&pLine->d, &PmC);
    c = VEC3LenSq(&PmC) - pSphere->r * pSphere->r;
    D = b * b - 4.0f * c;

    if (D > 0.0f) {
        f32 sq = FSqrt(D);

        if (pT0 != NULL) {
            *pT0 = 0.5f * (-b - sq);
        }

        if (pT1 != NULL) {
            *pT1 = 0.5f * (-b + sq);
        }

        return INTERSECTION_2;
    } else if (D == 0.0f) {
        if (pT0 != NULL) {
            *pT0 = -0.5f * b;
        }

        return INTERSECTION_1;
    } else {
        return INTERSECTION_NONE;
    }
}

IntersectionResult IntersectionSegment3Sphere(const SEGMENT3* pSegment,
                                              const SPHERE* pSphere, f32* pT0,
                                              f32* pT1) {
    VEC3 dir;
    f32 t0, t1;

    VEC3Sub(&dir, &pSegment->P1, &pSegment->P0);
    f32 len = FSqrt(dir.LenSq());

    LINE3 line(pSegment->P0, dir, false);
    IntersectionResult result =
        IntersectionLine3Sphere(&line, pSphere, &t0, &t1);

    if (result == INTERSECTION_NONE) {
    } else if (result == INTERSECTION_1) {
        if (t0 >= 0.0f && t0 <= len) {
            if (pT0 != NULL) {
                *pT0 = t0 / len;
            }
        } else {
            result = INTERSECTION_NONE;
        }
    } else if (t0 >= 0.0f) {
        if (t1 <= len) {
            f32 inv = 1.0f / len;

            if (pT0 != NULL) {
                *pT0 = t0 * inv;
            }

            if (pT1 != NULL) {
                *pT1 = t1 * inv;
            }
        } else if (t0 <= len) {
            if (pT0 != NULL) {
                *pT0 = t0 / len;
            }

            result = INTERSECTION_1;
        } else {
            result = INTERSECTION_NONE;
        }
    } else if (t1 >= 0.0f && t1 <= len) {
        if (pT0 != NULL) {
            *pT0 = t1 / len;
        }

        result = INTERSECTION_1;
    } else {
        result = INTERSECTION_NONE;
    }

    return result;
}

bool IntersectionAABB(const AABB* pA, const AABB* pB) {
    if (pA->min.x > pB->max.x || pB->min.x > pA->max.x ||
        pA->min.y > pB->max.y || pB->min.y > pA->max.y ||
        pA->min.z > pB->max.z || pB->min.z > pA->max.z) {
        return false;
    }

    return true;
}

bool IntersectionCapsule(const CAPSULE* pC0, const CAPSULE* pC1) {
    f32 r = pC0->r + pC1->r;
    return DistSqSegment3ToSegment3(&pC0->S, &pC1->S, NULL, NULL) <= r * r;
}

IntersectionResult FRUSTUM::IntersectAABB_Ex(const AABB* pBox) const {
    if (!IntersectionAABB(pBox, &mBox)) {
        return INTERSECTION_OUTSIDE;
    }

    IntersectionResult result = INTERSECTION_INSIDE;
    VEC3 p, n;

    for (int i = 0; i < PLANE_MAX; i++) {
        if (mPlanes[i].n.x >= 0.0f) {
            p.x = pBox->min.x;
            n.x = pBox->max.x;
        } else {
            p.x = pBox->max.x;
            n.x = pBox->min.x;
        }

        if (mPlanes[i].n.y >= 0.0f) {
            p.y = pBox->min.y;
            n.y = pBox->max.y;
        } else {
            p.y = pBox->max.y;
            n.y = pBox->min.y;
        }

        if (mPlanes[i].n.z >= 0.0f) {
            p.z = pBox->min.z;
            n.z = pBox->max.z;
        } else {
            p.z = pBox->max.z;
            n.z = pBox->min.z;
        }

        if (mPlanes[i].Test(p) > 0.0f) {
            return INTERSECTION_NONE;
        }

        if (mPlanes[i].Test(n) > 0.0f) {
            result = INTERSECTION_INTERSECT;
        }
    }

    return result;
}

} // namespace math
} // namespace nw4r
