# Supermodel (Sega Model 3) - Libretro Port (Modernized)

> [!IMPORTANT]
> This port is under active development. The current macOS ARM64 build has
> passed compile, link, dynamic-load, Libretro symbol, real-ROM loading, and
> initial frame-execution checks; gameplay quality and the other advertised
> platforms still need to be revalidated against the current Supermodel engine.

This branch combines three explicitly preserved lines of development:

- the historical [`libretro/supermodel`](https://github.com/libretro/supermodel)
  core lineage;
- the current [`trzy/Supermodel`](https://github.com/trzy/Supermodel) engine;
- the modern Libretro frontend developed by
  [`sgiannop/Libretro-Supermodel`](https://github.com/sgiannop/Libretro-Supermodel),
  imported at commit `1c094999664b23876323a50815022bad1f353a04`.

Most of the modern frontend implementation comes from sgiannop's work. The
subsequent commits in this branch adapt that frontend to the current upstream
engine while keeping the integration changes separate and reviewable. See
[`PORTING.md`](PORTING.md) for provenance, synchronization, and contribution
guidance.

## 🚀 Key Improvements
- **Unified Makefile:** Single build configuration supporting 6 platforms (Linux, Windows, macOS, Android, RPi64, aarch64) following libretro/skeletor standards.
- **Platform Auto-Detection:** Automatic platform detection with sensible defaults; platform-specific source filtering for incompatible features.
- **Native Libretro Audio:** Removed legacy SDL audio dependency in favor of native `audio_batch_cb` synchronization at a fixed 60 Hz cadence.
- **C++17 Migration:** Replaced legacy SDL-based threading and synchronization with native C++17 `std::mutex`, `std::lock_guard`, and atomic operations.
- **Ubuntu 24.04 Compatibility:** Fixed header conflicts and link-time errors present in the original codebase specifically for modern GCC versions.
- **Synchronous A/V Timing:** Matches standalone Supermodel's default 60 Hz cadence and 735-sample stereo audio packets; RetroArch owns final A/V synchronization.
- **Improved Input Mapping:** Full support for Analog/Digital gamepads and keyboard out of the box with improved deadzone handling.
- **Configurable Service & Test Buttons:** Service and Test buttons are now mappable through the RetroArch input configuration.
- **Force Feedback / Rumble:** Full force feedback support for steering wheel games via the Libretro rumble interface.
- **True Widescreen:** Expands the 3D horizontal field of view into a native
  16:9 framebuffer, with an optional wide lower-background layer. Plain 4:3
  stretching remains the frontend's responsibility.
- **Libretro Portability:** Remapped configuration, NVRAM, and asset paths to follow official Libretro standards (`system` and `save` directories).
- **Validated Save States:** Uses the current standalone format metadata plus
  Libretro integrity checking, rejects incompatible/corrupt states before
  modifying the machine, and remains compatible with older core states.
- **No External GL Dependency:** GLEW replaced with `glsym` from libretro-common — no system GL extension library required on any platform.
- **Android Support:** Full NDK integration with architecture-specific optimization (arm64, arm with NEON, x86_64, x86) and OpenGL ES 3.0.
- **macOS Universal Binary:** Builds for both Intel (x86_64) and Apple Silicon (arm64) via osxcross with automatic CPU tuning.
- **Raspberry Pi Optimized:** GLES3 rendering with CPU-specific tuning for RPi5 (Cortex-A76), RPi4 (Cortex-A72), and generic aarch64.
- **Windows Support:** Full cross-platform support with dedicated Windows build targets using MinGW — no vendored prebuilt libraries required.

## 📂 System assets and configuration

Place the engine data files in the RetroArch system directory:

* **Preferred path:** `[RetroArch System Directory]/supermodel/`
* **Files:**
    * `Games.xml` is required. It describes Model 3 games, hardware, ROM files,
      regions, and CRCs, and is therefore engine data rather than a user
      preference file.
    * `Music.xml` is optional and enables the corresponding music metadata.
    * `Supermodel.ini` is an optional expert override. If present, it is read
      before core options are applied. The core never creates or modifies it.

For compatibility with the initial port, files are also discovered in
`[RetroArch System Directory]/supermodel/Config/`. New installations should
use the preferred flat path. Without `Games.xml`, the core cannot identify or
load a game.

Normal settings belong to RetroArch: use core options for video, audio, CPU,
and control-layout choices; input remaps for controller bindings; and the
frontend save directory for NVRAM. Core options take precedence over an
optional `Supermodel.ini`.

## Video geometry

`Widescreen Mode` reproduces Supermodel's native widescreen behavior instead
of stretching the 4:3 image:

* `Disabled` renders the original 496x384 view.
* `Widescreen` expands full-screen 3D viewports horizontally inside a 16:9
  framebuffer (683x384 at native resolution), while keeping 2D layers at their
  original geometry.
* `Widescreen + Wide Background` also stretches the lower 2D background layer
  to fill the side areas. HUD and upper overlays retain their original aspect.

Supermodel's standalone `Stretch` setting is intentionally not exposed: final
4:3-to-16:9 stretching is already provided by RetroArch's aspect-ratio and
scaling controls. True widescreen renders about 37.7% more horizontal pixels
than the native 4:3 mode, so its performance should be measured separately.
Changes to `Widescreen Mode` take effect after restarting the content, matching
the renderer-initialization semantics of standalone Supermodel.

## Renderer options

Desktop builds that include both Supermodel renderers expose `3D Renderer`.
`New3D` remains the default. `Legacy3D` is experimental, uses the desktop
OpenGL compatibility profile, and may crash the frontend or fail to initialize
when the selected video driver does not provide the required fixed-function
OpenGL support. The option is omitted when Legacy3D is not part of the build,
including current macOS and normal GLES builds. This capability-based check
allows a future platform port to expose it without adding a platform-name
exception.

`Quad Rendering` is available only on builds that can negotiate an OpenGL 4.5
core context. It uses New3D's geometry-shader path to render Model 3
quadrilaterals directly and is ignored by Legacy3D. `CRT Colour` applies
Supermodel's own pre-output colour and gamma transform; it is separate from a
RetroArch shader and also applies only to New3D. All three settings require a
content restart because they affect renderer or OpenGL-context creation.

`Supersampling` exposes standalone Supermodel's native 1x-8x supersampling
pass on supported desktop OpenGL builds. It is applied on top of `Internal
Resolution`: 2x evaluates four samples per output pixel, 3x evaluates nine,
and 8x evaluates 64. The combined scale can consume substantial GPU time and
memory, and changes require restarting the content.

At resolutions above native, `2D Layer Upscaling Filter` selects Supermodel's
own `UpscaleMode` for tile layers before they are composited with the 3D scene.
At 496x384 the engine deliberately uses nearest-neighbor filtering regardless
of this option.

`SCSP DSP Engine` defaults to the current MAME-derived implementation. The
legacy ElSemi engine is retained as a compatibility choice for titles such as
Fighting Vipers 2; this is standalone's `LegacySoundDSP` setting. Both this
setting and the 2D filter require a content restart. Sound and DSB music volume
follow standalone's full 0–200% range. The separate standalone `EmulateDSB`
switch is intentionally not exposed.

## Timing and synchronization

The core reports `60 FPS` video and `44100 Hz` stereo audio to the frontend,
and consumes one fixed packet of 735 audio samples per `retro_run`. This is the
same cadence used by standalone Supermodel by default. The Model 3 hardware
refresh is approximately 57.524160 Hz, but upstream deliberately defaults to
60 Hz because true-Hz output can judder on ordinary 60 Hz displays.

The core does not expose its own VSync setting: the Libretro frontend owns the
display swapchain, video presentation, audio synchronization, and final sample
rate conversion. A future true-Hz mode would require a matching fractional
audio path (766/767 samples per frame), not just a different advertised FPS.

For objective performance checks, enable `Frame Timing Overlay`. Besides the
engine's PPC, renderer, GPU, synchronization and sound timings, it shows
61-frame averages for the engine, frontend audio submission, overlay, final
blit, miscellaneous core work, frontend presentation, total `retro_run`, the
worst frame, actual frontend cadence, engine capacity, and callback capacity. At 60 Hz,
sustained `retro_run` time must remain
below the 16.67 ms frame budget; `Present` may include the frontend's VSync wait.
`Actual` measures the real cadence between calls from the frontend, while
`Engine cap` is derived from Supermodel's frame execution alone. `Callback cap`
is the theoretical rate implied by all time spent inside `retro_run` and is not
the displayed frame rate. `Audio/pacing` may include intentional frontend
waiting when RetroArch audio synchronization is enabled.

For broad boot testing, `Scripts/libretro_smoke_test.py` enumerates the sets in
`Games.xml` and launches each available ROM in a separate temporary RetroArch
environment. `--seconds` is converted to a deterministic `--max-frames` count,
so it measures emulated time even when `--fast-forward` is enabled. On macOS,
the script records the actual RetroArch window through ScreenCaptureKit and
uses FFmpeg to extract the final video frame. Results include one named `.mov`,
final-frame `.png`, and log per set, generated isolated `.srm` files, and
CSV/JSON summaries containing missing ROMs, timeouts, non-zero exits, and crash
signals. These results are persistent and default to a timestamped folder under
`~/Documents/RetroArch/supermodel-smoke/`; only each game's disposable RetroArch
runtime environment uses temporary storage. The calling terminal needs macOS
Screen Recording permission. Run the script with `--help` for platform paths
and filters.

Controller mappings and RetroArch input labels are selected automatically from
the control signature declared by the loaded game. See
[Libretro control profiles](CONTROL_PROFILES.md) for the complete catalog and
the fallback rules.

NVRAM is normally persisted by the frontend as `<content>.srm`. To import a
standalone Supermodel save, place `<rom-set>.nv` directly in the frontend save
directory. The core reads `.nv` only when no `.srm` data was supplied. If both
are present, `.srm` takes precedence and the ignored `.nv` path is reported in
the log. `Automatic Initial NVRAM Setup` is enabled by default. When neither a
frontend `.srm` nor a valid native `.nv` exists, it initializes known Daytona
USA 2, Scud Race, Dirt Devils, and Star Wars Trilogy revisions with the machine
settings needed to boot without unsupported cabinet links or lever feedback.
Only the initial EEPROM is supplied; backup RAM starts empty. Existing saves
are never modified, and deleting a game's `.srm` regenerates the initial setup
on its next launch. Disable the option before first launch to retain the game's
unconfigured factory defaults. The core never writes or overwrites native
`.nv` files.

`System > NVRAM Settings` provides optional game-aware editing and is disabled
by default. When enabled, only settings known for the currently loaded game or
game family are displayed. Every field defaults to `Keep Current`, so merely
enabling the feature does not modify a save. Daytona USA 2 and Power Edition
expose Country, Link Mode, Car Number, and Cabinet Type. Scud Race and Scud
Race Plus expose Link Mode, Car Number, and Cabinet Type; Country is omitted
because that family uses a different encoding. Changes are written to the
frontend `.srm` with the required redundant copy and checksum; restart the
content before expecting the game to use the new machine setting.

### Experimental linked cabinets

`System > Network Board (Experimental)` connects two supported Type 1 cabinets
through RetroArch Netplay and Libretro's netpacket API. It is disabled by
default and currently supports the Daytona USA 2 and Scud Race families with
exactly two players. The standalone emulator's SDL_net transport is not used
or modified.

Configure both instances before starting Netplay:

- enable `NVRAM Settings` and `Network Board (Experimental)`;
- set the RetroArch host to `Link Mode: Master`, normally with `Car Number: 1`;
- set the client to `Link Mode: Slave` with a different car number;
- restart the content on both sides, then host/join the same content through
  RetroArch Netplay.

The core validates opposite cabinet roles and exchanges the Model 3 network
segments as reliable ordered packets. RetroArch disables pause, fast-forward,
rewind, and Save State loading while the linked session is active. More than
two cabinets, the remaining Type 1 families, and Type 2 network-board games
remain future work.

Use a stable, low-latency wired LAN. The emulated cabinets exchange one network
segment in lockstep, matching standalone Supermodel's send/receive behavior;
network latency and jitter therefore stall emulation rather than being hidden
by RetroArch's normal input rollback. A 250 ms bounded wait detects a broken
link, but it is a safety timeout rather than a supported latency target.

## 🛠 Build Instructions

**Unified Makefile System:** This core uses a single unified `Makefile` supporting 6 platforms:
- **Linux/Unix** (native)
- **Windows** (MinGW cross-compile or native MSYS2)
- **macOS** (osxcross universal binary: x86_64 + arm64)
- **Android** (NDK: arm64, arm, x86_64, x86)
- **Raspberry Pi 64-bit** (RPi5, RPi4, generic aarch64)
- **Generic aarch64** (ARM64 Linux)

### Quick Start (All Platforms)

```bash
# Linux (default platform)
make -j$(nproc)

# Windows (cross-compile from Linux)
make platform=win -j$(nproc)

# macOS (osxcross from Linux)
make platform=osx -j$(nproc)

# Android (all architectures default to arm64)
make platform=android -j$(nproc)

# Raspberry Pi 64-bit
make platform=rpi64 -j$(nproc)

# Generic aarch64
make platform=aarch64 -j$(nproc)

# Debug build (any platform)
make DEBUG=1 platform=<platform> -j$(nproc)

# Clean build artifacts
make clean
```

---

### Linux (Native Build)

#### 1. Install Dependencies (Ubuntu/Debian)
```bash
sudo apt update
sudo apt install build-essential libgl1-mesa-dev libglu1-mesa-dev zlib1g-dev
```

#### 2. Compile
```bash
make -j$(nproc)
```

#### 3. Install
```bash
cp supermodel_libretro.so ~/.config/retroarch/cores/
```

---

### Windows

You can build the core either natively on Windows or via cross-compilation from Linux.

#### Option A: Native Windows Build (MSYS2)

1. **Install MSYS2**: Download and install from [msys2.org](https://www.msys2.org/).
2. **Open the "MSYS2 MinGW 64-bit" terminal** (avoid the default MSYS terminal).
3. **Install Dependencies**:
    ```bash
    pacman -S mingw-w64-x86_64-toolchain mingw-w64-x86_64-make mingw-w64-x86_64-zlib
    ```
4. **Compile**:
    ```bash
    make platform=win -j%NUMBER_OF_PROCESSORS%
    ```

#### Option B: Cross-Compilation (from Linux)

1. **Install the MinGW-w64 toolchain**:
    ```bash
    sudo apt update
    sudo apt install binutils-mingw-w64-x86-64 g++-mingw-w64-x86-64 libz-mingw-w64-dev
    ```
2. **Compile**:
    ```bash
    make platform=win -j$(nproc)
    ```

**Output:** `supermodel_libretro.dll` → Copy to RetroArch `cores/` directory.

---

### macOS (Intel & Apple Silicon Universal Binary)

This core generates a universal binary supporting both Intel (x86_64) and Apple Silicon (arm64 M1/M2/M3+).

#### Option A: Native macOS Build

If building on a macOS system with Xcode installed:

```bash
# Install dependencies via Homebrew
brew install zlib

# Compile (generates universal binary)
make platform=osx -j$(sysctl -n hw.ncpu)

# Install
cp supermodel_libretro.dylib ~/.config/retroarch/cores/
```

#### Option B: Cross-Compilation from Linux (Recommended for CI/CD)

1. **Install osxcross toolchain** (to `/opt/osxcross`):
    ```bash
    sudo mkdir -p /opt
    sudo git clone https://github.com/tpoechtrager/osxcross /opt/osxcross
    cd /opt/osxcross
    
    # Download macOS SDK (follow osxcross documentation for MacOSX12.0.sdk)
    wget -nc https://github.com/rtrussell/osxcross-build/releases/download/12.0/MacOSX12.0.sdk.tar.xz
    mv MacOSX12.0.sdk.tar.xz tarballs/
    
    # Build osxcross
    sudo ./build.sh
    ```

2. **Compile** (Makefile auto-detects osxcross):
    ```bash
    # Universal binary (x86_64 + arm64)
    make platform=osx -j$(nproc)
    
    # With debug symbols
    make platform=osx DEBUG=1 -j$(nproc)
    ```
    
    The Makefile automatically:
    - Detects osxcross at `/opt/osxcross`
    - Uses `o64-clang`/`o64-clang++` compilers
    - Configures SDK and deployment target
    - Generates universal binary for both architectures
    
    To override osxcross location:
    ```bash
    make platform=osx OSXCROSS_ROOT=/custom/path -j$(nproc)
    ```

3. **Transfer to macOS** (if building on Linux):
    ```bash
    scp supermodel_libretro.dylib user@mac:~/Downloads/
    # On Mac: cp ~/Downloads/supermodel_libretro.dylib ~/.config/retroarch/cores/
    ```

**Build Details:**
- **Deployment Target:** macOS 10.15 (Catalina) and newer
- **Architecture:** Universal binary (x86_64 + arm64)
- **Renderer:** New3D with OpenGL 4.1 (Legacy3D and Quad Rendering excluded)
- **Build Time:** ~90 seconds on 4 cores

---

### Android (NDK)

Requires Android NDK. The Makefile checks `~/Android/Sdk/ndk/28.2.13676358` by default.

```bash
# arm64 (default and recommended)
make platform=android -j$(nproc)

# 32-bit ARM (armv7-a with NEON)
make platform=android arch=arm -j$(nproc)

# x86_64
make platform=android arch=x86_64 -j$(nproc)

# x86 (32-bit)
make platform=android arch=x86 -j$(nproc)

# Custom NDK path
NDK_ROOT=/path/to/ndk make platform=android -j$(nproc)
```

**Build Features:**
- Automatic NEON optimization for ARM architectures
- Position-independent code (PIC) for all binaries
- Static C++ runtime linking
- API level 24 (NDK Clang toolchain)
- GLES 3.0 rendering support

**Output:** `supermodel_libretro_android.so` → Copy to Android RetroArch cores directory (usually `/data/data/com.retroarch/cores/`)

---

### Raspberry Pi 64-bit (RPi5, RPi4, aarch64)

Build for Raspberry Pi 4/5 with OpenGL ES 3.0 support.

#### 1. Install Cross-Compilation Toolchain (on build machine)

```bash
sudo apt update
sudo apt install aarch64-linux-gnu-gcc aarch64-linux-gnu-g++ zlib1g-dev:arm64
```

#### 2. Compile

```bash
# Raspberry Pi 5 (cortex-a76)
make platform=rpi64 -j$(nproc)

# or generic aarch64
make platform=aarch64 -j$(nproc)
```

The Makefile auto-tunes the CPU based on platform:
- **rpi5**: Cortex-A76 optimizations
- **rpi4-64**: Cortex-A72 optimizations
- **rpi64 (default)**: Cortex-A53 optimizations
- **aarch64**: Generic aarch64 (no CPU-specific tuning)

#### 3. Transfer to Raspberry Pi

```bash
scp supermodel_libretro_aarch64.so pi@raspberrypi:~/.config/retroarch/cores/supermodel_libretro.so
```

**Platform Features:**
- GLES 3.0 rendering via `glsym_es3`
- Legacy3D renderer excluded (GLES incompatible)
- Optimized for aarch64 ARM architecture
- Full force feedback support
- Synchronous 60 Hz audio (735 stereo samples per frame)

**Performance Notes:** On Raspberry Pi, performance varies by game and model:
- **RPi 5:** Can handle most games at native resolution
- **RPi 4:** Older/simpler titles (VF3, Daytona) run well; may need scaling for demanding titles
- **RPi 3:** Limited performance; resolution scaling recommended

---

### Generic aarch64 (Standalone ARM64 Linux)

For generic ARM64 Linux systems (not Raspberry Pi):

```bash
make platform=aarch64 -j$(nproc)
```

Same as RPi64 but without CPU-specific tuning. Suitable for:
- ARM64 servers
- Generic ARM development boards
- Amazon Graviton instances
- Other aarch64 Linux systems

---

## 🎮 Performance Notes
For performance-heavy titles (e.g., Sega Rally 2 or Daytona USA 2), ensure you are running the core in Release mode. This core uses synchronous audio; if your CPU cannot maintain the full 60 Hz emulation speed, you may experience audio stuttering.

On Raspberry Pi, performance depends on the specific model and game. Older titles (e.g., Virtua Fighter 3) run well on Pi 4/5, while demanding titles may require resolution scaling adjustments via RetroArch core options.
