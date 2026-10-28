#pragma once

#include <string>

namespace UI::Character
{
// The character window's level line: "Level: %u | Resets: %u", or only "Level: %d" while the
// character has no resets (servers without resets would always show "Resets: 0").
std::wstring CharacterLevelText(unsigned int level, unsigned int resets);
}
