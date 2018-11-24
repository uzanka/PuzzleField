#include "PuzzleTitleScene.h"
#include "SimpleAudioEngine.h"
#include "MapReader.h"
#include "FieldMap.h"
#include "SelectorLabel.h"
#include "ScenarioManager.h"
#include "MapManager.h"
#include "FruitsFieldScene.h"
#include "ValueManager.h"
#include "ResultManager.h"

namespace puzzle {

///////////////////////////////////////////////////////////////////////////////
cocos2d::Scene* PuzzleTitleScene::createScene() {
  return PuzzleTitleScene::create();
}

///////////////////////////////////////////////////////////////////////////////
PuzzleTitleScene::PuzzleTitleScene()
  : start_button_(nullptr),
    completed_label_(nullptr),
    cleared_label_(nullptr) {
  scenario_title_ = "";
  scenario_filename_ = "title/puzzle_title.json";
  scenario_class_ = "Title";
}

///////////////////////////////////////////////////////////////////////////////
bool PuzzleTitleScene::StartPuzzle() {
  cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
  cocos2d::Vec2 visibleOrigin = cocos2d::Director::getInstance()->getVisibleOrigin();
  MapReader::Ptr reader = MapManager::getInstance().Read(scenario_class_, scenario_filename_);
  std::string fontname = reader->GetFontName();
  cocos2d::TTFConfig ttfConfig64(fontname, 64);
  cocos2d::TTFConfig ttfConfig24(fontname, 24);

  int scenario_index = ValueManager::getInstance().GetInt("PuzzleTitleScene::scenario_index", 1);
  int map_index = ValueManager::getInstance().GetInt("PuzzleTitleScene::map_index", 1);
  int selector = ValueManager::getInstance().GetInt("PuzzleTitleScene::selector", 0);

  // title
  auto label_title = cocos2d::Label::createWithTTF(ttfConfig64, reader->GetTitle());
  label_title->setPosition(visibleOrigin + cocos2d::Vec2(visibleSize.width / 2, visibleSize.height / 2 + scaler_->GetScaledSize(3)));
  label_title->setColor(cocos2d::Color3B::WHITE);
  label_title->enableBold();
  this->addChild(label_title, 50);

  // scenario selector
  std::vector<std::string> scenario_data;
  for (int i = 1; i <= ScenarioManager::getInstance().GetCount(); i++) {
    std::string title = ScenarioManager::getInstance().GetScenarioTitle(i);
    scenario_data.push_back(title);
  }
  cocos2d::Vec2 scenario_position(visibleOrigin + cocos2d::Vec2(visibleSize.width / 10 * 4, visibleSize.height / 2 - scaler_->GetScaledSize(0.5)));
  SelectorLabel::Ptr scenario_selector(new SelectorLabel(this, "* Scenario *", fontname, scenario_data, scenario_position, scenario_index));
  scenario_selector_ = scenario_selector;

  // map selector
  std::vector<std::string> map_data;
  GetMapSelectorData(scenario_index, map_data);
  cocos2d::Vec2 map_position(visibleOrigin + cocos2d::Vec2(visibleSize.width / 10 * 8, visibleSize.height / 2 - scaler_->GetScaledSize(0.5)));
  SelectorLabel::Ptr map_selector(new SelectorLabel(this, "* Map *", fontname, map_data, map_position, map_index));
  map_selector_ = map_selector;
  map_selector_->SetTag(scenario_index);

  scenario_selector_->SetMode(SelectorLabel::kModeSelect);
  map_selector_->SetMode(SelectorLabel::kModeDisable);

  // start button
  start_button_ = cocos2d::Label::createWithTTF(ttfConfig24, "[Enter key to start]");
  cocos2d::Vec2 start_position(visibleOrigin + cocos2d::Vec2(visibleSize.width / 2, visibleSize.height / 2 - scaler_->GetScaledSize(4)));
  start_button_->setPosition(start_position);
  start_button_->enableBold();
  start_button_->setColor(cocos2d::Color3B::GRAY);
  this->addChild(start_button_, 50);

  // completed label
  completed_label_ = cocos2d::Label::createWithTTF(ttfConfig24, "Completed!");
  cocos2d::Vec2 completed_position(visibleOrigin + cocos2d::Vec2(visibleSize.width / 10 * 4, visibleSize.height / 2 - scaler_->GetScaledSize(2.5)));
  completed_label_->setPosition(completed_position);
  completed_label_->enableBold();
  completed_label_->setColor(cocos2d::Color3B::GREEN);
  completed_label_->setVisible(false);
  this->addChild(completed_label_, 50);

  // cleared label
  cleared_label_ = cocos2d::Label::createWithTTF(ttfConfig24, "Cleared!");
  cocos2d::Vec2 cleared_position(visibleOrigin + cocos2d::Vec2(visibleSize.width / 10 * 8, visibleSize.height / 2 - scaler_->GetScaledSize(2.5)));
  cleared_label_->setPosition(cleared_position);
  cleared_label_->enableBold();
  cleared_label_->setColor(cocos2d::Color3B::GREEN);
  cleared_label_->setVisible(false);
  this->addChild(cleared_label_, 50);

  if ((scenario_data.size() == 1) || selector) {
    OnKeyPressedRight();
  }

  UpdateMapClearedState();

  return true;
}

///////////////////////////////////////////////////////////////////////////////
void PuzzleTitleScene::StopPuzzle() {
  scenario_selector_ = nullptr;
  map_selector_ = nullptr;
  start_button_ = nullptr;
  sprite_mapper_ = nullptr;
}

///////////////////////////////////////////////////////////////////////////////
void PuzzleTitleScene::GetMapSelectorData(const int index, std::vector<std::string>& data) {
  int maps = ScenarioManager::getInstance().GetScenarioMapCount(index);
  for (int i = 1; i <= maps; i++) {
    std::string item = std::to_string(i);
    data.push_back(item);
  }
}

///////////////////////////////////////////////////////////////////////////////
void PuzzleTitleScene::onEnterTransitionDidFinish() {

}

///////////////////////////////////////////////////////////////////////////////
void PuzzleTitleScene::UpdateMapClearedState() {
  bool completed = false;
  bool cleared = false;

  int scenario_index = scenario_selector_->GetIndex();
  std::string title = ScenarioManager::getInstance().GetScenarioTitle(scenario_index);
  if (ResultManager::getInstance().IsCompleted(title)) {
    completed = true;
  }

  if (map_selector_->GetMode() != SelectorLabel::kModeDisable) {
    int map_index = map_selector_->GetIndex();
    if (ResultManager::getInstance().IsCleared(title, map_index)) {
      cleared = true;
    }
  }

  completed_label_->setVisible(completed);
  cleared_label_->setVisible(cleared);
}

///////////////////////////////////////////////////////////////////////////////
std::string PuzzleTitleScene::GetOperationDescription() {
  return "Select>2468, Start>Enter";
}

}  // puzzle
