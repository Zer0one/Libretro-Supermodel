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

## Renderer capabilities

Renderer options are controlled by build capabilities rather than runtime
platform-name checks:

| Define | Core behavior |
| --- | --- |
| `HAVE_LEGACY3D` | Exposes runtime selection between New3D and experimental Legacy3D and negotiates a desktop OpenGL compatibility context for the latter. Forced `RENDERER=legacy` builds remain fixed to Legacy3D. |
| `HAVE_QUAD_RENDERING` | Exposes New3D native-quad rendering and requests an OpenGL 4.5 core context when enabled. |
| `HAVE_CRT_COLOURS` | Exposes Supermodel's native New3D pre-output colour/gamma transforms. |
| `HAVE_SUPERSAMPLING` | Exposes Supermodel's native 1x-8x supersampling pass on desktop OpenGL builds. |

The root Makefile derives these defines from the renderer sources and graphics
API supported by each build. A future macOS or GLES implementation should
enable the corresponding capability only after its renderer path and Libretro
context negotiation are actually supported. Legacy3D deliberately carries a
frontend-crash warning: the compatibility profile and fixed-function entry
points cannot be made safe through a fallback after context creation.

## Deferred standalone options

The first Libretro submission intentionally exposes only settings that affect
emulation compatibility or cannot be represented cleanly by the frontend.
The following standalone options are recorded for later evaluation:

| Option | Current decision |
| --- | --- |
| `NoWhiteFlash` | Defer as a renderer workaround; prefer a documented per-game reason rather than a generic default-facing switch. |
| `CrosshairStyle=bmp` | Defer until bitmap asset discovery and portable packaging are specified. Vector crosshairs remain self-contained. |
| `FlipStereo` and audio balance controls | Defer as low-priority output/downmix controls; evaluate what belongs to RetroArch and what must occur before the four-channel-to-stereo mix. |
| True 57.524160 Hz output | Requires fractional audio generation or resampling; the current core deliberately retains standalone's default 60 Hz cadence. |

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

Detailed macOS profiling shows that `audio_batch_cb` can spend roughly 0–9 ms
per frame in frontend pacing. RetroArch 1.22.2's synchronous audio path accepts
each complete Libretro batch and may block while the output FIFO drains; this
variable time therefore completes the 16.67 ms frame budget rather than
representing additional Supermodel audio emulation. With the experimental
ARM64 JIT enabled, the measured engine cost falls to about 5.4 ms in Daytona 2
and 4.9 ms in Sega Rally 2, while callback-inclusive capacity remains governed
largely by frontend pacing. Do not treat that capacity as pure emulator compute
capacity, and do not replace the synchronous path merely to reduce the timing
overlay value: the current output is clean and stably paced at 60 Hz.

The Libretro batch callback returns the number of frames processed. RetroArch
1.22.2 currently returns the complete requested count after routing the batch
through its audio pipeline, but the core still preserves any unaccepted frames
in its ring buffer for compatibility with other conforming frontends. A partial
submission is reported once at shutdown if it occurred during the session.

RetroArch audio rate control requires a driver that exposes buffer occupancy.
The SDL2 audio driver does not implement that interface and emits `Rate control
was desired, but driver does not support needed features`; macOS `coreaudio3`
does implement it and removes the warning. This is a frontend audio-driver
capability, not a Supermodel core option. The controller driver is independent
and may remain SDL2.

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
- automated Save State save/load cycles for Daytona 2 PE, Sega Rally 2, and
  Ocean Hunter, including a new-session load, legacy-state compatibility,
  cross-game rejection, and checksum-corruption rejection; interactive loads
  in all three games also restored their relevant video, audio, controls, and
  force-feedback state without an observed anomaly;
- exported `retro_init`, `retro_load_game`, `retro_run`, save-state, and unload
  entry points.

Still requiring validation or implementation:

- visual correctness and extended gameplay testing;
- extended audio, controls, force-feedback, and Save State coverage across more
  games;
- Linux, Windows, Android, and other advertised build targets;
- broader PPC JIT compatibility testing on macOS ARM64, plus runtime validation
  on Android ARM64, Raspberry Pi 64-bit, and generic Linux AArch64; compilation
  alone does not establish game compatibility;
- network-board emulation for multi-cabinet play: the current Libretro
  placeholder reports the board as detached. Automatic initial NVRAM setup
  selects Single/No Link for the known affected revisions; actual linked-cabinet
  transport remains unimplemented.

