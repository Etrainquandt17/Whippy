#include "nw4r/g3d.h" // IWYU pragma: export

#include "rvl/BASE.h" // IWYU pragma: export
#include "rvl/GX.h"   // IWYU pragma: export
#include <ss/cstdint>

namespace nw4r {
namespace g3d {

bool ResTev::GXGetTevSwapModeTable(
    GXTevSwapSel swap, GXTevColorChan *pR, GXTevColorChan *pG, GXTevColorChan *pB, GXTevColorChan *pA
) const {
    const u8 *pCmd = ref().dl.dl.common.dl.swapModeTable[swap];
    u32 cmd;

    if (pCmd[0] == 0) {
        return false;
    }

    detail::ResReadBPCmd(&pCmd[GX_BP_CMD_SZ * 1], &cmd);

    if (pR != NULL) {
        *pR = static_cast<GXTevColorChan>(cmd >> GX_BP_TEVKSEL_SWAP_RB_SHIFT & GX_BP_TEVKSEL_SWAP_RB_LMASK);
    }
    if (pG != NULL) {
        *pG = static_cast<GXTevColorChan>(cmd >> GX_BP_TEVKSEL_SWAP_GA_SHIFT & GX_BP_TEVKSEL_SWAP_GA_LMASK);
    }

    detail::ResReadBPCmd(&pCmd[GX_BP_CMD_SZ * 3], &cmd);

    if (pB != NULL) {
        *pB = static_cast<GXTevColorChan>(cmd >> GX_BP_TEVKSEL_SWAP_RB_SHIFT & GX_BP_TEVKSEL_SWAP_RB_LMASK);
    }
    if (pA != NULL) {
        *pA = static_cast<GXTevColorChan>(cmd >> GX_BP_TEVKSEL_SWAP_GA_SHIFT & GX_BP_TEVKSEL_SWAP_GA_LMASK);
    }

    return true;
}

void ResTev::GXSetTevSwapModeTable(
    GXTevSwapSel swap, GXTevColorChan r, GXTevColorChan g, GXTevColorChan b, GXTevColorChan a
) {
    u8 *pCmd = ref().dl.dl.common.dl.swapModeTable[swap];
    u32 cmd;

    // clang-format off
    detail::ResWriteSSMask(&pCmd[GX_BP_CMD_SZ * 0],
                           GX_BP_TEVKSEL_SWAP_RB_MASK | GX_BP_TEVKSEL_SWAP_GA_MASK);

    cmd = 0;
    cmd |= r << GX_BP_TEVKSEL_SWAP_RB_SHIFT;
    cmd |= g << GX_BP_TEVKSEL_SWAP_GA_SHIFT;
    cmd |= (swap * 2 + GX_BP_REG_TEVKSEL0) << GX_BP_OPCODE_SHIFT;

    detail::ResWriteBPCmd(&pCmd[GX_BP_CMD_SZ * 1], cmd,
        ~(GX_BP_TEVKSEL_KASEL_ODD_MASK | GX_BP_TEVKSEL_KCSEL_ODD_MASK |
          GX_BP_TEVKSEL_KASEL_EVEN_MASK | GX_BP_TEVKSEL_KCSEL_EVEN_MASK));

    detail::ResWriteSSMask(&pCmd[GX_BP_CMD_SZ * 2],
                           GX_BP_TEVKSEL_SWAP_RB_MASK | GX_BP_TEVKSEL_SWAP_GA_MASK);

    cmd = 0;
    cmd |= b << GX_BP_TEVKSEL_SWAP_RB_SHIFT;
    cmd |= a << GX_BP_TEVKSEL_SWAP_GA_SHIFT;
    cmd |= (swap * 2 + GX_BP_REG_TEVKSEL1) << GX_BP_OPCODE_SHIFT;

    detail::ResWriteBPCmd(&pCmd[GX_BP_CMD_SZ * 3], cmd,
        ~(GX_BP_TEVKSEL_KASEL_ODD_MASK | GX_BP_TEVKSEL_KCSEL_ODD_MASK |
          GX_BP_TEVKSEL_KASEL_EVEN_MASK | GX_BP_TEVKSEL_KCSEL_EVEN_MASK));
    // clang-format on
}

void ResTev::GXSetTevSwapMode(GXTevStageID stage, GXTevSwapSel ras, GXTevSwapSel tex) {
    u8 *pCmd = ref().dl.dl.var[stage / TEV_STAGES_PER_DL].dl.alphaCalcAndSwap[stage % TEV_STAGES_PER_DL];

    detail::ResWriteBPCmd(
        pCmd, (ras << 0) | (tex << 2) | ((GX_BP_REG_TEVALPHACOMBINER0 + stage * 2) << GX_BP_OPCODE_SHIFT), 0xFF00000F
    );
}

bool ResTev::GXGetTevAlphaIn(
    GXTevStageID stage, GXTevAlphaArg *pA, GXTevAlphaArg *pB, GXTevAlphaArg *pC, GXTevAlphaArg *pD
) const {
    const u8 *pCmd = ref().dl.dl.var[stage / TEV_STAGES_PER_DL].dl.alphaCalcAndSwap[stage % TEV_STAGES_PER_DL];

    if (pCmd[0] == 0) {
        return false;
    }

    u32 cmd;
    detail::ResReadBPCmd(pCmd, &cmd);

    if (pA != NULL) {
        *pA = static_cast<GXTevAlphaArg>(cmd >> 13 & 7);
    }
    if (pB != NULL) {
        *pB = static_cast<GXTevAlphaArg>(cmd >> 10 & 7);
    }
    if (pC != NULL) {
        *pC = static_cast<GXTevAlphaArg>(cmd >> 7 & 7);
    }
    if (pD != NULL) {
        *pD = static_cast<GXTevAlphaArg>(cmd >> 4 & 7);
    }

    return true;
}

bool ResTev::GXGetTevAlphaOp(
    GXTevStageID stage, GXTevOp *pOp, GXTevBias *pBias, GXTevScale *pScale, GXBool *pClamp, GXTevRegID *pReg
) const {
    const u8 *pCmd = ref().dl.dl.var[stage / TEV_STAGES_PER_DL].dl.alphaCalcAndSwap[stage % TEV_STAGES_PER_DL];

    if (pCmd[0] == 0) {
        return false;
    }

    u32 cmd;
    detail::ResReadBPCmd(pCmd, &cmd);

    GXTevOp op;
    GXTevBias bias;
    GXTevScale scale;

    bias = static_cast<GXTevBias>(cmd >> 16 & 3);

    if (pClamp != NULL) {
        *pClamp = cmd >> 19 & 1;
    }
    if (pReg != NULL) {
        *pReg = static_cast<GXTevRegID>(cmd >> 22 & 3);
    }

    op = static_cast<GXTevOp>(cmd >> 18 & 1);
    scale = static_cast<GXTevScale>(cmd >> 20 & 3);

    if (bias == 3) {
        op = static_cast<GXTevOp>((op | scale << 1) + 8);
        bias = GX_TB_ZERO;
        scale = GX_CS_SCALE_1;
    }

    if (pBias != NULL) {
        *pBias = bias;
    }
    if (pOp != NULL) {
        *pOp = op;
    }
    if (pScale != NULL) {
        *pScale = scale;
    }

    return true;
}

void ResTev::GXSetTevAlphaIn(GXTevStageID stage, GXTevAlphaArg a, GXTevAlphaArg b, GXTevAlphaArg c, GXTevAlphaArg d) {
    u8 *pCmd = ref().dl.dl.var[stage / TEV_STAGES_PER_DL].dl.alphaCalcAndSwap[stage % TEV_STAGES_PER_DL];

    detail::ResWriteBPCmd(
        pCmd,
        (d << 4) | (c << 7) | (b << 10) | (a << 13) | ((GX_BP_REG_TEVALPHACOMBINER0 + stage * 2) << GX_BP_OPCODE_SHIFT),
        0xFF00FFF0
    );
}

void ResTev::GXSetTevAlphaOp(
    GXTevStageID stage, GXTevOp op, GXTevBias bias, GXTevScale scale, GXBool clamp, GXTevRegID reg
) {
    u8 *pCmd = ref().dl.dl.var[stage / TEV_STAGES_PER_DL].dl.alphaCalcAndSwap[stage % TEV_STAGES_PER_DL];

    if (op <= GX_TEV_SUB) {
        detail::ResWriteBPCmd(
            pCmd,
            (bias << 16) | ((op & 1) << 18) | (clamp << 19) | (scale << 20) | (reg << 22) |
                ((GX_BP_REG_TEVALPHACOMBINER0 + stage * 2) << GX_BP_OPCODE_SHIFT),
            0xFFFF0000
        );
    } else {
        detail::ResWriteBPCmd(
            pCmd,
            (3 << 16) | ((op & 1) << 18) | (clamp << 19) | ((op & 6) << 19) | (reg << 22) |
                ((GX_BP_REG_TEVALPHACOMBINER0 + stage * 2) << GX_BP_OPCODE_SHIFT),
            0xFFFF0000
        );
    }
}

bool ResTev::GXGetTevKColorSel(GXTevStageID stage, GXTevKColorSel *pSel) const {
    const u8 *pCmd = ref().dl.dl.var[stage / TEV_STAGES_PER_DL].dl.tevKonstantSel;

    if (pCmd[0] == 0) {
        return false;
    }

    u32 cmd;
    detail::ResReadBPCmd(&pCmd[GX_BP_CMD_SZ], &cmd);

    if (stage & 1) {
        *pSel = static_cast<GXTevKColorSel>(cmd >> 14 & 0x1F);
    } else {
        *pSel = static_cast<GXTevKColorSel>(cmd >> 4 & 0x1F);
    }

    return true;
}

bool ResTev::GXGetTevKAlphaSel(GXTevStageID stage, GXTevKAlphaSel *pSel) const {
    const u8 *pCmd = ref().dl.dl.var[stage / TEV_STAGES_PER_DL].dl.tevKonstantSel;

    if (pCmd[0] == 0) {
        return false;
    }

    u32 cmd;
    detail::ResReadBPCmd(&pCmd[GX_BP_CMD_SZ], &cmd);

    if (stage & 1) {
        *pSel = static_cast<GXTevKAlphaSel>(cmd >> 19 & 0x1F);
    } else {
        *pSel = static_cast<GXTevKAlphaSel>(cmd >> 9 & 0x1F);
    }

    return true;
}

void ResTev::GXSetTevKColorSel(GXTevStageID stage, GXTevKColorSel sel) {
    u8 *pCmd = ref().dl.dl.var[stage / TEV_STAGES_PER_DL].dl.tevKonstantSel;
    u32 shift = (stage & 1) ? 14 : 4;
    u32 mask = 0x1F << shift;

    detail::ResWriteSSMask(pCmd, mask);
    detail::ResWriteBPCmd(
        &pCmd[GX_BP_CMD_SZ],
        ((GX_BP_REG_TEVKSEL0 + stage / TEV_STAGES_PER_DL) << GX_BP_OPCODE_SHIFT) | (sel << shift), 0xFF000000 | mask
    );
}

void ResTev::GXSetTevKAlphaSel(GXTevStageID stage, GXTevKAlphaSel sel) {
    u8 *pCmd = ref().dl.dl.var[stage / TEV_STAGES_PER_DL].dl.tevKonstantSel;
    u32 shift = (stage & 1) ? 19 : 9;
    u32 mask = 0x1F << shift;

    detail::ResWriteSSMask(pCmd, mask);
    detail::ResWriteBPCmd(
        &pCmd[GX_BP_CMD_SZ],
        ((GX_BP_REG_TEVKSEL0 + stage / TEV_STAGES_PER_DL) << GX_BP_OPCODE_SHIFT) | (sel << shift), 0xFF000000 | mask
    );
}

bool ResTev::GXGetTevOrder(GXTevStageID stage, GXTexCoordID *pCoord, GXTexMapID *pMap, GXChannelID *pChannel) const {
    // Convert RAS channel ID to GX channel ID
    static const GXChannelID r2c[GX_RAS_MAX_CHANNEL] = {GX_COLOR0A0,   GX_COLOR1A1,   GX_COLOR_NULL,  GX_COLOR_NULL,
                                                        GX_COLOR_NULL, GX_ALPHA_BUMP, GX_ALPHA_BUMPN, GX_COLOR_ZERO};

    const u8 *pCmd = ref().dl.dl.var[stage / TEV_STAGES_PER_DL].dl.tevOrder;

    if (pCmd[0] == 0) {
        return false;
    }

    u32 cmd;
    detail::ResReadBPCmd(pCmd, &cmd);

    bool enabled;
    GXTexCoordID coord;
    GXTexMapID map;
    GXChannelID channel;

    if (stage & 1) {
        channel = r2c[cmd >> GX_BP_RAS1_TREF_COLORCHAN_ODD_SHIFT & GX_BP_RAS1_TREF_COLORCHAN_ODD_LMASK];

        coord =
            static_cast<GXTexCoordID>(cmd >> GX_BP_RAS1_TREF_TEXCOORD_ODD_SHIFT & GX_BP_RAS1_TREF_TEXCOORD_ODD_LMASK);

        enabled = cmd >> GX_BP_RAS1_TREF_ENABLE_TEX_ODD_SHIFT & GX_BP_RAS1_TREF_ENABLE_TEX_ODD_LMASK;

        map = static_cast<GXTexMapID>(cmd >> GX_BP_RAS1_TREF_TEXMAP_ODD_SHIFT & GX_BP_RAS1_TREF_TEXMAP_ODD_LMASK);
    } else {
        channel = r2c[cmd >> GX_BP_RAS1_TREF_COLORCHAN_EVEN_SHIFT & GX_BP_RAS1_TREF_COLORCHAN_EVEN_LMASK];

        coord =
            static_cast<GXTexCoordID>(cmd >> GX_BP_RAS1_TREF_TEXCOORD_EVEN_SHIFT & GX_BP_RAS1_TREF_TEXCOORD_EVEN_LMASK);

        enabled = cmd >> GX_BP_RAS1_TREF_ENABLE_TEX_EVEN_SHIFT & GX_BP_RAS1_TREF_ENABLE_TEX_EVEN_LMASK;

        map = static_cast<GXTexMapID>(cmd >> GX_BP_RAS1_TREF_TEXMAP_EVEN_SHIFT & GX_BP_RAS1_TREF_TEXMAP_EVEN_LMASK);
    }

    if (pCoord != NULL) {
        *pCoord = coord;
    }

    if (pChannel != NULL) {
        *pChannel = channel;
    }

    if (!enabled) {
        map = GX_TEXMAP_NULL;
    }

    if (pMap) {
        *pMap = map;
    }

    return true;
}

void ResTev::GXSetTevOrder(GXTevStageID stage, GXTexCoordID coord, GXTexMapID map, GXChannelID channel) {
    static u8 c2r[0x10] = {0, 1, 0, 1, 0, 1, 7, 5, 6, 0, 0, 0, 0, 0, 0, 7};

    // Two statements that compile to nothing stand for what the original had here, most likely
    // assertions. Without them this function is small enough to be inlined into SetNumTevStages.
    (void)0;
    (void)0;

    GXTexCoordID currCoord;
    GXTexMapID currMap;
    if (GXGetTevOrder(stage, &currCoord, &currMap, NULL)) {
        if (currCoord != GX_TEXCOORD_NULL && currMap != GX_TEXMAP_NULL) {
            ref().texCoordToTexMapID[currCoord] = GX_TEXMAP_NULL;
        }
    }

    if (coord != GX_TEXCOORD_NULL) {
        ref().texCoordToTexMapID[coord] = map;
    }

    u8 *pCmd = ref().dl.dl.var[stage / TEV_STAGES_PER_DL].dl.tevOrder;

    // Use the shift to determine if Even or Odd
    u32 shift = ((stage & 1) ? GX_BP_RAS1_TREF_TEXMAP_ODD_SHIFT : GX_BP_RAS1_TREF_TEXMAP_EVEN_SHIFT);

    // clang-format off
    u32 mask = (
        (0xFF << 24) | 
        ( GX_BP_RAS1_TREF_TEXMAP_EVEN_MASK     | 
          GX_BP_RAS1_TREF_TEXCOORD_EVEN_MASK   |
          GX_BP_RAS1_TREF_ENABLE_TEX_EVEN_MASK |
          GX_BP_RAS1_TREF_COLORCHAN_EVEN_MASK  
        ) << shift
    );
    
    u32 cmd = ( 
        ( ( map & GX_BP_RAS1_TREF_TEXMAP_EVEN_LMASK          ) << GX_BP_RAS1_TREF_TEXMAP_EVEN_SHIFT     ) |
        ( ( coord & GX_BP_RAS1_TREF_TEXCOORD_EVEN_LMASK      ) << GX_BP_RAS1_TREF_TEXCOORD_EVEN_SHIFT   ) |
        ( ( map != GX_TEXMAP_NULL && !(map & GX_TEX_DISABLE) ) << GX_BP_RAS1_TREF_ENABLE_TEX_EVEN_SHIFT ) |
        ( ( c2r[channel & 0xF]                               )  << GX_BP_RAS1_TREF_COLORCHAN_EVEN_SHIFT )
    );
    // clang-format on

    cmd <<= shift;
    cmd |= (GX_BP_REG_RAS1_TREF0 + (stage / TEV_STAGES_PER_DL)) << 24;

    detail::ResWriteBPCmd(pCmd, cmd, mask);
}

bool ResTev::GXGetTevColorIn(
    GXTevStageID stage, GXTevColorArg *pA, GXTevColorArg *pB, GXTevColorArg *pC, GXTevColorArg *pD
) const {
    const u8 *pCmd = ref().dl.dl.var[stage / TEV_STAGES_PER_DL].dl.tevColorCalc[stage % TEV_STAGES_PER_DL];

    if (pCmd[0] == 0) {
        return false;
    }

    u32 cmd;
    detail::ResReadBPCmd(pCmd, &cmd);

    if (pA != NULL) {
        *pA = static_cast<GXTevColorArg>(cmd >> GX_BP_TEVCOLORCOMBINER_A_SHIFT & 0xF);
    }
    if (pB != NULL) {
        *pB = static_cast<GXTevColorArg>(cmd >> GX_BP_TEVCOLORCOMBINER_B_SHIFT & 0xF);
    }
    if (pC != NULL) {
        *pC = static_cast<GXTevColorArg>(cmd >> GX_BP_TEVCOLORCOMBINER_C_SHIFT & 0xF);
    }
    if (pD != NULL) {
        *pD = static_cast<GXTevColorArg>(cmd >> GX_BP_TEVCOLORCOMBINER_D_SHIFT & 0xF);
    }

    return true;
}

bool ResTev::GXGetTevColorOp(
    GXTevStageID stage, GXTevOp *pOp, GXTevBias *pBias, GXTevScale *pScale, GXBool *pClamp, GXTevRegID *pReg
) const {
    const u8 *pCmd = ref().dl.dl.var[stage / TEV_STAGES_PER_DL].dl.tevColorCalc[stage % TEV_STAGES_PER_DL];

    if (pCmd[0] == 0) {
        return false;
    }

    u32 cmd;
    detail::ResReadBPCmd(pCmd, &cmd);

    GXTevOp op;
    GXTevBias bias;
    GXTevScale scale;

    bias = static_cast<GXTevBias>(cmd >> 16 & 3);

    if (pClamp != NULL) {
        *pClamp = cmd >> 19 & 1;
    }
    if (pReg != NULL) {
        *pReg = static_cast<GXTevRegID>(cmd >> 22 & 3);
    }

    op = static_cast<GXTevOp>(cmd >> 18 & 1);
    scale = static_cast<GXTevScale>(cmd >> 20 & 3);

    if (bias == 3) {
        op = static_cast<GXTevOp>((op | scale << 1) + 8);
        bias = GX_TB_ZERO;
        scale = GX_CS_SCALE_1;
    }

    if (pBias != NULL) {
        *pBias = bias;
    }
    if (pOp != NULL) {
        *pOp = op;
    }
    if (pScale != NULL) {
        *pScale = scale;
    }

    return true;
}

void ResTev::GXSetTevColorIn(GXTevStageID stage, GXTevColorArg a, GXTevColorArg b, GXTevColorArg c, GXTevColorArg d) {
    u8 *pCmd = ref().dl.dl.var[stage / TEV_STAGES_PER_DL].dl.tevColorCalc[stage % TEV_STAGES_PER_DL];

    // clang-format off
    detail::ResWriteBPCmd(pCmd,
        (d << GX_BP_TEVCOLORCOMBINER_D_SHIFT) |
        (c << GX_BP_TEVCOLORCOMBINER_C_SHIFT) |
        (b << GX_BP_TEVCOLORCOMBINER_B_SHIFT) |
        (a << GX_BP_TEVCOLORCOMBINER_A_SHIFT) |
        ((GX_BP_REG_TEVCOLORCOMBINER0 + stage * 2)
            << GX_BP_OPCODE_SHIFT),

        ~(GX_BP_TEVCOLORCOMBINER_DEST_MASK |
          GX_BP_TEVCOLORCOMBINER_SCALE_OR_COMPARE_MODE_MASK |
          GX_BP_TEVCOLORCOMBINER_CLAMP_MASK |
          GX_BP_TEVCOLORCOMBINER_OP_OR_COMPARISON_MASK |
          GX_BP_TEVCOLORCOMBINER_BIAS_MASK));
    // clang-format on
}

void ResTev::GXSetTevColorOp(
    GXTevStageID stage, GXTevOp op, GXTevBias bias, GXTevScale scale, GXBool clamp, GXTevRegID reg
) {
    u8 *pCmd = ref().dl.dl.var[stage / TEV_STAGES_PER_DL].dl.tevColorCalc[stage % TEV_STAGES_PER_DL];

    if (op <= GX_TEV_SUB) {
        detail::ResWriteBPCmd(
            pCmd,
            (bias << 16) | ((op & 1) << 18) | (clamp << 19) | (scale << 20) | (reg << 22) |
                ((GX_BP_REG_TEVCOLORCOMBINER0 + stage * 2) << GX_BP_OPCODE_SHIFT),
            0xFFFF0000
        );
    } else {
        detail::ResWriteBPCmd(
            pCmd,
            (3 << 16) | ((op & 1) << 18) | (clamp << 19) | ((op & 6) << 19) | (reg << 22) |
                ((GX_BP_REG_TEVCOLORCOMBINER0 + stage * 2) << GX_BP_OPCODE_SHIFT),
            0xFFFF0000
        );
    }
}

bool ResTev::GXGetIndTexOrder(GXIndTexStageID stage, GXTexCoordID *pCoord, GXTexMapID *pMap) const {
    const u8 *pCmd = ref().dl.dl.common.dl.indTexOrder[stage / GX_MAX_INDTEXSTAGE];

    if (pCmd[0] == 0) {
        return false;
    }

    u32 cmd;
    detail::ResReadBPCmd(pCmd, &cmd);

    u32 shift = (stage % GX_MAX_INDTEXSTAGE) * (GX_BP_RAS1_IREF_MAP0_SZ + GX_BP_RAS1_IREF_TXC0_SZ);

    if (pMap) {
        *pMap = static_cast<GXTexMapID>(cmd >> (shift + GX_BP_RAS1_IREF_MAP0_SHIFT) & GX_BP_RAS1_IREF_MAP0_LMASK);
    }
    if (pCoord) {
        *pCoord = static_cast<GXTexCoordID>(cmd >> (shift + GX_BP_RAS1_IREF_TXC0_SHIFT) & GX_BP_RAS1_IREF_TXC0_LMASK);
    }

    return true;
}

void ResTev::GXSetIndTexOrder(GXIndTexStageID stage, GXTexCoordID coord, GXTexMapID map) {
    GXTexCoordID currCoord;
    GXTexMapID currMap;
    if (GXGetIndTexOrder(stage, &currCoord, &currMap)) {
        if (currCoord != GX_TEXCOORD_NULL && currMap != GX_TEXMAP_NULL) {
            ref().texCoordToTexMapID[currCoord] = GX_TEXMAP_NULL;
        }
    }

    if (coord != GX_TEXCOORD_NULL) {
        ref().texCoordToTexMapID[coord] = map;
    }

    u8 *pCmd = ref().dl.dl.common.dl.indTexOrder[stage / GX_MAX_INDTEXSTAGE];

    u32 shift = (stage % GX_MAX_INDTEXSTAGE) * (GX_BP_RAS1_IREF_MAP0_SZ + GX_BP_RAS1_IREF_TXC0_SZ);

    u32 reg = ((map & GX_BP_RAS1_IREF_MAP0_LMASK) << (shift + GX_BP_RAS1_IREF_MAP0_SHIFT)) |
              ((coord & GX_BP_RAS1_IREF_TXC0_LMASK) << (shift + GX_BP_RAS1_IREF_TXC0_SHIFT)) |
              (GX_BP_REG_RAS1_IREF << 24);

    u32 mask = ((GX_BP_RAS1_IREF_MAP0_LMASK) << (shift + GX_BP_RAS1_IREF_MAP0_SHIFT)) |
               ((GX_BP_RAS1_IREF_TXC0_LMASK) << (shift + GX_BP_RAS1_IREF_TXC0_SHIFT));

    detail::ResWriteBPCmd(pCmd, reg, mask);
}

void ResTev::GXSetTevDirect(GXTevStageID stage) {
    u8 *pCmd = ref().dl.dl.var[stage / TEV_STAGES_PER_DL].dl.tevIndirect[stage % TEV_STAGES_PER_DL];

    detail::ResWriteBPCmd(pCmd, (GX_BP_REG_INDTEVSTAGE0 + (stage & 0xF)) << GX_BP_OPCODE_SHIFT);
}

void ResTev::SetNumTevStages(u8 num) {
    if (num < 1 || num > GX_MAX_TEVSTAGE) {
        return;
    }

    ResTevData &r = ref();

    if (r.nStages > num) {
        u32 i;

        for (i = num; i < r.nStages; i++) {
            GXSetTevOrder(static_cast<GXTevStageID>(i), GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
        }

        for (i = (num + 1) / TEV_STAGES_PER_DL; i < static_cast<u32>(r.nStages + 1) / TEV_STAGES_PER_DL; i++) {
            ResTevVariableDL *pVar = &r.dl.dl.var[i];

            detail::ZeroMemory16ByteBlocks(pVar, sizeof(ResTevVariableDL));
            DCStoreRangeNoSync(pVar, sizeof(ResTevVariableDL));
        }
    }

    r.nStages = num;
}

void ResTev::CallDisplayList(bool sync) const {
    // Variable DL holds data for two GX tev stages
    static const u32 dlsize[GX_MAX_TEVSTAGE] = {
        ROUND_UP(sizeof(ResTevCommonDL) + 1 * sizeof(ResTevVariableDL), 32),
        ROUND_UP(sizeof(ResTevCommonDL) + 1 * sizeof(ResTevVariableDL), 32),
        ROUND_UP(sizeof(ResTevCommonDL) + 2 * sizeof(ResTevVariableDL), 32),
        ROUND_UP(sizeof(ResTevCommonDL) + 2 * sizeof(ResTevVariableDL), 32),
        ROUND_UP(sizeof(ResTevCommonDL) + 3 * sizeof(ResTevVariableDL), 32),
        ROUND_UP(sizeof(ResTevCommonDL) + 3 * sizeof(ResTevVariableDL), 32),
        ROUND_UP(sizeof(ResTevCommonDL) + 4 * sizeof(ResTevVariableDL), 32),
        ROUND_UP(sizeof(ResTevCommonDL) + 4 * sizeof(ResTevVariableDL), 32),
        ROUND_UP(sizeof(ResTevCommonDL) + 5 * sizeof(ResTevVariableDL), 32),
        ROUND_UP(sizeof(ResTevCommonDL) + 5 * sizeof(ResTevVariableDL), 32),
        ROUND_UP(sizeof(ResTevCommonDL) + 6 * sizeof(ResTevVariableDL), 32),
        ROUND_UP(sizeof(ResTevCommonDL) + 6 * sizeof(ResTevVariableDL), 32),
        ROUND_UP(sizeof(ResTevCommonDL) + 7 * sizeof(ResTevVariableDL), 32),
        ROUND_UP(sizeof(ResTevCommonDL) + 7 * sizeof(ResTevVariableDL), 32),
        ROUND_UP(sizeof(ResTevCommonDL) + 8 * sizeof(ResTevVariableDL), 32),
        ROUND_UP(sizeof(ResTevCommonDL) + 8 * sizeof(ResTevVariableDL), 32)
    };

    if (sync) {
        PPCSync();
    }

    GXCallDisplayList(const_cast<ResTevDL *>(&ref().dl), dlsize[GetNumTevStages() - 1]);
}

ResTev ResTev::CopyTo(void *pDst) {
    const ResTevData *pSrc = &ref();
    detail::Copy32ByteBlocks(pDst, pSrc, sizeof(ResTevData));

    ResTev tev(pDst);
    tev.ref().toResMdlData -= reinterpret_cast<uintptr_t>(pDst) - reinterpret_cast<uintptr_t>(pSrc);

    tev.DCStore(false);
    return tev;
}

void ResTev::DCStore(bool sync) {
    void *pBase = &ref();
    u32 size = ref().size;

    if (sync) {
        DC::StoreRange(pBase, size);
    } else {
        DC::StoreRangeNoSync(pBase, size);
    }
}

} // namespace g3d
} // namespace nw4r
