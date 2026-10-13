# Symbols and Splits
The `symbols.txt` and `splits.txt` of each version in `config/` were generated from `files/iuk.MAP`, which is the CodeWarrior link map that shipped on that version's retail disc. The map describes exactly the DOL next to it, so pretty much every symbol name, size and alignment in this project is original instead of guessed, and no version had to be ported from another one.

This page explains how a map gets turned into those two files, how far you can trust the result, and how to do it for another version. The figures are the ones of the US version (`SUKE01`), the other builds are within a handful of units of it.

## Why the Map Needs Preparing
decomp-toolkit can read CodeWarrior maps directly (the `map` key in `config.yml`), just not this one. There are two reasons for that.

The first one is that the game was linked with [code merging](code_merging.md). Instead of a symbol closure, the first 76,500 lines of the map are `--> duplicated code` messages, and the parser rejects those.

The second one is that the 4,393 game objects (`src.a`) are listed by file name only, and file names repeat across directories. There are 218 `ModelDesc.o`, 175 `Custom.o`, 136 `StateMain.o` and so on, and only 1,978 names are unique. Nothing in the map tells you which `.text`, `.data` or `.sdata2` piece belongs with which.

[`tools/prepare_map.py`](../tools/prepare_map.py) solves both and writes a cleaned map where every translation unit has a unique, path-like name.

## How Translation Units Were Reconstructed
Each object contributes at most one piece to each section, and objects show up in the same order in every section. Starting from the `.text` pieces, the tool assigns the pieces of every other section to translation units so that the object name matches, the link order is preserved, and as many references as possible stay inside a unit. The references are read from the DOL, and there are three kinds of them:

- Code that accesses a symbol only its own unit can see (`@1234` literals, statics, anonymous namespace members).
- `.ctors` entries, which point at the unit's `__sinit_` function.
- Jump tables and vtables, which point back into the unit's code.

This is how it went for the 7,732 non-code pieces of game objects:

| How the Piece Was Assigned | Pieces |
| --- | ---: |
| Only object of that name | 3,283 |
| Referenced through a unit-private symbol | 3,128 |
| Referenced through other symbols | 1,306 |
| No object of that name in range, so a unit of its own (no code) | 9 |
| Object name and link order alone | 6 |

As a cross-check, decomp-toolkit logs every unit-private symbol that ends up referenced from another unit. Among anonymous literals there are none. The 132 it does find are all shared by design (strings and statics of inline functions, thunks).

There are 7 pieces that are worth a second look if something about their units seems off. 6 of them were assigned on name and order alone, which are the `.data` of `scn/arena/bg/desc/BgDesc.cpp`, `scn/step/boss/mahoroabattle1/MagicBallCtrl.cpp`, `scn/step/hero/ScriptData.cpp` and `scn/step/sfx/CinemaScope.cpp`, and the `.rodata` of `scn/step/carryitem/ModelDescUtil.cpp` and `scn/step/item/ModelDescUtil.cpp`. The last one is the `.data` of `g3d/AddOnMint.cpp`. `gobj/AddOnMint.cpp` references it more often, but owning it would break the link order.

## How Units Are Named
Unit names are source paths relative to `src/`, as usual for decomp-toolkit projects.

### Libraries
Libraries are named after the library they were linked from.

| Library in the Map | Units |
| --- | --- |
| `Runtime.PPCEABI.H.a` | `Runtime/` |
| `MSL_C.PPCEABI.bare.H.a`, `MSL_C++.PPCEABI.bare.H.a` | `MSL_C/`, `MSL_C++/`, keeping the path recorded in the map |
| `TRK_Hollywood_Revolution.a` | `MetroTRK/` |
| `os.a`, `gx.a`, `bte.a`, ... | `RVL_SDK/<library>/` |
| `libnw4r_<module>.a` | `nw4r/<module>/` |
| `homebuttonLib.a` | `homebuttonLib/`, with its private NintendoWare copy under `nw4hbm/` |
| `nrel.a`, `libMobiclip.a`, `libms.a` | `nrel/`, `Mobiclip/`, `libms/` |

### Game Code
Game code has no paths in the map, so the directories are inferred. HAL's namespaces mirror its directory tree, the game is linked one directory at a time, and the files within a directory are linked in name order. Each unit votes with the namespaces of the symbols it defines (`scn::step::hero::Hero` puts `Hero.o` in `scn/step/hero`), and a pass over the whole link order picks the labeling that agrees best with the votes while keeping every directory contiguous and sorted.

