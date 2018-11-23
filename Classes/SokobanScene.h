#ifndef __PUZZLE_SOKOBAN_SCENE_H__
#define __PUZZLE_SOKOBAN_SCENE_H__

#include "PuzzleDefine.h"
#include "SpriteMapper.h"
#include "PuzzleFieldScene.h"

namespace puzzle {

/*!
 * @brief SokobanSceneシーン
 */
class SokobanScene : public PuzzleFieldScene {
public:
  /*!
   * @brief Implement the "static create()" method manually.
   * @param[in] title    シナリオタイトル名
   * @param[in] filename ファイル名
   * @param[in] index    マップ番号(1～)
   * @details
   * SokobanSceneシーンを作成する.
   */
  //CREATE_FUNC(SokobanScene);
  static SokobanScene* create(const std::string title, const std::string filename, const int index) {
    SokobanScene* instance = new(std::nothrow) SokobanScene(title, filename, index);
    if (instance && instance->init()) {
      instance->autorelease();
      return instance;
    } else {
      delete instance;
      instance = nullptr;
      return nullptr;
    }
  }

  /*!
   * @brief SokobanSceneシーンを作成する.
   * @param[in] title    シナリオタイトル名
   * @param[in] filename ファイル名
   * @param[in] index    マップ番号(1～)
   * @details
   * SokobanSceneシーンを作成する.
   */
  static cocos2d::Scene* createScene(const std::string title, const std::string filename, const int index);

  /*!
   * @brief Constructor
   * @param[in] title    シナリオタイトル名
   * @param[in] filename ファイル名
   * @param[in] index    マップ番号(1～)
   */
  SokobanScene(const std::string title, const std::string filename, const int index);

  // InputDispatcher
  virtual void OnKeyPressedUp();
  virtual void OnKeyPressedDown();
  virtual void OnKeyPressedLeft();
  virtual void OnKeyPressedRight();
  virtual void OnKeyPressedEnter();
  virtual void OnKeyPressedSpace();
  virtual void OnKeyPressedEscape();
  void OnMove(const int vx, const int vy, const int vec);

  void MovePlayer(const int vx, const int vy);
  void MoveBox(const int vx, const int vy);

  std::string Vec2Image(const int vec);

private:
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

  virtual void ReplaceScene(const int next_index);
  virtual int GetFillValue();
  virtual std::string GetOperationDescription();

private:
  enum ValueType {
    kValueSpace        = ' ',
    kValueWall         = '#',
    kValueBox          = '$',
    kValueBoxOnGoal    = '*',
    kValuePlayer       = '@',
    kValuePlayerOnGoal = '+',
    kValueGoal         = '.',
    kValuePlayerDown   = 'D',
    kValuePlayerLeft   = 'L',
    kValuePlayerRight  = 'R',
    kValuePlayerUp     = 'U'
  };
};

}  // puzzle

#endif  // __PUZZLE_SOKOBAN_SCENE_H__
