#include "libs/libms/libms/projfile.h"

#include "libs/libms/libms/commonlib.h"
#include "libs/libms/libms/libms.h"

struct ProjectInfo {
    /* 0x00 */ struct MsbInfo base;
    /* 0x10 */ int clb1Index;
    /* 0x14 */ int clr1Index;
    /* 0x18 */ int alb1Index;
    /* 0x1C */ int ati2Index;
    /* 0x20 */ int ali2Index;
    /* 0x24 */ int tgg2Index;
    /* 0x28 */ int tag2Index;
    /* 0x2C */ int tgp2Index;
    /* 0x30 */ int tgl2Index;
    /* 0x34 */ int syl3Index;
    /* 0x38 */ int slb1Index;
    /* 0x3C */ int cti1Index;
};

struct OffsetTable {
    /* 0x00 */ unsigned short count;
    /* 0x04 */ int offsets[1];
};

struct TagGroupInfo {
    /* 0x00 */ unsigned short tagCount;
    /* 0x02 */ unsigned short tags[1];
};

struct TagInfo {
    /* 0x00 */ unsigned short paramCount;
    /* 0x02 */ unsigned short params[1];
};

struct TagParamInfo {
    /* 0x00 */ unsigned char type;
    /* 0x02 */ unsigned short itemCount;
    /* 0x04 */ unsigned short items[1];
};

extern "C" {
struct TagInfo *LMSi_GetTagInfoStart(struct ProjectInfo *info, struct TagGroupInfo *group, unsigned short tag);
struct TagParamInfo *LMSi_GetParamInfoStart(struct ProjectInfo *info, struct TagInfo *tag, unsigned short param);
const wchar_t *LMSi_GetListItemInfoStart(struct ProjectInfo *info, struct TagParamInfo *param, unsigned short item);
}

static inline struct TagGroupInfo *LMSi_GetTagGroupInfoStart(struct ProjectInfo *info, unsigned short group) {
    if (info->tgg2Index == -1) {
        return NULL;
    }

    struct OffsetTable *table = (struct OffsetTable *)info->base.sectionInfos[info->tgg2Index].ptr;
    if (group >= table->count) {
        return NULL;
    }

    return LMS_OFS_TO_PTR(struct TagGroupInfo, table, table->offsets[group]);
}

struct ProjectInfo *LMS_InitProject(void *data) {
    struct ProjectInfo *info = (struct ProjectInfo *)LMSi_Malloc(sizeof(struct ProjectInfo));
    info->base.header = (struct MsbHeader *)data;
    LMSi_AnalyzeMessageBinary(&info->base, "MsgPrjBn");
    info->clr1Index = LMSi_SearchBlockByName(&info->base, "CLR1");
    info->clb1Index = LMSi_SearchBlockByName(&info->base, "CLB1");
    info->ati2Index = LMSi_SearchBlockByName(&info->base, "ATI2");
    info->alb1Index = LMSi_SearchBlockByName(&info->base, "ALB1");
    info->ali2Index = LMSi_SearchBlockByName(&info->base, "ALI2");
    info->tgg2Index = LMSi_SearchBlockByName(&info->base, "TGG2");
    info->tag2Index = LMSi_SearchBlockByName(&info->base, "TAG2");
    info->tgp2Index = LMSi_SearchBlockByName(&info->base, "TGP2");
    info->tgl2Index = LMSi_SearchBlockByName(&info->base, "TGL2");
    info->syl3Index = LMSi_SearchBlockByName(&info->base, "SYL3");
    info->slb1Index = LMSi_SearchBlockByName(&info->base, "SLB1");
    info->cti1Index = LMSi_SearchBlockByName(&info->base, "CTI1");
    return info;
}

const wchar_t *LMS_GetTagGroupName(struct ProjectInfo *info, unsigned short group) {
    unsigned short *groupInfo = (unsigned short *)LMSi_GetTagGroupInfoStart(info, group);
    if (groupInfo == NULL) {
        return NULL;
    }

    return (const wchar_t *)&groupInfo[groupInfo[0] + 1];
}

const wchar_t *LMS_GetTagName(struct ProjectInfo *info, unsigned short group, unsigned short tag) {
    struct TagGroupInfo *groupInfo = LMSi_GetTagGroupInfoStart(info, group);
    if (groupInfo == NULL) {
        return NULL;
    }

    struct TagInfo *tagInfo = LMSi_GetTagInfoStart(info, groupInfo, tag);
    if (tagInfo == NULL) {
        return NULL;
    }

    return (const wchar_t *)&tagInfo->params[tagInfo->paramCount];
}

const wchar_t *LMS_GetTagListItemName(struct ProjectInfo *info, unsigned short group, unsigned short tag, unsigned short param,
                                      unsigned short item) {
    struct TagGroupInfo *groupInfo = LMSi_GetTagGroupInfoStart(info, group);
    if (groupInfo == NULL) {
        return NULL;
    }

    struct TagInfo *tagInfo = LMSi_GetTagInfoStart(info, groupInfo, tag);
    if (tagInfo == NULL) {
        return NULL;
    }

    struct TagParamInfo *paramInfo = LMSi_GetParamInfoStart(info, tagInfo, param);
    if (paramInfo == NULL) {
        return NULL;
    }

    const wchar_t *name = LMSi_GetListItemInfoStart(info, paramInfo, item);
    if (name == NULL) {
        return NULL;
    }

    return name;
}

struct TagInfo *LMSi_GetTagInfoStart(struct ProjectInfo *info, struct TagGroupInfo *group, unsigned short tag) {
    if (info->tag2Index == -1) {
        return NULL;
    }

    struct MsbBlock *block = &info->base.sectionInfos[info->tag2Index];
    if (tag >= group->tagCount) {
        return NULL;
    }

    struct OffsetTable *table = (struct OffsetTable *)block->ptr;
    return LMS_OFS_TO_PTR(struct TagInfo, table, table->offsets[group->tags[tag]]);
}

struct TagParamInfo *LMSi_GetParamInfoStart(struct ProjectInfo *info, struct TagInfo *tag, unsigned short param) {
    if (info->tgp2Index == -1) {
        return NULL;
    }

    struct MsbBlock *block = &info->base.sectionInfos[info->tgp2Index];
    if (param >= tag->paramCount) {
        return NULL;
    }

    struct OffsetTable *table = (struct OffsetTable *)block->ptr;
    return LMS_OFS_TO_PTR(struct TagParamInfo, table, table->offsets[tag->params[param]]);
}

// TODO: registers differ: the original keeps the section index in r0 and the type in r7, this has them in r6 and r0.
const wchar_t *LMSi_GetListItemInfoStart(struct ProjectInfo *info, struct TagParamInfo *param, unsigned short item) {
    if (info->tgl2Index == -1) {
        return NULL;
    }

    struct MsbBlock *block = &info->base.sectionInfos[info->tgl2Index];
    int type = param->type;
    if (type != 9) {
        return NULL;
    }

    if (item >= param->itemCount) {
        return NULL;
    }

    struct OffsetTable *table = (struct OffsetTable *)block->ptr;
    return LMS_OFS_TO_PTR(const wchar_t, table, table->offsets[param->items[item]]);
}
