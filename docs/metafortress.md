# MetaFortress
Kirby's Return to Dream Land is protected with MetaFortress, which is an anti-tamper product. The binary names it in symbols like `MFortressDefaultResponseVariant_1`. It works at the source level, so before compilation, selected source files get rewritten so that the program checks itself while it runs. Nothing about it is documented publicly. Everything below was worked out from the two supported builds with [`tools/metafortress.py`](../tools/metafortress.py), which runs each protected function in a small interpreter and reports what it does.

The figures are the ones of the US version. The Korean build has the same structure and differs by a handful.

## What Is in the Game
1,316 functions in 425 translation units, all in game code, carry data in the middle of their instructions. That's 5,313 runs of 4 to 152 bytes, 63,780 bytes in total. A run is reached like this:

```
    bl      skip        ; lr = address of the data
    .4byte  ...         ; never executed
skip:
    mflr    r21
    lwz     r28, 0x14(r21)
```

Most of the words in a run are filler. The rest are used for 4 things.

### Checksums
There are 1,310 checksums in 1,285 functions. Each one reads a range of memory in 16-bit steps, hashes it, and compares the result with a word of inline data.

The range is given by inline words, either as two plain addresses or as offsets from the address of the data itself. The hash is one of several simple functions, each with its own constants and finishing steps at every site. There's multiply by 61 and add, there's add, shift and xor in the manner of Jenkins's one-at-a-time, there's rotate and xor, and there's xor and multiply in the manner of FNV.

What happens on a mismatch depends on the function:

- 1,136 functions jump to `MFortressDefaultResponseVariant_1`, whose only instruction is a branch to itself, so the game hangs. The jump target is computed from more inline words, and the stack's back chain is overwritten on the way, so there's nothing to return to or to unwind.
- 26 functions hang in place instead with `while (hash - expected != 0) {}`, no jump and no response function. Several of these loops sit in the `default:` of a `switch` that the game never reaches, so they can only fire if something else has gone wrong as well.
- The other 123 functions neither jump nor hang. They use the result of the comparison where the original code had a constant `true` or `false`, as an argument, a stored flag, a return value or a branch condition. A failed checksum there makes the game misbehave instead of stopping. [What a Failed Check Does](metafortress_effects.md) lists them one by one.

53 checksums are inverted. The stored word is the complement of the right value, and the response runs when the two are *equal*. Damage to the checked range can never set these off. They catch whoever rewrites every stored word to match, or forces every comparison to succeed.

Together the checksums cover everything that doesn't change at run time:

| Section | Checked |
|---|---|
| `.text` | all of 0x702680 bytes but one stored word and the padding at the end |
| `.rodata` | all of 0x27E60 bytes but the padding at the end |
| `extab`, `extabindex`, `.ctors` | all but 4 to 12 bytes each |
| `.dtors` | 12 of 32 bytes |
| `.init`, `.data`, the small data sections | nothing |

The stored words are inside checked ranges themselves, so the checksums guard each other. The dependencies form no circle, and the longest chain is 83 deep. The one unchecked word of `.text`, at `0x80175C34`, is the stored word at the top of it.

### Device Probes
8 functions call `IOS_Open` on a device name that's stored encrypted (XXTEA) and decrypted on the stack. The names are `/dev/flash` (twice), `/dev/mload`, `/dev/sdio/sdhc`, `/dev/sdio/slot1`, `/dev/usb/oh1`, `/dev/usb123` and `/dev/usb2`. `/dev/mload`, `/dev/usb2`, `/dev/usb123` and `/dev/sdio/sdhc` are known as modules of custom IOS builds, and nobody has checked what a stock console answers for the other 3. If the open succeeds, the function jumps to an address that isn't code, a different one at each site. The probes sit in the constructors of 6 `seq::Sequence...Root` classes and `scn::movie::SceneMovie`, and in the destructor of `scn::arena::SceneArena`.

### Console State
5 constructors of `scn::subgame` scenes test something about the console and, if the test fails, write 1 into a hidden object (next section) instead of responding on the spot. 4 of the tests read low memory:

