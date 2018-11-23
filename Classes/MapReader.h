#ifndef __PUZZLE_MAPREADER_H__
#define __PUZZLE_MAPREADER_H__

#include "json/rapidjson.h"
#include "json/document.h"
#include "PuzzleDefine.h"
#include "FieldMap.h"
#include "ClassReader.h"

namespace puzzle {

/*!
 * @brief マップファイルを読み込む.
 */
class MapReader {
public:
  typedef std::shared_ptr<MapReader> Ptr;

  /*!
   * @brief Constructor
   * @param[in] class_name クラス名
   * @param[in] filename   ファイル名
   */
  MapReader(const std::string class_name, const std::string filename);

  /*!
   * @brief Destructor
   */
  virtual ~MapReader();

  /*!
   * @brief マップファイル(JSON)を読み込む.
   * @return 処理結果
   * @details
   * マップファイル(JSON)を読み込む.
   */
  bool Read();

  /*!
   * @brief マップを取得する.
   * @param[in] index マップ番号(1～)
   * @return マップ
   * @details
   * マップJSONから指定のマップを取得する.
   */
  FieldMap::Ptr Get(const int index);

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
   * @brief マップ幅を取得する.
   * @return マップ幅
   * @details
   * マップ幅を取得する.
   */
  int GetMaxWidth() const;

  /*!
   * @brief マップ高さを取得する.
   * @return マップ高さ
   * @details
   * マップ高さを取得する.
   */
  int GetMaxHeight() const;

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
   * @brief マップ数を取得する.
   * @return マップ数
   * @details
   * マップ数を取得する.
   */
  int GetMapCount();

  /*!
   * @brief 隙間を埋めるマップ値を取得する.
   * @return 隙間を埋めるマップ値
   * @details
   * 隙間を埋めるマップ値を取得する.
   */
  int GetFillValue() const;

private:
  bool ReadClass();

protected:
  std::string                class_name_;  //!< クラス名
  ClassReader::Ptr           class_reader_;
  std::string                filename_;    //!< マップファイル
  std::vector<FieldMap::Ptr> maps_;        //!< 読み込んだマップ
  int                        max_width_;
  int                        max_height_;
};

}  // puzzle

#endif  // __PUZZLE_MAPREADER_H__
