# Decompiling
This page is about how you turn one of the split objects back into source, and how you can tell that it's right.

## The Loop
1. Pick a function and find its unit. Units are listed in `config/<ID>/splits.txt`, and the disassembly of each one is in `build/<ID>/asm/<unit>.s` after a build. `python tools/unwritten.py [path prefix]` lists the game units that have no source yet, smallest first. Most of them are the small classes that [Object Classes](object_classes.md) describes.
2. Write it in `src/<unit>.cpp`, with declarations in `include/<unit>.h`. A source file can hold just some of its unit's functions.
3. Compare it with the original:

   ```sh
   python tools/compare.py all src/scn/step/hero/Heap.cpp
   python tools/compare.py SUKE01 src/scn/step/hero/Heap.cpp -f setUse
   ```

   The tool takes each unit's compiler and flags from `configure.py` (through `build/unit_flags.json`), so it works for library units as well as game units. The first form compiles the file for every version and tells you, per function and per data section, whether it matches the original object. A section of a unit that's only partly written shows as `matches the first 0xN of 0xM bytes`. When there's nothing left to write, the tool says `the unit is complete`. `-f` adds a side-by-side listing of the functions whose symbol contains the given text. If you give it a directory (`python tools/compare.py all src`), it checks every source below it and only prints what doesn't match. The tool compiles to a temporary file and leaves the build alone.
4. When the tool calls the unit complete in every version, link it:

   ```sh
   python tools/linktest.py SUKE01 -u scn/step/hero/Heap --map   # one scratch link with the unit from source
   python tools/link_complete.py                                # test every complete unit, mark the good ones Matching
   python tools/check_all.py                                    # build and check the DOL of every version
   ```

   `linktest.py` links the game in `build/linktest/` with the named units compiled from source and says `identical`, or names the symbols whose bytes differ. With `--map` it also names the first symbols that sit at another address than in the original map, which is usually the cause. `link_complete.py` does that for every unit `compare.py` calls complete, changes the ones that link identically from `NonMatching` to `Matching` in `configure.py`, and remembers the others in `config/not_linkable.txt`. `check_all.py` is the proof, as the build fails if a DOL is no longer identical. A scratch link only covers the version the tree is configured for, and the versions really do differ, a function can be folded into one look-alike in the US build and into another in the Korean one.

   The link has the last word. `compare.py` judges a unit by its split object, and where the splitter read a constant as an address or missed a relocation, a unit that links identically is still reported as differing. `python tools/link_complete.py --force src/<unit>.cpp` links a unit like that anyway and lists it in `config/force_linked.txt`.

`python tools/status.py [directory]` lists every source with its state (linked, complete, every function matching, partial, broken) and its function counts. A line that starts with `LINKED BUT` is a linked unit that no longer matches, most often because of a header.

A unit whose source exists is compiled by the build even while it's `NonMatching`, so a file that doesn't compile breaks the build for everyone. Keep your files compiling.

## Conventions
- Namespaces, class names and function signatures come from the mangled symbol names. `compare.py` reports a function as `same code, other symbols referenced` when the instructions agree but a call or a variable goes by a different name than in the original.
- Members whose purpose is unknown are named after their offset, like `u8 _4[0x60];` and `u32 _64;`.
- Game code is compiled with `-O4,s -ipa file -opt nopeephole,noschedule -func_align 4` (`cflags_game` in `configure.py`).
- Comments are for what a reader couldn't work out by themselves, which is a TODO, a surprise or a bug in the game. They aren't for what the code plainly does.

## Protected Functions
About 1,300 functions begin with a MetaFortress check ([MetaFortress](metafortress.md)). You can print one with:

```sh
python tools/metafortress_c.py SUKE01 onLanding__Q43scn4step5enemy9BrainBaseFv     # the check as C, the game's instructions as comments
python tools/metafortress.py SUKE01 --source setUseHeapGear__Q43scn4step4hero4HeapFv   # the whole function as inline assembly
python tools/metafortress_c.py SUKE01 --survey                                     # one line per protected function
```

The first one is the place to start. It writes the check in the canonical form described below, which is the locals, the data fetches as `asm` blocks, the start value, the bounds, the loop, the finish, the compare and the response, each at its place among the game's own instructions. It leaves those as comment lines for you to write as statements. It prints 1,123 of the 1,316 functions whole, and of 127 linked functions it could be tested on, 115 match exactly as printed and 9 more with another order of the 4 declarations. This is what it can't tell:

- 121 functions hand the check's result to the game (an argument, a store, a return value, the game's own condition). The expression stands in a comment, `// r3 = expected != hash; for the game`, and goes into the game's statement.
- In the kind `i = -1; while (i != limit - 1) { i += 2; ... }` (191 functions) the order of the 4 declarations varies, and `compare.py -p` finds it in 24 tries.
- Functions with 2 checksums or with none (device probes, hidden objects) come out in part, with the rest as instructions under `// NOT RECOGNISED`.
- It doesn't see a temporary of the loop that shares a register with a local used after the loop (`ChallengeDoor::mfModelMainStart`).

The second form prints the whole function as inline assembly, with the data as `opword` lines and a summary of what the check does. Very little of it was assembly in the original source.

MetaFortress works on the source. It adds C statements to a function, and only uses an `asm` block for what C can't do, which is fetching the data that sits between the instructions:

```
    bl      after1
    opword  ...
after1:
    mflr    r21
    lwz     r27, 0x0(r21)
    stw     r27, end
```

Everything else is C, which is copying the bounds out of `volatile` locals, the checksum loop and the comparison. It doesn't look like C in the listing though, because of the `bl` in the block. To the compiler that's a call to something unknown, which may take any scratch register as an argument. Due to this, in code that runs before a block like that it keeps its own values in r14 to r31 and puts its compares on cr4. Code after the last block uses r0, r3 to r12 and cr0 as usual. A checksum loop in saved registers with `cmplw cr4` is still just a `for` loop.

These are finished examples:

- In `pause::PageAbility::pageIsBusy` the loop comes after the last `asm` block.
- In `app::BackupFileAccessor::updateUnlockState` the loop sits between 2 blocks, among the game's own statements. A failed check changes what the function unlocks.
- In `pause::PageManager::changePage` the check is spread through a longer function.
- `seq::SequenceWMapRoot::onSceneEnd` has a check that hangs in the `default:` of a `switch`.
- `pause::FramePanel::FramePanel` has a check inside a constructor.
- `storage::ArenaGameData::isCleared` has a check that jumps to the response on a mismatch.

### The Canonical Form
Write a protected function this way first. As far as we can tell it's what MetaFortress generated, as functions that had resisted hundreds of other forms matched in it at once (`VacuumSoundCtrl::unregisterObj`, `ChoseData::init` and `initPlayer`, `MintSuperBackPicture::Register`).

- No copies of `this` or of the parameters. The game's own statements use `this` and the parameters directly.
- The check has exactly 4 locals, which are `u32 i; u32 last; u32 limit; u32 hash;`, declared in that order behind the `volatile` ones.
- The hash's start value is written whole (`hash = 0x811C9E29;`), at the place where the original loads it.
- The bounds are `last = end; limit = last - start + 1;`, or `limit = end - start + 1; last = end;` where the original loads `end` twice. A bound that's one less stays in the condition, so `limit = last - start;` and `while (i != limit - 1)`.
- The loop has no variable for its base and no named temporaries. Its body is one or two statements on `hash`, as the instructions say, like `hash ^= *(u16*)(last - 1 - i); hash *= 0x010001AB;`, or `hash *= 193; hash += *(u16*)(last - 1 - i);`, or `hash = ((hash << 4) ^ (hash >> 28)) ^ *(u16*)(last - 1 - i);`.
- The finish is in natural expressions too, `hash ^= hash >> 10; hash ^= hash << 20;`, followed by `if (hash - expected == 0)`, `if (hash == expected)` or `hash ^= expected; if (hash != 0)`.

```cpp
void ChoseData::PlayerData::initPlayer(u32 player) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 i;
    u32 last;
    u32 limit;
    u32 hash;

    hash = 0x811C9E29;
    asm { ... }
    i = 1;
    last = end;
    limit = last - start + 1;
    asm { ... }
    for (;;) {
        if (i == limit) {
            break;
        }
        hash ^= *(u16*)(last - 1 - i);
        hash *= 0x010001AB;
        i += 2;
    }
    hash ^= hash >> 10;
    hash ^= hash << 20;
    if (hash - expected == 0) {
        const Kind kinds[] = { ... };
        initKind(kinds[player]);
    } else {
        ...
    }
}
```

These are the kinds, counted over all 1,316 functions by the printer (`w` is the word read in the loop):

- Bounds: index backward is `last = end; limit = last - start + 1;` (140) or `limit = end - start + 1; last = end;` (179), with `w` as `*(u16*)(last - 1 - i)`. Index forward is `base = start; limit = end - base + 1;` (164) or `limit = end - start + 1; base = start;` (157), with `*(u16*)(base + i - 1)`. The `+ 1` is left out where the loop tests `limit - 1` (191). Pointer is `word = start; last = end;` in either order, then `word -= 2;` where the loop steps first (443), with `*(u16*)word` and the locals `word, last, hash`.
- Loop: `for (;;) { if (i == limit) { break; } ...; i += 2; }`, the same with `i = -1` and the step first, `while (i != limit) { ...; i += 2; }`, and `i = -1; while (i != limit - 1) { i += 2; ... }`, plus the same 4 on `word` and `last`. That's about 200 functions each.
- Body: `hash ^= w; hash *= K;` (472), `hash *= K; hash += w;` (277), `hash += w; hash += hash << 10; hash ^= hash >> 6;` (265), `hash = ((hash << 4) ^ (hash >> 28)) ^ w;` (136) and with a pointer `hash = *(u16*)word ^ ((hash << 4) ^ (hash >> 28));` (90). After that come up to 16 finishing statements such as `hash ^= hash >> 10;`.
- Compare: `hash ^= expected;`, `hash -= expected;` or `hash = expected ^ hash;` followed by `if (hash == 0)` or `!= 0` (681), `if (hash == expected)` or `!=` (268), `if (hash - expected == 0)` or `!= 0` (96), `if ((hash ^ expected) == 0)` or `!= 0` (83), and the hang `while (hash - expected != 0) {}` (32).
- Obfuscated compare: `hash = (hash & ~expected) | (expected & ~hash);`, in about 120 functions followed by `hash = __cntlzw(hash);` and one of `hash = (hash >> 5) + ((hash >> 5) * 57);`, `hash = (hash >> 5) - ((hash >> 5) >> 2);`, `hash = (hash >> 5) | ((hash >> 5) << 8);`. A value used twice is written out at each use and the compiler shares it, so you don't need an extra local or one-operation statements. `__cntlzw` is signed here, so write `(u32)` ahead of `>> 5` or an `srawi` comes out.
- The bool handed to the game is `expected == hash` (`subf; cntlzw; srwi 5`) or `expected != hash` (`subic; subfe`).

