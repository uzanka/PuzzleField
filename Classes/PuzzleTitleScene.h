#ifndef __PUZZLE_PUZZLE_TITLE_SCENE_H__
#define __PUZZLE_PUZZLE_TITLE_SCENE_H__

#include "PuzzleDefine.h"
#include "SpriteMapper.h"
#include "SelectorLabel.h"
#include "PuzzleFieldScene.h"

namespace puzzle {

class PuzzleTitleScene : public PuzzleFieldScene {
public:
  /*!
   * @brief Implement the "static create()" method manually.
   */
  CREATE_FUNC(PuzzleTitleScene);

  /*!
   * @brief 自シーンを生成する.
   * @return Scene
   * @details
   * 自シーンを生成する.
   */
  static cocos2d::Scene* createScene();

  PuzzleTitleScene();

  virtual void onEnterTransitionDidFinish();

  // InputDispatcher
  virtual void OnKeyPressedUp();
  virtual void OnKeyPressedDown();
  virtual void OnKeyPressedLeft();
  virtual void OnKeyPressedRight();
  virtual void OnKeyPressedEnter();

protected:
  /*!
   * @brief 画面を作成する.
   * @retval true  成功
   * @retval false 失敗
   * @details
   * 画面を作成する.
   */
  virtual bool StartPuzzle();

  /*!
   * @brief 画面を破棄する.
   * @details
   * 画面を破棄する.
   */
  virtual void StopPuzzle();

  virtual void ReplaceScene(const int next_index) {}
  virtual void DisplayMapInformation() {}
  void GetMapSelectorData(const int index, std::vector<std::string>& data);
  void UpdateMapClearedState();
  virtual std::string GetOperationDescription();

private:
  SelectorLabel::Ptr scenario_selector_;  //!< シナリオ選択コントロール
  SelectorLabel::Ptr map_selector_;       //!< マップ選択コントロール
  cocos2d::Label*    start_button_;       //!< スタートラベル
  cocos2d::Label*    completed_label_;    //!< シナリオ完了ラベル
  cocos2d::Label*    cleared_label_;      //!< マップクリアラベル
};

}  // puzzle

#endif  // __PUZZLE_PUZZLE_TITLE_SCENE_H__
