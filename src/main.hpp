#pragma once
#include <Geode/Geode.hpp>

// Variables globales del bot
inline bool g_lancelotBotActive = false;
inline bool g_autoRetry = false;
inline bool g_noclip = false;
inline bool g_recordingMacro = false;
inline bool g_buttonPushed = false;

// Vector para almacenar posiciones de salto
inline std::vector<float> g_jumpPositions;

void showCustomNotification(const std::string& text);