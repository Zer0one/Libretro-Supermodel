#include "libretro.h"
#include "libretro_cbs.h"
#include <cstdlib>
#include <cstring>

// --- Core Options ---
static struct retro_core_option_v2_category option_cats[] = {
   {
      "video",
      "Video",
      "Configure graphics and rendering options."
   },
   {
      "audio", 
      "Audio",
      "Configure audio settings."
   },
   {
      "input",
      "Input",
      "Configure input and control settings."
   },
   {
      "cpu",
      "CPU",
      "Configure CPU performance and emulation settings."
   },
   { NULL, NULL, NULL },
};

static struct retro_core_option_v2_definition option_defs[] = {
   // Video
   {
      "supermodel_resolution",
      "Internal Resolution",
      NULL,
      "Render at higher internal resolution for improved image quality. Lower values reduce GPU load. 'Half' (248x192) recommended for low-end systems.",
      NULL,
      "video",
      {
         { "half",   "Half (248x192) - Low-End Mobile" },
         { "native", "Native (496x384) - Recommended" },
         { "2x",     "2x (992x768)" },
         { "3x",     "3x (1488x1152)" },
         { "4x",     "4x (1984x1536)" },
         { NULL, NULL },
      },
      "native"
   },
   {
      "supermodel_timing_overlay",
      "Frame Timing Overlay",
      NULL,
      "Show the per-frame timing overlay (PPC/Render/GPU/Total) and log timing averages. Costs an extra draw pass every frame, so leave it off unless you are profiling.",
      NULL,
      "video",
      {
         { "disabled", NULL },
         { "enabled",  NULL },
         { NULL, NULL },
      },
      "disabled"
   },
   {
      "supermodel_upscale_mode",
      "2D Layer Upscaling Filter",
      NULL,
      "Select the native Supermodel filter used to upscale internal 2D tile layers before they are composited with 3D. At native resolution Supermodel always uses Nearest. Takes effect after restarting content.",
      NULL,
      "video",
      {
         { "0", "Nearest" },
         { "1", "Biquintic" },
         { "2", "Bilinear (Default)" },
         { "3", "Bicubic" },
         { NULL, NULL },
      },
      "2"
   },
   {
      "supermodel_wide_screen",
      "Widescreen Mode",
      NULL,
      "Expand full-screen 3D viewports horizontally to render a true 16:9 field of view. 'Widescreen + Wide Background' also stretches the lower 2D background layer to fill the sides; HUD and upper overlays remain at their original aspect ratio. Takes effect after restarting content. May expose geometry or background artifacts in some games.",
      NULL,
      "video",
      {
         { "disabled", NULL },
         { "enabled", "Widescreen" },
         { "wide_background", "Widescreen + Wide Background" },
         { NULL, NULL },
      },
      "disabled"
   },
   {
      "supermodel_crosshairs",
      "Show Crosshair",
      NULL,
      "Select which native Supermodel vector crosshair is displayed in light gun games.",
      NULL,
      "video",
      {
         { "0", "Disabled" },
         { "1", "Player 1 Only" },
         { "2", "Player 2 Only" },
         { "3", "Players 1 & 2" },
         { NULL, NULL },
      },
      "0"
   },
   // Input
   {
      "supermodel_gun_input",
      "Gun Input Mode",
      NULL,
      "Input source for analog-gun games. Hybrid accepts RetroArch Lightgun, Mouse, and the left Analog Stick through one virtual cursor. Dedicated modes restrict input to the selected source. Changes take effect immediately.",
      NULL,
      "input",
      {
         { "hybrid",   "Hybrid (Lightgun / Mouse / Analog)" },
         { "lightgun", "Lightgun" },
         { "mouse",    "Mouse" },
         { "analog",   "Analog Stick Cursor" },
         { NULL, NULL },
      },
      "hybrid"
   },
   {
      "supermodel_star_wars_input",
      "Star Wars Trilogy Input Mode",
      NULL,
      "Input source for the arcade analog joystick used by Star Wars Trilogy Arcade. Hybrid accepts the Mouse and left Analog Stick through one virtual control, with the last moved source taking priority. Changes take effect immediately.",
      NULL,
      "input",
      {
         { "hybrid", "Hybrid (Mouse / Analog Stick)" },
         { "mouse",  "Mouse" },
         { "analog", "Analog Stick" },
         { NULL, NULL },
      },
      "hybrid"
   },
   {
      "supermodel_force_feedback",
      "Force Feedback",
      NULL,
      "Enable force feedback for racing games (requires compatible hardware).",
      NULL,
      "input",
      {
         { "disabled", NULL },
         { "enabled",  NULL },
         { NULL, NULL },
      },
      "disabled"
   },
   {
      "supermodel_steering_response",
      "Driving Steering Response",
      NULL,
      "Applied only to games recognized as Driving. Select the steering response curve; Progressive and FBNeo Logarithmic reduce sensitivity around the center while retaining the available output range.",
      NULL,
      "input",
      {
         { "linear",      "Linear" },
         { "progressive", "Progressive (Fine Center)" },
         { "fbneo",       "FBNeo Logarithmic (Fine Center)" },
         { NULL, NULL },
      },
      "linear"
   },
   {
      "supermodel_steering_output_range",
      "Driving Steering Output Range",
      NULL,
      "Applied only to games recognized as Driving. Scale steering around its center. Values below 100% reduce the emulated wheel range; values above 100% reach full lock with less physical stick travel.",
      NULL,
      "input",
      {
         { "50",  "50%" },
         { "60",  "60%" },
         { "63",  "63% (30-80-D0)" },
         { "70",  "70%" },
         { "80",  "80%" },
         { "90",  "90%" },
         { "100", "100%" },
         { "110", "110%" },
         { "120", "120%" },
         { "130", "130%" },
         { "140", "140%" },
         { "150", "150%" },
         { NULL, NULL },
      },
      "100"
   },
   {
      "supermodel_accelerator_output_range",
      "Driving Accelerator Output Range",
      NULL,
      "Applied only to games recognized as Driving. Scale the accelerator from its zero rest position. Values below 100% reduce the maximum emulated pedal output; values above 100% reach full output with less physical trigger travel.",
      NULL,
      "input",
      {
         { "50",   "50%" },
         { "60",   "60%" },
         { "70",   "70%" },
         { "75.3", "75.3% (00-C0)" },
         { "80",   "80%" },
         { "90",   "90%" },
         { "100",  "100%" },
         { "110",  "110%" },
         { "120",  "120%" },
         { "130",  "130%" },
         { "140",  "140%" },
         { "150",  "150%" },
         { NULL, NULL },
      },
      "100"
   },
   {
      "supermodel_brake_output_range",
      "Driving Brake Output Range",
      NULL,
      "Applied only to games recognized as Driving. Scale the brake from its zero rest position. Values below 100% reduce the maximum emulated pedal output; values above 100% reach full output with less physical trigger travel.",
      NULL,
      "input",
      {
         { "50",   "50%" },
         { "60",   "60%" },
         { "70",   "70%" },
         { "75.3", "75.3% (00-C0)" },
         { "80",   "80%" },
         { "90",   "90%" },
         { "100",  "100%" },
         { "110",  "110%" },
         { "120",  "120%" },
         { "130",  "130%" },
         { "140",  "140%" },
         { "150",  "150%" },
         { NULL, NULL },
      },
      "100"
   },
   // Audio
   {
      "supermodel_sound_volume",
      "Sound Volume",
      NULL,
      "Adjust overall sound volume.",
      NULL,
      "audio",
      {
         { "0",   "0%" },
         { "10",  "10%" },
         { "20",  "20%" },
         { "30",  "30%" },
         { "40",  "40%" },
         { "50",  "50%" },
         { "60",  "60%" },
         { "70",  "70%" },
         { "80",  "80%" },
         { "90",  "90%" },
         { "100", "100%" },
         { "110", "110%" },
         { "120", "120%" },
         { "130", "130%" },
         { "140", "140%" },
         { "150", "150%" },
         { "160", "160%" },
         { "170", "170%" },
         { "180", "180%" },
         { "190", "190%" },
         { "200", "200%" },
         { NULL, NULL },
      },
      "100"
   },
   {
      "supermodel_music_volume",
      "Music Volume",
      NULL,
      "Adjust DSB music volume (affects games with separate music board e.g. Sega Rally 2, Virtua Fighter 3).",
      NULL,
      "audio",
      {
         { "0",   "0%" },
         { "10",  "10%" },
         { "20",  "20%" },
         { "30",  "30%" },
         { "40",  "40%" },
         { "50",  "50%" },
         { "60",  "60%" },
         { "70",  "70%" },
         { "80",  "80%" },
         { "90",  "90%" },
         { "100", "100%" },
         { "110", "110%" },
         { "120", "120%" },
         { "130", "130%" },
         { "140", "140%" },
         { "150", "150%" },
         { "160", "160%" },
         { "170", "170%" },
         { "180", "180%" },
         { "190", "190%" },
         { "200", "200%" },
         { NULL, NULL },
      },
      "100"
   },
   {
      "supermodel_sound_enable",
      "Sound Enable",
      NULL,
      "Enable or disable sound emulation. Disabling sound can significantly improve performance on slow hardware.",
      NULL,
      "audio",
      {
         { "enabled",  NULL },
         { "disabled", NULL },
         { NULL, NULL },
      },
      "enabled"
   },
   {
      "supermodel_scsp_dsp",
      "SCSP DSP Engine",
      NULL,
      "Select the Sega Custom Sound Processor DSP implementation. The modern MAME-derived engine is recommended; use Legacy ElSemi for games with audio compatibility issues such as Fighting Vipers 2. Takes effect after restarting content.",
      NULL,
      "audio",
      {
         { "new",    "New (MAME, Default)" },
         { "legacy", "Legacy (ElSemi)" },
         { NULL, NULL },
      },
      "new"
   },
   // CPU
   {
      "supermodel_frameskip",
      "Frame Skip",
      NULL,
      "Skip rendering every N frames to reduce GPU load on slow hardware. '0' disables frame skipping. Higher values improve speed at the cost of visual smoothness.",
      NULL,
      "cpu",
      {
         { "0", "Disabled" },
         { "1", "Skip 1 (render every 2nd frame)" },
         { "2", "Skip 2 (render every 3rd frame)" },
         { "3", "Skip 3 (render every 4th frame)" },
         { NULL, NULL },
      },
      "0"
   },
   {
      "supermodel_ppc_frequency",
      "PowerPC CPU Frequency",
      NULL,
      "Adjust PowerPC CPU frequency to trade cycle accuracy for performance on low-end hardware. 'Auto' follows the game's stepping (66/100/166 MHz): a Stepping 2.x game such as Daytona 2 runs at 166 MHz, which is over twice the CPU work of 70 MHz. Underclocking is the single biggest performance lever on weak hardware, at the cost of cycle accuracy.",
      NULL,
      "cpu",
      {
         { "auto", "Auto (Default)" },
         { "33",   "33 MHz (Half Speed - Aggressive)" },
         { "50",   "50 MHz (0.75x Speed)" },
         { "66",   "66 MHz (Step 1.0 Default)" },
         { "70",   "70 MHz (Fast - Underclocked)" },
         { "100",  "100 MHz (Step 1.5 Default)" },
         { "133",  "133 MHz (2.0x Base)" },
         { "166",  "166 MHz (Step 2.x Default)" },
         { "200",  "200 MHz (Max)" },
         { NULL, NULL },
      },
      "auto"
   },
#ifdef HAVE_PPC_JIT
   {
      "supermodel_jit_enable",
      "ARM64 JIT Recompiler (Experimental)",
      NULL,
      "Enable the experimental ARM64 dynamic recompiler for the emulated PowerPC CPU. Disabled by default; the interpreter remains the correctness reference. Restart content to apply.",
      NULL,
      "cpu",
      {
         { "enabled",  "Enabled" },
         { "disabled", "Disabled (Interpreter)" },
         { NULL, NULL },
      },
      "disabled"
   },
#endif
   { NULL, NULL, NULL, NULL, NULL, NULL, {{NULL, NULL}}, NULL },
};

