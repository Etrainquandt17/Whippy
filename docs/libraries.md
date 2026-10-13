# Libraries
About a fifth of the program isn't the game's own code. That's the Metrowerks runtime, MSL, MetroTRK, the Revolution SDK, NintendoWare (`nw4r`), the HOME Menu library, Mobiclip and two smaller libraries. Other Wii decompilation projects have already written most of these. This project reuses their sources wherever they compile to this game's code, and we don't decompile a library function that someone else already has.

## Where the Code Came From
| Project | Game | Commit | Gave |
|---|---|---|---|
| [Garigari](https://github.com/SMGCommunity/Garigari) | Super Mario Galaxy 2 | `f52b99642de` | the header trees, most of the SDK, the whole Bluetooth stack, MSL |
| [ss](https://github.com/zeldaret/ss) | Skyward Sword | `3a93d428e87` | most of `nw4r` snd, g3d, lyt and ut; `libms` |
| [xenoblade](https://github.com/xbret/xenoblade) | Xenoblade Chronicles | `ea25691b202` | MetroTRK, the C++ exception runtime, and better versions of many SDK and `nw4r` files |
| [kdc](https://github.com/Swiftshine/kdc) | Kirby's Dream Collection | `e5bd14dcb01` | `nw4r` ef, parts of ax, os and the runtime |
| [tp](https://github.com/zeldaret/tp) | Twilight Princess | `c8fa8c9e2aa` | the HOME Menu library's `nw4hbm` part |
| [key](https://github.com/Swiftshine/key) | Kirby's Epic Yarn | `e78492b01c3` | the HOME Menu library's own files and its sound part; all of `wpad` and `wud` |

All 6 are released under CC0-1.0. The Bluetooth stack's files carry Apache-2.0 headers of their own (they're a decompilation based on bluedroid), and their notice is in `src/RVL_SDK/bte/NOTICE`.

[`library_sources.tsv`](library_sources.tsv) lists every file under `libs/` and every library source with the project and the path it was copied from, and notes the ones that were edited here. Copied files keep their comments and their style.

We also tried Petari (Super Mario Galaxy), ogws (Wii Sports) and mkw (Mario Kart Wii), with nothing gained over the above. Their libraries are older builds.

## State
| Library | Units | Linked | Code Matched |
|---|---|---|---|
| `Runtime` | 10 | 10 | 100% |
| `MSL_C` | 64 | 64 | 100% |
| `MSL_C++` | 3 | 0 | 0% |
| `MetroTRK` | 25 | 23 | 72% |
| `RVL_SDK` | 200 | 197 | 98% |
| `homebuttonLib` | 39 | 39 | 100% |
| `nw4r/snd` | 58 | 57 | 97% |
| `nw4r/g3d` | 58 | 56 | 98% |
| `nw4r/lyt` | 15 | 14 | 91% |
| `nw4r/ut` | 17 | 17 | 100% |
| `nw4r/db` | 3 | 3 | 100% |
| `nw4r/ef` | 30 | 21 | 37% |
| `nw4r/math` | 4 | 3 | 95% |
| `libms` | 4 | 3 | 95% |
| `nrel` | 16 | 0 | 0% |
| `Mobiclip` | 43 | 0 | 0% |

"Linked" means compiled from source in the build, and the percentage counts every matching function, linked or not. No project has sources for Mobiclip, `nrel` or the C++ part of MSL. A few single units had none either and were written here from the disassembly, which are `kpad/KMPLS.c` and `KZMplsTestSub.c` (both partly), `mem/mem_unitHeap.c`, `qsort.c`, `nw4r/ut/ut_PairFont.cpp` and `nw4r/g3d/g3d_scnmdlexpand.cpp`. `nw4r/snd/snd_WavePlayer.cpp` and 6 `nw4r/ef` units are still without any source.

Search the other projects by file name before you believe that a unit has no source. An earlier version of this page said nobody had the HOME Menu's `HBMBase`, `HBMController`, `HBMRemoteSpk` and `sound/mix`, or `wpad/lint`. Kirby's Epic Yarn has all of them, in directories its own build never compiles.

## Layout
Sources are in `src/` under the unit names of `configure.py`, so `Runtime/`, `MSL_C/`, `MetroTRK/`, `RVL_SDK/<library>/`, `homebuttonLib/`, `nw4r/<library>/` and `libms/`.

Headers are in `libs/`, not in `include/`. Library code doesn't see the game's headers, and the game doesn't see these yet.

`libs/RVL_SDK`, `libs/MSL_C`, `libs/MSL_C++`, `libs/Runtime`, `libs/MetroTRK` and `libs/nw4r` are Garigari's trees. The other projects' header trees aren't interchangeable with them or with each other (one `stdarg.h` defines `va_list`, the next doesn't), so each of them has a private copy in a subdirectory (`libs/RVL_SDK/ss`, `libs/MSL_C/kdc` and so on), and a source copied from that project includes from there. That's about 1,600 header files for what should be 400.

The Bluetooth stack keeps its private headers beside its sources in `src/RVL_SDK/bte`, and that directory is first on its include path, because other roots hold headers of the same names.

## Compilers and Flags
All of this is in `configure.py`. This is what each library turned out to need:

| Library | Compiler | Beyond the Common Flags |
|---|---|---|
| `Runtime` | Wii/1.5 | `-O4,s`, functions aligned to 4. `NMWException.cpp`, `Gecko_ExceptionPPC.cpp` and `GCN_mem_alloc.c` take `-O4,p`; the first two and `New.cpp` have exceptions on, the last two of those RTTI as well |
| `MSL_C` | Wii/1.5 | `-fp_contract off -ipa file`, aligned to 4. `Math/Double_precision`, `mem_funcs.c`, `wmem.c` and `string.c` take `-O4,s`, except `e_rem_pio2.c` and `k_rem_pio2.c`, which take `-O4,p`; `mem.c` takes `-O2` |
| `MetroTRK` | Wii/1.0a | `-fp_contract off -str reuse,pool,noreadonly`, aligned to 4. `targimpl.c` takes `-pool off`, which decides the order of its `.bss` |
| `RVL_SDK` | Wii/1.0 | `-ipa file -fp_contract off`, aligned to 16. `wenc.c` is from GC/3.0a5.2, `nand.c` from Wii/1.0a, `EXIBios.c` takes `-schedule off` |
| `RVL_SDK/bte` | Wii/1.0 and GC/3.0a3 | the first 13 units in link order are the SDK team's, aligned to 16; the other 55 are Broadcom's prebuilt stack, from a GameCube compiler, aligned to 4 |
| `homebuttonLib` | Wii/1.0 | RTTI on, `-sdata 0 -sdata2 0`; its four `syn*` sound files are C++ |
| `nw4r` | Wii/1.5 | `-ipa file -fp_contract off`, aligned to 16 |
| `libms` | Wii/1.5 | C++ in files named `.c`, `-inline noauto` |

## Things That Cost Us Time
- Every library carries a version string with its build date, and each donor's is its own game's. This game's SDK was built on Dec 11 2009 and its `nw4r` in March and April 2011. A unit with another date matches in every function and still differs in `.data`. The strings in the sources are this game's now.
- The other projects give single files extra flags in their `configure.py`. Where a unit matches in every function and its data comes out in another order, look the file up there before you do anything else.
- Twilight Princess's SDK sources, compiled with `SDK_AUG2010` defined, are this SDK's version. `SIBios.c`, `ipcclt.c`, `ipcProfile.c` and `Pad.c` matched straight from there after the build date was set.
- This build of the SDK has no `DBPrintf`, `DBInit` or `__DBIsExceptionMarked` calls. A donor function that's longer by one of those calls just loses the line.
- Donor scaffolding has to go first. `dummyString` functions, float-ordering helpers, `#pragma dont_inline`, `NO_INLINE` and `DECOMP_FORCE...` helpers were the whole difference in about 10 `nw4r` units. Where a helper forced a string or a literal into the object, the real cause was an unused function the link dropped (its size is in the map under `UNUSED`) or a value computed into a local first.
- HAL changed `nw4r/lyt` to count the users of a palette. The `Material` constructor and destructor and `AnimTransformBasic::SetResource` call `HALTPLBind` and `HALTPLUnbind` from the game's own `TPL` unit, and `Material` is 0x7C bytes, not 0x5C.
- The HOME Menu library's `Pane` inherits `detail::PaneBase` publicly. With the private inheritance one donor header had, the type information of every pane class is one base short.
- `key`'s `src/revolution/WPAD/` is this game's `wpad` exactly (it carries the same build stamp), where Twilight Princess's wasn't. 11 of 80 functions matched from there, all of them from `key`. When one donor's file stays far off, try every other donor's copy before you work on it by hand. `key`'s SDK sources are C99 (`#pragma c99 on` as the first line) and need `<key/macros.h>` first.
- Several units here are larger than every donor's copy, because this game's link kept functions that the donor's game dropped. `g3d_anmscn` has 43 functions where Skyward Sword's has 1. The map has the names and sizes.
- This game's HOME Menu library is the May 19 2010 build, and `key`'s is Dec 10 2009. `HBMBase` and `HBMController` differ in a few places (the simple-sync callback, the Classic Controller through MotionPlus as device type 7).
- `nw4r/ef` against the Wii Sports text has a recipe. `sinf`/`cosf` pairs are `PSSinCosRad`, `std::sqrtf` is `math::FSqrt`, `1.0f / x` is `math::FInv(x)`, a conditional `VEC3Normalize` is an unconditional `ef::Normalize`, and the bugs the donor marks in `InitTev` and `InitColor` are fixed. That recipe finished all 7 emitter shapes.
- Auto-inlining counts statements, empty ones too. 2 `(void)0;` statements, which is what compiled-out assertions leave behind, kept `ResTev::GXSetTevOrder` from being inlined into its caller, and 1 didn't.
- A function the link dropped can decide the order of a unit's float constants, as they're created as each function is compiled, and a later function reuses an equal one. The sign is `UNUSED` constants numbered directly after used ones in the map (`KPAD.c`).
- Xenoblade's `nw4r/math` header has a live assertion in `FSqrt` that emits a call. `nw4r/math` units that use it include the plain `"nw4r/math.h"`.
- `OSExec.c` wants Twilight Princess's `CheckDVDLowIntType`, a `static` function with a `switch` that the compiler expands at all 7 places, where the other donors repeat an `if` block. Line numbers in its messages are this build's (1037, 1046, 1055, 1071).
- A C unit keeps the strings of functions the link dropped, and they have to be there for the strings behind them to sit right. `OSExec.c` has 3 dropped functions (`__OSLaunchDisk`, `OSExecv`, `__OSLaunchPartition`) whose strings are known and whose bodies aren't.
- Small C forms decided 3 SDK units that had every instruction but one or two. Those were a `u8` counter advanced by `i += (u8)7`, a `const char` parameter, and `*(path + len - 1)` in place of `path[len - 1]` ([Decompiling](decompiling.md) has them).
- An optimization level resets the function alignment. `-func_align 4` has to come after `-O4,s` on the command line, or the object's code section is aligned to 16 and everything behind it in the link moves.
- A function-by-function comparison doesn't see a wrong alignment. The link does.

## Checking a Library Source
`tools/compare.py` takes each unit's compiler and flags from `build/unit_flags.json`, which `configure.py` writes, so a library file is checked just like a game file:

```sh
python tools/compare.py all src/RVL_SDK/os/OSAlarm.c
python tools/compare.py SUKE01 <a file anywhere> -u RVL_SDK/os/OSAlarm          # compare another project's file with that unit
python tools/compare.py SUKE01 <file> -u <unit> --mw Wii/1.1 --flags=" -inline on"   # another compiler, extra flags
```

Write `--flags=` with the equals sign and a leading space, otherwise a value that starts with `-f` or `-p` is taken for one of the tool's own options.

## Units the Comparison Can't Judge
18 library units are linked on the strength of the link alone (`config/force_linked.txt`, `python tools/link_complete.py --force <source>`, and the list has one game unit as well). They reproduce the DOL, and `tools/compare.py` still objects, for one of these reasons:

- The split object's `.bss` is longer than the compiled one by the padding in front of the next unit (`OSFatal.c`, `snd_SoundPlayer`).
- The original link swapped a function with its look-alike ("was interchanged with" in the map), which the comparison doesn't follow. That's `__close_console` in `uart_console_io_gcn.c`.
- The splitter missed a relocation the compiler left in dead code (the HOME Menu's `lyt_textBox`).
- The source emits an unused weak function or a helper that the original object never had, and the link drops it. That's `snd_MmlSeqTrackAllocator`, `snd_SoundArchivePlayer`, `snd_StrmPlayer`, `snd_AnimSound`, `ut_DvdFileStream`, `AXVPB.c`, `dvd_broadway.c`, `usb.c`, `WPAD.c` (9 `__deadstrip` helpers that hold the strings of dropped functions), `HBMBase.cpp` (1 helper like that) and `New.cpp` (a function that exists only to make the compiler emit type information). These sources aren't what the original was, only equivalent after the link.
- `nw4r::math::MTX34RotXYZFIdx` is the original's paired-single code transcribed as assembly, with a TODO.
- MetroTRK's `cc_gdev.c` and `dolphin_trk_glue.c` emit `__DB*` functions from a shared debugger header that the link drops, and their `.bss` is split at other boundaries than the map's.

4 more link without being on that list although the comparison has a remark, because every function matches in order. Those are `Gecko_ExceptionPPC.cpp` (weak type information and the tables of dropped functions), `KPAD.c` (`.sdata2` holds 2 constants of dropped functions), `g3d_restev` (padding) and `OSExec.c` (`.sdata` holds an empty string of a dropped function).

Unverified bodies stand in for functions the link dropped, each with a TODO. Those are `ResMdl::UpdateFurLayer` in `g3d_resmdl`, `KPADGetMplsZeroDriftMode` in `KPAD.c`, `SPHERE::Set` in `math_geometry`, the 3 string holders in `OSExec.c`, and a handful in `nw4r/ef`. They're there because the unit's data only comes out right with them.

8 more were on that list until the cause was removed. The splitter had taken 3 constants for addresses, so `0x80808080` (the mask in `strcpy`), `0x80808081` (a division by 255) and `0x80004000` became relocations to whatever symbol sits there. Those 38 instructions are listed under `block_relocations` in each version's `config.yml` now, in `string.c`, `OS.c`, `OSFatal.c`, `WPADEncrypt.c`, Mobiclip's `VX2_Pred` and both `lyt_common` and `ut_CharWriter` units. If a function matches in every instruction except a `lis`/`addi` pair that the original shows with a symbol and the compiled one with a number, it's this again, so add the two instructions there.

## Known Issues
### `nw4r/ef` is at 21 of 30 units linked
`ef_drawfreestrategy` has one function left. The original has every `switch` as a compare tree, which this compiler only writes with optimization off, and `ef_drawdirectionalstrategy` has one function of the same kind. What we tried is under "Switches" in [Decompiling](decompiling.md). `ef_particlemanager`'s `Calc` is the older library's body, 474 instructions for 1,364. `ef_util` has 7 functions that are paired-single assembly in the original. There's no source at all for `ef_animcurve`, `ef_postfield`, and the billboard, directional, stripe and smooth-stripe strategies.
### `kpad` is partly done
`KPAD.c` is linked. `KMPLS.c` (12 of 17 functions, 4 not written) and `KZMplsTestSub.c` (4 of 6) are open, and what's left is float register allocation and 4 large functions.
### `FExp` and `FLog` in `nw4r/math/math_arithmetic` use other registers
They have the right instructions in other registers.
### `g3d_obj` has its inline virtual functions in the wrong order
Its 3 inline virtual functions come out as `GetTypeName`, `GetTypeObj`, `IsDerivedFrom`, and the original has `IsDerivedFrom` first. Inline virtuals are emitted in reverse order of declaration, so the original declared it last, yet it sits in the first vtable slot. Declared last it gives the right order and the wrong vtable. We haven't solved this one.
### `OSNet.c` is 6 of 8
It takes `-inline noauto` and gets 6 of 8 with it. `NWC24SuspendScheduler` and `NWC24iSetRtcCounter_` are 2 instructions long. The original has no `&fd == NULL` check from the inlined open helper and keeps `fd` in a register. We ruled out the compiler version, `-ipa file`, the inline flags, the helper's place and a `const` pointer parameter as the cause.
### A few functions only differ in registers
`g3d_resanmchr`, the `lyt` `Material` constructor, and `LMSi_GetListItemInfoStart` in `libms/projfile.c` (24 forms tried).
### MetroTRK is 23 of 25
The 2 left, `targsupp.s` and `__exception.s`, are assembly sources in the original.
### `key`'s `SC/scapi.h` doesn't fit this SDK
It has other member names and return types than this SDK. `key/revolution/WPAD/context_rvl.h` renames around it and must be the first include of the `wpad` sources. Correcting the header would be cleaner.
### `ef::FAbs` is a stand-in
It stands in for `std::fabs(float)`, which `libs/MSL_C/kdc/cmath` declares without the inline body this library needs.
### `OSThread.c` defines `DefaultSwitchThreadCallback` without `static`
It's the survivor of 226 folded empty functions, and the split objects call it by name.
### The header trees want merging into one per library
There's about 1,600 header files for what should be 400, see "Layout" above. Nobody has merged them yet.
