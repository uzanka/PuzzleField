#ifndef __PUZZLE_VALUE_MANAGER_H__
#define __PUZZLE_VALUE_MANAGER_H__

#include "PuzzleDefine.h"
#include "json/rapidjson.h"
#include "json/document.h"

namespace puzzle {

/*!
 * @brief 値を管理する.
 */
class ValueManager {
public:
  /*!
   * @brief インスタンスを取得する.
   * @return ValueManager
   * @details
   * 唯一のインスタンスを返す.
   */
  static ValueManager& getInstance();

  /*!
   * @brief インスタンスを初期化する.
   * @retval true  成功
   * @retval false 失敗
   * @details
   * インスタンスを初期化する.
   */
  bool Initialize();

  /*!
   * @brief 文字列値を登録する.
   * @param[in] key   キー
   * @param[in] value 値
   * @details
   * 文字列値を登録する.
   */
  void SetString(const std::string key, const std::string value);

  /*!
   * @brief 整数値を登録する.
   * @param[in] key   キー
   * @param[in] value 値
   * @details
   * 整数値を文字列化して登録する.
   */
  void SetInt(const std::string key, const int value);

  /*!
   * @brief 実数値を登録する.
   * @param[in] key   キー
   * @param[in] value 値
   * @details
   * 実数値を文字列化して登録する.
   */
  void SetFloat(const std::string key, const float value);

  /*!
   * @brief 文字列値を取得する.
   * @param[in] key           キー
   * @param[in] default_value 値
   * @return 値
   * @details
   * 文字列値を取得する.
   * キーが存在しない場合はデフォルト値を返す.
   */
  std::string GetString(const std::string key, const std::string default_value = "");

  /*!
   * @brief 整数値を取得する.
   * @param[in] key           キー
   * @param[in] default_value 値
   * @return 値
   * @details
   * 数値を取得する.
   * キーが存在しない場合はデフォルト値を返す.
   * 保持している値が整数値でない場合はデフォルト値を返す.
   */
  int GetInt(const std::string key, const int default_value = 0);

  /*!
   * @brief 実数値を取得する.
   * @param[in] key           キー
   * @param[in] default_value 値
   * @return 値
   * @details
   * 実数値を取得する.
   * キーが存在しない場合はデフォルト値を返す.
   * 保持している値が実数値でない場合はデフォルト値を返す.
   */
  float GetFloat(const std::string key, const float default_value = 0.0f);

  /*!
   * @brief キーを削除する.
   * @param[in] key キー
   * @return 値
   * @details
   * キーを削除する.
   */
  void Remove(const std::string key);

protected:
  /*!
   * @brief コンストラクタ
   */
  ValueManager();

  /*!
   * @brief デストラクタ
   */
  virtual ~ValueManager();

protected:
  std::map<std::string, std::string> values_;  //!< 値(Key=Key, Value=Value)
};

}  // puzzle

#endif  // __PUZZLE_VALUE_MANAGER_H__