- `SceneSetsuna` compares the word at `0x800030D8` with the time base.
- `SceneGunShoot` sums `0x80000020` to `0x8000004C` twice in a way that cancels everything except the console type at `0x8000002C`, and fails if that's 0x208. Dolphin puts 0x23 there, as retail consoles are said to.
- `SceneSubgameGuide` does the same over `0x80003104` to `0x800031D0`, but its arithmetic has no solution. It can't fail.
- `SceneSubgameTitle` reads the words at `0x80000060` and `0x80000064` and fails if either is zero. Its constructor is decompiled, test and all.

We haven't worked out what `SceneSubgameSelect` tests.

### Hidden Objects
21 objects named `dcpl_0x…_dcpl0_mfort6317_`, of 16 or 24 bytes, are spread over the `.data` of 21 translation units. 26 functions use them, and reach them through addresses that are decoded from inline data by a hundred or so instructions of bit shuffling.

A typical one reads 2 to 4 objects that belong to other files, derives from each the value its own object ought to have, and writes that. In an untampered run all 54 of those writes store the value that's already there. Once any object holds something else, every function that reads it passes the damage on. 3 functions (`SceneStaffCredit::updateEffect`, `ChallengeDoor::isUnlockEnd`, `wmap::Ship::procFixPos`) compare an object with inline data and hang on a mismatch.

The effect is that a failed test in one place stops the game somewhere else, later.

### The Rest
- `metafortress.o`, linked third after `Main.o` and `TPL.o`, provides `MFortressDefaultResponseVariant_1` and a 12-byte object, `MFortressDefaultResponseVariant_1_0x0897f0fd_ResponseFnPtr_mfort6317_`, that nothing reads. The link map also lists `MFortressDiagnosticResponse` (0xD4 bytes) as unused, and its code isn't in the game.
- 3 runs of inline data, 140 to 152 bytes long, are jumped over and never read. We don't know what they're for.
- Symbols that embed their source file name show that 307 translation units were compiled from `<Name>_prt.cpp` instead of `<Name>.cpp`. These are the files MetaFortress rewrote, as every unit with inline data whose source name is known is one of them. The map only reveals the source name of 887 units, so the real number is higher.
- The link map lists unused static locals named `rt_n_`, `rt_i_` and `rt_j_dcpl0_mfort6317_` in the functions that use hidden objects.

## How a Protected Function Is Written
MetaFortress rewrites source files before they're compiled, and what it adds is mostly C. [Decompiling](decompiling.md) has the working details, this is just the outline.

- A few lines of inline assembly fetch the data. That's a `bl` over the `opword` lines, `mflr`, one or two loads, and a store into a `volatile` local. These blocks name their registers outright, a different set at every site, which is why a protected function saves so many of them.
- Everything else is C added to the function, meaning reading the bounds back from the `volatile` locals, the checksum loop, the final mixing steps and the comparison. The statements are spread among the function's own, so a call the game makes can sit in the middle of a checksum.
- The compiler makes it look like assembly. The `bl` in an `asm` block is, to the compiler, a call to something unknown that may take any scratch register as an argument. In code that runs before a block like that it keeps its values in r14 to r31 and puts its compares on cr4 because of that. A checksum loop just ahead of an `asm` block uses no scratch register at all.
- The response is one of 3 things. A jump to the response function, whose address is computed in C from more inline words and moved to the link register by a last `asm` block. A loop that never ends. Or nothing at all, where the comparison stands where the game had a constant.
- The constant is hidden behind a real condition. `if (x)` becomes `if (true && x)` or `if (false || x)`, and `f(true)` becomes `f(expected == hash)`.

`storage::ArenaGameData::isCleared` in [`src/storage/ArenaGameData.cpp`](../src/storage/ArenaGameData.cpp) was the first protected function to be matched and shows a jump to the response. `app::BackupFileAccessor::updateUnlockState` and `pause::PageManager::changePage` show a check woven into game logic.

This only compiles to the same code because the game was built with the peephole pass and instruction scheduling off, see `cflags_game` in [`configure.py`](../configure.py).

The two supported versions have identical instructions in every protected function. Only the inline words that mean something differ, which are the bounds of a range, a stored checksum and an offset to the response. They were evidently filled in after linking. The build takes them from each disc instead of from the sources. `tools/metafortress.py <ID> --words` writes every inline word of a version to a header, and a source names the ones its check reads by their offset in the function (`MF_WORD(0x2C)`, see [`include/metafortress.h`](../include/metafortress.h)).

