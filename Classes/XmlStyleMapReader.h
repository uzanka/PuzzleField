#ifndef __PUZZLE_XML_STYLE_MAP_READER_H__
#define __PUZZLE_XML_STYLE_MAP_READER_H__

#include "PuzzleDefine.h"
#include "BaseStyleMapReader.h"
#include "FieldMap.h"
#include "tinyxml2/tinyxml2.h"

namespace puzzle {

/*!
 * @brief 個別マップファイルを読み込む.
 * @details
 * 以下のフォーマットとする.
 * ";"で始まる行をコメントとする.
 * 文字コードをマップ値とする.
 * 縦横サイズは全体の解析結果から決定する.
 */
class XmlStyleMapReader : public BaseStyleMapReader {
public:
  /*!
   * @brief Constuctor
   * @param[in]  filename 個別マップファイル名
   * @param[out] maps     マップリスト
   */
  XmlStyleMapReader(const std::string filename, std::vector<FieldMap::Ptr>& maps, const int fillvalue);

  /*!
   * @brief Destructor
   */
  virtual ~XmlStyleMapReader();

  /*!
   * @brief 個別マップファイルを読み込む.
   * @retval true  成功
   * @retval false 失敗
   * @details
   * 個別マップファイルを読み込む.
   */
  virtual void Read();

  int GetWidth() const;
  int GetHeight() const;

protected:
  void ReadOneMap(tinyxml2::XMLElement* LevelElement);

  void ConvertMap(
    std::vector<std::string>& field,
    const int width,
    const int height,
    const std::string title,
    const std::string author);
};

}  // puzzle

#endif  // __PUZZLE_XML_STYLE_MAP_READER_H__
