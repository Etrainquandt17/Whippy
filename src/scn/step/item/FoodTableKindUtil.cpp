#include "scn/step/item/FoodTableKindUtil.h"

#include "app/Random.h"

using app::Random;

namespace scn {
namespace step {
namespace item {

namespace {

const u32 T_TABLE_STANDARD[] = { 0, 1, 2, 3, 4 };
const u32 T_TABLE_LV1[] = { 0, 6, 8, 3, 19 };
const u32 T_TABLE_LV2[] = { 1, 9, 2, 4, 32 };
const u32 T_TABLE_LV3[] = { 7, 5, 21, 12, 33 };
const u32 T_TABLE_LV4[] = { 20, 13, 34, 25, 31 };
const u32 T_TABLE_LV5[] = { 10, 21, 14, 29, 26 };
const u32 T_TABLE_LV6[] = { 17, 13, 22, 24, 23 };
const u32 T_TABLE_LV7[] = { 3, 2, 15, 34, 28 };

struct Table {
    u32 mNum;
    const u32* mKinds;
};

const Table T_TABLES[] = {
    { 5, T_TABLE_STANDARD }, { 5, T_TABLE_LV1 }, { 5, T_TABLE_LV2 }, { 5, T_TABLE_LV3 },
    { 5, T_TABLE_LV4 },      { 5, T_TABLE_LV5 }, { 5, T_TABLE_LV6 }, { 5, T_TABLE_LV7 },
};

}

u32 FoodTableKindUtil::RandomFoodKind(FoodTableKind kind) {
    const Table& table = T_TABLES[kind];
    return table.mKinds[Random::RandU32(table.mNum)];
}

}}}  // namespace scn::step::item
