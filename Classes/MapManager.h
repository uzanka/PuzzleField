#ifndef __PUZZLE_MAP_MANAGER_H__
#define __PUZZLE_MAP_MANAGER_H__

#include <string>
#include <map>
#include "MapReader.h"

namespace puzzle {

/*!
 * @brief MapReaderを管理する.
 */
class MapManager {
public:
  /*!
   * @brief MapManagerを取得する.
   * @return MapManager
   * @details
   * 唯一のインスタンスを返す.
   */
  static MapManager& getInstance();

  /*!
   * @brief インスタンスを初期化する.
   * @retval true  成功
   * @retval false 失敗
   * @details
   * インスタンスを初期化する.
   */
  bool Initialize();

  /*!
   * @brief シナリオを取得する.
   * @param[in] class_name クラス名
   * @param[in] filename   シナリオファイル名
   * @return シナリオ
   * @details
   * シナリオを取得する.
   */
  MapReader::Ptr GetScenario(const std::string class_name, const std::string filename);

  /*!
   * @brief シナリオファイルを読み込む.
   * @param[in] class_name クラス名
   * @param[in] filename   シナリオファイル名
   * @return シナリオ
   * @details
   * シナリオファイルを読み込む.
   */
  MapReader::Ptr Read(const std::string class_name, const std::string filename);

protected:
  /*!
   * @brief Constructor
   */
  MapManager();

  /*!
   * @brief Destructor
   */
  virtual ~MapManager();

protected:
  std::map<std::string, MapReader::Ptr> scenarios_;  //!< シナリオマップ(Key=シナリオファイル名, Value=シナリオ)
};

}  // puzzle

#endif  // __PUZZLE_MAP_MANAGER_H__
