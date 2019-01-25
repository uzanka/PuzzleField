#ifndef __PUZZLE_SCENARIO_MANAGER_H__
#define __PUZZLE_SCENARIO_MANAGER_H__

#include "PuzzleDefine.h"
#include "json/rapidjson.h"
#include "json/document.h"

namespace puzzle {

const static std::string kPuzzleFieldFileName = "puzzle_field.json";

/*!
 * @brief シナリオを管理する.
 */
class ScenarioManager {
public:
  /*!
   * @brief シナリオインスタンスを取得する.
   * @return ScenarioManager
   * @details
   * 唯一のインスタンスを返す.
   */
  static ScenarioManager& getInstance();

  /*!
   * @brief インスタンスを初期化する.
   * @retval true  成功
   * @retval false 失敗
   * @details
   * "puzzle_scenario.json" ファイルを読み込む.
   */
  bool Initialize();

  /*!
   * @brief パズルタイトルを取得する.
   * @return パズルタイトル
   * @details
   * パズルタイトルを取得する.
   */
  std::string GetTitle() const;

  /*!
   * @brief 画面幅を取得する.
   * @return 画面幅
   * @details
   * 画面幅(ブロック数)を取得する.
   */
  int GetWidth() const;

  /*!
   * @brief 画面高さを取得する.
   * @return 画面高さ
   * @details
   * 画面高さ(ブロック数)を取得する.
   */
  int GetHeight() const;

  /*!
   * @brief シナリオ数を取得する.
   * @return シナリオ数
   * @details
   * シナリオ数を取得する.
   */
  int GetCount() const;

  /*!
   * @brief シナリオ情報を取得する.
   * @param[in]  index      要素番号(1～)
   * @param[out] title      シナリオタイトル
   * @param[out] filename   ファイル名
   * @param[out] maps       マップ数
   * @param[out] class_name クラス名
   * @retval true  成功
   * @retval false 失敗
   * @details
   * シナリオ情報を取得する.
   */
  bool GetScenario(const int index, std::string& title, std::string& filename, int& maps, std::string& class_name) const;

  /*!
   * @brief シナリオ情報を取得する.
   * @param[in]  index    要素番号(1～)
   * @return シナリオタイトル
   * @details
   * シナリオタイトルを取得する.
   */
  std::string GetScenarioTitle(const int index) const;

  int GetScenarioMapCount(const int index);

  std::string GetFontName() const;

  /*!
   * @brief 自動検出を取得する.
   * @retval true  自動検出ON
   * @retval false 自動検出OFF
   * @details
   * 自動検出を取得する.
   */
  bool GetAutoDetect() const;

protected:
  /*!
   * @brief コンストラクタ
   */
  ScenarioManager();

  /*!
   * @brief デストラクタ
   */
  virtual ~ScenarioManager();

protected:
  rapidjson::Document doc_;  //!< シナリオJSON
};

}  // puzzle

#endif  // __PUZZLE_SCENARIO_MANAGER_H__
