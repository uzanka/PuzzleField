#ifndef __PUZZLE_JSON_STYLE_MAP_READER_H__
#define __PUZZLE_JSON_STYLE_MAP_READER_H__

#include "json/rapidjson.h"
#include "json/document.h"
#include "PuzzleDefine.h"
#include "BaseStyleMapReader.h"
#include "FieldMap.h"

namespace puzzle {

/*!
 * @brief マップファイル(JSON)を読み込む.
 */
class JsonStyleMapReader : public BaseStyleMapReader {
public:
  /*!
   * @brief Constructor
   * @param[in]  filename 個別マップファイル名
   * @param[out] maps     マップリスト
   */
  JsonStyleMapReader(const std::string filename, std::vector<FieldMap::Ptr>& maps, const int fillvalue);

  /*!
   * @brief Destructor
   */
  virtual ~JsonStyleMapReader();

  /*!
   * @brief マップファイル(JSON)を読み込む.
   * @details
   * マップファイル(JSON)を読み込む.
   */
  virtual void Read();

protected:
  void ReadOneMap(const rapidjson::Value& json_phase);

  FieldMap::Ptr ConvertMap(
    std::vector<std::string>& lines,
    const int width,
    const int height);
};

}  // puzzle

#endif  // __PUZZLE_JSON_STYLE_MAP_READER_H__
