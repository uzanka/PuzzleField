#include "PuzzleFieldScene.h"
#include "PuzzleTitleScene.h"
#include "ScenarioManager.h"
#include "ResultManager.h"
#include "ValueManager.h"

namespace puzzle {

///////////////////////////////////////////////////////////////////////////////
PuzzleFieldScene::PuzzleFieldScene()
  : scenario_title_(""),
    scenario_filename_(""),
    scenario_class_(""),
    map_index_(1),
    input_event_enabled_(false),
    repeatable_(true),
    repeat_interval_(0.1f),
    repeat_delay_(0.6f),
    repeat_key_code_(cocos2d::EventKeyboard::KeyCode::KEY_NONE) {
}

///////////////////////////////////////////////////////////////////////////////
bool PuzzleFieldScene::init() {


  // super init first
  if (!Scene::init()) {
    return false;
  }

  repeat_interval_ = 0.1f;
  repeat_delay_ = 0.6f;
  repeat_key_code_ = cocos2d::EventKeyboard::KeyCode::KEY_NONE;

  // マップを読み込む.
  MapReader::Ptr reader = MapManager::getInstance().GetScenario(scenario_class_, scenario_filename_);
  FieldMap::Ptr field_map = reader->Get(map_index_);
  if (field_map == nullptr) {
    return false;
  }

  // マップをセンタリングする.
  int design_width = ScenarioManager::getInstance().GetWidth();
  int design_height = ScenarioManager::getInstance().GetHeight();
  field_map = FieldMap::ExpandMap(field_map, design_width, design_height, reader->GetFillValue());
  if (field_map == nullptr) {
    return false;
  }
  SetScale(field_map);

  std::map<int, std::string> images;
  reader->GetImages(images);

  SpriteMapper::Ptr mapper(new SpriteMapper(this, field_map, images, scaler_->GetScale()));
  sprite_mapper_ = mapper;

  // add your codes below...
  if (!StartPuzzle()) {
    return false;
  }

  // マップ情報を表示する.
  DisplayMapInformation();
  DisplayOperation();
  CreateSystemButtons();

  AddKeyboardEventListener();
  AddTouchEventListener();

  SetInputEventEnabled(true);

  return true;
}

///////////////////////////////////////////////////////////////////////////////
void PuzzleFieldScene::Cleanup() {
  this->getEventDispatcher()->removeAllEventListeners();
}

///////////////////////////////////////////////////////////////////////////////
void PuzzleFieldScene::OnCheckComplete() {
  if (IsComplete()) {
    OnNextMap();
  }
}

///////////////////////////////////////////////////////////////////////////////
bool PuzzleFieldScene::IsComplete() {
  if (player_.fixed_ > 0) {
    return false;
  }
  return true;
}

///////////////////////////////////////////////////////////////////////////////
void PuzzleFieldScene::OnNextMap() {
  MapReader::Ptr reader = MapManager::getInstance().GetScenario(scenario_class_, scenario_filename_);
  int maps = reader->GetMapCount();

  // 結果を登録する.
  ResultManager& result_manager = ResultManager::getInstance();
  result_manager.SetCleared(scenario_title_, map_index_);
  if (result_manager.GetMinumumUnClearedIndex(scenario_title_) >= maps) {
    result_manager.SetCompleted(scenario_title_);
  }
  result_manager.Flush();

  // 最終マップの場合は親画面に戻る.
  int next_index = map_index_ + 1;
  if (next_index > maps) {
    ValueManager::getInstance().SetInt("PuzzleTitleScene::map_index", 1);
    EscapePuzzle();
    return;
  } else {
    ValueManager::getInstance().SetInt("PuzzleTitleScene::map_index", next_index);
  }

  // 画面を切り替える.
  ReplaceScene(next_index);
}

///////////////////////////////////////////////////////////////////////////////
void PuzzleFieldScene::EscapePuzzle() {
  //cocos2d::Director::getInstance()->popScene();
  cocos2d::Scene* scene = PuzzleTitleScene::createScene();
  cocos2d::Scene* transition = cocos2d::TransitionFade::create(0.5f, scene);
  cocos2d::Director::getInstance()->replaceScene(transition);
}

///////////////////////////////////////////////////////////////////////////////
void PuzzleFieldScene::DisplayMapInformation() {
  cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
  cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();

  MapReader::Ptr reader = MapManager::getInstance().GetScenario(scenario_class_, scenario_filename_);
  std::string name = std::to_string(map_index_);
  std::string title = sprite_mapper_->GetMap()->GetTitle();
  if (title.empty()) {
    title = reader->GetTitle();
  }
  std::string author = sprite_mapper_->GetMap()->GetAuthor();
  if (author.empty()) {
    author = reader->GetAuthor();
  }

  if (!title.empty()) {
    name += std::string(" / ") + title;
  }
  if (!author.empty()) {
    name += std::string(" / ") + author;
  }

  bool cleared = ResultManager::getInstance().IsCleared(scenario_title_, map_index_);

  cocos2d::TTFConfig ttfConfig24(reader->GetFontName(), 24);
  cocos2d::Label* label = cocos2d::Label::createWithTTF(ttfConfig24, name);
  label->setWidth(640);
  label->setPosition(origin + cocos2d::Vec2(label->getWidth() / 2, visibleSize.height - 12));
  label->setHorizontalAlignment(cocos2d::TextHAlignment::LEFT);
  label->enableBold();
  if (cleared) {
    label->setColor(cocos2d::Color3B::GREEN);
  } else {
    label->setColor(cocos2d::Color3B::WHITE);
  }
  this->addChild(label, 20);
}

///////////////////////////////////////////////////////////////////////////////
void PuzzleFieldScene::DisplayOperation() {
  cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
  cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();

  std::string name = GetOperationDescription();

  MapReader::Ptr reader = MapManager::getInstance().GetScenario(scenario_class_, scenario_filename_);
  cocos2d::TTFConfig ttfConfig24(reader->GetFontName(), 24);
  cocos2d::Label* operation = cocos2d::Label::createWithTTF(ttfConfig24, name);
  operation->setWidth(640);
  operation->setPosition(origin + cocos2d::Vec2(operation->getWidth() / 2, 12));
  operation->setHorizontalAlignment(cocos2d::TextHAlignment::LEFT);
  //operation->enableBold();
  this->addChild(operation, 20);
}

///////////////////////////////////////////////////////////////////////////////
int PuzzleFieldScene::GetFillValue() {
  return 0;
}

///////////////////////////////////////////////////////////////////////////////
std::string PuzzleFieldScene::GetOperationDescription() {
  return "";
}

///////////////////////////////////////////////////////////////////////////////
void PuzzleFieldScene::SetScale(FieldMap::Ptr field_map) {
  Scaler::Ptr scaler(new Scaler(field_map->Width(), field_map->Height()));
  scaler_ = scaler;
}

///////////////////////////////////////////////////////////////////////////////
void PuzzleFieldScene::CreateSystemButtons() {
  cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
  cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();

  cocos2d::ui::Button* button_power = cocos2d::ui::Button::create("images/power.png", "images/power_selected.png", "images/power_disabled.png");
  button_power->setPosition(origin + cocos2d::Vec2(visibleSize.width - 16, visibleSize.height - 16));
  this->addChild(button_power, 50);

  cocos2d::ui::Button* button_escape = cocos2d::ui::Button::create("images/escape.png", "images/escape_selected.png", "images/escape_disabled.png");
  button_escape->setPosition(origin + cocos2d::Vec2(visibleSize.width - 32 - 20, visibleSize.height - 16));
  this->addChild(button_escape, 50);

  button_power->addTouchEventListener(CC_CALLBACK_2(PuzzleFieldScene::buttonEventPower, this));
  button_escape->addTouchEventListener(CC_CALLBACK_2(PuzzleFieldScene::buttonEventEscape, this));
}

///////////////////////////////////////////////////////////////////////////////
void PuzzleFieldScene::buttonEventPower(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type) {
  switch (type) {
  case cocos2d::ui::Widget::TouchEventType::BEGAN:
    //StopPuzzle();
    //cocos2d::Director::getInstance()->end();
    break;
  case cocos2d::ui::Widget::TouchEventType::ENDED:
    StopPuzzle();
    cocos2d::Director::getInstance()->end();
    break;
  }
}

///////////////////////////////////////////////////////////////////////////////
void PuzzleFieldScene::buttonEventEscape(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type) {
  switch (type) {
  case cocos2d::ui::Widget::TouchEventType::BEGAN:
    //EscapePuzzle();
    break;
  case cocos2d::ui::Widget::TouchEventType::ENDED:
    EscapePuzzle();
    break;
  }
}

}  // puzzle
