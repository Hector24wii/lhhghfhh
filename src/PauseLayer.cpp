#include "main.hpp"
#include <Geode/modify/PauseLayer.hpp>

using namespace geode::prelude;

class $modify(MyPauseLayer, PauseLayer) {
    void customSetup() {
        PauseLayer::customSetup();

        auto winSize = CCDirector::get()->getWinSize();
        auto menu = CCMenu::create();

        // 1. Botón Bot ON/OFF
        std::string txtBot = g_lancelotBotActive ? "Bot: ON" : "Bot: OFF";
        auto botBtn = CCMenuItemSpriteExtra::create(
            ButtonSprite::create(txtBot.c_str(), "bigFont.fnt", "GJ_button_01.png", 0.4f),
            this, menu_selector(MyPauseLayer::onToggleBot)
        );

        // 2. Botón Grabar Macro
        std::string txtRec = g_recordingMacro ? "REC: ON" : "REC: OFF";
        auto recBtn = CCMenuItemSpriteExtra::create(
            ButtonSprite::create(txtRec.c_str(), "bigFont.fnt", "GJ_button_04.png", 0.4f),
            this, menu_selector(MyPauseLayer::onToggleRecord)
        );

        // 3. Botón Auto-Retry
        std::string txtRetry = g_autoRetry ? "Retry: ON" : "Retry: OFF";
        auto retryBtn = CCMenuItemSpriteExtra::create(
            ButtonSprite::create(txtRetry.c_str(), "bigFont.fnt", "GJ_button_02.png", 0.4f),
            this, menu_selector(MyPauseLayer::onToggleRetry)
        );

        // 4. Botón Noclip
        std::string txtNoclip = g_noclip ? "Noclip: ON" : "Noclip: OFF";
        auto noclipBtn = CCMenuItemSpriteExtra::create(
            ButtonSprite::create(txtNoclip.c_str(), "bigFont.fnt", "GJ_button_03.png", 0.4f),
            this, menu_selector(MyPauseLayer::onToggleNoclip)
        );

        menu->addChild(botBtn);
        menu->addChild(recBtn);
        menu->addChild(retryBtn);
        menu->addChild(noclipBtn);

        botBtn->setPosition({-60, 20});
        recBtn->setPosition({60, 20});
        retryBtn->setPosition({-60, -20});
        noclipBtn->setPosition({60, -20});

        menu->setPosition({winSize.width - 90, 70});
        this->addChild(menu);
    }

    void onToggleBot(CCObject*) {
        g_lancelotBotActive = !g_lancelotBotActive;
        g_recordingMacro = false; // Desactiva grabación al activar bot
        showCustomNotification(g_lancelotBotActive ? "Bot Activado" : "Bot Desactivado");
    }

    void onToggleRecord(CCObject*) {
        g_recordingMacro = !g_recordingMacro;
        if (g_recordingMacro) {
            g_lancelotBotActive = false;
            g_jumpPositions.clear(); // Limpia la macro previa
        }
        showCustomNotification(g_recordingMacro ? "Grabando Macro..." : "Grabacion Detenida");
    }

    void onToggleRetry(CCObject*) {
        g_autoRetry = !g_autoRetry;
        showCustomNotification(g_autoRetry ? "Auto-Retry ON" : "Auto-Retry OFF");
    }

    void onToggleNoclip(CCObject*) {
        g_noclip = !g_noclip;
        showCustomNotification(g_noclip ? "Noclip ON" : "Noclip OFF");
    }
};