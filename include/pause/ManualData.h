#ifndef PAUSE_MANUALDATA_H
#define PAUSE_MANUALDATA_H

#include "hel/common/FixedStringIN.h"
#include "pause/ManualKind.h"
#include "pause/ModeKind.h"
#include "types.h"

namespace pause {

class ManualData {
public:
    static hel::common::FixedStringIN<char, 48> PathFrameAbilityIcon(ManualKind kind);
    static hel::common::FixedStringIN<char, 48> LabelFrameAbiilityTitle(ManualKind kind);
    static hel::common::FixedStringIN<char, 48> PathAbilityBG(ManualKind kind);
    static hel::common::FixedStringIN<char, 48> LabelAbilityInfo(ManualKind kind, ModeKind mode);
    static u32 CommandPageCount(ManualKind kind);
    static u32 CommandTextCount(ManualKind kind, u32 page);
    static u32 CommandLineCount(ManualKind kind, u32 page);
    static hel::common::FixedStringIN<char, 48> LabelCommandInput(ManualKind kind, u32 page, u32 index);
    static hel::common::FixedStringIN<char, 48> LabelCommandName(ManualKind kind, u32 page, u32 index);
    static bool IsCommandLineDouble(ManualKind kind, u32 page, u32 index);
};

}  // namespace pause

#endif
