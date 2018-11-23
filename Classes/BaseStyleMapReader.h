#ifndef __PUZZLE_BASE_STYLE_MAP_READER_H__
#define __PUZZLE_BASE_STYLE_MAP_READER_H__

#include "PuzzleDefine.h"
#include "FieldMap.h"

namespace puzzle {

/*!
 * @brief マップファイルを読み込む.
 */
class BaseStyleMapReader {
public:
  typedef std::shared_ptr<BaseStyleMapReader> Ptr;

  /*!
   * @brief Constructor
   * @param[in]  filename  個別マップファイル名
   * @param[out] maps      マップリスト
   * @param[in]  fillvalue 隙間を埋めるマップ値
   */
  BaseStyleMapReader(const std::string filename, std::vector<FieldMap::Ptr>& maps, const int fillvalue);

  /*!
   * @brief Destructor
   */
  virtual ~BaseStyleMapReader();

  /*!
   * @brief マップファイルを読み込む.
   * @details
   * マップファイルを読み込む.
   */
  virtual void Read() = 0;

  virtual std::string GetTitle() const;
  virtual std::string GetAuthor() const;

protected:
  std::string                 filename_;   //!< 個別マップファイル名
  std::vector<FieldMap::Ptr>& maps_;       //!< マップリスト
  int                         fillvalue_;  //!< 隙間を埋めるマップ値
  std::string scenario_title_;
  std::string scenario_author_;
};

}  // puzzle

#endif  // __PUZZLE_BASE_STYLE_MAP_READER_H__
