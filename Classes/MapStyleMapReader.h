#ifndef __PUZZLE_MAP_STYLE_MAP_READER_H__
#define __PUZZLE_MAP_STYLE_MAP_READER_H__

#include "PuzzleDefine.h"
#include "BaseStyleMapReader.h"
#include "FieldMap.h"

namespace puzzle {

/*!
 * @brief 個別マップファイルを読み込む.
 * @details
 * 以下のフォーマットとする.
 * ";"で始まる行をコメントとする.
 * 文字コードをマップ値とする.
 * ";Author: {author}" を著作者として認識する.
 * ";Title: {title}" をタイトルとして認識する.
 * 縦横サイズは全体の解析結果から決定する.
 */
class MapStyleMapReader : public BaseStyleMapReader {
public:
  /*!
   * @brief Constuctor
   * @param[in]  filename 個別マップファイル名
   * @param[out] maps     マップリスト
   */
  MapStyleMapReader(const std::string filename, std::vector<FieldMap::Ptr>& maps, const int fillvalue);

  /*!
   * @brief Destructor
   */
  virtual ~MapStyleMapReader();

  /*!
   * @brief 個別マップファイルを読み込む.
   * @retval true  成功
   * @retval false 失敗
   * @details
   * 個別マップファイルを読み込む.
   */
  virtual void Read();

protected:
  int ReadOneMap(const std::vector<std::string>& lines, std::size_t i);

  void ConvertMap(
    std::vector<std::string>& field,
    const int width,
    const int height,
    const std::string title,
    const std::string author);
};

}  // puzzle

#endif  // __PUZZLE_MAP_STYLE_MAP_READER_H__
