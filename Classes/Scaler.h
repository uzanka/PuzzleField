#ifndef __PUZZLE_SCALER_H__
#define __PUZZLE_SCALER_H__

#include "PuzzleDefine.h"

namespace puzzle {

/*!
 * @brief スケールを管理する.
 */
class Scaler {
public:
  typedef std::shared_ptr<Scaler> Ptr;

  /*!
   * @brief コンストラクタ
   * @param[in] scale スケール
   */
  Scaler(const double scale);
  Scaler(const int width, const int height);

  /*!
   * @brief デストラクタ
   */
  virtual ~Scaler();

  double GetScale() const;

  /*!
   * @brief スプライトを描画する位置を取得する.
   * @param[in] x X座標
   * @param[in] y Y座標
   * @return 描画位置
   * @details
   * スプライトを描画する位置を取得する.
   */
  cocos2d::Vec2 GetDisplayPosition(const int x, const int y);

  double GetScaledSize(const double count = 1.0f);
  cocos2d::Sprite* CreateSprite(const std::string name);
  cocos2d::Sprite* CreateSprite(const std::string name, const int x, const int y);

protected:
  double scale_;  //!< スケール
};

}  // puzzle

#endif // __PUZZLE_SCALER_H__
