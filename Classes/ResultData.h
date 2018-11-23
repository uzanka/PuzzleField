#ifndef __PUZZLE_RESULT_DATA_H__
#define __PUZZLE_RESULT_DATA_H__

#include "PuzzleDefine.h"

namespace puzzle {

/*!
 * @brief 結果情報
 */
class ResultData {
public:
  typedef std::shared_ptr<ResultData> Ptr;
  ResultData(const std::string title);
  virtual ~ResultData();

  std::string GetKey();
  std::string MakeKey(const std::string title);

  bool             dirty_;      //!< 更新あり
  std::string      title_;      //!< シナリオ名
  std::vector<int> cleared_;    //!< クリアしたマップ番号(1～)
  bool             completed_;  //!< 全マップクリア済み
  std::string      key_;
};

}  // puzzle

#endif  // __PUZZLE_RESULT_DATA_H__