These are the variations we've met so far, all of them still without copies and with the same 4 names where they apply:

- A loop that walks forward has a pointer in place of `last`, like `word = start; word -= 2; for (;;) { word += 2; if (word == last) break; hash = *(u16*)word ^ ...; }` (`SelectPanel::big`, `Option::complete`).
- An obfuscated compare is natural too, with or without a `cntlzw` tail, like `hash = (expected & ~hash) | (hash & ~expected); hash -= hash >> 2;`. 7 linked functions that were written with one operation per statement for a tail like that match in the natural form as well.
- Where the check sits in a file-local helper that the function expands, the helper's volatile locals take ascending stack offsets in declaration order, which is the reverse of a function's own (`TheArena`'s constructor).
- A local of the check that the original keeps on the stack and reloads in the loop needs nothing, as the natural form spills it when the registers run out.
- Some responses open with `addi rA, rB, N; mtlr rA; ...; blrl` in place of `mtlr; bl`. That goes into the asm block as it stands.

The order of the 4 declarations really is part of the form. `HeroStatus::toIdleState` matches with `i, last, limit, hash` and with none of the other 23 orders.

If it doesn't match, change one thing at a time and count the differing lines. Start with the form of one statement (the finish through `limit`, `limit = hash >> 10; hash ^= limit;`, where the original keeps its temporaries in `limit`'s register), then the order of the 4 declarations (which `-p` tries). The rules that were found before we knew this form are ways around not writing it (`self = this;`, one operation per statement, a `base` variable, a value bound to a reference). About 150 linked functions are written with them. They produce the same code and can stay, just don't start a new function from them. You'll find them under "Older Forms and Fallbacks" at the end of "The Loop and Its Registers".

This is what has held so far, by topic.

### The Check Itself
- A stack slot `N(r1)` is a `volatile u32` local, written by the `asm` block and read by C. The first one declared gets the highest offset.
- Words printed as `MF_WORD(offset)` are the ones the check reads. They differ per version and come from the disc through `metafortress_words.h`. The other words are filler and are written out. Always compare with `all`, as a word that should have been `MF_WORD` only shows in the other version.
- Wrap the function in `#define MF_FUNCTION <name>` and `#undef MF_FUNCTION`, with the name as the tool prints it.
- Never write `cr4` in an `asm` block. If the block names it, the compiler stops using it and puts its own compares on cr3.
- Consecutive data fetches with no C between them are one `asm` block.
- `a == b` compiles to `b - a`. If the operands of the `subf` come out swapped, swap the comparison. `end - start` loads `start` first.
- MetaFortress hides a constant behind a condition the function already has. `if (true && x)` and `if (false || x)` are both in the game, with the check in place of `true` or `false`.
- A check that hangs instead of feeding the game does it in place, with `while (hash - expected != 0) {}`.
- Where the tool calls a checksum `inverse`, the stored word is the complement of the sum. `hash - expected != 0` is then the untampered state, and the roles of the two branches swap.
- The check can sit in a file-local helper that the protected function inlines (`scn::subgame::title::window::OnGameEndGuide`). The helper goes inside the caller's `MF_FUNCTION` region, because the offsets count from the caller.
- A conditional branch over an unconditional one (`cmpwi; bne next; b elsewhere; next:`) is `if (!cond) { asm { b done } }` with `done:;` at the end of the function.
- An `asm` block can take a C variable as a register operand (`mr addr, r28`) if the variable is declared `register`. That's how a fetched word reaches C without a stack slot.
- The decoding of a hidden object's address is C with one operation per statement on a few scratch variables, like `t2 = addr - K; addr = t2 << 24; t2 = t2 >> 8; t2 = addr | t2;`. Nested expressions give the same instructions in other registers. `scn::subgame::SceneSubgameTitle` is the example.
- `ChallengeDoor::isUnlockEnd` is a later and more natural model for the 26 hidden-object functions:
  - The fetch names its register in the block and moves it to a `register` variable, `lwz r17, 4(r21); ...; mr w, r17`. The compiler gives `w` r17 and drops the move, and r17 stays reserved, which is why `this` lives on the stack in these functions (`stw r3, 8(r1)`). With `lwz w, ...` the frame is 4 bytes short and every register is off.
  - The decoding is natural expressions, one step per statement, on a main variable with a fresh variable at each hand-over (`v`, `b1`, `v`, `b2`, ... `b5`), declared `t, v, b1` to `b5`. A bit-field swap keeps its temporary in the destination, like `v = ((b >> i) ^ (b >> j)) & m; v = b ^ ((v << i) | (v << j));`.
  - An added constant whose high half lands in the source's register and whose low half in a new one was 2 statements, `v = v + 0x0C220000; b1 = v + 0x2201;`.
  - Declare exactly the variables that are used. One unused `u32 b6;` turned 7 differing lines into 95.
  - The stored object is a plain global at the end of the file, `u32 dcpl_...[4] = { ... };`, the same in both versions.

### The Loop and Its Registers
- The loop comes in 2 shapes, tested at the bottom (`for (; i != limit; i += 2)`) and tested at the top with a branch back (`for (;;) { if (i == limit) break; ... }`).
- Write the `- 1` or `- 2` of a loop bound in the loop condition, not in a variable, so `size = end - base; i = -1; while (i != size - 1) { i += 2; ... }`, or `word -= 2; while (word != last - 2) { word += 2; ... }`. The compiler hoists the bound into a temporary of its own, and a declared variable in its place changes which registers `this` and the hash get. `scn::step::hero::Heap::setUseHeapGear` is the model.
- When the compiler's variables land in each other's registers, the order of their declarations is wrong. The rule is easier to search for than to state. `python tools/compare.py SUKE01 <file> -p "Class::function"` tries every order and prints the ones that match. For a constructor it wants the text of the last initializer line, the one that ends in `{`.
- How a statement is split decides it too, as `hash *= 61; hash += x;` and `hash = hash * 61 + x;` rank `hash` differently against `this`. Where a shift's result shares a register with another variable, that variable was reused for it.
- A local assigned from a call result is ranked by where the call sits in the code, not by its declaration.
- Half of the hash's start constant sitting in another variable's register means that variable was used for it, like `last = 0x811D0000; hash = last - 0x6225;` (`font::Font::load`).
- Where the loop base shares a register with the compiler's temporaries, write no variable at all, `*(u16*)(last - 1 - i)`, and then try the orders of the locals.
- A `cntlzw` whose result lands in another variable's register is the intrinsic as a statement of its own, like `hash = __cntlzw(word); word = hash >> 5;`.
- `hash -= expected; if (hash != 0)` leaves the difference in `hash`'s register, while `if (hash - expected != 0)` puts it in a temporary.
- Volatile locals of the response declared inside the response's block land below the locals of the function body on the stack.
- Take the `opword` values from `metafortress.py --source`, not from reading the listing.
- Temporaries after the loop that sit in `limit`'s register are that variable reused, like `limit = hash >> 10; hash ^= limit; limit = expected;`.
- A constant that the original keeps in a saved register and stores from there (`li r22, 1; stb r22, ...`) can be a local of its own with the stored type. That's `bool flag;`, declared where it gets that register, then `flag = true; self->mIsSELocked = flag;`. Assigned through one of the check's `u32` variables the value is normalized to a bool first, and as a literal it gets a fresh register (`PauseLockRequestor`).
- The `volatile` locals take no part in the ranking of registers. With 7 or more declarations, make a scratch copy in which the `volatile` declarations stand behind the first statement, where `-p` doesn't see them, and search the rest. If every order of the register locals fails, the order isn't what differs.
- In a response, the stack offsets of the volatile locals give the order of their declarations. A `b end` after the response's `blr` means `if (bad) { response } else { ... }`, and without it the source was `if (ok) return x;` followed by the response.
- The device probes ([MetaFortress](metafortress.md)) decode their device name in plain C. `seq::SequenceTheaterRoomRoot` is the model.
- The checksum with no named temporaries at all occurs at least as often as one operation per statement, and it's the form to try first. `SelectPanel::big` had `this` in r31 for r27, the hash in r24 for r31 and a temporary in r27 for r24 in every order of the declarations, and matched when the checksum had no named temporaries at all. That was `hash = *(u16*)word ^ ((hash << 4) ^ (hash >> 28));` in the loop, then `hash ^= hash >> 10; hash ^= hash << 20; hash = expected ^ hash; hash += hash * 44;`. The sign is that the original's temporaries all sit in one register that ranks below `this`. Take the names away after the loop first, then in the loop body, and then search the orders of the 3 to 5 locals that are left. 7 more functions matched that way (`Switch::mfGetOCNodeDesc`, `MainCamera::initWorldRect`, 3 in `gimmick/block/Block`, 2 in `ChallengeKindUtil`).
- In the natural form the loop's base has no variable either, it's `*(u16*)(last - 1 - i)`. The finishing temporaries only sit in `limit`'s register where the function has parameters in saved registers (`limit = hash >> 10; hash ^= limit;`).
- `-p` only tells you whether an order matches. To see which change of form moves a function closer, count the differing lines per form with a small script, one compile each (`tools/compare.py ... -f name` prints `!=` in front of each differing line).
- A copy of a parameter, `index = player;` or `self = &obj;`, is merged with the parameter in every type of the same width, and `self = this;` is merged in some functions. The merged value then takes r31 whatever the declarations say. That was the cause wherever "`this` sits in r31 in every order", and the answer is the canonical form, which has no copies. Writing the copy as an instruction (`register u32 index;` and `asm { mr index, r4 }`) also gives the original's registers, since the copy then ranks where it's declared. That's a stand-in for the few places where the canonical form fails, with a TODO.
- `VacuumSoundCtrl::unregisterObj` took about 500 forms and orders before we found the canonical form, and the cause was 2 things at once, a `base` variable for the loop (`last = last - 1;` ahead of it, where the original has `*(u16*)(last - 1 - i)`) and the copies of `this` and of the parameter. Neither of them alone showed an improvement that pointed the way, which is why counting differing lines per form matters.

