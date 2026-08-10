# Libretro Port Maintenance

This document records the ancestry and maintenance model of the modern
Supermodel Libretro port. The goal is to make updates reviewable for the
official Libretro repository and easy to exchange with the developers whose
work made the port possible.

## Repository ancestry

The `supermodel-modern` branch deliberately preserves three sources:

| Role | Repository | Recorded revision |
| --- | --- | --- |
| Historical Libretro lineage | `libretro/supermodel` (forked as `Zer0one/supermodel`) | `44ba6a72c820fec474c2b3a748ec409c8f8e2090` |
| Emulator engine | `trzy/Supermodel` (`upstream`) | `24d2ffcfc7f14229337f05f4920fe26b56633d9d` |
| Modern Libretro frontend | `sgiannop/Libretro-Supermodel` | `1c094999664b23876323a50815022bad1f353a04` |

The first modernization commit is a real two-parent merge. Its first parent is
the historical Libretro branch, its second parent is the current Supermodel
revision, and its tree is exactly the Supermodel upstream tree. This avoids a
source dump with no ancestry and lets later engine updates use ordinary Git
merges.

The next commit imports sgiannop's frontend-owned files without modifying them.
Adaptations required by the newer engine are kept in later commits. Reviewers
can therefore distinguish existing port work from new compatibility changes,
and sgiannop can cherry-pick useful adaptation commits without re-importing his
own frontend.

## Ownership boundaries

Keep future changes within these boundaries whenever practical:

- `Src/OSD/libretro/`, the root `Makefile`, `jni/`, and
  `supermodel_libretro.info` are the Libretro integration layer.
- The rest of `Src/` follows `trzy/Supermodel`. Engine changes needed only by
  Libretro should be small, conditional on `SUPERMODEL_OSD_LIBRETRO`, and kept
  in focused commits.
- Third-party snapshots such as `libretro-common` and `deps/ugui` should be
  updated separately from engine synchronization.

These boundaries are guidelines rather than a claim of independent ownership:
the imported frontend remains derived from and credited to sgiannop's work.

## Updating the Supermodel engine

The configured `upstream` remote points to `https://github.com/trzy/Supermodel.git`.
After the initial ancestry merge, normal update merges are sufficient:

```sh
git fetch upstream
git switch supermodel-modern
git merge --no-ff upstream/master
```

Resolve engine changes in the engine-facing bridge first, then rebuild every
supported platform. Do not replace the engine tree wholesale or squash the
upstream merge: either action would discard the relationship this branch was
created to preserve.

## Following sgiannop's frontend

Adding a read-only reference remote is optional but useful during development:

```sh
git remote add sgiannop https://github.com/sgiannop/Libretro-Supermodel.git
git fetch sgiannop
git log --oneline 1c094999664b23876323a50815022bad1f353a04..sgiannop/master
```

Review new commits one at a time. Cherry-pick frontend fixes when they apply
cleanly, then place any adaptation to the newer engine in a following commit.
This preserves authorship and makes the result useful in both directions.

Conversely, sgiannop does not need the import commit, because it contains his
own work. He can fetch this repository and cherry-pick only the focused
post-import compatibility commits that are useful to his branch.

## Pull request policy

The primary integration target is `libretro/supermodel`. Pull requests should:

1. Credit `sgiannop/Libretro-Supermodel` prominently and name the exact source
   revision used.
2. Preserve imported frontend work and new adaptations as separate commits.
3. Describe the exact Supermodel upstream revision and retain its merge
   ancestry.
4. List tested hosts, architectures, frontends, games, renderers, input paths,
   audio, save states, and known limitations.
5. Avoid claiming platform support that has not been revalidated after an
   upstream update.

## Current validation and limitations

Validated on macOS ARM64:

- clean compilation and linking with `make platform=osx`;
- Mach-O ARM64 dynamic library output;
- dynamic loading without SDL or SDL_net dependencies;
- loading by RetroArch 1.22.2 with VFS v3, core options v2, hardware OpenGL,
  XRGB8888, and full-path content negotiation;
- loading and CRC validation of the real `dayto2pe` ROM set through the
  current upstream `Games.xml`;
- discovery of `Games.xml` and `Music.xml` in the preferred flat
  `system/supermodel` directory without creating a `Supermodel.ini`;
- negotiation of an OpenGL 4.1 core profile, successful creation of the
  Libretro and Real3D framebuffers, and sustained execution of the frame loop;
- visible boot of `dayto2pe` up to its network-board check;
- exported `retro_init`, `retro_load_game`, `retro_run`, save-state, and unload
  entry points.

Still requiring validation or implementation:

- visual correctness and extended gameplay testing;
- audio, controls, force feedback, and save states;
- Linux, Windows, Android, and other advertised build targets;
- PPC JIT integration on supported architectures;
- network-board emulation: the current Libretro placeholder reports the board
  as detached, so `dayto2pe` stops at `Network Board Not Present`. A future
  core option should default to an in-process single-cabinet simulation while
  preserving the upstream `Games.xml` metadata;
- frame-skip behavior against the current `CModel3::RunFrame()` interface.