This gives 585 directories, each showing up exactly once in link order, with no two units sharing a name. Treat the result as a well-supported reconstruction and not as fact, as there are a few things that can be wrong with it:

- Directory names are namespace names. Where the two differ in the original tree, the name here is wrong.
- 72 units define nothing that reveals a namespace (interfaces and other units whose code was entirely inlined or stripped) and were placed by their neighbors alone. The report lists them.
- `Main.cpp`, `TPL.cpp` and `metafortress.c` are linked first and out of name order, so they're assumed to sit at the root.
- File extensions are a guess. It's `.cpp` unless a unit only defines C symbols.

307 units are known to have been compiled from a file called `<Name>_prt.cpp` instead of `<Name>.cpp`, see [MetaFortress](metafortress.md) for that.

## What Is Not in the Splits
56 objects (51 from the game, 5 from libraries) show up in the map with an empty `.text` and nothing else. Everything they defined was inlined, stripped or merged away, so they left no bytes in the DOL and have no split. They still existed in the original link order, and the report shows where.

## Differences Between Versions
The same procedure gives every version the same unit names, so one object list in `configure.py` serves all of them. Only a few units don't exist everywhere:

| Unit | `SUKE01` | `SUKK01` |
| --- | :---: | :---: |
| `app/DvdWatch_GER.cpp`, `app/DvdWatch_ITA.cpp`, `app/DvdWatch_KOR.cpp` | | yes |
| `MSL_C/MSL_Common/Src/arith.c` | | yes |
| `scn/subgame/gunshoot/info/PlayerScore.cpp` | yes | |

Other than that the two builds are really close. Of about 45,650 functions, 45,587 have the same name and size in both.

## Generating the Config of a Version
You don't need any of this for a normal build. If you want to add a version, or redo an existing one from scratch, extract its disc so that `orig/<VERSION>/sys/main.dol` and `orig/<VERSION>/files/iuk.MAP` exist, and run:

```sh
python tools/setup_version.py SUKK01
```

This writes `config/<VERSION>` in full. After that, a new version just needs to be added to `VERSIONS` in `configure.py`, along with any units that are new to it. `python configure.py --version <VERSION> && ninja` should end with `build/<VERSION>/main.dol: OK`.

Running it for an existing version reproduces the committed files exactly, which is a quick way to check that a change to the tools did what you wanted it to.

The script takes these steps:

1. [`tools/prepare_map.py`](../tools/prepare_map.py) cleans the map as described above. Its report, `build/<VERSION>/units.txt`, lists every unit, the object it came from, and the decisions that were made on thin evidence.
2. [`tools/metafortress.py`](../tools/metafortress.py) locates the [MetaFortress](metafortress.md) inline data for the `block_relocations` list in `config.yml`.
3. decomp-toolkit imports the cleaned map (the `map` key, which is only used during this step) and writes `symbols.txt` and `splits.txt`.
4. The corrections the import can't make on its own get applied:
   - `splits.txt`: the `.ctors` and `.dtors` entries of `Runtime/__init_cpp_exceptions.cpp` are marked `rename:.ctors$10`, `rename:.dtors$10` and `rename:.dtors$15` (see [Getting Started](getting_started.md#gc-27-and-wii-linkers)).
   - `splits.txt`: section alignments are set to 32, or to the largest alignment a symbol in the section asks for (128 in `.bss`). decomp-toolkit only guesses the smallest value that fits.
   - `symbols.txt`: the MetroTRK assembly stubs `TRKAccessFile`, `TRKOpenFile`, `TRKCloseFile` and `TRKPositionFile` become functions instead of labels.
   - `symbols.txt`: the entry points of the register save and restore routines (`_savegpr_14` to `_restfpr_31`) that the game doesn't use, and that the map leaves out because of that, are added.
   - `symbols.txt`: numeric tables that were mistaken for pointers, and the MetaFortress constants, are marked `noreloc`. A data word is taken for a mistake when it points into the middle of another unit's symbol. The only real pointers of that kind are jump tables left behind by duplicate template instantiations.

`config.yml` sets `quick_analysis`, which stops decomp-toolkit from searching for function boundaries itself. The map already provides every function, and the search can go wrong on MetaFortress data. In the Korean build, one such word decodes as a branch into another function.
