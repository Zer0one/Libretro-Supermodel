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

## Libretro continuous integration

`.github/workflows/libretro-ci.yml` builds the actual Libretro core rather
than the standalone Supermodel executable. Its desktop matrix currently
covers Linux x86_64, Windows x86_64, macOS ARM64, and macOS x86_64.

Each job starts from a clean checkout, builds through the unified root
`Makefile`, verifies the binary format and target architecture, checks the
required Libretro API exports, and audits runtime dependencies. The uploaded
artifact contains the core, `supermodel_libretro.info`, and the required
system assets under `system/supermodel/`.

Compilation proves that the integration layer remains portable; it does not
replace real-ROM runtime validation. A platform should only be described as
runtime-tested after loading content in a frontend on that platform.

## Deferred standalone options

The first Libretro submission intentionally exposes only settings that affect
emulation compatibility or cannot be represented cleanly by the frontend.
The following standalone options are recorded for later evaluation:

| Option | Current decision |
| --- | --- |
| `Supersampling` | Defer: distinct from, but easily confused with, Libretro internal resolution and frontend downscaling. Define a clear UX before exposing it. |
| `CRTcolors` | Defer to RetroArch shaders unless a need for Supermodel's exact pre-output color transforms is demonstrated. |
| `QuadRendering` | Defer pending renderer capability negotiation. The desktop path currently requests GLSL 4.5 while macOS OpenGL is limited to 4.1. |
| `New3DEngine` / Legacy3D | Do not expose until the legacy renderer is consistently buildable and tested; it is unavailable on Apple and GLES targets. |
| `EmulateDSB` | Defer a separate MPEG music-board switch; muting music is already possible, while disabling emulation is primarily a performance/debug choice. |
| `NoWhiteFlash` | Defer as a renderer workaround; prefer a documented per-game reason rather than a generic default-facing switch. |
| `CrosshairStyle=bmp` | Defer until bitmap asset discovery and portable packaging are specified. Vector crosshairs remain self-contained. |
| `FlipStereo` and audio balance controls | Defer as low-priority output/downmix controls; evaluate what belongs to RetroArch and what must occur before the four-channel-to-stereo mix. |
| Network and true 57.524160 Hz output | Separate projects: network requires multi-cabinet transport, while true-Hz output requires fractional audio generation or resampling. |

## CPU options

`Emulation Threading` represents the three meaningful combinations of the
standalone `MultiThreaded` and `GPUMultiThreaded` settings. `Single Thread`
disables both; `Multi-threaded` runs the sound and drive boards on worker
threads; and the default `Multi-threaded + GPU` mode additionally overlaps
PowerPC emulation with graphics processing. The option is internal to
Supermodel and is independent of RetroArch's frontend-side `Threaded Video`
setting. A content restart is required after changing it.

`Emulated PowerPC Frequency` is the Libretro representation of standalone
Supermodel's `PowerPCFrequency` setting. `Auto` preserves the current upstream
stepping defaults (66, 100, or 166 MHz); the explicit values are emulated CPU
clocks, not host-CPU or frontend performance settings. A content restart is
required after changing the option.

The ARM64 PowerPC JIT is imported from sgiannop's Libretro work and kept behind
the build-time `HAVE_PPC_JIT` capability. It is shown only by targets that
actually compile the backend (Android ARM64, Raspberry Pi 64-bit, and generic
Linux AArch64, plus native macOS ARM64), is labelled experimental, and is
disabled by default. The interpreter remains the correctness reference.

On Apple Silicon the backend allocates its code cache with `MAP_JIT` and uses
`pthread_jit_write_protect_np()` to alternate the current thread between write
and execute access while emitting blocks. This follows the established pattern
used by ARM64 Libretro dynarecs such as Flycast and ParaLLEl N64. It also
requires the frontend executable to carry Apple's `allow-jit` entitlement; if
allocation is denied, the core logs the failure and falls back to the PowerPC
interpreter. Native Intel and osxcross universal builds do not expose this JIT.

No `Frame Skip` core option is exposed. Current standalone Supermodel has no
equivalent setting, and the former Libretro implementation only suppressed the
final frontend presentation while `CModel3::RunFrame()` still performed the
internal render. Frame duplication or dropping therefore remains frontend
policy.

Detailed macOS profiling also shows that `audio_batch_cb` can spend roughly
0–9 ms per frame in frontend pacing. With the experimental ARM64 JIT enabled,
the measured engine cost falls to about 5.4 ms in Daytona 2 and 4.9 ms in Sega
Rally 2, while callback-inclusive capacity remains around 84 FPS. Do not treat
that capacity as pure emulator compute capacity: audio/frontend pacing is now
the main measured constraint. Its investigation is the highest-priority
follow-up, and any synchronization change must preserve the currently clean,
crackle-free 60 Hz output.

A 90-second Daytona 2 interpreter run measured 7.93 ms in the PowerPC and
7.95 ms in the engine, versus 5.37 and 5.43 ms respectively in the comparable
JIT run. This is a roughly 32% reduction in CPU/engine time and raises measured
engine capacity from about 126 to 184 FPS. Overall callback capacity improves
only from about 78 to 84 FPS because the frontend consumes much of the freed
frame budget in audio/pacing waits.

## Current validation and limitations

The Libretro timing contract intentionally follows standalone Supermodel's
default 60 Hz mode: video is reported as 60 FPS, audio as 44100 Hz, and each
frontend frame consumes 735 stereo samples. VSync remains frontend-owned. The
optional standalone true-Hz mode (57.524160 Hz) is not exposed because it also
requires fractional audio generation or resampling to remain synchronized.

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
- visible boot of `dayto2pe` beyond its network-board check with standalone
  Supermodel NVRAM configured for a single cabinet;
- successful `MAP_JIT` allocation and sustained ARM64 JIT execution in Daytona
  2 and Sega Rally 2, with no evident gameplay, graphics, or audio regressions;
- service-mode validation of the dedicated fishing profile: rod and fishing
  stick axes, analog `00-FF` reel speed, cast, and select; the Japan Standard
  `getbass` set additionally exposes and correctly reads the tension axis;
- exported `retro_init`, `retro_load_game`, `retro_run`, save-state, and unload
  entry points.

Still requiring validation or implementation:

- investigate `audio_batch_cb`/frontend pacing, including RetroArch's
  unsupported rate-control warning, without regressing clean 60 Hz audio;
- visual correctness and extended gameplay testing;
- Sega Bass Fishing / Get Bass extended gameplay testing beyond the validated
  service-mode input checks;
- audio, controls, force feedback, and save states;
- Linux, Windows, Android, and other advertised build targets;
- broader PPC JIT compatibility testing on macOS ARM64, plus runtime validation
  on Android ARM64, Raspberry Pi 64-bit, and generic Linux AArch64; compilation
  alone does not establish game compatibility;
- network-board emulation for multi-cabinet play: the current Libretro
  placeholder reports the board as detached. Single-cabinet operation works
  when selected in the game's machine settings and stored in NVRAM.

Libretro save RAM is canonical and is persisted by the frontend as a fixed-size
`.srm`. Its payload uses the same block container as standalone Supermodel
NVRAM, with zero padding after the final block. A native `<rom-set>.nv` in the
frontend save directory is imported only when the frontend supplied no `.srm`
data; when both sources exist, `.srm` wins and the decision is logged. The core
never modifies `.nv`; if native import fails, default NVRAM is initialized and
persisted to a new `.srm`. Older headerless `.srm` files from the initial
Libretro port remain readable.