#### Older Forms and Fallbacks
These are the ways around the canonical form from before we knew it, plus what to fall back on when it fails. Don't start a new function from them. Use one only where the canonical form doesn't give the registers, and leave a TODO.

- A separate register for `end - 1` is a separate variable (`base = last - 1;`), not `last--`. One load of `end` used twice means it was copied to a local first.
- When `this` and a parameter trade saved registers, copy both to locals in parameter order (`AbilityManager* self = this; int k = kind;`). `-p` can't find that.
- When the compiler's own values land one register away in every declaration order, bind one computed value to a reference, like `const u32& size = end - start;` or `const u32& base = last - 1;`. That makes it a compiler temporary, and those are given registers ahead of named locals. It was the last step for `scn::titlemenunew::File`, `ModePanel`, `AbilityManager::initAbilityCore` and the gun game's `PlayerController::shot`. `-p` can't find it either.
- The same works on a value of the game's own that's loaded at the top of a loop body and used after a call (`pause::PageDropout` has `const u32& entry = context.mEntries[n];`). To find the local in question, write each local's expression inline in turn, and the one whose removal puts `this` and the parameters right is the one to bind.
- When no order of the locals gives the registers, write the check one operation per statement and try the orders again. That's `t = start; last = end; last = last - t; limit = last + 1;` for the bounds, `t = last - i; t = *(u16*)t; hash += t;` for the loop body, and the finishing shifts through the variable whose register the original uses there (`limit = hash << 3; hash += limit;`). The registers of the temporaries tell you which variable was reused. `ResultTargetNumber::close` and `MintSuperBackPicture::Unregister` matched that way.
- Where `this` and the parameters sit below the check's variables, copy them to declared locals first (`self = this; v = visible;`). In `ResultTargetNumber::setVisibility` the registers then followed the declaration order exactly.
- An obfuscated compare is one operation per statement, like `t = expected; t = hash & ~t; word = expected; word = word & ~hash; word = t | word;`.
- An obfuscated compare with a count of leading zeros is `hash = (hash & ~expected) | (expected & ~hash); hash = __cntlzw(hash); first = hash >> 5; hash = first >> 4; hash = first - hash;` (`LevelTitle::mfSetText`).
- When `compare.py -p` finds no order for a check (`Beam::onStateEndCleanUp`), one operation per statement with a fifth variable works: `last = start; limit = end; limit = limit - last; last = end; i = -1; last = last - 1; stop = limit - 1; while (i != stop) { i += 2; limit = hash << 4; hash = hash >> 28; hash = limit ^ hash; limit = last - i; limit = *(u16*)limit; hash ^= limit; }`, with the finishing shifts through `limit`, then `limit = expected; limit = hash - limit; if (limit != 0)`, declared `i, hash, stop, last, limit`. The last step is what puts `i` and `hash` in their registers.

Where the C form gives the right instructions but nothing gives the right registers, the loop can go inside the `asm` block with its registers written out. That matches, but it isn't what the source looked like, so mark it with a TODO.

### The Rest of the Function
- Where the function has no compare of its own ahead of the last block, and no compiler temporary has to share a register with the check, the output of `metafortress.py --source` goes in almost as it is. That's volatile locals in descending stack order, the whole check in one `asm` block that ends in `beq`/`bne cr4`, the response arithmetic as C, then `asm { lwz rN, response; mtlr rN; blr }`. `util::Mutex`, `util::Alarm::init` and `util::AnimController::setFrameToHead` matched on the first or second compile that way. It fails where the compiler makes a compare of its own (it lands on cr3) or where a temporary has to share a register with the loop.
- In a function that returns a value, `return x;` straight from the intact path, with the function ending after the response, gives `addi r3, ...; b epilogue` and puts the response arithmetic in r4 (`app::RomFontWrapper::font`).
- Versions can differ in more than the check's data. `scn::challengeresult::info::ResultLyt` is 0x194 bytes larger in the Korean build, and the Korean `scn::strap::SceneStrap` constructor calls a function where the US one reads a global. `#ifdef VERSION_SUKK01` works around `opword` lines and in initializer lists. Only comparing with `all` shows any of it.

## General Rules
These hold for any function, protected or not.

