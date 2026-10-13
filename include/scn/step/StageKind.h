#ifndef SCN_STEP_STAGEKIND_H
#define SCN_STEP_STAGEKIND_H

namespace scn {
namespace step {

// TODO: name the stages. They are in level order: five each for levels 0 to 2, six each for
// levels 3 to 6 (StageKindUtil's T_INFOS). The last stage of a level is its boss, except in
// level 6, where the last three are.
enum StageKind {
    STAGE_KIND_0,
    STAGE_KIND_1,
    STAGE_KIND_2,
    STAGE_KIND_3,
    STAGE_KIND_4,
    STAGE_KIND_5,
    STAGE_KIND_6,
    STAGE_KIND_7,
    STAGE_KIND_8,
    STAGE_KIND_9,
    STAGE_KIND_10,
    STAGE_KIND_11,
    STAGE_KIND_12,
    STAGE_KIND_13,
    STAGE_KIND_14,
    STAGE_KIND_15,
    STAGE_KIND_16,
    STAGE_KIND_17,
    STAGE_KIND_18,
    STAGE_KIND_19,
    STAGE_KIND_20,
    STAGE_KIND_21,
    STAGE_KIND_22,
    STAGE_KIND_23,
    STAGE_KIND_24,
    STAGE_KIND_25,
    STAGE_KIND_26,
    STAGE_KIND_27,
    STAGE_KIND_28,
    STAGE_KIND_29,
    STAGE_KIND_30,
    STAGE_KIND_31,
    STAGE_KIND_32,
    STAGE_KIND_33,
    STAGE_KIND_34,
    STAGE_KIND_35,
    STAGE_KIND_36,
    STAGE_KIND_37,
    STAGE_KIND_38,
};

}
}

#endif
