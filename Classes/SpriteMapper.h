#ifndef __PUZZLE_SPRITE_MAPPER_H__
#define __PUZZLE_SPRITE_MAPPER_H__

#include "PuzzleDefine.h"
#include "FieldMap.h"
#include "Scaler.h"

namespace puzzle {

/*!
 * @brief マップ上のスプライトを管理する.
 */
class SpriteMapper {
public:
  typedef std::shared_ptr<SpriteMapper> Ptr;

  /*!
   * @brief コンストラクタ
   * @param[in] scene     シーン
   * @param[in] field_map マップ
   * @param[in] images    画像マップ(Key=マップ値, Value=画像ファイル名)
   * @param[in] scale     スケール
   */
  SpriteMapper(
    cocos2d::Scene* scene,
    FieldMap::Ptr field_map,
    const std::map<int, std::string>& images,
    const double scale);

  /*!
   * @brief デストラクタ
   */
  virtual ~SpriteMapper();

  /*!
   * @brief マップ幅を取得する.
   * @return マップ幅
   * @details
   * マップ幅を取得する.
   */
  int Width() const;

  /*!
   * @brief マップ高さを取得する.
   * @return マップ高さ
   * @details
   * マップ高さを取得する.
   */
  int Height() const;

  /*!
   * @brief スプライトを取得する.
   * @param[in] x X座標
   * @param[in] y Y座標
   * @return スプライト
   * @details
   * スプライトを取得する.
   */
  cocos2d::Sprite* Get(const int x, const int y);

  /*!
   * @brief マップにスプライトをセットする.
   * @param[in] x X座標
   * @param[in] y Y座標
   * @param[in] sprite スプライト
   * @details
   * マップにスプライトをセットする.
   */
  void Set(const int x, const int y, cocos2d::Sprite* sprite);

  /*!
   * @brief マップを取得する.
   * @return マップ
   * @details
   * マップを取得する.
   */
  FieldMap::Ptr GetMap();

  /*!
   * @brief 画像ファイル名を取得する.
   * @param[in] index 画像番号(0～)
   * @return 画像ファイル名
   * @details
   * 画像ファイル名を取得する.
   */
  std::string GetImage(const int index);

  /*!
   * @brief スプライトを削除する.
   * @param[in] x X座標
   * @param[in] y Y座標
   * @details
   * スプライトを削除する.
   */
  void Delete(const int x, const int y);

private:
  /*!
   * @brief マップをクリアする.
   * @details
   * マップをクリアする.
   */
  void Clear();

  /*!
   * @brief マップのスプライトを作成する.
   * @details
   * マップ値に該当するスプライトを作成しシーンに登録する.
   */
  void Initialize();

protected:
  cocos2d::Scene*                 scene_;       //!< シーン
  FieldMap::Ptr                   field_map_;   //!< マップ
  std::map<int, cocos2d::Sprite*> sprite_map_;  //!< スプライトマップ(Key=y*width+x, Value=Sprite)
  std::map<int, std::string>      images_;      //!< マップ値と画像のマップ(Key=マップ値, Value=画像ファイル名)
  Scaler                          scaler_;
};

}  // puzzle

#endif // __PUZZLE_SPRITE_MAPPER_H__
