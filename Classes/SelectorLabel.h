#ifndef __PUZZLE_SELECTOR_LABEL_H__
#define __PUZZLE_SELECTOR_LABEL_H__

#include "PuzzleDefine.h"

namespace puzzle {

/*!
 * @brief 選択機能を持つラベルを管理する.
 */
class SelectorLabel {
public:
  typedef std::shared_ptr<SelectorLabel> Ptr;

  enum SelectorLabelMode {
    kModeDisable  = 0,  //!< 無効
    kModeUnselect = 1,  //!< 非選択
    kModeSelect   = 2   //!< 選択
  };

  /*!
   * @brief コンストラクタ
   * @param[in] scene    シーン
   * @param[in] title    ラベル名
   * @param[in] data     選択可能テキスト一覧
   * @param[in] position 描画位置
   * @param[in] index    選択項目(1～)
   */
  SelectorLabel(
    cocos2d::Scene* scene,
    const std::string title,
    const std::string fontname,
    const std::vector<std::string>& data,
    const cocos2d::Vec2 position,
    const int index);

  /*!
   * @brief デストラクタ
   */
  virtual ~SelectorLabel();

  /*!
   * @brief ラベルのモードをセットする.
   * @param[in] mode モード
   * @details
   * ラベルのモードをセットする.
   * - 0の場合は無効状態で描画する.
   * - 1の場合は有効状態の非選択状態で描画する.
   * - 2の場合は有効状態の選択状態で描画する.
   */
  void SetMode(const int mode);

  int GetMode() const;

  void OnKeyPressUp();
  void OnKeyPressDown();

  int GetTag() const;
  void SetTag(const int tag);
  int GetIndex() const;
  void SetIndex(const int index);
  void SetData(std::vector<std::string>& data);
  void SetData(std::vector<std::string>& data, const int index);

protected:
  cocos2d::Scene*          scene_;     //!< シーン
  std::string              title_;
  std::string              fontname_;
  std::vector<std::string> data_;
  cocos2d::Vec2            position_;
  int                      mode_;
  int                      index_;     //!< 選択されているデータ(0, 1～)
  cocos2d::Label*          label_;
  cocos2d::Label*          text_;
  int                      tag_;
};

}  // puzzle

#endif // __PUZZLE_SELECTOR_LABEL_H__
