#include "stdafx.h"
#include "UI/Character/CharacterLevelText.h"

#include "I18N/All.h"

namespace UI::Character
{
std::wstring CharacterLevelText(unsigned int level, unsigned int resets)
{
    wchar_t text[128] = {};
    if (resets == 0)
        mu_swprintf(text, I18N::Game::LevelD, static_cast<int>(level));
    else
        mu_swprintf(text, I18N::Game::LevelUResetsU, level, resets);
    return text;
}
}
