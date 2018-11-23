#include "PuzzleTitleScene.h"
#include "ScenarioManager.h"
#include "ValueManager.h"
#include "PuzzleFieldSceneFactory.h"

namespace puzzle {

///////////////////////////////////////////////////////////////////////////////
void PuzzleTitleScene::OnKeyPressedUp() {
  if (scenario_selector_->GetMode() == SelectorLabel::kModeSelect) {
    scenario_selector_->OnKeyPressUp();
    if (scenario_selector_->GetIndex() == map_selector_->GetTag()) {
      map_selector_->SetMode(SelectorLabel::kModeUnselect);
    } else {
      map_selector_->SetMode(SelectorLabel::kModeDisable);
    }
    UpdateMapClearedState();
  }
  if (map_selector_->GetMode() == SelectorLabel::kModeSelect) {
    map_selector_->OnKeyPressUp();
    UpdateMapClearedState();
  }
}

///////////////////////////////////////////////////////////////////////////////
void PuzzleTitleScene::OnKeyPressedDown() {
  if (scenario_selector_->GetMode() == SelectorLabel::kModeSelect) {
    scenario_selector_->OnKeyPressDown();
    if (scenario_selector_->GetIndex() == map_selector_->GetTag()) {
      map_selector_->SetMode(SelectorLabel::kModeUnselect);
    } else {
      map_selector_->SetMode(SelectorLabel::kModeDisable);
    }
    UpdateMapClearedState();
  }
  if (map_selector_->GetMode() == SelectorLabel::kModeSelect) {
    map_selector_->OnKeyPressDown();
    UpdateMapClearedState();
  }
}

///////////////////////////////////////////////////////////////////////////////
void PuzzleTitleScene::OnKeyPressedLeft() {
  map_selector_->SetMode(SelectorLabel::kModeUnselect);
  scenario_selector_->SetMode(SelectorLabel::kModeSelect);
  start_button_->setColor(cocos2d::Color3B::GRAY);
}

///////////////////////////////////////////////////////////////////////////////
void PuzzleTitleScene::OnKeyPressedRight() {
  scenario_selector_->SetMode(SelectorLabel::kModeUnselect);
  int index = scenario_selector_->GetIndex();

  map_selector_->SetMode(SelectorLabel::kModeSelect);
  start_button_->setColor(cocos2d::Color3B::RED);
  if (map_selector_->GetTag() == index) {
    UpdateMapClearedState();
    return;
  }

  std::vector<std::string> data;
  GetMapSelectorData(index, data);

  map_selector_->SetTag(index);
  map_selector_->SetData(data, 1);

  UpdateMapClearedState();
}

///////////////////////////////////////////////////////////////////////////////
void PuzzleTitleScene::OnKeyPressedEnter() {
  if (map_selector_->GetMode() != SelectorLabel::kModeSelect) {
    return;
  }

  // 選択したシナリオとマップ番号を取得する.
  int scenario_index = scenario_selector_->GetIndex();
  std::string title;
  std::string filename;
  int maps = 1;
  std::string class_name;
  ScenarioManager::getInstance().GetScenario(scenario_index, title, filename, maps, class_name);
  int map_index = map_selector_->GetIndex();

  // この画面に戻ってきたときの選択項目を退避する.
  ValueManager::getInstance().SetInt("PuzzleTitleScene::scenario_index", scenario_index);
  ValueManager::getInstance().SetInt("PuzzleTitleScene::map_index", map_index);
  ValueManager::getInstance().SetInt("PuzzleTitleScene::selector", 1);

  // 画面を切り替える.
  PuzzleFieldSceneFactory factory;
  cocos2d::Scene* scene = factory.Create(class_name, title, filename, map_index);
  if (scene == nullptr) {
    return;
  }
  cocos2d::Scene* transition = cocos2d::TransitionFade::create(0.5f, scene);
  //cocos2d::Director::getInstance()->pushScene(transition);
  cocos2d::Director::getInstance()->replaceScene(transition);
}

}  // puzzle
