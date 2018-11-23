#ifndef __PUZZLE_TARGET_INFO_H__
#define __PUZZLE_TARGET_INFO_H__

#include "PuzzleDefine.h"

namespace puzzle {

/*!
 * @brief 対象位置情報を管理する.
 */
class TargetInfo {
public:
  typedef std::shared_ptr<TargetInfo> Ptr;

  enum TargetVec {
    kVecDown  = 2,
    kVecLeft  = 4,
    kVecRight = 6,
    kVecUp    = 8
  };

  /*!
   * @brief Constructor
   */
  TargetInfo()
    : x_(0), y_(0), vec_(kVecDown), value_(0), fixed_(0) {
  }

  /*!
   * @brief Constructor
   * @param[in] x X座標
   * @param[in] y Y座標
   */
  TargetInfo(const int x, const int y)
    : x_(x), y_(y), vec_(kVecDown), value_(0), fixed_(0) {
  }

  /*!
   * @brief Constructor
   * @param[in] x   X座標
   * @param[in] y   Y座標
   * @param[in] vec 方向(2,4,6,8)
   */
  TargetInfo(const int x, const int y, const int vec)
    : x_(x), y_(y), vec_(vec), value_(0), fixed_(0) {
  }

  /*!
   * @brief Destructor
   */
  virtual ~TargetInfo() {}

public:
  int x_;      //!< X座標
  int y_;      //!< Y座標
  int vec_;    //!< 方向(2,4,6,8)
  int value_;  //!< 値
  int fixed_;  //!< 完了数(0以下になるとゴール)
};

}  // puzzle

#endif  // __PUZZLE_TARGET_INFO_H__