// --- Helper: Read Core Option ---
static const char* option_get(const char* key, const char* default_value)
{
   struct retro_variable var = { key, NULL };
   if (environ_cb && environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value)
      return var.value;
   return default_value;
}

// Cache for parsed options
#include "CoreOptionsTypes.h"

// --- Update Core Options ---
void update_core_options(void)
{
   const char* resolution = option_get("supermodel_resolution", "native");
   if (strcmp(resolution, "half") == 0)
      g_options.resolution_multiplier = 0.5f;
   else if (strcmp(resolution, "2x") == 0)
      g_options.resolution_multiplier = 2.0f;
   else if (strcmp(resolution, "3x") == 0)
      g_options.resolution_multiplier = 3.0f;
   else if (strcmp(resolution, "4x") == 0)
      g_options.resolution_multiplier = 4.0f;
   else
      g_options.resolution_multiplier = 1.0f;  // native

   g_options.upscale_mode = atoi(option_get("supermodel_upscale_mode", "2"));
   if (g_options.upscale_mode < 0 || g_options.upscale_mode > 3)
      g_options.upscale_mode = 2;

   g_options.timing_overlay = strcmp(option_get("supermodel_timing_overlay", "disabled"), "enabled") == 0;

   {
      const char *widescreen = option_get(
         "supermodel_wide_screen", "disabled");
      g_options.widescreen_mode =
         strcmp(widescreen, "wide_background") == 0
            ? WidescreenMode::WidescreenWideBackground
         : strcmp(widescreen, "enabled") == 0
            ? WidescreenMode::Widescreen
            : WidescreenMode::Disabled;
   }
   {
      const char *crosshairs = option_get("supermodel_crosshairs", "0");
      // Accept the values used by earlier development builds so an existing
      // .opt file cannot leave the option in an undefined state.
      g_options.crosshairs = strcmp(crosshairs, "enabled") == 0 ? 3u
                           : strcmp(crosshairs, "disabled") == 0 ? 0u
                           : static_cast<unsigned>(atoi(crosshairs)) & 3u;
   }

   g_options.sound_enable = strcmp(option_get("supermodel_sound_enable", "enabled"), "enabled") == 0;
   g_options.sound_volume = atoi(option_get("supermodel_sound_volume", "100"));
   g_options.music_volume = atoi(option_get("supermodel_music_volume", "100"));
   g_options.legacy_sound_dsp =
      strcmp(option_get("supermodel_scsp_dsp", "new"), "legacy") == 0;

   {
      const char *gun_input = option_get("supermodel_gun_input", "hybrid");
      g_options.gun_input = strcmp(gun_input, "lightgun") == 0 ? GunInput::Lightgun
                          : strcmp(gun_input, "mouse") == 0    ? GunInput::Mouse
                          : strcmp(gun_input, "analog") == 0   ? GunInput::AnalogSticks
                                                               : GunInput::Hybrid;
   }
   {
      const char *star_wars_input = option_get(
         "supermodel_star_wars_input", "hybrid");
      g_options.star_wars_input =
         strcmp(star_wars_input, "mouse") == 0
            ? StarWarsInput::Mouse
         : strcmp(star_wars_input, "analog") == 0
            ? StarWarsInput::AnalogSticks
            : StarWarsInput::Hybrid;
   }
   g_options.force_feedback = strcmp(option_get("supermodel_force_feedback", "disabled"), "enabled") == 0;
   {
      const char *response = option_get("supermodel_steering_response", "linear");
      g_options.steering_response = strcmp(response, "progressive") == 0
                                      ? SteeringResponse::Progressive
                                   : strcmp(response, "fbneo") == 0
                                      ? SteeringResponse::FBNeoLogarithmic
                                      : SteeringResponse::Linear;
   }
   g_options.steering_output_range = atoi(option_get("supermodel_steering_output_range", "100"));
   {
      const char *accelerator_range = option_get("supermodel_accelerator_output_range", "100");
      const char *brake_range = option_get("supermodel_brake_output_range", "100");
      g_options.accelerator_output_range_per_mille =
         strcmp(accelerator_range, "75.3") == 0 ? 753 : atoi(accelerator_range) * 10;
      g_options.brake_output_range_per_mille =
         strcmp(brake_range, "75.3") == 0 ? 753 : atoi(brake_range) * 10;
   }

   // Parse frame skip option
   g_options.frameskip = atoi(option_get("supermodel_frameskip", "0"));
   if (g_options.frameskip < 0) g_options.frameskip = 0;
   if (g_options.frameskip > 3) g_options.frameskip = 3;

   // Parse PowerPC frequency option
   const char* ppc_freq = option_get("supermodel_ppc_frequency", "auto");
   if (strcmp(ppc_freq, "auto") == 0)
      g_options.ppc_frequency = 0;
   else
   {
      int mhz = atoi(ppc_freq);
      g_options.ppc_frequency = (mhz > 0) ? mhz : 0;
   }
   
#ifdef HAVE_PPC_JIT
   g_options.jit_enable = strcmp(option_get("supermodel_jit_enable", "disabled"), "enabled") == 0;
#else
   g_options.jit_enable = false;
#endif

}
