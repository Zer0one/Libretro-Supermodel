#ifndef INCLUDED_LIBRETRO_NETBOARD_H
#define INCLUDED_LIBRETRO_NETBOARD_H

#include <cstdint>
#include <map>
#include <string>
#include <vector>

#include "Network/INetBoard.h"
#include "LibretroNetPacket.h"

namespace Util { namespace Config { class Node; } }

// Model 3 network-board simulation transported through libretro's netpacket
// interface. The first implementation deliberately targets a two-cabinet
// Daytona 2 link; the native standalone CSimNetBoard transport is unchanged.
class CLibretroNetBoard final : public INetBoard
{
public:
  explicit CLibretroNetBoard(const Util::Config::Node &config);
  ~CLibretroNetBoard() override;

  static bool RegisterNetpacketInterface(retro_environment_t environment,
                                         retro_log_printf_t logger);
  static void ShutdownNetpacketInterface();

  void SaveState(CBlockFile *) override {}
  void LoadState(CBlockFile *) override {}
  void RunFrame() override;
  void Reset() override;

  bool IsAttached() override { return m_attached; }
  bool IsRunning() override { return m_attached && m_running; }

  Result Init(UINT8 *netRAMPtr, UINT8 *netBufferPtr) override;
  void GetGame(const Game &game) override { m_gameInfo = game; }

  UINT8 ReadCommRAM8(unsigned addr) override;
  UINT16 ReadCommRAM16(unsigned addr) override;
  UINT32 ReadCommRAM32(unsigned addr) override;

  void WriteCommRAM8(unsigned addr, UINT8 data) override;
  void WriteCommRAM16(unsigned addr, UINT16 data) override;
  void WriteCommRAM32(unsigned addr, UINT32 data) override;

  UINT16 ReadIORegister(unsigned reg) override;
  void WriteIORegister(unsigned reg, UINT16 data) override;

private:
  enum class State { Start, Init, Testing, Ready, Error };

  struct ParsedPacket
  {
    uint8_t type = 0;
    uint16_t role = 0;
    uint32_t frame = 0;
    std::vector<uint8_t> payload;
  };

  const Util::Config::Node &m_config;
  Game m_gameInfo;
  UINT8 *m_ram = nullptr;
  UINT8 *m_buffer = nullptr;
  UINT8 *m_commRAM = nullptr;
  UINT8 *m_externalCommRAM = nullptr;
  bool m_attached = false;
  bool m_running = false;
  bool m_commBank = false;
  State m_state = State::Start;
  uint16_t m_irq2Ack = 0;
  uint16_t m_status0 = 0;
  uint16_t m_status1 = 0;
  uint16_t m_counter = 0;
  uint16_t m_segmentSize = 0;
  uint16_t m_peerId = RETRO_NETPACKET_BROADCAST;
  uint16_t m_localRole = 0;
  uint32_t m_gameHash = 0;
  unsigned m_helloInterval = 0;
  unsigned m_readyDelay = 0;
  std::map<uint32_t, std::vector<uint8_t>> m_framePackets;

  bool IsGame(const char *gameName) const;
  uint16_t ReadNetRAM16(unsigned index) const;
  void WriteCommWord(unsigned index, uint16_t value);
  void SwapCommBanks();
  void DrainPackets();
  bool DecodePacket(const std::vector<uint8_t> &bytes,
                    ParsedPacket &packet) const;
  std::vector<uint8_t> BuildPacket(uint8_t type, uint32_t frame,
                                   const uint8_t *payload,
                                   size_t payloadSize) const;
  void SendHello();
  void EnterReadyState();
  void ExchangeFrame();
  void EnterError(const char *message);
};

#endif
