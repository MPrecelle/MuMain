// Tests of the content which the server locked: how the locked content message is parsed, and
// that nothing is locked until the server sends it.

#include "stdafx.h"

#include "doctest.h"

#include "GameLogic/Content/LockedContent.h"

#include <array>
#include <cstdint>

using GameLogic::Content::ClearLockedContent;
using GameLogic::Content::IsCashShopLocked;
using GameLogic::Content::IsGensLocked;
using GameLogic::Content::IsMapLocked;
using GameLogic::Content::LockedContent;
using GameLogic::Content::ParseLockedContent;
using GameLogic::Content::SetLockedContent;

TEST_CASE("the locked content message has the flags and the maps")
{
    // Gens locked, cash shop not; maps 41 and 300 (0x012C, little endian).
    const std::array<uint8_t, 10> packet = {0xC2, 0x00, 0x0A, 0xFA, 0x01, 0x02, 41, 0x00, 0x2C, 0x01};

    const auto content = ParseLockedContent(packet);

    REQUIRE(content.has_value());
    CHECK(content->IsGensLocked);
    CHECK_FALSE(content->IsCashShopLocked);
    REQUIRE(content->LockedMaps.size() == 2);
    CHECK(content->LockedMaps[0] == 41);
    CHECK(content->LockedMaps[1] == 300);
}

TEST_CASE("the locked content message without locked content")
{
    const std::array<uint8_t, 6> packet = {0xC2, 0x00, 0x06, 0xFA, 0x00, 0x00};

    const auto content = ParseLockedContent(packet);

    REQUIRE(content.has_value());
    CHECK_FALSE(content->IsGensLocked);
    CHECK_FALSE(content->IsCashShopLocked);
    CHECK(content->LockedMaps.empty());
}

TEST_CASE("the cash shop flag is the second bit")
{
    const std::array<uint8_t, 6> packet = {0xC2, 0x00, 0x06, 0xFA, 0x02, 0x00};

    const auto content = ParseLockedContent(packet);

    REQUIRE(content.has_value());
    CHECK_FALSE(content->IsGensLocked);
    CHECK(content->IsCashShopLocked);
}

TEST_CASE("a message shorter than its fixed part is rejected")
{
    const std::array<uint8_t, 5> packet = {0xC2, 0x00, 0x05, 0xFA, 0x01};

    CHECK_FALSE(ParseLockedContent(packet).has_value());
}

TEST_CASE("maps beyond the received bytes are ignored")
{
    // Announces three maps, but only one and a half arrived.
    const std::array<uint8_t, 9> packet = {0xC2, 0x00, 0x09, 0xFA, 0x00, 0x03, 41, 0x00, 42};

    const auto content = ParseLockedContent(packet);

    REQUIRE(content.has_value());
    REQUIRE(content->LockedMaps.size() == 1);
    CHECK(content->LockedMaps[0] == 41);
}

TEST_CASE("nothing is locked until the server sends the locked content")
{
    ClearLockedContent();

    CHECK_FALSE(IsGensLocked());
    CHECK_FALSE(IsCashShopLocked());
    CHECK_FALSE(IsMapLocked(41));
}

TEST_CASE("the stored locked content locks the gens, the cash shop and the maps")
{
    SetLockedContent(LockedContent{true, true, {41, 64}});

    CHECK(IsGensLocked());
    CHECK(IsCashShopLocked());
    CHECK(IsMapLocked(41));
    CHECK(IsMapLocked(64));
    CHECK_FALSE(IsMapLocked(0));

    ClearLockedContent();
    CHECK_FALSE(IsGensLocked());
    CHECK_FALSE(IsMapLocked(41));
}
