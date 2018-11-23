#ifndef __PUZZLE_STRING_UTIL_H__
#define __PUZZLE_STRING_UTIL_H__

#include "PuzzleDefine.h"
#include "FieldMap.h"

namespace puzzle {

/*!
 * @brief 個別マップファイルを読み込む.
 * @details
 * 以下のフォーマットとする.
 * ";"で始まる行をコメントとする.
 * 文字コードをマップ値とする.
 * ";Author: {author}" を著作者として認識する.
 * ";Title: {title}" をタイトルとして認識する.
 * 縦横サイズは全体の解析結果から決定する.
 */
class StringUtil {
public:
  /*!
   * @brief Constuctor
   */
  StringUtil();

  /*!
   * @brief Destructor
   */
  virtual ~StringUtil();

  static std::string Replace(std::string target, const std::string before, const std::string after);
  static int Split(const std::string target, const char delimiter, std::vector<std::string>& lines);
  static std::string TrimLeft(std::string target);
  static std::string TrimRight(std::string target);
  static std::string Trim(std::string target);
  static std::string Left(std::string target, const std::size_t length);
  static std::string Right(std::string target, const std::size_t length);
  static std::string Mid(std::string target, const std::size_t offset, const std::size_t length = std::string::npos);
  static std::string Hex2(const char ch);
  static std::string ConvertCode(const std::wstring utf16);
  static std::wstring ConvertCode(const std::string utf8);
};

}  // puzzle

#endif  // __PUZZLE_STRING_UTIL_H__
