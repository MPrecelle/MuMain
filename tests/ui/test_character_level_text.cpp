#include "App/stdafx.h"

#include <doctest.h>

#include <string>

#include "I18N/All.h"
#include "UI/Character/CharacterLevelText.h"

TEST_CASE("character level text hides the resets while there are none [ui][i18n]")
{
    const std::string previousLocale = I18N::GetCurrentLocale();
    I18N::SetLocale("en");

    CHECK(UI::Character::CharacterLevelText(400, 0) == L"Level: 400");
    CHECK(UI::Character::CharacterLevelText(400, 3) == L"Level: 400 | Resets: 3");

    I18N::SetLocale(previousLocale.c_str());
}
