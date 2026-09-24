#pragma once

#include <cstdint>
#include <hyprland/src/plugins/PluginAPI.hpp>

inline HANDLE SCROLLOVERVIEW_HANDLE = nullptr;

// Published for hyprbars, which dlsym()s this symbol to scale its bar to match the overview
inline float g_fOverviewRenderScale = 1.F;

bool ensureScrollOverviewHooks();
void disableScrollOverviewHooks();
bool consumeOverviewMouseAxisBind(uint32_t lastInputTimeMs);