Libretro save RAM is canonical and is persisted by the frontend as a fixed-size
`.srm`. Its payload uses the same block container as standalone Supermodel
NVRAM, with zero padding after the final block. A native `<rom-set>.nv` in the
frontend save directory is imported only when the frontend supplied no `.srm`
data; when both sources exist, `.srm` wins and the decision is logged. The core
never modifies `.nv`; if native import fails, default NVRAM is initialized and
persisted to a new `.srm`. With `Automatic Initial NVRAM Setup` enabled, the
core instead supplies a game-generated 93C46 EEPROM template for known Daytona
USA 2, Scud Race, Dirt Devils, and Star Wars Trilogy revisions whenever no
valid save source exists. These templates configure Single/No Link or disable
unsupported lever feedback as appropriate. They include the checksums written
by each game's Service menu; backup RAM is not templated. This is a one-time
initialization: an existing `.srm` or valid `.nv` is never patched, and deleting
the `.srm` explicitly requests regeneration. Older headerless `.srm` files from
the initial Libretro port remain readable.

### Model 3 EEPROM checksums

The 93C46 device does not impose a checksum. Each game writes and validates its
own 64-word EEPROM layout. Analysis of first-boot, Service-configured, embedded
template, and standalone NVRAM samples identified three checksum families. The
word values below are the 16-bit values seen by the emulated machine; bytes in
each word are therefore processed most-significant byte first.

| EEPROM format | Checksum | Covered logical bytes |
| --- | --- | --- |
| `M3SEGA`, format word `0xA3xx` | Sega CRC-CCITT variant described below, stored in word 3 | 12 through 69 |
| Other `M3SEGA` layouts | CRC-16/XMODEM (`poly=0x1021`, `init=0x0000`, `xorout=0x0000`), stored in word 3 | 12 through 69 |
| Tagged `M3SEGA SRC2` and `M3SEGA SWTA` layouts | CRC-16/GENIBUS (`poly=0x1021`, `init=0xFFFF`, `xorout=0xFFFF`), stored in word 5 | 16 through 127 |

The `0xA3xx` games use the standard 256-entry `0x1021` lookup table but a
non-standard 32-bit working state. The game routine is equivalent to the
following pseudocode, where `table` contains the normal big-endian CRC-CCITT
table and all arithmetic is 32-bit:

```text
state = 0xDEBDEB00
for byte in eeprom[12..69]:
    index = rotl32(state, 9) & 0x1FE
    state = ((state ^ (table[index / 2] << 8)) | byte) << 8
index = rotl32(state, 9) & 0x1FE
state ^= table[index / 2] << 8
checksum = rotl32(state, 24) & 0xFFFF
```

This classification reproduced all 84 checksum-bearing samples available
during analysis: 48 XMODEM, 23 Sega-variant, and 13 tagged GENIBUS images.
Four Virtua Fighter 3 samples use an older duplicated `SEGA` layout and require
separate analysis; two Fighting Vipers 2 smoke-test images remained erased.
Country and Link/Cabinet options must additionally map the corresponding fields
per game or game family and update redundant copies or sequence fields where
present; checksum support alone is not sufficient to patch those settings
safely.

For Daytona USA 2, controlled Service-menu samples locate `Country` in the
high byte of EEPROM words 12 and 41 (primary and redundant settings copies):

| Country | Stored value |
| --- | --- |
| Japan | `0x01` |
| USA | `0x02` |
| Export | `0x03` |
| Australia | `0x04` |
| Korea | `0x05` |

The settings sequence counter is duplicated in words 6 and 35. Entering and
Saving through the Service menu also normalized unrelated fields in the
original template. The game-aware NVRAM settings implementation therefore does
not copy those incidental changes and updates only
both Country copies and the checksum. It leaves the sequence counter unchanged
because both redundant settings copies are replaced atomically.

Additional controlled Daytona USA 2 samples locate the Link, Car Number, and
Cabinet settings in the same two settings copies:

| Setting | Primary / redundant words | Stored value |
| --- | --- | --- |
| Link: Single | 15 / 44, high byte | `0x00` |
| Link: Master | 15 / 44, high byte | `0x01` |
| Link: Slave | 15 / 44, high byte | `0x02` |
| Link: Live | 15 / 44, high byte | `0x03` |
| Car Number | 15 / 44, low byte | displayed number minus one (`0x00` through `0x0F`) |
| Cabinet: Deluxe | 16 / 45, high byte | `0x00` |
| Cabinet: Twin | 16 / 45, high byte | `0x01` |

