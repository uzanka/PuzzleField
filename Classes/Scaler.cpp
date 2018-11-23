#include "Scaler.h"
#include "ScenarioManager.h"

namespace puzzle {

///////////////////////////////////////////////////////////////////////////////
Scaler::Scaler(const double scale)
  : scale_(scale) {
}

///////////////////////////////////////////////////////////////////////////////
Scaler::Scaler(const int width, const int height)
  : scale_(1.0f) {
  int design_width = ScenarioManager::getInstance().GetWidth();
  int design_height = ScenarioManager::getInstance().GetHeight();

  // 範囲外にあるときは縮小する.
  if ((design_width < width) || (design_height < height)) {
    double scale_x = (double)design_width / (double)width;
    double scale_y = (double)design_height / (double)height;
    scale_ = scale_x;
    if (scale_ > scale_y) {
      scale_ = scale_y;
    }
  }
}

double Scaler::GetScale() const {
  return scale_;
}

///////////////////////////////////////////////////////////////////////////////
Scaler::~Scaler() {
}

///////////////////////////////////////////////////////////////////////////////
cocos2d::Vec2 Scaler::GetDisplayPosition(const int x, const int y) {
  cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
  cocos2d::Vec2 visibleOrigin = cocos2d::Director::getInstance()->getVisibleOrigin();
  return cocos2d::Vec2(visibleOrigin + cocos2d::Vec2((x * GetScaledSize(1) + GetScaledSize(0.5)),
                                                     (visibleSize.height - y * GetScaledSize(1) - GetScaledSize(0.5))));
}

///////////////////////////////////////////////////////////////////////////////
double Scaler::GetScaledSize(const double count) {
  return 32 * scale_ * count;
}

///////////////////////////////////////////////////////////////////////////////
cocos2d::Sprite* Scaler::CreateSprite(const std::string name) {
  cocos2d::Sprite* sprite = cocos2d::Sprite::create(name);
  sprite->setScale(scale_, scale_);
  return sprite;
}

///////////////////////////////////////////////////////////////////////////////
cocos2d::Sprite* Scaler::CreateSprite(const std::string name, const int x, const int y) {
  cocos2d::Sprite* sprite = CreateSprite(name);
  sprite->setPosition(GetDisplayPosition(x, y));
  return sprite;
}

}  // puzzle
