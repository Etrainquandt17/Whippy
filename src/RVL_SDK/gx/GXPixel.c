#include <kdc/revolution/GX.h>

#include <kdc/math.h>

// The fields are set with the rlwimi intrinsic here, as the SDK's own macro does; the expression form
// of GX_BITSET gives the same instructions in other registers.
#define FOG_SET_FIELD(reg, size, shift, val)                                    \
    (reg) = (u32)__rlwimi((u32)(reg), (val), (shift), 32 - (shift) - (size),    \
                          31 - (shift))

void GXSetFog(GXFogType type, GXColor color, f32 start, f32 end, f32 near,
              f32 far) {
    u32 fogColorReg;
    u32 fogParamReg0;
    u32 fogParamReg1;
    u32 fogParamReg2;
    u32 fogParamReg3;
    f32 A, B, B_mant, C;
    f32 a, c;
    u32 B_expn;
    u32 b_m, b_s;
    u32 a_bits, c_bits;
    u32 fsel;
    u32 ortho;
    u32 rgba;

    fogColorReg = 0;
    fogParamReg0 = 0;
    fogParamReg1 = 0;
    fogParamReg2 = 0;
    fogParamReg3 = 0;

    fsel = type & 7;
    ortho = (type >> 3) & 1;

    if (ortho) {
        if (far == near || end == start) {
            a = 0.0f;
            c = 0.0f;
        } else {
            A = (1.0f / (end - start));
            a = A * (far - near);
            c = A * (start - near);
        }
    } else {
        if (far == near || end == start) {
            A = 0.0f;
            B = 0.5f;
            C = 0.0f;
        } else {
            A = (far * near) / ((far - near) * (end - start));
            B = far / (far - near);
            C = start / (end - start);
        }

        B_mant = B;
        B_expn = 0;
        while (B_mant > 1.0) {
            B_mant /= 2.0f;
            B_expn++;
        }
        while (B_mant > 0.0f && B_mant < 0.5) {
            B_mant *= 2.0f;
            B_expn--;
        }

        a = A / (f32)(1 << (B_expn + 1));
        b_m = 8.388638e6f * B_mant;
        b_s = B_expn + 1;
        c = C;

        FOG_SET_FIELD(fogParamReg1, 24, 0, b_m);
        FOG_SET_FIELD(fogParamReg1, 8, 24, GX_BP_REG_FOGPARAM1);

        FOG_SET_FIELD(fogParamReg2, 5, 0, b_s);
        FOG_SET_FIELD(fogParamReg2, 8, 24, GX_BP_REG_FOGPARAM2);

        GX_BP_LOAD_REG(fogParamReg1);
        GX_BP_LOAD_REG(fogParamReg2);
    }

    a_bits = *(u32*)&a;
    c_bits = *(u32*)&c;

    FOG_SET_FIELD(fogParamReg0, 11, 0, (a_bits >> 12) & 0x7FF);
    FOG_SET_FIELD(fogParamReg0, 8, 11, (a_bits >> 23) & 0xFF);
    FOG_SET_FIELD(fogParamReg0, 1, 19, (a_bits >> 31));
    FOG_SET_FIELD(fogParamReg0, 8, 24, GX_BP_REG_FOGPARAM0);

    FOG_SET_FIELD(fogParamReg3, 11, 0, (c_bits >> 12) & 0x7FF);
    FOG_SET_FIELD(fogParamReg3, 8, 11, (c_bits >> 23) & 0xFF);
    FOG_SET_FIELD(fogParamReg3, 1, 19, (c_bits >> 31));
    FOG_SET_FIELD(fogParamReg3, 1, 20, ortho);
    FOG_SET_FIELD(fogParamReg3, 3, 21, fsel);
    FOG_SET_FIELD(fogParamReg3, 8, 24, GX_BP_REG_FOGPARAM3);

    rgba = *(u32*)&color;
    FOG_SET_FIELD(fogColorReg, 24, 0, rgba >> 8);
    FOG_SET_FIELD(fogColorReg, 8, 24, GX_BP_REG_FOGCOLOR);

    GX_BP_LOAD_REG(fogParamReg0);
    GX_BP_LOAD_REG(fogParamReg3);
    GX_BP_LOAD_REG(fogColorReg);

    gxdt->lastWriteWasXF = FALSE;
}

