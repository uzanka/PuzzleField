#ifndef __PUZZLE_DIRECTORY_ITERATOR_H__
#define __PUZZLE_DIRECTORY_ITERATOR_H__

#include "PuzzleDefine.h"

namespace puzzle {

/*!
 * @brief ディレクトリ一覧を取得する.
 * @note 本クラスはPFによって異なる.
 */
class DirectoryIterator {
public:
  typedef std::shared_ptr<DirectoryIterator> Ptr;

  /*!
   * @brief コンストラクタ
   * @param[in]  directory ディレクトリ
   * @param[out] dirs      ディレクトリ一覧
   */
  DirectoryIterator(const std::string directory, std::vector<std::string>& dirs);

  /*!
   * @brief デストラクタ
   */
  virtual ~DirectoryIterator();

  /*!
   * @brief ディレクトリ一覧を取得する.
   */
  void List();

protected:
  std::string               directory_;  //!< ディレクトリ
  std::vector<std::string>& dirs_;       //!< ディレクトリ一覧
};

}  // puzzle

#endif // __PUZZLE_DIRECTORY_ITERATOR_H__
