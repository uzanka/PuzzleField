#ifndef __PUZZLE_CLASS_READER_H__
#define __PUZZLE_CLASS_READER_H__

#include "json/rapidjson.h"
#include "json/document.h"
#include "PuzzleDefine.h"
#include "FieldMap.h"

namespace puzzle {

/*!
 * @brief クラスファイルを読み込む.
 */
class ClassReader {
public:
  typedef std::shared_ptr<ClassReader> Ptr;

  /*!
   * @brief Constructor
   * @param[in] class_name クラス名
   */
  ClassReader(const std::string class_name);

  /*!
   * @brief Destructor
   */
  virtual ~ClassReader();

  /*!
   * @brief クラスファイル(JSON)を読み込む.
   * @return 処理結果
   * @details
   * クラスファイル(JSON)を読み込む.
   */
  bool Read();

  /*!
   * @brief マップタイトルを取得する.
   * @return マップタイトル
   * @details
   * マップタイトルを取得する.
   */
  std::string GetTitle() const;

  /*!
   * @brief マップ著作者を取得する.
   * @return マップ著作者
   * @details
   * マップ著作者を取得する.
   */
  std::string GetAuthor() const;

  /*!
   * @brief 画像マップを取得する.
   * @param[out] images 画像ファイル名マップ(Key=マップ値, Value=画像ファイル名)
   * @details
   * マップ値と画像ファイル名のマップを取得する.
   */
  void GetImages(std::map<int, std::string>& images);

  /*!
   * @brief フォント名を取得する.
   * @return フォント名
   * @details
   * フォント名を取得する.
   */
  std::string GetFontName() const;

  /*!
   * @brief 隙間を埋めるマップ値を取得する.
   * @return 隙間を埋めるマップ値
   * @details
   * 隙間を埋めるマップ値を取得する.
   */
  int GetFillValue() const;

protected:
  std::string                class_name_;  //!< クラス名
  std::string                title_;
  std::string                author_;
  std::string                fontname_;
  int                        fill_value_;
  std::map<int, std::string> images_;
};

}  // puzzle

#endif  // __PUZZLE_CLASS_READER_H__
