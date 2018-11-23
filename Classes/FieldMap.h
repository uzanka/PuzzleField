#ifndef __PUZZLE_FIELD_MAP_H__
#define __PUZZLE_FIELD_MAP_H__

#include "PuzzleDefine.h"

namespace puzzle {

/*!
 * @brief マップを管理する.
 */
class FieldMap {
public:
  typedef std::shared_ptr<FieldMap> Ptr;

  /*!
   * @brief Constructor
   * @param[in] width  マップ幅
   * @param[in] height マップ高さ
   * @param[in] value  マップ値
   */
  FieldMap(const int width, const int height, const int value = 0);

  /*!
   * @brief Destructor
   */
  virtual ~FieldMap();

  /*!
   * @brief マップ幅を取得する.
   * @return マップ幅
   * @details
   * マップ幅を取得する.
   */
  int Width() const;

  /*!
   * @brief マップ高さを取得する.
   * @return マップ高さ
   * @details
   * マップ高さを取得する.
   */
  int Height() const;

  /*!
   * @brief マップ値を取得する.
   * @param[in] x X座標
   * @param[in] y Y座標
   * @return マップ値
   * @details
   * マップ値を取得する.
   */
  int Get(const int x, const int y) const;

  /*!
   * @brief マップに値をセットする.
   * @param[in] x X座標
   * @param[in] y Y座標
   * @param[in] value マップ値
   * @details
   * マップに値をセットする.
   */
  void Set(const int x, const int y, const int value);

  /*!
   * @brief マップをクリアする.
   * @param[in] value マップ値
   * @details
   * マップをクリアする.
   */
  void Clear(const int value = 0);

  /*!
   * @brief マップ値の位置を探す.
   * @param[in]  value 検索するマップ値
   * @param[out] x     X座標
   * @param[out] y     Y座標
   * @retval true  見つかった
   * @retval false 見つからなかった
   * @details
   * マップからマップ値の座標を探し最初に見つかった座標を返す.
   */
  bool Find(const int value, int& x, int& y);

  /*!
   * @brief マップ値の位置を探す.
   * @param[in]  value 検索するマップ値
   * @param[out] xy    座標一覧
   * @return 見つかった座標数
   * @details
   * マップからマップ値の座標を探す.
   */
  int Find(const int value, std::vector<std::pair<int, int>>& xy);

  std::string GetTitle() const;
  std::string GetAuthor() const;
  void SetTitle(const std::string title);
  void SetAuthor(const std::string author);

  /*!
   * @brief マップをセンタリングする.
   * @param[in] src           元マップ
   * @param[in] width         幅
   * @param[in] height        高さ
   * @param[in] value         埋めるマップ値
   * @return 新しいマップ
   * @details
   * マップを拡張してセンタリングする.
   */
  static FieldMap::Ptr ExpandMap(FieldMap::Ptr src, const int width, const int height, const int value = 0);

protected:
  int  width_;      //!< マップ幅
  int  height_;     //!< マップ高さ
  int* field_map_;  //!< マップ(int[width*height])
  std::string title_;
  std::string author_;
};

}  // puzzle

#endif  // __PUZZLE_FIELD_MAP_H__
