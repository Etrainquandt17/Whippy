# Whippy

Whippy is a WIP decompilation of Kirby's Return to Dream Land (known as Kirby's Adventure Wii in Europe and Australia and Kirby of the Stars Wii in Japan and Korea), affectionately named after the enemy of the same name introduced in this game.

## AI Usage
AI may or may not be used in some parts of this project to accelerate workflows. Any AI contributions are checked by our eyes to minimalize mistakes.

## Status
About 39% of the code is decompiled and matching right now. That's 28.2% of the game's own code and about 80% of the libraries it's linked with. The build gives you a `main.dol` that's byte for byte the same as the original for both supported versions. 2,489 of about 4,930 objects are compiled from source and linked in (37.7% of the code), about 85 more have some of their functions written, and 17,275 of the 45,656 functions match.

Each DOL is split into about 4,930 objects following the link map that shipped on the disc, so the symbol names and the file boundaries are the original ones. The first functions we decompiled were the 149 whose anti-tamper check changes what the game does instead of just stopping it, and all of them match. Most of Mint (the game's scripting system) is done too, meaning the virtual machine, the engine around it and the script bindings of every enemy and boss. The library code (Revolution SDK, NintendoWare, MSL, MetroTRK and the HOME Menu library) is taken from other decompilation projects wherever their sources compile to this game's code. Kirby's Dream Collection runs on the same engine, so its decompilation gave us 85 units of engine code as well (`hel`, `mem`, `gfx`, `hid`, `util` and so on).

The flags for game code in [`configure.py`](configure.py) are the ones the matched functions agree on. The flags and compiler versions of the libraries are still educated guesses.

## Read These Before You Start
There are two things about this game that make it harder to decompile than most, and you really should read about both of them before you write anything.
### MetaFortress
About 1,300 game functions carry anti-tamper code that checksums all of the code and read-only data at runtime. If you change anything in those, the game hangs or misbehaves unless the checksums get recomputed. [MetaFortress](docs/metafortress.md) explains how it works, and [What a Failed Check Does](docs/metafortress_effects.md) lists the 149 functions that do something other than hang.
### Code Merging
The original link folded identical functions together, so thousands of functions only exist as a branch to a look-alike, or don't exist at all. [Code Merging](docs/code_merging.md) explains what the linker did and how a decompiled unit gets linked in spite of that.

## Documentation
These are the docs that are specific to this game. The ones that came with the [dtk template](https://github.com/encounter/dtk-template) (Dependencies, Getting Started, `symbols.txt`, `splits.txt` and GitHub Actions) are in the [docs](docs) folder with them.
### Symbols and Splits
[docs/map.md](docs/map.md). Where `symbols.txt` and `splits.txt` come from, how units are named, how far you can trust them and how to generate them for another version.
### Decompiling
[docs/decompiling.md](docs/decompiling.md). How to write a function and check it against the original, one file at a time.
### Object Classes
[docs/object_classes.md](docs/object_classes.md). What the enemy, boss, weapon and hero classes look like in source, and what order to write a directory of them in.
### Libraries
[docs/libraries.md](docs/libraries.md). Which projects the library code came from, with what flags, and what nobody has decompiled yet.
### Engine Code From Dream Collection
[docs/dream_collection.md](docs/dream_collection.md). The units that came from the Dream Collection decompilation and what's still left over there.

## Building Notes
The dtk stuff below tells you how to build, but there are two things it doesn't mention. If you don't want to copy a whole disc image, you can extract the data partition with Dolphin instead ("Extract Entire Partition") so that `orig/SUKE01/sys/main.dol` exists. Also, the first build downloads the toolchain into the build folder, so it takes a while. A successful build ends with `build/SUKE01/main.dol: OK`.

Anyway, back to your regularly secheduled dtk stuff.

Kirby's Return to Dream Land
============================

A work-in-progress decompilation of Kirby's Return to Dream Land.

This repository does **not** contain any game assets or assembly whatsoever. An existing copy of the game is required.

Supported versions:

- `SUKE01`: Rev 0 (USA)
- `SUKK01`: Rev 0 (Korea)

Dependencies
============

Windows
--------

On Windows, it's **highly recommended** to use native tooling. WSL or msys2 are **not** required.  
When running under WSL, [objdiff](#diffing) is unable to get filesystem notifications for automatic rebuilds.

- Install [Python](https://www.python.org/downloads/) and add it to `%PATH%`.
  - Also available from the [Windows Store](https://apps.microsoft.com/store/detail/python-311/9NRWMJP3717K).
- Download [ninja](https://github.com/ninja-build/ninja/releases) and add it to `%PATH%`.
  - Quick install via pip: `pip install ninja`

macOS
------

- Install [ninja](https://github.com/ninja-build/ninja/wiki/Pre-built-Ninja-packages):

  ```sh
  brew install ninja
  ```

[wibo](https://github.com/decompals/wibo), a minimal 32-bit Windows binary wrapper, will be automatically downloaded and used.

Linux
------

- Install [ninja](https://github.com/ninja-build/ninja/wiki/Pre-built-Ninja-packages).

[wibo](https://github.com/decompals/wibo), a minimal 32-bit Windows binary wrapper, will be automatically downloaded and used.

Building
========

- Copy your game's disc image to `orig/SUKE01`.
  - Supported formats: ISO (GCM), RVZ, WIA, WBFS, CISO, NFS, GCZ, TGC
  - After the initial build, the disc image can be deleted to save space.

- Configure:

  ```sh
  python configure.py
  ```

  To use a version other than `SUKE01` (USA), specify it with `--version`.

- Build:

  ```sh
  ninja
  ```

Diffing
=======

Once the initial build succeeds, an `objdiff.json` should exist in the project root.

Download the latest release from [encounter/objdiff](https://github.com/encounter/objdiff). Under project settings, set `Project directory`. The configuration should be loaded automatically.

Select an object from the left sidebar to begin diffing. Changes to the project will rebuild automatically: changes to source files, headers, `configure.py`, `splits.txt` or `symbols.txt`.

![](assets/objdiff.png)