## What It Means for This Project
### Analysis
decomp-toolkit assumes everything in `.text` is an instruction. Inline words that happen to decode as a small data access or a branch would become relocations to arbitrary symbols, so all runs are listed under `block_relocations` in `config.yml`:

```sh
python tools/metafortress.py SUKE01 --yaml
```

For the same reason `config.yml` sets `quick_analysis` (a run in the Korean build decodes as a branch into another function, which derails the search for function boundaries), and the `dcpl_` objects are marked `noreloc` in `symbols.txt`. Nothing refers to the response function or its pointer object by name, so `config.yml` lists both under `force_active`. Without that the linker drops them.

### Matching
Protected functions can be matched like any other, and you don't have to write their checks by hand anymore. `tools/metafortress_c.py <ID> SYMBOL` prints a function's check as C in the one form that the compiler turns back into the original's instructions and registers, with the game's own instructions as comments around it ([Decompiling](decompiling.md), "Protected Functions"). `tools/metafortress.py <ID> --source SYMBOL` prints the whole function as inline assembly.

Symbols in unnamed namespaces show that the compiled file was the rewritten copy, as they carry `X_prt_cpp` where a build of `X.cpp` produces `X_cpp`. A unit with symbols like that will need them renamed in `symbols.txt` before it can be linked from source.

### Modified Builds
Any change to code or read-only data fails at least one checksum. To see which ones, and to repair them:

```sh
python tools/metafortress.py SUKE01 --verify modified.dol
python tools/metafortress.py SUKE01 --seal modified.dol sealed.dol
```

`--seal` recomputes the stored words in dependency order, keeping the inverted ones inverted. It takes a few minutes, because a change near the bottom of the chain reaches the top one checksum at a time. Changing one unused inline word at `0x8017AE00` fails 5 checksums and takes 65 rewritten words to repair, and the result passes `--verify`. In Dolphin the unrepaired DOL stops during startup in the branch at `0x80175978`, and the repaired one runs.

Changes that leave the layout alone are possible today. Replaced assets need nothing, and patches to code or read-only data need `--seal`.

## The Tool
```sh
python tools/metafortress.py SUKE01                # summary
python tools/metafortress.py SUKE01 --list         # one line per finding
python tools/metafortress.py SUKE01 --json out.json
python tools/metafortress.py SUKE01 --source SYMBOL  # one function as inline assembly
python tools/metafortress_c.py SUKE01 SYMBOL         # one function with its check as C, the starting point for its source
python tools/metafortress_c.py SUKE01 --survey       # what that printer can do for each protected function
python tools/metafortress.py SUKE01 --words out.h     # every inline word as a macro; the build runs this
```

It finds protected functions by the one thing they share, which is a call that lands inside its own function, and it makes no assumptions about the shape of a check. Each function is run along every path with all values tagged by where they came from (inline data, memory read through an address taken from inline data, or outside the function). A checksum is then whatever compares a value of the second kind, gathered in a loop, with one of the first.

## Known Issues
### We don't know which saved register the compiler gives to each added variable
For most functions the order of the declarations settles it. For some, the C form gives the right instructions with two registers swapped in every order, and those keep their loop inside the `asm` block for now, each with a TODO.
### The progress report shows some protected functions just short of 100%
Inline data that happens to decode as an instruction on r13 or r2 makes decomp-toolkit lose track of the small data base for the rest of the function. 238 of the 1,305 small-data references in protected functions (US) have no relocation in the split objects for that reason. `tools/compare.py` allows for it, the progress report doesn't. The fix is a list of `add_relocations` in `config.yml`, which first needs unique names for their targets. Half of them are compiler-numbered locals like `@49126`, and those numbers repeat between units.
### A build where code or data has moved can't be sealed
`--verify` and `--seal` both need a DOL with the layout of the original, so bytes may differ but addresses may not. A build where code or data has moved needs more, and none of it exists yet:

- The hidden objects are found through absolute addresses encoded in inline data. If `.data` moves, those addresses have to be re-encoded, or the code that decodes them patched.
- Ranges given as plain addresses keep pointing at the old place. Sealing would still make them pass as long as they land in memory that never changes, which has to be checked.
- The tool finds functions through `symbols.txt` and would need the symbols of the new build.
