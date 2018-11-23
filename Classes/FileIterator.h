#ifndef __PUZZLE_FILE_ITERATOR_H__
#define __PUZZLE_FILE_ITERATOR_H__

#include "PuzzleDefine.h"

namespace puzzle {

/*!
 * @brief ファイル一覧を取得する.
 * @note 本クラスはPFによって異なる.
 */
class FileIterator {
public:
  typedef std::shared_ptr<FileIterator> Ptr;

  /*!
   * @brief コンストラクタ
   * @param[in]  directory ディレクトリ
   * @param[out] files     ファイル一覧
   */
  FileIterator(const std::string directory, std::vector<std::string>& files);

  /*!
   * @brief デストラクタ
   */
  virtual ~FileIterator();

  /*!
   * @brief ファイル一覧を取得する.
   */
  void List();

protected:
  std::string               directory_;  //!< ディレクトリ
  std::vector<std::string>& files_;      //!< ファイル一覧
};

}  // puzzle

#endif // __PUZZLE_FILE_ITERATOR_H__
