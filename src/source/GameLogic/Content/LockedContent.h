#pragma once

#include <cstdint>
#include <optional>
#include <span>
#include <vector>

// The content which the server locked, e.g. the gens or the maps of a later season, so the
// client hides its user interface. The server tells it with the locked content message when a
// character enters the game. Without the message nothing is locked: servers which don't send it
// get the full user interface.
namespace GameLogic::Content
{
/// The head code of the locked content message (C2), a custom message of Torvik MU.
inline constexpr uint8_t LockedContentHeadCode = 0xFA;

struct LockedContent
{
    bool IsGensLocked = false;
    bool IsCashShopLocked = false;
    /// The numbers of the locked maps.
    std::vector<uint16_t> LockedMaps;
};

/// Parses the locked content message: the C2 header, a byte of flags (bit 0: gens, bit 1: cash
/// shop), the count of locked maps and their numbers, little endian. Empty when the message is
/// shorter than its fixed part; maps beyond the received bytes are ignored.
std::optional<LockedContent> ParseLockedContent(std::span<const uint8_t> packet);

/// Stores the content which the server locked.
void SetLockedContent(LockedContent content);

/// Unlocks everything, until the server sends the locked content again.
void ClearLockedContent();

bool IsGensLocked();
bool IsCashShopLocked();
bool IsMapLocked(int mapNumber);
} // namespace GameLogic::Content
