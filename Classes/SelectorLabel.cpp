#include "SelectorLabel.h"

namespace puzzle {

///////////////////////////////////////////////////////////////////////////////
SelectorLabel::SelectorLabel(
  cocos2d::Scene* scene,
  const std::string title,
  const std::string fontname,
  const std::vector<std::string>& data,
  const cocos2d::Vec2 position,
  const int index)
  : scene_(scene),
    title_(title),
    fontname_(fontname),
    data_(data),
    position_(position),
    mode_(kModeDisable),
    index_(index),
    label_(nullptr),
    text_(nullptr),
    tag_(0) {

  if (data_.size() == 0) {
    data_.push_back("");
  }
  if ((index_ < 1) || (index_ > (int)data_.size())) {
    index_ = 1;
  }

  cocos2d::TTFConfig ttfConfig24(fontname_, 24);
  label_ = cocos2d::Label::createWithTTF(ttfConfig24, title_);
  label_->setPosition(position_);
  label_->enableBold();

  text_ = cocos2d::Label::createWithTTF(ttfConfig24, data_[index_ - 1]);
  text_->setPosition(position_ + cocos2d::Vec2(0, -32));
  text_->enableBold();

  SetMode(mode_);

  scene_->addChild(label_);
  scene_->addChild(text_);
}

///////////////////////////////////////////////////////////////////////////////
SelectorLabel::~SelectorLabel() {
  scene_->removeChild(text_);
  scene_->removeChild(label_);
  text_ = nullptr;
  label_ = nullptr;
  scene_ = nullptr;
}

///////////////////////////////////////////////////////////////////////////////
void SelectorLabel::SetMode(const int mode) {
  switch (mode) {
  case kModeUnselect:
    mode_ = kModeUnselect;
    label_->setColor(cocos2d::Color3B::WHITE);
    label_->disableEffect(cocos2d::LabelEffect::UNDERLINE);
    text_->setColor(cocos2d::Color3B::WHITE);
    break;
  case kModeSelect:
    mode_ = kModeSelect;
    label_->setColor(cocos2d::Color3B::ORANGE);
    label_->enableUnderline();
    text_->setColor(cocos2d::Color3B::ORANGE);
    break;
  case kModeDisable:
  default:
    mode_ = kModeDisable;
    label_->setColor(cocos2d::Color3B::GRAY);
    label_->disableEffect(cocos2d::LabelEffect::UNDERLINE);
    text_->setColor(cocos2d::Color3B::GRAY);
    break;
  }
}

///////////////////////////////////////////////////////////////////////////////
int SelectorLabel::GetMode() const {
  return mode_;
}

///////////////////////////////////////////////////////////////////////////////
int SelectorLabel::GetTag() const {
  return tag_;
}

///////////////////////////////////////////////////////////////////////////////
void SelectorLabel::SetTag(const int tag) {
  tag_ = tag;
}

///////////////////////////////////////////////////////////////////////////////
int SelectorLabel::GetIndex() const {
  return index_;
}

///////////////////////////////////////////////////////////////////////////////
void SelectorLabel::SetIndex(const int index) {
  if ((index < 1) || (index >(int)data_.size())) {
    return;
  }
  index_ = index;
  text_->setString(data_[index_ - 1]);
}

///////////////////////////////////////////////////////////////////////////////
void SelectorLabel::SetData(std::vector<std::string>& data) {
  data_ = data;
  if (data_.size() == 0) {
    data_.push_back("");
  }
  // データを差し替えた場合はインデックスをリセットする.
  SetIndex(1);
}

///////////////////////////////////////////////////////////////////////////////
void SelectorLabel::SetData(std::vector<std::string>& data, const int index) {
  data_ = data;
  if (data_.size() == 0) {
    data_.push_back("");
  }
  SetIndex(index);
}

///////////////////////////////////////////////////////////////////////////////
void SelectorLabel::OnKeyPressDown() {
  int index = index_ + 1;
  if (index > (int)data_.size()) {
    index = 1;
  }
  SetIndex(index);
}

///////////////////////////////////////////////////////////////////////////////
void SelectorLabel::OnKeyPressUp() {
  int index = index_ - 1;
  if (index < 1) {
    index = data_.size();
  }
  SetIndex(index);
}

}  // puzzle
