#include "main.hpp"

using namespace geode::prelude;

void showCustomNotification(const std::string& text) {
    auto icon = CCSprite::createWithSpriteFrameName("GJ_completesIcon_001.png");
    Notification::create(text, icon)->show();
}