#include "stdafx.h"
#include "GameLogic/Content/LockedContent.h"

#include <algorithm>
#include <utility>

namespace
{
// C2 header (type, size high, size low, head code), then the flags and the count of maps.
constexpr size_t FlagsOffset = 4;
constexpr size_t MapCountOffset = 5;
constexpr size_t FirstMapOffset = 6;
constexpr size_t MapSize = 2;

constexpr uint8_t GensLockedFlag = 0x01;
constexpr uint8_t CashShopLockedFlag = 0x02;

GameLogic::Content::LockedContent CurrentLockedContent;
} // namespace

namespace GameLogic::Content
{
std::optional<LockedContent> ParseLockedContent(std::span<const uint8_t> packet)
{
    if (packet.size() < FirstMapOffset)
    {
        return std::nullopt;
    }

    LockedContent content;
    const uint8_t flags = packet[FlagsOffset];
    content.IsGensLocked = (flags & GensLockedFlag) != 0;
    content.IsCashShopLocked = (flags & CashShopLockedFlag) != 0;

    const size_t receivedMaps = (packet.size() - FirstMapOffset) / MapSize;
    const size_t mapCount = std::min<size_t>(packet[MapCountOffset], receivedMaps);
    content.LockedMaps.reserve(mapCount);
    for (size_t i = 0; i < mapCount; ++i)
    {
        const size_t offset = FirstMapOffset + i * MapSize;
        content.LockedMaps.push_back(static_cast<uint16_t>(packet[offset] | (packet[offset + 1] << 8)));
    }

    return content;
}

void SetLockedContent(LockedContent content)
{
    CurrentLockedContent = std::move(content);
}

void ClearLockedContent()
{
    CurrentLockedContent = {};
}

bool IsGensLocked()
{
    return CurrentLockedContent.IsGensLocked;
}

bool IsCashShopLocked()
{
    return CurrentLockedContent.IsCashShopLocked;
}

bool IsMapLocked(int mapNumber)
{
    const auto& maps = CurrentLockedContent.LockedMaps;
    return std::find(maps.begin(), maps.end(), mapNumber) != maps.end();
}
} // namespace GameLogic::Content