#undef FOG_SET_FIELD

void GXInitFogAdjTable(GXFogAdjTable* table, u16 width, const Mtx44 proj) {
    f32 f31, f30, f29, f28, f27;
    u32 i;

    if (proj[3][3] == 0.0l) {
        f30 = proj[2][3] / (proj[2][2] - 1.0f);
        f28 = f30 / proj[0][0];
    } else {
        f28 = 1.0f / proj[0][0];
        f30 = M_SQRT3 * f28;
    }

    f29 = 2.0f / width;

    for (i = 0; i < ARRAY_SIZE(table->r); i++) {
        f31 = (i + 1) * 32;
        f31 *= f29;
        f31 *= f28;
        f27 = sqrtf(1.0f + (f31 * f31) / (f30 * f30));
        table->r[i] = (u32)(f27 * 256) & 0xFFF;
    }
}

void GXSetFogRangeAdj(GXBool enable, u16 center, const GXFogAdjTable* table) {
    u32 fogRangeReg;
    u32 fogRangeRegK;
    int i;

    if (enable) {
        for (i = 0; i < ARRAY_SIZE(table->r); i += 2) {
            fogRangeRegK = 0;
            GX_BP_SET_FOGRANGEK_HI(fogRangeRegK, table->r[i]);
            GX_BP_SET_FOGRANGEK_LO(fogRangeRegK, table->r[i + 1]);
            GX_BP_SET_OPCODE(fogRangeRegK, GX_BP_REG_FOGRANGEK0 + (i / 2));
            GX_BP_LOAD_REG(fogRangeRegK);
        }
    }

    fogRangeReg = 0;
    GX_BP_SET_FOGRANGE_CENTER(fogRangeReg, center + 342);
    GX_BP_SET_FOGRANGE_ENABLED(fogRangeReg, enable);
    GX_BP_SET_OPCODE(fogRangeReg, GX_BP_REG_FOGRANGE);
    GX_BP_LOAD_REG(fogRangeReg);

    gxdt->lastWriteWasXF = FALSE;
}

void GXSetBlendMode(GXBlendMode mode, GXBlendFactor src, GXBlendFactor dst,
                    GXLogicOp op) {
    u32 blendModeReg = gxdt->blendMode;
    GX_BP_SET_BLENDMODE_SUBTRACT(blendModeReg, mode == GX_BM_SUBTRACT);
    GX_BP_SET_BLENDMODE_BLEND_ENABLE(blendModeReg, mode);
    GX_BP_SET_BLENDMODE_LOGIC_OP_ENABLE(blendModeReg, mode == GX_BM_LOGIC);
    GX_BP_SET_BLENDMODE_LOGIC_MODE(blendModeReg, op);
    GX_BP_SET_BLENDMODE_SRC_FACTOR(blendModeReg, src);
    GX_BP_SET_BLENDMODE_DST_FACTOR(blendModeReg, dst);

    GX_BP_LOAD_REG(blendModeReg);
    gxdt->blendMode = blendModeReg;

    gxdt->lastWriteWasXF = FALSE;
}

void GXSetColorUpdate(GXBool enable) {
    u32 blendModeReg = gxdt->blendMode;
    GX_BP_SET_BLENDMODE_COLOR_UPDATE(blendModeReg, enable);

    GX_BP_LOAD_REG(blendModeReg);
    gxdt->blendMode = blendModeReg;

    gxdt->lastWriteWasXF = FALSE;
}

void GXGetColorUpdate(GXBool* enable) {
    *enable = GX_BP_GET_BLENDMODE_COLOR_UPDATE(gxdt->blendMode);
}

void GXSetAlphaUpdate(GXBool enable) {
    u32 blendModeReg = gxdt->blendMode;
    GX_BP_SET_BLENDMODE_ALPHA_UPDATE(blendModeReg, enable);

    GX_BP_LOAD_REG(blendModeReg);
    gxdt->blendMode = blendModeReg;

    gxdt->lastWriteWasXF = FALSE;
}

void GXGetAlphaUpdate(GXBool* enable) {
    *enable = GX_BP_GET_BLENDMODE_ALPHA_UPDATE(gxdt->blendMode);
}

