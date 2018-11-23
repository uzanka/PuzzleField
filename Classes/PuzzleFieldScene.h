#ifndef __PUZZLE_PUZZLE_FIELD_SCENE_H__
#define __PUZZLE_PUZZLE_FIELD_SCENE_H__

#include "PuzzleDefine.h"
#include "MapManager.h"
#include "MapReader.h"
#include "SpriteMapper.h"
#include "TargetInfo.h"
#include "Scaler.h"
#include "ui/CocosGUI.h"

namespace puzzle {

class PuzzleFieldScene : public cocos2d::Scene {
public:
  PuzzleFieldScene();

  /*!
   * @brief on "init" you need to initialize your instance.
   * @retval true  成功
   * @retval false 失敗
   * @details
   * シーンを初期化する.
   */
  virtual bool init();

protected:
  /*!
   * @brief 画面を作成する.
   * @retval true  成功
   * @retval false 失敗
   * @details
   * 画面を作成する.
   */
  virtual bool StartPuzzle() = 0;

  /*!
   * @brief 画面を破棄する.
   * @details
   * 画面を破棄する.
   */
  virtual void StopPuzzle() = 0;

  // InputReceiver
  virtual void OnKeyPressedUp() {}
  virtual void OnKeyPressedDown() {}
  virtual void OnKeyPressedLeft() {}
  virtual void OnKeyPressedRight() {}
  virtual void OnKeyPressedEnter() {}
  virtual void OnKeyPressedSpace() {}
  virtual void OnKeyPressedEscape() {}
  void SetRepeatable(const bool flag);
  void SetInputEventEnabled(const bool enable);

  // TouchEventListener
  void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);
  void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);

  void OnCheckComplete();
  virtual bool IsComplete();
  virtual void OnNextMap();
  virtual void ReplaceScene(const int next_index) = 0;
  virtual void DisplayMapInformation();
  virtual void DisplayOperation();
  void CreateSystemButtons();
  void EscapePuzzle();
  virtual int GetFillValue();
  virtual std::string GetOperationDescription();
  void SetScale(FieldMap::Ptr field_map);

private:
  void Cleanup();
  void AddKeyboardEventListener();
  void AddTouchEventListener();
  void SetRepeatTimer(cocos2d::EventKeyboard::KeyCode keyCode);
  void DeleteRepeatTimer();
  void OnRepeatTimer(float frame);
  void OnKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode);
  void OnKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode);

  void buttonEventPower(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
  void buttonEventEscape(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);

protected:
  // 選択画面から渡される情報
  std::string scenario_title_;
  std::string scenario_filename_;
  std::string scenario_class_;
  int map_index_;

  Scaler::Ptr scaler_;

  // イベントディスパッチ
  bool input_event_enabled_;
  bool repeatable_;
  float repeat_interval_;
  float repeat_delay_;
  cocos2d::EventKeyboard::KeyCode repeat_key_code_;

  SpriteMapper::Ptr sprite_mapper_;  //!< 画面管理

  // 対象情報
  TargetInfo player_;
};

}  // puzzle

#endif  // __PUZZLE_PUZZLE_FIELD_SCENE_H__
