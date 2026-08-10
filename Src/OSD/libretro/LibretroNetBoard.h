#ifndef INCLUDED_LIBRETRO_NETBOARD_H
#define INCLUDED_LIBRETRO_NETBOARD_H

#include "Network/INetBoard.h"

// Libretro does not currently expose Supermodel's SDL_net transport. Keep the
// device detached while preserving the Model 3 bus contract. Networking can be
// added later without pulling SDL into the core.
class CLibretroNetBoard final : public INetBoard
{
public:
  void SaveState(CBlockFile *) override {}
  void LoadState(CBlockFile *) override {}
  void RunFrame() override {}
  void Reset() override {}

  bool IsAttached() override { return false; }
  bool IsRunning() override { return false; }

  Result Init(UINT8 *, UINT8 *) override { return Result::OKAY; }
  void GetGame(const Game &) override {}

  UINT8 ReadCommRAM8(unsigned) override { return 0xFF; }
  UINT16 ReadCommRAM16(unsigned) override { return 0xFFFF; }
  UINT32 ReadCommRAM32(unsigned) override { return 0xFFFFFFFF; }

  void WriteCommRAM8(unsigned, UINT8) override {}
  void WriteCommRAM16(unsigned, UINT16) override {}
  void WriteCommRAM32(unsigned, UINT32) override {}

  UINT16 ReadIORegister(unsigned) override { return 0xFFFF; }
  void WriteIORegister(unsigned, UINT16) override {}
};

#endif
