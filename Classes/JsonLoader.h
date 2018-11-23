#ifndef __PUZZLE_JSON_LOADER_H__
#define __PUZZLE_JSON_LOADER_H__

#include "PuzzleDefine.h"
#include "json/rapidjson.h"
#include "json/document.h"

namespace puzzle {

/*!
 * @brief JSONファイルを読み込む.
 */
class JsonLoader {
public:
  /*!
   * @brief Constuctor
   * @param[out] doc      JSON
   * @param[in]  filename JSONファイル名
   */
  JsonLoader(rapidjson::Document& doc, const std::string filename);

  /*!
   * @brief Destructor
   */
  virtual ~JsonLoader();

  /*!
   * @brief JSONファイルを読み込む.
   * @retval true  成功
   * @retval false 失敗
   * @details
   * JSONファイルを読み込む.
   */
  bool Read();

protected:
  rapidjson::Document& doc_;       //!< JSON
  std::string          filename_;  //!< JSONファイル名
};

}  // puzzle

#endif  // __PUZZLE_JSON_LOADER_H__
