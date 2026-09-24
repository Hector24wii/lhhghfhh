#include "main.hpp"
#include <Geode/utils/web.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

class $modify(MyMenuLayer, MenuLayer) {
    struct Fields {
        TaskHolder<web::WebResponse> m_listener;
    };

    bool init() {
        if (!MenuLayer::init()) return false;

        auto myButton = CCMenuItemSpriteExtra::create(
            ButtonSprite::create("Lancelot", "bigFont.fnt", "GJ_button_04.png", 0.8f),
            this,
            menu_selector(MyMenuLayer::onOpenLancelot)
        );

        auto menu = this->getChildByID("right-menu");
        if (menu) {
            menu->addChild(myButton);
            menu->updateLayout();
        }

        return true;
    }

    void onOpenLancelot(CCObject*) {
        showCustomNotification("¡Lancelot BOT conectado!");
        
        auto req = web::WebRequest();
        req.header("Content-Type", "application/json");
        req.bodyString(R"({"model":"lancelot1B:1.0V","prompt":"Hola Lancelot","stream":false})");

        m_fields->m_listener.spawn(
            req.post("http://localhost:11434/api/generate"),
            [](web::WebResponse response) {
                if (response.ok()) {
                    log::info("Ollama respondió correctamente.");
                } else {
                    log::warn("Ollama no respondió. Código: {}", response.code());
                }
            }
        );
    }
};