void GXSetZMode(GXBool enableTest, GXCompare func, GXBool enableUpdate) {
    u32 zModeReg = gxdt->zMode;
    GX_BP_SET_ZMODE_TEST_ENABLE(zModeReg, enableTest);
    GX_BP_SET_ZMODE_COMPARE(zModeReg, func);
    GX_BP_SET_ZMODE_UPDATE_ENABLE(zModeReg, enableUpdate);

    GX_BP_LOAD_REG(zModeReg);
    gxdt->zMode = zModeReg;

    gxdt->lastWriteWasXF = FALSE;
}

void GXSetZCompLoc(GXBool beforeTex) {
    GX_BP_SET_ZCONTROL_BEFORE_TEX(gxdt->zControl, beforeTex);
    GX_BP_LOAD_REG(gxdt->zControl);
    gxdt->lastWriteWasXF = FALSE;
}

void GXSetPixelFmt(GXPixelFmt pixelFmt, GXZFmt16 zFmt) {
    static u32 p2f[GX_MAX_PIXELFMT] = {
        GX_PF_RGB8_Z24, GX_PF_RGBA6_Z24, GX_PF_RGBA565_Z16, GX_PF_Z24,
        GX_PF_Y8,       GX_PF_Y8,        GX_PF_Y8,          GX_PF_U8};

    u32 zControlRegOld = gxdt->zControl;

    GX_BP_SET_ZCONTROL_PIXEL_FMT(gxdt->zControl, p2f[pixelFmt]);
    GX_BP_SET_ZCONTROL_Z_FMT(gxdt->zControl, zFmt);

    if (zControlRegOld != gxdt->zControl) {
        GX_BP_LOAD_REG(gxdt->zControl);
        GX_BP_SET_GENMODE_MULTISAMPLE(gxdt->genMode,
                                      pixelFmt == GX_PF_RGBA565_Z16);
        gxdt->gxDirtyFlags |= GX_DIRTY_GEN_MODE;
    }

    if (p2f[pixelFmt] == GX_PF_Y8) {
        GX_BP_SET_DSTALPHA_YUV_FMT(gxdt->dstAlpha, pixelFmt - GX_PF_Y8);
        GX_BP_SET_OPCODE(gxdt->dstAlpha, GX_BP_REG_DSTALPHA);
        GX_BP_LOAD_REG(gxdt->dstAlpha);
    }

    gxdt->lastWriteWasXF = FALSE;
}

void GXSetDither(GXBool enable) {
    u32 blendModeReg = gxdt->blendMode;
    GX_BP_SET_BLENDMODE_DITHER(blendModeReg, enable);

    GX_BP_LOAD_REG(blendModeReg);
    gxdt->blendMode = blendModeReg;

    gxdt->lastWriteWasXF = FALSE;
}

void GXSetDstAlpha(GXBool enable, u8 alpha) {
    u32 dstAlphaReg = gxdt->dstAlpha;
    GX_BP_SET_DSTALPHA_ALPHA(dstAlphaReg, alpha);
    GX_BP_SET_DSTALPHA_ENABLE(dstAlphaReg, enable);

    GX_BP_LOAD_REG(dstAlphaReg);
    gxdt->dstAlpha = dstAlphaReg;

    gxdt->lastWriteWasXF = FALSE;
}

void GXSetFieldMask(GXBool enableEven, GXBool enableOdd) {
    u32 fieldMaskReg = 0;
    GX_BP_SET_FIELDMASK_ODD(fieldMaskReg, enableOdd);
    GX_BP_SET_FIELDMASK_EVEN(fieldMaskReg, enableEven);
    GX_BP_SET_OPCODE(fieldMaskReg, GX_BP_REG_FIELDMASK);

    GX_BP_LOAD_REG(fieldMaskReg);
    gxdt->lastWriteWasXF = FALSE;
}

void GXSetFieldMode(GXBool texLOD, GXBool adjustAR) {
    GX_BP_SET_LINEPTWIDTH_ADJUST_AR(gxdt->linePtWidth, adjustAR);
    GX_BP_LOAD_REG(gxdt->linePtWidth);

    __GXFlushTextureState();
    GX_BP_LOAD_REG(GX_BP_REG_FIELDMODE << 24 | texLOD);
    __GXFlushTextureState();
}
