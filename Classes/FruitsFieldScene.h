#ifndef __PUZZLE_FRUITS_FIELD_SCENE_H__
#define __PUZZLE_FRUITS_FIELD_SCENE_H__

#include "PuzzleDefine.h"
#include "SpriteMapper.h"
#include "PuzzleFieldScene.h"

namespace puzzle {

/*!
 * @brief FruitsFieldSceneシーン
 */
class FruitsFieldScene : public PuzzleFieldScene {
public:
  /*!
   * @brief Implement the "static create()" method manually.
   * @param[in] title    シナリオタイトル名
   * @param[in] filename ファイル名
   * @param[in] index    マップ番号(1～)
   * @details
   * FruitsFieldシーンを作成する.
   */
  //CREATE_FUNC(FruitsFieldScene);
  static FruitsFieldScene* create(const std::string title, const std::string filename, const int index) {
    FruitsFieldScene* instance = new(std::nothrow) FruitsFieldScene(title, filename, index);
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
   * @brief FruitsFieldSceneシーンを作成する.
   * @param[in] title    シナリオタイトル名
   * @param[in] filename ファイル名
   * @param[in] index    マップ番号(1～)
   * @details
   * FruitsFieldSceneシーンを作成する.
   */
  static cocos2d::Scene* createScene(const std::string title, const std::string filename, const int index);

  FruitsFieldScene(const std::string title, const std::string filename, const int index);

  // InputDispatcher
  virtual void OnKeyPressedUp();
  virtual void OnKeyPressedDown();
  virtual void OnKeyPressedLeft();
  virtual void OnKeyPressedRight();
  virtual void OnKeyPressedEnter();
  virtual void OnKeyPressedSpace();
  virtual void OnKeyPressedEscape();
  void OnMove(const int vx, const int vy, const int vec);
  void OnAction(const int vx, const int vy, const int vec);

  void MoveBlock(const int x, const int y, const int vx, const int vy, const int vec);
  void DeleteBlock(const int x, const int y);
  std::string Vec2Image(const int vec);
  virtual void ReplaceScene(const int next_index);

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
  virtual int GetFillValue();
  virtual std::string GetOperationDescription();

private:
  enum ValueType {
    kValueSpace       = 0,
    kValueFruits      = 1,
    kValueArrowDown   = 2,
    kValueArrowLeft   = 4,
    kValueArrowRight  = 6,
    kValuePlayer      = 7,
    kValueArrowUp     = 8,
    kValueWall        = 9,
    kValuePlayerDown  = 10,
    kValuePlayerLeft  = 11,
    kValuePlayerRight = 12,
    kValuePlayerUp    = 13
  };
};

}  // puzzle

#endif  // __PUZZLE_FRUITS_FIELD_SCENE_H__