The low byte of words 16 and 45 was unchanged in the Cabinet samples and must
therefore be preserved. Each Service save advanced both copies of the sequence
counter by one; samples matching the base value (`Slave`, car 1, and `Twin`)
confirm the base configuration rather than introducing a third encoding.

`System > NVRAM Settings` is disabled by default. Enabling it dynamically
exposes only the fields supported by the loaded game family. Each field
defaults to `Keep Current`; selected values are applied through Supermodel's
normal NVRAM block interface after the frontend `.srm` or native `.nv` has been
loaded. The Daytona USA 2 family currently exposes Country, Link Mode, Car
Number, and Cabinet Type. The core preserves unrelated bits, writes both
settings copies, regenerates CRC-16/XMODEM, and does not alter backup RAM.

## Libretro linked-cabinet transport

The Libretro backend registers `RETRO_ENVIRONMENT_SET_NETPACKET_INTERFACE` in
`retro_init()`. This lets RetroArch manage peer discovery and transport while
the core sends the actual emulated network-board data. The bundled
`libretro.h` predates the API, so `LibretroNetPacket.h` backports only the
official compatible declarations instead of replacing the entire vendored
libretro-common snapshot.

`CLibretroNetBoard` is independent from standalone `CSimNetBoard`: standalone
continues to use its SDL_net TCP ring. The first Libretro protocol version is
deliberately limited to two Type 1 cabinets and currently recognizes the
Daytona USA 2 and Scud Race families. RetroArch client 0 must be the Model 3
Master and client 1 the Slave. After a bidirectional role handshake, each core
sends one reliable packet per emulated network-board frame. For two nodes this
replaces the TCP ring's returned local segment with a local copy, preserving
the same communication-RAM order while avoiding a redundant packet.

This exchange deliberately remains lockstep. The official netpacket API's
`RETRO_NETPACKET_FLUSH_HINT` already flushes without blocking, and
`retro_netpacket_poll_receive_t` explicitly supports a short bounded receive
loop; the backend uses both. Standalone `CSimNetBoard` likewise sends and then
waits for the corresponding segment every network-board frame. RetroArch's
ordinary Netplay input prediction and rollback do not apply to custom
netpacket payloads, so replacing the wait with stale or predicted cabinet data
would change the emulated protocol rather than optimize its transport.

A real wired IPv4 Daytona USA 2 link between RetroArch 1.22.2 on Batocera
x86-64 and RetroArch 1.21.0 on macOS ARM64 remained synchronized without
timeouts. A controlled one-way 100 ± 25 ms delay kept the logical link alive
but reduced the Batocera instance to roughly 14 FPS. This confirms that the
current mode is intended for a stable low-latency LAN; the 250 ms wait is only
a bounded failure guard and must not be interpreted as a performance target.

The transport uses explicit little-endian protocol headers, validates the game
family, role, segment size, frame number, and protocol version, and performs a
short bounded receive poll inside `retro_run()`. A four-frame ready barrier
prevents one frontend from entering the first blocking exchange while its peer
is still completing the Netplay handshake. Localhost tests with isolated
Master/Slave NVRAM reached normal linked gameplay in both Daytona USA 2 Power
Edition and Scud Race; Scud Race completed synchronized race startup and
gameplay without a timeout or visible divergence.

Expansion to more than two cabinets requires generalizing machine enumeration
and segment ordering. Games using Supermodel's type-2 network-board protocol
(Le Mans 24, Virtual-On 2, and Dirt Devils) require their separate status and
playable/relay index layout before they can be enabled.

Libretro Save States use standalone Supermodel's current version-6 header and
ROM-set identifier before the normal subsystem blocks. This rejects states
from an incompatible engine format or different game before any emulator
memory is modified. A final Libretro-only integrity block contains a CRC32 of
the complete preceding payload, allowing padded truncation and in-place data
corruption to be detected even when a frontend supplies the expected buffer
size. Standalone Supermodel safely ignores this additional named block. The
core accepts standalone-compatible states without the integrity block and the
older headerless Libretro layout, logging which compatibility path was used.

Before loading, the core compares every block name and payload size against a
layout generated from the running game. Memory reads are bounded to the
selected block, and buffer overflow or underflow now propagates failure through
`retro_serialize()` or `retro_unserialize()` instead of returning success after
a partial operation.