### Order and Inlining in a Unit
- Inline functions, template instances and implicit destructors are emitted where they're first needed. A constructor makes the compiler emit the destructors of its bases and members right after it, and a destructor that the class declares is emitted earlier than an implicit one.
- With the game's flags an inline function is expanded where the unit calls it once, and stays a call where the unit calls it twice or more. That goes for `std::auto_ptr` members and for implicit copy and assignment functions too. Due to this, a partly written unit inlines more than the original did. Until the other callers are written, a pragma stands in. That's `#pragma ipa function` as the first line of `app/AppImpl.cpp`, `#pragma dont_inline on` in `scn/step/hero/IndiviUtil.cpp` and `scn/step/info/HeroStatus.cpp`, and `#pragma auto_inline off` in `scn/step/hero/FormationUtil.cpp`.
- A bool that's materialized with `li rN, 1 ... li rN, 0` or `subic; subfe` and then tested is an inline function returning bool. A value loaded ahead of the object it's passed to went through an inline accessor.
- A small helper that sits before its first caller in the text is an ordinary function defined in the source file. One that sits right after its first caller is inline in the class.
- Static member functions with one caller aren't inlined with the game's flags, non-static ones are.
- Call operands are evaluated right to left, so in `a() + b()` and `a() != b()`, `b()` runs first. Assignment evaluates the right side first, also through an `operator=`. Where the original runs them left to right, the source had locals.
- A load through a const member function isn't merged with the same load through a non-const one. An extra reload at the top of a loop body means the accessor in the condition had the other constness.
- Bools that are zeroed up front and then set one by one come from nested inline functions, each `return inner() && cond;`.
- A single `b other` isn't always the linker's doing, the compiler makes real tail calls.
- A function the linker dropped as unused still leaves its strings in `.data`. `grep UNUSED orig/<ID>/files/iuk.MAP` lists functions like that with their sizes, which is enough to reconstruct a small one.
- `@LOCAL@function@name` is any function-local static, not a sign of an inline function.
- A constructor that sits behind the unit's static initializer is `inline` on its definition in the source file, written ahead of the statics that use it (`hel/common/Color.cpp`).
- An operator that sits in the middle of its class's own unit, at the place of its first use, can still be an inline function of the header. `hel/math/Vector2.cpp` matched all 21 functions as plain definitions in the unit's order, and the same functions turned out to be inline when other units' objects showed weak copies of them. Look for a copy in another unit's object before you call a small function ordinary.
- `Vector2 operator+(const Vector2& o) const { return Vector2(*this) += o; }` is written like that because a named result is built in place and loses the 2 copy constructor calls the original has.
- `Result r = {};` zero-fills the local in place, with unrolled stores for a small struct and an inline loop for a larger one, as far as we've seen. `= Result()` gives a temporary and a copy instead. A named local of a class is only built in place if the class declares a copy constructor. `= {}` also zero-fills a class with public members whose members have constructors, and calls none of them (`seq::SequenceStep`'s `Recipe`).
- Destructors are never expanded, not even inline ones with a single caller. The exception is an explicit `p->~T()` on a class with an implicit destructor, which is expanded in place, and it passes -1 to a member's destructor and 0 to a base's.
- A destructor that's missing from the unit while nothing in it destroys the class is defined in the source file with an empty body.
- A function with one caller isn't expanded when its definition follows the caller.
- A function the map lists as `UNUSED` can be the second caller that keeps an inline function a call in its unit.
- An accessor that the original calls in every function of a unit (a `bl` to a look-alike such as `ARCGetLength`) isn't inline. If the map's `Code folded in file: <Class>.o` list has it, and no other file's list does, it's an ordinary function of the class's own source and the header only declares it. With a body in the class this compiler expands `obj.manager()` on a named reference and calls it in `MintLvMapDoor::Obj().manager()`, so most of a unit like that matches by accident (`lvmapdoor/AddOnMint`).
- An argument register loaded ahead of the return slot (`lwz r4; addi r3`), with a bool materialized in a temporary, is a file-local helper that takes the object and was expanded once. 2 expansions like that in one function are 2 helpers.
- The once-or-twice count includes uses inside weak copies that the unit emits and the link drops. A unit with one visible call of an inline function has its second use in a copy like that (`Vector3::operator+=` called once beside 2 `operator+` in `MainCamera`).
- A unit that emits a weak copy with a constant of its own shows `.sdata2 not in the original object` in the comparison and links identically (`boss/Desc`, `ChallengeDoor`, `WarpStarPanel`).
- The once-or-twice rule for inline functions covers operators and default constructors. In `Piggyback`, writing the second use of `Vector3::operator+=` in another function turned the expanded one into the original's call, and a plain `Vec2` local in `SpiralScreen::update` avoids a second `Vector2()`.
- A member call through `PointerWrapper::operator->` isn't expanded, so `mChild->setParent(*this)` is a call, while `child.setParent(*this)` on a reference is expanded.
- An explicit instantiation of a class template ahead of the code (`template class util::ObjListNode<g3d::Model, util::ObjListDummyType>;`) turns its expanded members into calls. It's a stand-in where the original calls them and we don't know the reason (`MintUtility`). Instantiating just one member didn't do it.
- The implicit assignment of `lyt::PaneAccessor` and of `g3d::NodeAccessor` is `ObjRefHandle::operator=` plus a word copy.
- An inline function with `const T` value parameters reads an lvalue argument at once, and with plain `T` the load is deferred (`GXTexCoord2f32`, and `revolution/gx/GXVert.h` has the opt-in `REVOLUTION_GX_GXVERT_PLAIN_PARAMETERS`).
- Inside `scn::step::...`, the names `ocoll::`, `info::` and `sfx::` resolve to the nested namespaces. Write `::ocoll::NodeDesc`. A local named like a namespace (`item`) makes its member calls "undefined identifier".
- Statics land in `.sbss` and `.bss` in reverse order of declaration (library C code, no pooling). `kpad` is an exception and we don't understand it yet. Its static arrays came out in the order the code first uses them, and its zero-initialized statics with an explicit `= 0` in declaration order.
- These are small forms that change the code. `lo <= c && c <= hi` stays 2 compares where `c >= lo && c <= hi` becomes subtract-and-compare, `(x & MASK) == 0` and `!(x & MASK)` give different instructions, and `if (p == NULL) return false; else return p->f();` puts the false return first with a tail call.
- The strings of a template's member functions come out in the order the members are first instantiated, and inline functions in a class body are instantiated in the order the class defines them, ahead of everything in the source file. `mintvm::Runner` defines `currentModule() const` ahead of `pushModule()`. The other way around, the two assertion strings of `MArray::at` swap places and the unit no longer links.
- Between classes it's the other way around, the strings and weak functions of the class whose header was read last come out first. `mintvm/VMObjectType.h` includes `VMVariableList.h` ahead of `VMFunctionList.h` for that reason. Where 2 classes' strings are swapped in a unit and nothing in the source file explains it, swap the includes.
- A function template defined below its class is emitted at the end of the unit, whether or not it's marked `inline`. One defined in the class body is emitted where it's first needed. The rotations of `std::__red_black_tree` sit in the class body, after `balance_insert`, to come out where the original has them. The same goes for the members of a class template. Defined below the class they come out at the unit's end, in the order the class declares them, and defined in the class body they come out after the constructor that needs them.
- Instances of a class template come out grouped by member, not class by class, when the class declares no destructor. The weapon factory has 100 `onInit` in reverse order of first use, then the 100 implicit destructors in the same order, then the 100 `create` functions of the state factories in the order of the `onInit`s, then their destructors in the opposite order. A destructor declared in the template breaks the grouping (`onInit`, destructor per class), so the grouping itself tells you the destructor is implicit.
- A member function template called twice with the same arguments is emitted directly behind its caller, ahead of all class instances, and called once it's expanded.
- An explicit specialization of a function template that's defined in a header is emitted in every unit that includes the header, at the place of the include and ahead of the source's own functions. The type info functions at the head of the 3 `CustomFactory` units give the original's include order that way.
- The vtables in `.data` follow the order in which the templates are first instantiated. An include in the middle of a source file can be what the original had (`info/sequence/Sequence.cpp`).
- Strings in `.data` whose size is a multiple of 8 are aligned to 8.
- The inline virtual functions of a class come out in reverse order of their declaration in the class, each followed directly by the inline function it calls. Where the body stands, in the class or below it as `inline`, changes nothing (we tried it 3 ways on `nw4r::g3d::G3dObj`). Due to this, a class with the type macro at its end emits `IsDerivedFrom`, `GetTypeName`, `GetTypeObj`.
- An explicit specialization's inline members are emitted at first use. An implicitly instantiated class, a partial specialization included, follows the rule above for classes read last. `font::FontManager` got its order from `template <int N> class ExplicitAutoDeleteArray<font::Font, N>`.
- A function the link dropped still decides what its unit emits. `nw4r/g3d/g3d_resmdl` keeps 2 weak strings of an inline accessor that only a dropped function expanded, and didn't link until a stand-in for that function existed.
- 2 calls of an inline accessor in one expression read the pointer once into a saved register, while 2 uses of the variable itself read it twice (`ExplicitSingleton<T>::Object()` in `file::FileManager`'s constructor).
- An inline accessor's object expression is evaluated ahead of the call's arguments, so `mHero.model().weapon().set(Path(), Model())` calls `model()` first and adds the offset late. Direct member access evaluates the arguments first, and a named reference adds the offset up front.
- A compiler temporary that ranks above a named local was a named local in the source (`gear = &mHero.model().hat();` in `Wing::setup`).
- A literal bound to a `const T&` parameter of an inline function becomes an anonymous object in `.sdata`, not `.sdata2`.
- A destructor with an empty body doesn't store the vtable ahead of the call to a non-polymorphic base's destructor.
- Members that the original link folded or dropped still get written (`Crash::releaseHatLight`, `Evaluation::~Evaluation`). The comparison reports them as folded or unused, and the unit only links with them.
- `hel::common::ScopedPtr`'s constructor is a real function. A unit that builds 2 calls it, and a unit that builds one expands it. `HEL_COMMON_SCOPEDPTR_CONSTRUCTOR_INLINE` ahead of the include gives a unit the body.
- A named local gets a higher stack slot than a temporary. Where 2 temporaries come out swapped, one of them was a named local.
- A base destructor call whose folded target has another size than the known base's destructor means there's a class in between (`mem::IHeap`, 92 bytes against 68).
- A 4-byte class is returned in r3 and stored to the stack to serve as `this`.
- Every `hel::common::ExplicitSingleton<T>` stores itself in its own constructor body, after its members are built (`SetInstance(*this);`), and clears the pointer first in its own destructor body. The base's constructor and destructor are empty. `object_` sits in the `.sbss` of the first unit in link order that uses it.
- This game's `nw4r` inline accessors keep their assertions, with a file name of the form `g3d_rescommon_ac.h` and a fixed line number. The donor headers in `libs/nw4r/include/kdc/nw4r/g3d` have the right lines, and the game-side declarations in `include/nw4r/g3d` repeat them.
- Two functions with the same bytes that the original link didn't fold into each other call differently named functions somewhere, and the bytes can't show it (`obj()` and `objPtr()` are the same code). `sword::StateSwordAttackFinish::procFixPos` and `common::StateGuard::procFixPos` are a pair like that. With `objPtr()` in both, the linker folds the sword states into `StateGuard`'s and they can't link. With `setNextState<common::StateFall, Hero*>(&obj())` in the sword body, they do. `compare.py` says complete for both forms, so before you write the body of a branch, check which function the map says it's replaced by.
- A branch that isn't a destructor usually only folds once its target's unit is compiled from source too. [Object Classes](object_classes.md) has that under "Folding Between Directories".

### What a Unit Leaves in Its Data
- The strings of functions that the link dropped stay in a C unit's `.data`, at their place in the pool. A stand-in with a TODO holds them, which is one function per dropped function, in the map's order, that passes the strings to `OSReport`. `(void)"...";` emits nothing in C (`OSExec.c`).
- An initialized local that nothing uses (`GXColor fg = { ... };`) still creates its constant in `.sdata2`.
- `(void)name;` in an inlined helper keeps the `__FUNCTION__` object of each caller that passes it in `.data`. An unused parameter drops it (`OSNet.c`).
- The two strings `NW4R:Pointer must not be NULL (p)` and `LinkList.h` at the head of a unit's unnamed `.data` come from `#include "util/ObjList.h"`, which means the unit saw the body of `util::ObjListNode<...>::~ObjListNode`. 86 game units have them, and a unit that destroys the same classes without that body doesn't (`pause::PageAbility` has them, `scn::titlemenunew::FileNumber` doesn't). Look at the original object's `.data` before you add the include. Where the pair sits at the tail of `.data` in a unit that destroys a `g3d::ModelAccessor`, the include alone isn't enough and an explicit instantiation stands in, which is `template util::ObjListNode<g3d::Model, util::ObjListDummyType>::~ObjListNode();` (`WarpLowper`, and `ShipDoor`, `StrikeBox` and both `Salamander` units have the same tail).
- A buffer that sits 8 bytes later in the link map than its size explains was declared `__attribute__((aligned(32)))` (`gfx/RenderSetting.cpp`).
- File-local tables of pointers aren't `const`. They sit in `.data`, and `const` moves them to `.rodata`.
- A pure virtual destructor with an inline body gives the zero slot in the vtable (`scn::subgame::title::window::IGuide`). `right()` and `left()` that are tail calls through the vtable are inline virtuals, `{ return down(); }`.
- An implicit copy constructor that the unit expands once shows the class's whole layout (`hid::SimpleWRHID` in `SceneStrap::isButtonReceived`).
- A function that uses 2 or more strings from `.data` addresses them from the unit's first string. Its offsets only match once every earlier string of the unit is in the file, in order. `#pragma force_active on` around an unused constant keeps it and its string in the object, which holds the place until the functions that use it exist (`pause/PageManager.cpp`).

### Loops, Constants and Small Forms
- How a loop is written decides how far it's unrolled. `while (length--)` is unrolled 4 times, `for (i = 0; i < length; i++)` 8 times (`OSCalcCRC32`). A loop over a known count is unrolled completely as `for`, and stays a loop as `i = 0; do { } while (++i < n);`.
- `x = cond ? 0 : x;` as its own statement is branchless (`neg; or; srawi; andc`), while `if (cond) x = 0;` branches.
- `a = b = x;` stores `b` first. The operands of an `add` keep the source's order, so `a[0] + a[1] + n` and `n + a[0] + a[1]` differ.
- A product of a value loaded from memory and a computed one comes out with the loaded operand first, whatever the source says. To get the computed one first, put it in a local.
- `alpha = alpha * x; alpha >>= 8;` in 2 statements keeps the intermediate in the variable's register, one statement uses r0.
- `x = FSqrt(expr);` recomputes `expr` after the call inside, while `x = expr; x = FSqrt(x);` keeps it in a saved register. Both occur.
- For a `u8`, `x >= lo && x <= hi` gives `addi; clrlwi; cmplwi`, and `static_cast<u32>(x) == a || ... == b` gives `addi; cmplwi`.
- A sum computed ahead of a loop that stores lets the compiler reuse the loaded values inside it, and computed after, it reloads. Loads ahead of where the source seems to need them mean the statement stood earlier.
- A store through a saved register with no reload after calls on the right-hand side is a pointer local taken ahead of the calls, not another order of evaluation.
- `extsb` or `lha` on a load of a small-data variable gives you its signedness. With the unsigned type the code is one instruction off at every use.
- `int i;` at function scope against `for (int i ...)` in each loop changes which saved register an earlier local gets. A flag set ahead of a loop only gets its register ahead of the compiler's hoisted address temporaries when it's declared ahead of the other locals and assigned later.
- Several copies of zero in saved registers ahead of a loop (`li rA, 0`, then `mr rB, rA` again and again) aren't about types. The zero stored in each basic block is hoisted in front of the loop, and normally they merge into one register. They stay apart when the back end, not the optimizer before it, has made a strength-reduced index that starts at zero, and it gets that job when the multiplier is something the optimizer doesn't treat as loop-invariant. That's a member load, `&bufs[kp->len * i]`, where a local or a parameter gives one copy (`KPADInitEx`). `--flags=" -opt nostrength"` is the quick test. If the instruction count becomes the original's, the loop has to be written so that its multiplication is left alone.
- A 64-bit carry's upper half as `(ULONG)(x >> 32)`, in cast form, gives a hoisted zero register, while `& ULONG_MAX` and `% (1ull << 32)` don't (`LINTMul`).
- A value in its own saved register that's used in several places may be a repeated expression and not a local. Removing the local re-ranks every register after it, which no order of declarations finds (`KPADiRead`).
- `uwp = &tp->w;` after `--tp;`, with reads through `uwp`, puts only the first load ahead of the decrement. Reading through `tp->w` everywhere folds every load of the block ahead of it.
- `b = c ? TRUE : FALSE;` and `if (c) b = TRUE; else b = FALSE;` give the same instructions, but the second form's variable gets its register at that statement, and the first form's ranks behind variables defined after it (`CXSecureUncompressLZ`, where 720 orders of declarations didn't make up for it).
- A loop bound read through an accessor (`i < Size()`) isn't unrolled, and copied to a local first, the loop is unrolled 8 times.
- `VEC3 u = a - b;` and `VEC3Sub(&u, &a, &b)` use registers differently, and both occur. `x / 2.0f` has its operands in other registers than `x * 0.5f`.
- Step-wise statements on one variable keep the value in one register, like `v = a * (b - c); v -= d;`. The single expression puts the result in the other operand's register.
- If every float register after a call result is one off and a low register stays unused, the function probably returns that value. `if (len != 0.0f) { ... } return len;` gives one `beq` to the epilogue, while an early `return` gives `bne` plus `b`.
- A struct-returning ternary copies once more than `if (...) return a(); else return b();`.
- Of aggregate locals, the one declared last gets the lowest stack offset.
- A `u8` counter stays untruncated through `i++` and through `i += (u8)7`. `i += 7` truncates it through a second register (`NANDErrorMessage.c`).
- A `const` on a by-value parameter of an inlined C function moves its sign extension (`nandCheckCharacter(const char)` in `nand.c`).
- `*(buf + len - 1)` indexes from `buf - 1` (`addi r3, r1, 23; lbzx`) and keeps the `extsb`, while `buf[len - 1]` adds first.
- `&p[n - 4]` against `p + n - 4` changed the saved registers of a whole function.
- `x * 228 * 2` folds to a multiplication by 456, while `(x * 228) << 1` keeps `mulli; slwi`.
- A ternary of enumerators stays `cmpwi; li; beq; li`. With ints, `c ? 0 : 7` goes branchless.
- A zero stored to several bool members through a saved register that other values share is a `bool zero` local, declared ahead of the lower-ranked locals. A late temporary in a saved register that no loop variable accounts for is one more named local.
- `bool r = !a && !b;` ranks registers differently from `bool r = false; if (...) r = true;`, with the same instructions (`Block::onHit`).
- `const T& x = f();` avoids the temporary and the copy that a named local of a class without a copy constructor costs (`WarpLowper::mfUpdateSRT`).
- `mParam.obj()._4` converts ahead of a following call, while `mParam->_4` keeps the pointer and loads late. 3 uses of `->` in a unit emit `operator->` as a function, which the original may not have (`Block`).
- For 2 temporaries swapped on the stack, hand one of them to a file-local inline helper as `const T&` (`Switch::objCollReact`).
- A handle that's destroyed in the middle of a function sits in a block of its own.
- `a[n].b[Rand(2)] = x` scales the index ahead of the base, and `int index = Rand(2);` first gives the other order. `pos = (pos + 1) % num` goes through a scratch register, `pos++; pos %= num;` doesn't. `Boss& boss = mBosses[pos]` adds the member's offset up front, plain indexing keeps `this + pos * 16` (`BossSet::reset`).
- A virtual call on a member object is `static_cast<IModeButton&>(mHelp).setParent(...)` at each call, while a named reference keeps the address in a saved register.
- `static T x = {};` on a function-local static gives the guard byte and no initializing code, while `static T x;` gives no guard.
- Any user-declared default constructor, even an empty one on the element type of an array, makes this compiler emit out-of-line copy constructors. A class whose copies are word loops has none.

### Switches
- A small `switch` becomes a compare chain in source order (`cmpwi a; beq; cmpwi b; beq`).
- A run of case labels is folded to `addi; cmplwi` when the operand is a parameter or a local. On a member, `switch (mType)`, the run 3 to 4 is tested with 2 signed compares, `cmpwi 3; blt; cmpwi 4; ble` (`setsuna/chara/Blind`).
- `Type t = mType; switch (t)` ranks the registers differently from `switch (mType)`.
- `cmplwi 3` for the cases 0 to 3 followed by `cmpwi` for 4 to 6 needs a signed member (`SceneStrap::draw`). In a compare chain an `int` state gives `cmpwi` and a `u32` gives `cmplwi`.
- A switch whose middle case only breaks (`case 1: case 3: ...; case 0: ...; case 2: break;`) gives `cmpwi 2; beq end; bge`.
- In a `switch` without `default`, a run of labels is tested ahead of the single cases, and the bodies keep the source's order.
- A jump table starts at 8 cases, and a case that only repeats the initial value (`case 4: rot = 0.0f; break;`) counts. With 7 the same switch is a compare chain.
- A switch whose default body stands ahead of the case bodies has `default:` first in the source. A statement that the other cases branch past belongs inside `default:`. A compare chain that seems to fall into the first case has no `default`.
- `cmpwi 0; cmplwi 1; cmplwi 2` is the plain switch on a `u32`, and a chain of `cmpwi` only is `switch (static_cast<int>(...))`. `subi; cmplwi 1` behind one call is a case with 2 labels.
- A dense chain `beq, beq, ...` on a `u32` member is a `switch`, an if-chain gives `bne`.
- An or-chain `k == a || k == b || ...` gives a range check and a bit mask, while a `switch` with the same labels gives a jump table. Written as an inline member that reads the member itself, the `li 0` of the result comes ahead of the load (`Block`'s constructor).
- This one is still open. `nw4r::ef`'s `DrawFreeStrategy::Draw` and one function of the directional strategy have their switches as a tree (`cmpwi 1; beq; bge; cmpwi 0; bge`) with the operand evaluated once, and their `if (c) t = 1; else t = 0;` flags as branches. This compiler only writes both forms at `-opt off`. From level 1 up it gives the chain and the branchless flag, in every version from Wii/1.0 to 1.7 and with every single optimization switched off. The same inlined switch is a chain in the billboard, line and particle units, so the cause is per function. `#pragma global_optimizer off` around `Draw` gives the tree and the right instruction count, and with it a frame pointer and fewer saved float registers, so that's not it.

### Operands, Arguments and Stack Slots
These came out of writing about 1,000 state classes ([Object Classes](object_classes.md)), where the same few statements keep coming back and one of them is always in another order.

#### Arguments and Temporaries
- Class temporaries among a call's arguments are built ahead of the scalar arguments. Those built by an inline constructor or by a `Zero()` or `Create()` call are built right to left, like in `addBodyColl(0, 0.9f, Vector2(0, 1.6f), Vector2(0, 0.7f))` and `airAccelFall(dir, MoveParamAccel::Zero(), MoveParamFall::Zero())`.
- String literals among a call's arguments are numbered in evaluation order, right to left, not in text order.
- An inline constructor is expanded where its arguments are constants or loads, and called where an argument contains a call, like `Vector2(0.0f, 0.5f)` against `Vector2(0.5f * getSign(), 0.0f)` in one function.
- An inline two-float constructor with constant arguments is expanded even on its second use in a unit, and with loaded arguments the second use is a call (`Vector2 zero(0.0f, 0.0f)` beside `Vector2 dir(p.x, p.y)`).
- A class temporary among the arguments is built ahead of the call that yields the object, `obj().effect()._58.requestND(k, 0, obj().model().getDirection3())`, unless the object is a named reference taken first.
- `stb r31, N(r30); clrlwi r0, r31, 24; cmpwi` in a constructor is the member read back after its initializer (`mIsUp ? a : b`), not the parameter.
- A by-value class argument given a temporary is built in place. An extra copy of its words means a named local was passed. `addi r4, r1, N` again after a constructor call is a named local, `mr r4, r3` a temporary.
- An argument computed ahead of the arguments to its right was a named local (`Vector3 pos = obj().location().pos(); manager.onVomit(pos);`). So was a value computed ahead of a call and used behind it, like `f32 speed = ...; setSpeedH(speed * getSign())` and `f32 angle = mAngle; Abs(call() - angle)`.
- `obj().move().setSpeedV(arg)` evaluates the argument ahead of `obj().move()` when both are real functions. Through an inline accessor the object's call comes first, then the argument, then the offset.
- A bool written in the argument (`setIsRightDir(a.x > call().x)`) lands in the dying temporary's register, and a named `bool` takes another. A compare done ahead of the call that uses it is a named `bool`.
- A reference to a call result that nothing uses still emits its calls.
- By-value class arguments written as temporaries, like `request(kind, obj().location().pos(), Vector3::ZERO, n)`, are passed without copies. Named locals add a copy each.
- A value that's computed ahead of the `mr r3, this` or the `addi r3/r4` of a call is a named local, like `f32 rate = ...; LinearInterpolation(a, b, rate)` or `f32 deg = call(); v.rotate(axis, 0.017453292f * deg)`.
- A product that's finished ahead of `mr r3, obj` was assigned in place, like `rate *= param._10; context.setRotAngle(rate);`. The same goes for a sum (`u32 frame = min + Rand(max - min); mContext.setMaxRotFrame(frame);`).
- A reference member that's loaded into a saved register ahead of `objPtr()` went through `std::tr1::ref`, like `ChangeStateNoScrew(objPtr(), std::tr1::ref(mContext))`.

#### Stack Slots
- Larger classes sit higher. Within one size the named locals come first, the first declared highest, then the temporaries in text order going down, whatever the order of evaluation.
- A call result whose slot is the highest in the frame is a named local. In `a.y - b.y` on 2 call results `b` is evaluated first and `a` gets the higher slot, and a local for `b` swaps the slots.
- The locals of an expanded helper sit below the caller's own. A reference-bound temporary below a later named local means the earlier statements were a helper function.
- A temporary that lands 4 bytes off in a frame of the right size, or a frame of the wrong size with every instruction otherwise equal, means a class passed or returned by value is declared with the wrong size.
- A helper that returns a matrix builds its named result in the return slot. Matrices declared as named locals in the order they're made give the original's stack.
- `f32 x = call().x;` puts the vector below the other temporaries, and a named `Vector2` goes above them.
- A result slot between named locals is a named local too (`Vector3 newPos = pos + offset;`).
- A matrix product in one expression, like `CreateRotXYZDeg(Vector3(x, 0, 0)) * CreateRotXYZDeg(Vector3(0, y, 0))`, evaluates the right operand first and gives the temporaries slots in evaluation order. Named matrices land elsewhere.
- `Vector2` temporaries of `(b - a) * rate + a` in descending slots are `Math::LinearInterpolation(a, b, rate)`. `a + (b - a) * rate` gives other slots.
- For a frame that's 0x10 too large with every instruction right, check the sizes of the unit's own stand-in classes before anything else (`challengedoor/AddOnMint` had one of 0xD words where 0xC was right).

#### Float Expressions
- Float constants are numbered as each inline function is expanded, an argument's function first. `f32 t = a / b; SinDegF(90.0f * t)` numbers the function's constants ahead of the 90, and `SinDegF(90.0f * (a / b))` numbers the 90 first. `compare.py` doesn't see the order when `.sdata2` has another size, the link test does.
- The same expression written out 4 times numbers its constants differently from one computed once and reused. Where the original has the code 3 times, a file-local helper used 3 times is a call, so write it out.
- `f32 v = call(); v += mMember;` adds with the call result first, while `call() + mMember` puts the loaded operand first. `x = param; x *= local;` puts the loaded operand first, while `param * local` and `local * param` both put the local first.
- A sum or product of a call result and a value held in a named local puts the local first, whatever the source says. To get the call result first, put it in a named local too (`f32 sign = getSign(); if (sign * nururi < 0.0f)`), or write 2 calls in one expression, where the right one runs first (`velocity().x + prevVelocity().x`).
- `f32 angle = 60.0f; angle += 10.0f * RandAF();` loads the constant ahead of the call.
- `x *= 0.5f` and `x / 2.0f` put `x` first in the `fmuls`, while `x * 0.5f` puts the constant first. `X * (X * X)` gives `fmuls new, old`.
- `p * (cond ? 1.0f : -1.0f)` as one expression loads `p` first, and through a local the local comes first.
- There's no `fmadds` where the product was a local, like `f32 offset = a * b; pos.y += offset;`. `fmuls; fsubs` where the compiler would fuse is `fall *= fall; f32 rate = 1.0f - fall;`. `f32 sign = getSign(); x += sign * distance;` puts the call result first in the `fmadds`.
- A float local declared ahead of an earlier-assigned one takes the higher saved register, like `f32 height; f32 rate = ...; height = ...;`. A constant held in a saved register from the top of a function is `f32 bound = 2.0f;` as its first statement. Loads ahead of an int-to-float conversion are named locals in that order.
- `lfd` of a zero in a float compare is a double literal, like `velocity().y <= 0.0`.
- `!(a <= b)` on floats is `cror; beq`, and `a > b` is `ble`. A `bool` local from a compare, followed by `if (!flag)`, keeps the `mfcr`.
- Degrees to radians is written at the call as `0.017453292f * x`. `Math::DegToRad` is emitted and called at 2 uses and orders the multiply the other way. Where the operand is a call result it's a local first, like `f32 angle = RandF32(..) * sign; dir.rotate(0.017453292f * angle);`.
- `std::min(max, v)`, not `(v, max)`, gives `fcmpo v, max`.
- An inline function with `const f32&` parameters puts a literal argument in `.sdata` and reads member operands where they're used, and with by-value parameters the members are loaded right to left ahead of the expression. A clamp whose limits sit in `.sdata` and are loaded twice is a template like that, `if (v > max) return max; if (v < min) return min; return v;`.
- `(b - a) * rate + a` on vectors whose temporaries interleave on the stack is `hel::math::Math::LinearInterpolation(a, b, rate)`.
- An int-to-float conversion without `xoris` tells you the operand is unsigned.
- `s32` is `long`, so `Math::Abs` on it emits `Abs<l>`, and the original's `Abs<i>` needs `int`.
- `rate * (b - a) + a` is `Math::Interpolate` and `(b - a) * rate + a` is `Math::LinearInterpolation`. They differ in the operand order of `fmadds`. A literal bound to a `const f32&` parameter lands in `.sdata`, a file-local constant doesn't.
- `param._34 * obj().target().getSign()` in one expression calls `getSign` first and multiplies load by result. A named `f32 sign` reverses the operands.
- `f32 speed = obj().param().sword()._A4;` loads straight off the call. A named `const Param&` adds `mr r4, r3`.
- `0.0f == velocity().x` gives `fcmpu f0, f1` with the constant in f0.
- `f32 cos = CosDegF(180.0f * t); f32 rate = 0.5f * (1.0f + cos);` numbers the cosine's constants first. A rate that's computed ahead of the `addi r3/r4` of a by-reference call is a named local.
- `Vector3 heroPos = GetHatedHeroPos(obj()); diff = heroPos - other();` evaluates the hero first. With both operands as calls, the right one is evaluated first.
- `call() * AbsF32(local)` inside one expression keeps the call result as the first `fmuls` operand. With the absolute value in a named local, the register operand comes first whichever way you write it.
- A product assigned to a local and added in the next statement stays `fmuls` plus `fadds`. In one expression it becomes `fmadds` (`rateX = t * (..); rateX += t;`).
- `a * k + b * (1 - k)` evaluates `b * (1 - k)` first, so read the operand order from the call order. A lerp written out as `a * (1.0f - r) + b * r` gives `1 - r` first, then `b * r`, then `fmadds` on `a`.
- Writing `(1.0f - t)` out each time instead of going through a local can be what gives the original's store order and registers.
- `f32 t = a / b; k * CosDegF(90.0f * t)` numbers the cosine's constants ahead of 90. With the division inside the argument, 90 comes first.
- `f32 speed = param; speed += obj().move().velocity().y;` loads the parameter first and gives `fadds param, velocity`.
- `mEnd.y = mEnd.y + a + b` with the sum first needs `f32 y = mEnd.y + a; mEnd.y = y + b;`.

#### Integers, Bools and Branches
- `return a | b | c;` on bools gives the `or` tree and `subic; subfe`, while `||` gives branches.
- `ble X; b Y; X:` around one assignment is a ternary that keeps the value, like `speed = isRightDir() ? speed : -speed;`. `x = c ? Math::Min(x, m) : Math::Max(x, m);` stores once, the `if` and `else` form twice.
- `mIsValid = arg; if (!mIsValid)` gives `clrlwi` on the parameter, `if (!arg)` gives `cmpwi`. `u32 a = f(); if (flag) a = 0; mColor.a = a;` truncates at the store.
- An inline byte setter that stores through `reinterpret_cast<u8*>` gives `clrlwi`, through `bool*` it doesn't.
- Re-assigning a variable from itself (`v = v * 10 + f()`, `rot = 360.0f * rot + g()`) takes a new register, and a new named variable takes the freed one, while `rot *= expr` keeps the register.
- `addi r3, r3, A` in one arm and `addi r3, r3, B` in the other, then one load through r3, is a reference picked by a ternary, like `const f32& v = cond ? p.a : p.b;`. On sub-structs the same picks a parameter block.
- `kind = A; if (cond) kind = B;` puts `li A` ahead of the call in `cond`, while `cond ? B : A` loads both behind it.
- `switch (k) { case 5: case 6: return true; default: return false; }` is branch-free (`subfc; subfze`), while `k >= 5 && k <= 6` gives `cmplwi; bgtlr`. A `return` inside each case reorders the bodies, while `f32 r; switch (m) { default: r = a; break; case 1: ... } return r;` keeps the source's order.
- `if (x == A) ... else if (x == B)` on a local gives one `bne` per block, while a switch with 2 cases puts both compares first.
- `if (x % n == 0) return a != b; return false;` isn't `return x % n == 0 && a != b;`.
- `cmpwi n, 0; beq end; b cond` ahead of a loop is an explicit `if (n != 0) { for (...) }`. `li i, 0; b <increment>` is `u32 i = 0; while (++i < n)`.
- `!(6 <= s && s <= 9)` on a local keeps 2 signed compares, while `s < 6 || s > 9` becomes subtract-and-compare. `r >= 0 && r <= 1` on an `int` is `cmplwi r, 1`.
- A constant in the middle of a sum stops the sharing of a repeated sum. `Rand(far + 4 + near)` gives `add; addi` each time, and `far + near + 4` is shared with an earlier `far + near + 8`.
- `a + Rand() * b` on members loads `b` first, and `int rand = Rand();` ahead of it gives the other order.
- An index written inside the brackets, `mPositions[interval * (num - 1 - i)]`, ranks its register ahead of the locals, and a named `index` moves 4 registers.
- `if (handle.isAlive()) { ...; return; }`, and any early `return;` inside the scope of an object with a destructor, gives the destructor sequence twice with the body first.
- A run of tests that each return is one `||` chain (`beq next; b end` at the last term, or a trailing `cmpwi r3, 0` behind the last call). Separate `if`s give `bne end` everywhere. `if (v > 0.0f) { return; }` ahead of a chain gives `bgt end`, while the nested `if (v <= 0.0f) { chain }` gives `cror; bne`.
- `gobj::Move& move = obj().move(); move.setSpeedV(p.a / p.b);` stops a load of `p.b` in an `if` above from being reused across the call.
- After `fcmpo`, `extrwi r, r, 1, 1` is `>` and `srwi 31` is `<`.
- `flag ? 1 : 0` on a bool folds away. `subic; subfe` on a loaded byte needed a `u8` member.
- A trailing `cmpwi r3, 0` behind a call that returns a bool is `if (...) { return; }`, also as the last statement of a `switch` case.
- `cond ? 0xDE : 0xDD` (values 1 apart) compiles branch-free, and `static_cast<ScriptKind>` on both gives `li; beq; li`. Values 2 apart (`0xDA : 0xD8`) branch anyway. An enum-typed ternary like `c ? static_cast<E>(3) : static_cast<E>(2)` gives `cmpwi; li; beq; li`, while an int ternary gives `addic; subfe; addi` and other registers.
- `!handle.isAlive()` materialized with `cntlzw; srwi` is `handle.isNull()`.
- `case 0: rate = 0.0f; break;` with `rate` already zero drops the store but keeps `cmpwi r0, 0; beq` and a dead `b`.
- `setIsRightDir(obj().location().pos().x < baseX)` without a named bool gives the flag its own register. A named bool reuses a dead register.
- `Math::Min(a, b)` gives `bge` over `addi r3, &a`, and `Max` gives `ble`.
- `subic; subfe; cmpwi 0` on a pointer member is a conversion to a member pointer used as a bool, `operator int T::*() const` (`std::tr1::function` in `std/tr1/function.h`).

#### Structs and Classes
- A struct returned by value is built on the stack and copied out only if no member has a copy constructor.
- A struct passed by value is copied by words, and a returned reference is copied member by member, like in `static ColorF Scale(ColorF c, f32 s) { return c *= s; }`.
- A struct with any user-declared constructor gets an out-of-line `operator=`. A struct of scalar members has its implicit `operator=` as a function that's called from the second use in a unit on. With an array member the copy is always an inline block copy.
- A handle that sits above the other temporaries and is destroyed with -1 was bound to a reference, `const util::ObjRefHandle<weapon::Weapon>& beam = manager.request(desc);`, while a named handle's destructor gets 0.
- A function-local `static const` that the map lists as `UNUSED` is written as a plain `const` local.
- An out-of-line instance of a member template (`setNextState<...>`) in a unit with one visible user means a second user that the link dropped.
- An 8-byte class is returned in r3 and r4.
- A struct of an int and a struct of 2 floats is copied `lwz, lwz, lwz, stw, stw, stw`, which means the pair is a nested struct.
- A `GXColor` constant loaded as one word from `.sdata2` is a compound literal, `(GXColor){ r, g, b, a }`, in an initializer, an assignment or a ternary. The ternary builds each colour inside its branch, while 2 named constants build both up front.
- A member named in the initializer list with empty parentheses (`mPoints()` on a `MutableArray`) merges its end pointer with the next member's address. Left out of the list it matches.
- `gobj::MoveParamAccel accel; switch (...) { case 0: accel = Create(...); ... }` gives the temporaries plus one assignment call per case.
- A file-local table that the original keeps in `.rodata` is `const`, otherwise `compare.py` says `.rodata not in the compiled object`.
- A class with a user-declared constructor but no declared copy constructor (`mcoll::detail::MoveGridGroupId`) is returned in r3, and the compiler still emits `__ct__X(const X&)` as a function in a unit that copies it 2 times or more. A declared copy constructor forces the return through memory.
- A struct of scalars gets its out-of-line `operator=` from 2 uses (a `MutableArray`'s `add` plus `removeAtIndex`). A user constructor adds an out-of-line copy constructor the original lacks (`SwordBeamCtrl::ReqData`).
- With `UTIL_OBJREFHANDLE_ASSIGNMENT_IN_CLASS`, `isAlive()` is still called from its second use on, and the assignment is expanded at one use. A local `ObjRefHandle` tested with `isAlive()` only gives `lwz; cmpwi` with that macro defined.
- A by-value `GXColor` argument written as `static_cast<GXColor>(hel::common::Color(..))` copies, then takes the address. The implicit conversion takes the address first.
- `const Vec2& v = param._B0; Vector2 speed(v.x, v.y);` loads y first, `Vector2 speed(param._B0)` loads x first.
- `mPos = obj().basePos(); mPos.y += 4.0f;` gives the x copy, then `y + 4` stored once. Through a local, the constant loads first.
- An 8-byte struct of scalars returned by value comes back in r3:r4.
- `mOffset(hel::math::Vector3(0.0f, y, 0.0f))` in the initializer list is built on the stack plus a 3-word copy.
- `hel::common::Color(v, v, v, 0xff)` handed to a `const GXColor&` gives 4 `stb` and a word copy.
- A factory `create` that passes the stored vector's address means the constructor takes `const Vector3&` while the template argument is `Vector3`.
- An object that's destroyed in the middle of a function (a `NodeAccessor` for example) sits in a block of its own.
- A version can drop a member. `hammer::StateThrow` has no `mIsEnd` in the Korean build and another destructor, so it's written with `#ifdef VERSION_SUKK01`.
- You can read an opaque class's member boundaries from its `__as__`, as the implicit assignment copies each direct member as an object of its own.
- A class made only of `u8 _0[N]` has alignment 1 and lands at the wrong offset after a `bool`. Use `u32` arrays for opaque classes.

### Vectors and Matrices
`hel::math::Vector2`, `Vector3`, `Direction3`, `Matrix34` and `Matrix44` have the original's inline bodies in `include/hel/math/`. Don't define anything of theirs locally.

- Which functions are inline was settled per function by 2 kinds of evidence. A copy of the function in another unit's object in the link map proves it's weak, and so inline, and the number of units that call it once separates the rest (`toVector3` is called once by 305 units and is ordinary, `Vector2()` by one of 99 and is inline). The ordinary ones are `normalize`, `setLength`, `cos`, `rotate`, `signedAngle`, `scale`, `toVector3`, `slerp`, `reflect`, the two normalized crosses, `getScaled`, every `Create...`, `toMatrix44`, `mtxInverse` and `mulVec`. Constructors, the arithmetic operators, `dot`, `length`, `squareLength`, the distances, the `isZero` and `equals` family, `getXY` and the matrix column getters and setters are inline.
- The copy constructor of `Vector3` is a declared inline copy of the 3 words. A unit that copies once has the word copies in place, a unit that copies twice calls it. With no declared constructor at all, 3 units fail, and with float copies, others do. `operator=` of `Vector2` and `Vector3` is the compiler's own and the headers don't declare it, so a class that holds a vector is assigned by words.
- To check an inline body against the original, take the member's address in a scratch source and compare it with the unit that holds the weak copy, using `python tools/compare.py SUKE01 <scratch>.cpp -u <that unit>`.
- The classes' own sources (`hel/math/Vector2.cpp`, `Vector3.cpp`, `Direction3.cpp`) take declarations through opt-in macros, because where each inline function would land in them depends on functions the link dropped.
- 3 units keep a stand-in, each with a TODO. `gimmick/warplowper/WarpLowper` and `gimmick/block/Block` call a constructor at its only visible use, and the partly written `hero/Piggyback` needs the copy constructor undeclared.
- The arithmetic operators of `Vector3` copy `*this` through a private struct of words. That gives the original's bytes, but it isn't the original's source.
- `hel::math::Vector2` converts to the plain `Vec2` through an inline conversion operator, which is what keeps the address of the copy in a saved register (`bonkers`, `kingsdoo`).
- The state factories of `util/StateChanger.h` take their arguments by value. `bonkers` has an out-of-line `setNextState` of 53 instructions that only by-value constructors give. Where a unit passes a `Vector3` temporary and everything is expanded, the original still builds the vector once and leaves a 12-byte slot unused, and this compiler copies it twice. A unit like that defines `UTIL_STATECHANGER_FACTORY_ARGUMENTS_BY_REFERENCE` (`fattybuffer`, `fattybufferjr`). That's a stand-in, as with references everywhere 19 linked boss units stop matching.

### Opt-in Macros
Some shared headers have 2 forms of one function, and a unit picks the other one by defining a macro ahead of its includes. Each of them is a stand-in with a TODO in its header. Most of them exist because the original expands an inline function in a unit that uses it once and calls it in a unit that uses it twice, and a partly written unit has too few uses.

| Macro | Header | What the Unit Gets | Units |
|---|---|---|---|
| `HEL_MATH_VECTOR2_OUT_OF_LINE` | `hel/math/Vector2.h` | the inline functions as declarations | `hel/math/Vector2` itself, `gimmick/warplowper/WarpLowper` |
| `HEL_MATH_VECTOR3_OPERATORS_OUT_OF_LINE` | `hel/math/Vector3.h` | the inline functions as declarations | `hel/math/Vector3` itself |
| `HEL_MATH_VECTOR3_COPY_CONSTRUCTOR_OUT_OF_LINE` | `hel/math/Vector3.h` | the copy constructor as a declaration | `gimmick/block/Block`, `enemy/mahoroamagicball/StateNWayShot` |
| `HEL_MATH_VECTOR3_NO_COPY_CONSTRUCTOR` | `hel/math/Vector3.h` | no declared copy constructor | `hero/Piggyback` (partly written) |
| `HEL_MATH_DIRECTION3_OUT_OF_LINE`, `..._CONSTRUCTOR_OUT_OF_LINE`, `HEL_MATH_MATRIX34_OUT_OF_LINE` | `hel/math/Direction3.h`, `Matrix34.h` | declarations | `hel/math/Direction3` itself |
| `HEL_COMMON_SCOPEDPTR_CONSTRUCTOR_INLINE` | `hel/common/ScopedPtr.h` | the constructor's body | `gunshoot/info/Victory`, `setsuna/info/ResultTargetNumber` |
| `HEL_COMMON_MUTABLEARRAY_ADD_IN_CLASS` | `hel/common/MutableArray.h` | `add()` in the class body, emitted at its first use | `info/sequence/Sequence`, `pause/PageManager`, and the boss and weapon classes with a `MutableArray` member, which define it in their own header (about 17 places) |
| `HEL_COMMON_MUTABLEARRAY_DESTRUCTOR_IN_CLASS` | `hel/common/MutableArray.h` | an empty destructor in the class | `gimmick/popflower/PopFlower`, `boss/DamagePrevent`, `boss/WeakPointCtrl`, and the headers of the classes with a `MutableArray` member (about 16 places) |
| `HEL_COMMON_MUTABLEARRAY_REMOVEATINDEX_IN_CLASS` | `hel/common/MutableArray.h` | `removeAtIndex()` in the class body | `gimmick/popflower/PopFlower` and the classes that take an element out of an array, like `boss/DamagePrevent`, `dubior/EnemyCtrl` and `fattybuffer/EnemyReqBuff` (about 13 places) |
| `UTIL_OBJLISTNODE_CONSTRUCTOR_LINK_REFERENCE` | `util/ObjListNode.h` | a constructor that builds the empty link through a reference | `gimmick/popflower/PopFlower` |
| `UTIL_OBJREFHANDLE_ASSIGNMENT_END_ITERATOR` | `util/ObjRefHandleInline.h` | an assignment that calls `LinkListImpl::GetEndIter` | `gimmick/popflower/PopFlower` |
| `UTIL_STATECHANGER_FACTORY_ARGUMENTS_BY_REFERENCE` | `util/StateChanger.h` | factory constructors that take references | `fattybuffer` and `fattybufferjr` `AddOnMint` |
| `UTIL_OBJREFHANDLE_ASSIGNMENT_IN_CLASS` | `util/ObjRefHandle.h` | the bodies of the assignment and of `isAlive()` in the class | `scn/step/info/HeroStatus` and about 40 units that assign a handle, mostly from a manager's `request()` |
| `REVOLUTION_GX_GXVERT_PLAIN_PARAMETERS` | `revolution/gx/GXVert.h` | vertex writers with `T` parameters, not `const T` | `scn/step/sfx/SpiralScreen` |
| `MEM_EXPLICITSCOPEDPTR_DESTRUCT_INLINE` | `mem/ExplicitScopedPtr.h` | the original bodies of `destruct()` and `ref()` | `pause/FramePanel`, `pause/PageManager`, `lvmapdoor/AddOnMint`, `warplowper/WarpLowper`, `wmap/hero/InactiveHero`, `wmap/info/LevelName`, and any unit that calls `gimmick::Manager::shipeventManager()` |
| `MEM_EXPLICITAUTODELETEARRAY_INLINE` | `mem/ExplicitAutoDeleteArray.h` | the original bodies | `pause/PageShip`, `pause/PageDropout`, `mint/Heap`, `titlemenunew/ModePanel`, `wmap/MapModelRoute`, and the capture controllers of doubter, fattybuffer and galactaknight |
| `MEM_MEMBLOCK_IMPLICIT_ASSIGNMENT` | `mem/MemBlock.h` | the implicit assignment, two word copies in place | `file/FileLoader` |
| `NW4R_G3D_RESFILE_CONSTRUCTOR_INLINE` | `nw4r/g3d/res/g3d_resfile.h` | the constructor's body | `g3d/ResFile` |
| `NW4R_UT_LINKLIST_GETNODEFROMPOINTER_OUT_OF_LINE` | `nw4r/ut/LinkList.h` | `GetNodeFromPointer` as a declaration, for a unit that expands a handle's assignment and calls it | about 15 units, `enemy/buraburadee/Custom` was the first |
| `OS_F32_TO_U8_DEFER_INLINE` | `libs/RVL_SDK/revolution/os.h` | `OSf32tou8` as a declaration | no unit defines it |

A sign that you need one is a call to an empty look-alike followed by a load (`Manager::x()` as `mX.ref()` on a `mem::ExplicitScopedPtr`, which in full is `lwz r3, N(r3); bl DefaultSwitchThreadCallback; lwz r3, N(r31)`, where the empty function is `mem::ExplicitScopedPtrUtil::CheckPointerIsValid` and the accessor is inline in its class, like `gimmick::Manager::shipeventManager()` is), or a function that's one call short or one copy long with everything else right. Each of them should go once the units that use the class are whole.

## Mint Bindings
Each library has an `AddOnMint.cpp` that registers its script functions. They're long, regular, and quick to write once one of them is right.

- A binding is `MINT_NATIVE_FUNCTION(core, module, declaration, name, function)` from `mintglue/WrapNative.h`. The macro makes a class local to the registration function, `Mint_<name>_0`, whose `Func` is what the listing shows. Its symbol carries a serial number that depends on everything the compiler saw before, and `compare.py` ignores it.
- The `Func`s come out after the registration function, in reverse order of the bindings.
- The generator cast each bound function to the signature in its declaration string, so a cast in the binding is normal. Some of them are wrong. `gobj::MintGearAnim::frame` is bound as returning nothing, so a script never gets its result.
- Identical declaration strings are shared, so the order of strings in `.data` is the order of first use.
- A state change is `obj->stateChanger().setNextState<StateX, Arg>(arg)`, with the argument evaluated first. `util/StateChanger.h` makes the compiler emit the factory's `create()` and destructor that follow in the unit. `scn/step/enemy/como/AddOnMint.cpp` is the smallest example.
- This one is still open. Where a one-argument binding is expanded whole inside its `Func`, the argument index and the register set come out in each other's registers (`scn/step/enemy/clayn`, `knucklejoe`, `pluid`, `scn/step/boss/kingsdoo`). One more level of inlining above `internal_getArg_addr` fixes those and breaks the rest.

## What the Tools Allow For
- The original link folded identical functions together ([Code Merging](code_merging.md)), so a call often names an unrelated look-alike. `compare.py` reads the pairs from the link map and accepts any name of the same group. In the disassembly, a call to an unrelated tiny function (`GKI_getfirst`, `DefaultSwitchThreadCallback`) is a merged accessor, so read the body, and `grep "is duplicated by <name>" orig/<ID>/files/iuk.MAP` lists what it stands for.
- A function the compiler emits that isn't in the original object isn't counted if the original link folded it away, kept its copy in another unit (inline functions), or dropped it as unused. `compare.py` tells you which. A unit with functions like that still links from source, as the linker script names every folded function.
- A function that the original link replaced by a branch (one `b other` in the original) is shown that way when the compiled body has the size the map gives. Linking a unit with one needs the look-alike un-exported in `symbols.txt`, and [Code Merging](code_merging.md) says how.
- The tool checks the order of the functions too, section by section. A unit whose functions match in another order can't be linked.
- `python tools/compare.py all <any path>/<File>.c -u <unit>` compares a file that isn't at the unit's path, so you can try a candidate without replacing the source. Keep the file's base name, as `__FILE__` is the bare file name, and with another name every function that uses an assertion string seems to differ.
- `-p` takes about 0.09 seconds per order, so 5 declarations take 12 seconds, 6 take a minute and 7 take 7 and a half minutes. Beyond that, permute a chosen subset with a small script.
- `-p` permutes the declaration lines of a function's first block. `u32 a, b;` on one line is never tried as `b, a`, and declarations that follow a statement or sit in a nested block aren't seen, so split and move them first. It reads the source once, so you can edit the file while it runs.
- A search script of your own counts before it runs. 7 lines are 5,040 orders and 12 are 479 million, so iterate lazily, never build the list of orders, and treat more than a few thousand tries as a sign that the search is set up wrong. A script that built a list like that once took all of the machine's memory.
- To try a change to a shared header without touching it, put a modified copy in a scratch directory and include it by absolute path as the first line of a scratch copy of the source. The include guard keeps the real header out. The compiler doesn't search the source's own directory, so a relative include doesn't find the copy.
- A static local's symbol ends in a number that depends on what was compiled before it (`buffer$1234`). `compare.py` ignores the number where a relocation names one.
- `--flags=" -maxerrors 200"` shows every compile error of a file at once.
- `--flags=" -include <header>"` puts a header in front of one unit, so you can try a change to it without touching the tree.
- The link test passes with a call to an undefined function inside a function the link drops.
- Some units only exist in one version (`arith.c` and 3 `DvdWatch` files are Korean). The tools skip the other version for them.
- A `.sdata2` larger than the split object's can be right, as the source has the constants of functions the link dropped, which the map lists as `UNUSED`. A `.bss` that's a few bytes short of the split object's is usually the padding in front of the next unit, which the split counted in, and the map has the unit's real size.
- `status.py` can show `LINKED BUT BROKEN` for a few units while another process is compiling. Run it again on that directory before you believe it.
- A data section that's larger than the original only because it holds strings and tables of inline functions is reported as holding weak data. What the link does with a duplicate depends on the section ([Code Merging](code_merging.md)), so only a link can check a section like that.
- Symbols in unnamed namespaces carry the name of the file MetaFortress compiled, `X_prt.cpp`. `compare.py` treats `@unnamed@X_prt_cpp@` and `@unnamed@X_cpp@` as the same name.
- Inline data that happens to decode as an instruction on r13 or r2 made the splitter lose about 1 in 5 small-data relocations in protected functions. `compare.py` allows for that, the build's progress report doesn't.
- `python tools/compare.py ... --flags=-DVARIANT` lets one scratch file hold several variants of a function.
- A weak copy only compares equal when the scratch source also uses its inner inline functions 2 times (`MutableArray::at()` needed 2 uses of `Array::operator[]`).
- A unit can be `Matching` while `compare.py` still says `.sdata2 differs at +0x0` (`galactaknight/StateShuttleLoop`, where the 0.0f of the weak `Vector3()` copy is numbered first). The link is what counts there.
- `.sdata2 differs at +N` with every function matching can also be a wrong literal, as `compare.py` doesn't see the values of the constants in the code. It can be the 0.0f of a weak `Vector2()` or `Vector3()` copy too, and that one links fine.
- `compare.py` accepts `obj().location()` where the asm has `location() const`. Write `static_cast<const Hero&>(obj())` wherever the asm says `HeroCFv`.
