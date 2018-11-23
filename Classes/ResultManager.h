#ifndef __PUZZLE_RESULT_MANAGER_H__
#define __PUZZLE_RESULT_MANAGER_H__

#include "PuzzleDefine.h"
#include "ResultData.h"
#include "json/rapidjson.h"
#include "json/document.h"

namespace puzzle {

/*!
 * @brief 結果を管理する.
 * @details
 * "C:\Users\{username}\AppData\Local\PuzzleField\UserDefault.xml"
 */
class ResultManager {
public:
  /*!
   * @brief インスタンスを取得する.
   * @return ResultManager
   * @details
   * 唯一のインスタンスを返す.
   */
  static ResultManager& getInstance();

  /*!
   * @brief 結果情報ファイルを読み込む.
   * @details
   * 永続ファイルを読み込む.
   */
  bool Initialize();

  ResultData::Ptr GetResult(const std::string title);
  ResultData::Ptr Read(const std::string title);

  void Flush();
  void Flush(ResultData::Ptr result);

  /*!
   * @brief シナリオのクリア済みマップ番号を登録する.
   * @param[in] title シナリオ名
   * @param[in] index クリア済みマップ番号(1～)
   * @details
   * シナリオがなければシナリオの箱を作成する.
   * クリア済みマップ番号を登録する.
   * 結果を永続ファイルに書き込む.
   */
  void SetCleared(const std::string title, const int index);
  bool IsCleared(const std::string title, const int index);
  void SetCompleted(const std::string title);

  bool IsCompleted(const std::string title);

  /*!
   * @brief 未クリアの最小マップ番号を取得する.
   * @param[in] title シナリオ名
   * @param[in] first 検索開始マップ番号
   * @return 未クリアの最小マップ番号
   * @details
   * 対象シナリオのクリア済みマップ番号を探索し未クリアの最小マップ番号を返す.
   * 結果がシナリオのマップ数を超えていれば全クリア状態と判断できる.
   * シナリオが見つからない場合は 1 を返す.
   */
  int GetMinumumUnClearedIndex(const std::string title, const int first = 1);

protected:
  /*!
   * @brief Constructor
   */
  ResultManager();

  /*!
   * @brief Destructor
   */
  virtual ~ResultManager();

  /*!
   * @brief JSON文字列に変換する.
   * @param[in] doc JSON
   * @return JSON文字列
   * @details
   * JSONをJSON文字列に変換する.
   */
  std::string GetJsonString(rapidjson::Document& doc);

protected:
  std::map<std::string, ResultData::Ptr> results_;  //!< 結果(Key=シナリオタイトル, Value=結果情報)
};

}  // puzzle

#endif  // __PUZZLE_RESULT_MANAGER_H__
