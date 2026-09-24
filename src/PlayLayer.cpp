#include "main.hpp"
#include <Geode/modify/PlayLayer.hpp>

using namespace geode::prelude;

class $modify(MyPlayLayer, PlayLayer) {
    void update(float dt) {
        PlayLayer::update(dt);

        if (!g_lancelotBotActive || !m_player1 || m_player1->m_isDead) return;

        float posX = m_player1->getPositionX();

        bool shouldJump = (posX > 210.0f && posX < 215.0f) ||
                         (posX > 330.0f && posX < 335.0f) ||
                         (posX > 445.0f && posX < 450.0f);

        if (shouldJump && !g_buttonPushed) {
            m_player1->pushButton(PlayerButton::Jump);
            g_buttonPushed = true;
        } else if (!shouldJump && g_buttonPushed) {
            m_player1->releaseButton(PlayerButton::Jump);
            g_buttonPushed = false;
        }
    }

    void destroyPlayer(PlayerObject* player, GameObject* object) {
        PlayLayer::destroyPlayer(player, object);

        float porcentaje = (m_levelLength > 0) ? (player->getPositionX() / m_levelLength) * 100.0f : 0.0f;
        log::info("Lancelot detectó muerte en el {:.1f}%", porcentaje);

        if (porcentaje >= 70.0f) {
            showCustomNotification("¡Casi lo pasas!");
        }
    }
};