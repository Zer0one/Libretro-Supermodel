#pragma once

#include <cstdint>
#include <string>

#include "Game.h"

namespace LibretroNvramSettings {

enum Capability : unsigned {
  None       = 0,
  Country    = 1u << 0,
  LinkMode   = 1u << 1,
  CarNumber  = 1u << 2,
  Cabinet    = 1u << 3,
};

struct Selection {
  // Negative values preserve the setting already stored in NVRAM.
  int country = -1;    // 1=Japan, 2=USA, 3=Export, 4=Australia, 5=Korea
  int linkMode = -1;   // 0=Single, 1=Master, 2=Slave, 3=Live
  int carNumber = -1;  // user-facing range 1..16
  int cabinet = -1;    // 0=Deluxe, 1=Twin
};

enum class ApplyResult {
  Unsupported,
  InvalidLayout,
  Unchanged,
  Changed,
};

inline unsigned GetCapabilities(const Game *game)
{
  if (!game)
    return None;

  // Daytona USA 2 and Power Edition share the same M3SEGA/A2 settings
  // layout and CRC-16/XMODEM checksum.
  if (game->name == "daytona2" || game->name == "dayto2pe" ||
      game->parent == "daytona2")
    return Country | LinkMode | CarNumber | Cabinet;

  return None;
}

inline uint16_t Crc16Xmodem(const uint16_t *words)
{
  uint16_t crc = 0;

  // Logical EEPROM bytes 12..69: words 6..34, high byte first.
  for (unsigned word = 6; word <= 34; ++word)
  {
    const uint8_t bytes[] = {
      static_cast<uint8_t>(words[word] >> 8),
      static_cast<uint8_t>(words[word] & 0xff),
    };
    for (uint8_t byte : bytes)
    {
      crc ^= static_cast<uint16_t>(byte) << 8;
      for (unsigned bit = 0; bit < 8; ++bit)
        crc = (crc & 0x8000)
          ? static_cast<uint16_t>((crc << 1) ^ 0x1021)
          : static_cast<uint16_t>(crc << 1);
    }
  }
  return crc;
}

inline ApplyResult Apply(const Game &game, uint16_t *words,
                         const Selection &selection)
{
  if (!words || GetCapabilities(&game) == None)
    return ApplyResult::Unsupported;

  // Refuse to interpret a different EEPROM layout as Daytona settings.
  if (words[0] != 0x4d33 || words[1] != 0x5345 || words[2] != 0x4741 ||
      (words[4] & 0xff00) != 0xa200)
    return ApplyResult::InvalidLayout;

  bool changed = false;
  auto replaceHighByte = [&changed](uint16_t &word, unsigned value) {
    const uint16_t updated = static_cast<uint16_t>(
      (word & 0x00ff) | ((value & 0xff) << 8));
    changed |= word != updated;
    word = updated;
  };
  auto replaceLowByte = [&changed](uint16_t &word, unsigned value) {
    const uint16_t updated = static_cast<uint16_t>(
      (word & 0xff00) | (value & 0xff));
    changed |= word != updated;
    word = updated;
  };

  if (selection.country >= 1 && selection.country <= 5)
  {
    replaceHighByte(words[12], selection.country);
    replaceHighByte(words[41], selection.country);
  }
  if (selection.linkMode >= 0 && selection.linkMode <= 3)
  {
    replaceHighByte(words[15], selection.linkMode);
    replaceHighByte(words[44], selection.linkMode);
  }
  if (selection.carNumber >= 1 && selection.carNumber <= 16)
  {
    const unsigned stored = static_cast<unsigned>(selection.carNumber - 1);
    replaceLowByte(words[15], stored);
    replaceLowByte(words[44], stored);
  }
  if (selection.cabinet >= 0 && selection.cabinet <= 1)
  {
    replaceHighByte(words[16], selection.cabinet);
    replaceHighByte(words[45], selection.cabinet);
  }

  if (changed)
    words[3] = Crc16Xmodem(words);
  return changed ? ApplyResult::Changed : ApplyResult::Unchanged;
}

} // namespace LibretroNvramSettings
