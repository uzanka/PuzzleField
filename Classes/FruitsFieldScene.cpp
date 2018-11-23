#include "FruitsFieldScene.h"
#include "MapManager.h"
#include "MapReader.h"

namespace puzzle {

///////////////////////////////////////////////////////////////////////////////
cocos2d::Scene* FruitsFieldScene::createScene(const std::string title, const std::string filename, const int index) {
  return FruitsFieldScene::create(title, filename, index);
}

///////////////////////////////////////////////////////////////////////////////
FruitsFieldScene::FruitsFieldScene(const std::string title, const std::string filename, const int index) {
  scenario_title_ = title;
  scenario_filename_ = filename;
  scenario_class_ = "FruitsField";
  map_index_ = index;
}

///////////////////////////////////////////////////////////////////////////////
bool FruitsFieldScene::StartPuzzle() {
  // 主人公の位置を探す.
  if (!sprite_mapper_->GetMap()->Find(kValuePlayer, player_.x_, player_.y_)) {
    return false;
  }
  player_.vec_ = TargetInfo::kVecDown;

  // ボーナスの数を調べる
  std::vector<std::pair<int, int>> xy;
  player_.fixed_ = sprite_mapper_->GetMap()->Find(kValueFruits, xy);

  return true;
}

///////////////////////////////////////////////////////////////////////////////
void FruitsFieldScene::StopPuzzle() {

}

///////////////////////////////////////////////////////////////////////////////
std::string FruitsFieldScene::Vec2Image(const int vec) {
  switch (vec) {
  case TargetInfo::kVecDown : return sprite_mapper_->GetImage(kValuePlayerDown);
  case TargetInfo::kVecLeft : return sprite_mapper_->GetImage(kValuePlayerLeft);
  case TargetInfo::kVecRight: return sprite_mapper_->GetImage(kValuePlayerRight);
  case TargetInfo::kVecUp   : return sprite_mapper_->GetImage(kValuePlayerUp);
  }
  return "";
}

///////////////////////////////////////////////////////////////////////////////
void FruitsFieldScene::ReplaceScene(const int next_index) {
  // 画面を切り替える.
  cocos2d::Scene* transition = cocos2d::TransitionFade::create(0.5f, FruitsFieldScene::createScene(scenario_title_, scenario_filename_, next_index));
  cocos2d::Director::getInstance()->replaceScene(transition);
}

///////////////////////////////////////////////////////////////////////////////
int FruitsFieldScene::GetFillValue() {
  return kValueWall;
}

///////////////////////////////////////////////////////////////////////////////
std::string FruitsFieldScene::GetOperationDescription() {
  return "Move>2468, Action>Space, Abort>Esc";
}

}  // puzzle
