#ifndef SUPERMODEL_LIBRETRO_TIMING_H
#define SUPERMODEL_LIBRETRO_TIMING_H

#include <cstdint>

namespace LibretroTiming {

// Match Supermodel standalone's default cadence. Although Model 3 video
// hardware runs at 57.524160 Hz, upstream defaults to 60 Hz to avoid judder,
// and its SoundBoard produces exactly 44100 / 60 samples per audio chunk.
// A future true-Hz mode must first teach the audio path to generate/resample
// the required fractional 766/767-sample cadence.
inline constexpr unsigned kFrameRate = 60;
inline constexpr double kFramesPerSecond = static_cast<double>(kFrameRate);
inline constexpr unsigned kAudioSampleRate = 44100;
inline constexpr unsigned kAudioFramesPerVideoFrame =
   kAudioSampleRate / kFrameRate;
inline constexpr unsigned kAudioBytesPerVideoFrame =
   kAudioFramesPerVideoFrame * 2 * sizeof(std::int16_t);

static_assert(kAudioSampleRate % kFrameRate == 0,
              "The 60 Hz audio packet must contain a whole number of samples");

} // namespace LibretroTiming

#endif
