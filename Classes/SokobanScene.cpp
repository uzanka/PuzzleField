#include "SokobanScene.h"
#include "MapManager.h"
#include "MapReader.h"

namespace puzzle {

///////////////////////////////////////////////////////////////////////////////
cocos2d::Scene* SokobanScene::createScene(const std::string title, const std::string filename, const int index) {
  return SokobanScene::create(title, filename, index);
}

///////////////////////////////////////////////////////////////////////////////
SokobanScene::SokobanScene(const std::string title, const std::string filename, const int index) {
  scenario_title_ = title;
  scenario_filename_ = filename;
  scenario_class_ = "Sokoban";
  map_index_ = index;
}

///////////////////////////////////////////////////////////////////////////////
bool SokobanScene::StartPuzzle() {
  // 主人公の位置を探す.
  bool player_on_goal = false;
  if (!sprite_mapper_->GetMap()->Find(kValuePlayer, player_.x_, player_.y_)) {
    if (!sprite_mapper_->GetMap()->Find(kValuePlayerOnGoal, player_.x_, player_.y_)) {
      return false;
    }
    player_on_goal = true;
  }
  player_.vec_ = TargetInfo::kVecDown;

  // 箱の数を調べる
  std::vector<std::pair<int, int>> xy_box;
  player_.fixed_ = sprite_mapper_->GetMap()->Find(kValueBox, xy_box);

  std::vector<std::pair<int, int>> xy_box_on_goal;
  sprite_mapper_->GetMap()->Find(kValueBoxOnGoal, xy_box_on_goal);

  // 箱・主人公とゴールが重なっている場合はspriteを作成する.
  if (player_on_goal) {
    // ゴールを作る.
    cocos2d::Sprite* sprite_goal = cocos2d::Sprite::create(sprite_mapper_->GetImage(kValueGoal));
    sprite_goal->setScale(scaler_->GetScale(), scaler_->GetScale());
    sprite_goal->setPosition(scaler_->GetDisplayPosition(player_.x_, player_.y_));
    this->addChild(sprite_goal, 20);
    // 主人公の方向画像に変える.
    //cocos2d::Sprite* sprite_player = sprite_mapper_->Get(player_.x_, player_.y_);
    //sprite_player->setSpriteFrame(cocos2d::Sprite::create(Vec2Image(player_.vec_))->getSpriteFrame());
  }
  for (auto xy1 : xy_box_on_goal) {
    // ゴールを作る.
    cocos2d::Sprite* sprite_goal = cocos2d::Sprite::create(sprite_mapper_->GetImage(kValueGoal));
    sprite_goal->setScale(scaler_->GetScale(), scaler_->GetScale());
    sprite_goal->setPosition(scaler_->GetDisplayPosition(xy1.first, xy1.second));
    this->addChild(sprite_goal, 20);
    // 箱画像に変える.
    //cocos2d::Sprite* sprite_box = sprite_mapper_->Get(xy1.first, xy1.second);
    //sprite_box->setSpriteFrame(cocos2d::Sprite::create(sprite_mapper_->GetImage(kValueBox))->getSpriteFrame());
  }

  // ゴールのspriteをSpriteMapperの管理対象外にする.
  std::vector<std::pair<int, int>> xy_goal;
  sprite_mapper_->GetMap()->Find(kValueGoal, xy_goal);
  for (auto xy2 : xy_goal) {
    cocos2d::Sprite* sprite_box = sprite_mapper_->Get(xy2.first, xy2.second);
    sprite_box->setLocalZOrder(20);
    sprite_mapper_->Set(xy2.first, xy2.second, nullptr);
  }

  return true;
}

///////////////////////////////////////////////////////////////////////////////
void SokobanScene::StopPuzzle() {

}

///////////////////////////////////////////////////////////////////////////////
void SokobanScene::ReplaceScene(const int next_index) {
  // 画面を切り替える.
  cocos2d::Scene* transition = cocos2d::TransitionFade::create(0.5f, SokobanScene::createScene(scenario_title_, scenario_filename_, next_index));
  cocos2d::Director::getInstance()->replaceScene(transition);
}

///////////////////////////////////////////////////////////////////////////////
std::string SokobanScene::Vec2Image(const int vec) {
  switch (vec) {
  case TargetInfo::kVecDown : return sprite_mapper_->GetImage(kValuePlayerDown);
  case TargetInfo::kVecLeft : return sprite_mapper_->GetImage(kValuePlayerLeft);
  case TargetInfo::kVecRight: return sprite_mapper_->GetImage(kValuePlayerRight);
  case TargetInfo::kVecUp   : return sprite_mapper_->GetImage(kValuePlayerUp);
  }
  return "";
}

///////////////////////////////////////////////////////////////////////////////
int SokobanScene::GetFillValue() {
  return kValueSpace;
}

///////////////////////////////////////////////////////////////////////////////
std::string SokobanScene::GetOperationDescription() {
  return "Move>2468, Abort>Esc";
}

}  // puzzle
