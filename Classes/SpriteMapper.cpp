#include "SpriteMapper.h"
#include "base/CCDirector.h"

namespace puzzle {

///////////////////////////////////////////////////////////////////////////////
SpriteMapper::SpriteMapper(
  cocos2d::Scene* scene,
  FieldMap::Ptr field_map,
  const std::map<int, std::string>& images,
  const double scale)
  : scene_(scene),
    field_map_(field_map),
    images_(images),
    scaler_(scale) {
  Initialize();
}

///////////////////////////////////////////////////////////////////////////////
SpriteMapper::~SpriteMapper() {
  Clear();
  scene_ = nullptr;
}

///////////////////////////////////////////////////////////////////////////////
int SpriteMapper::Width() const {
  return field_map_->Width();
}

///////////////////////////////////////////////////////////////////////////////
int SpriteMapper::Height() const {
  return field_map_->Height();
}

///////////////////////////////////////////////////////////////////////////////
cocos2d::Sprite* SpriteMapper::Get(const int x, const int y) {
  if (y < 0 || y >= Height()) return nullptr;
  if (x < 0 || x >= Width()) return nullptr;
  auto itr = sprite_map_.find(y * Width() + x);
  if (itr == sprite_map_.end()) {
    return nullptr;
  }
  return itr->second;
}

///////////////////////////////////////////////////////////////////////////////
void SpriteMapper::Set(const int x, const int y, cocos2d::Sprite* sprite) {
  if (y < 0 || y >= Height()) return;
  if (x < 0 || x >= Width()) return;
  auto itr = sprite_map_.find(y * Width() + x);
  if (itr != sprite_map_.end()) {
    sprite_map_.erase(itr);
  }
  sprite_map_.insert(std::make_pair(y * Width() + x, sprite));
}

///////////////////////////////////////////////////////////////////////////////
void SpriteMapper::Clear() {
  for (auto itr = sprite_map_.begin(); itr != sprite_map_.end(); ++itr) {
    scene_->removeChild(itr->second);
  }
  sprite_map_.clear();
}

///////////////////////////////////////////////////////////////////////////////
void SpriteMapper::Initialize() {
  Clear();

  for (int y = 0; y < Height(); y++) {
    for (int x = 0; x < Width(); x++) {
      int value = field_map_->Get(x, y);
      auto itr = images_.find(value);
      if (itr == images_.end()) {
        continue;
      }
      if (itr->second.empty()) {
        continue;
      }
      cocos2d::Sprite* sprite = scaler_.CreateSprite(itr->second, x, y);
      if (sprite == nullptr) {
        continue;
      }
      scene_->addChild(sprite, 10);
      Set(x, y, sprite);
    }
  }
}

///////////////////////////////////////////////////////////////////////////////
FieldMap::Ptr SpriteMapper::GetMap() {
  return field_map_;
}

///////////////////////////////////////////////////////////////////////////////
void SpriteMapper::Delete(const int x, const int y) {
  cocos2d::Sprite* sprite = Get(x, y);
  if (sprite == nullptr) {
    return;
  }
  Set(x, y, nullptr);
  scene_->removeChild(sprite);
}

///////////////////////////////////////////////////////////////////////////////
std::string SpriteMapper::GetImage(const int index) {
  auto itr = images_.find(index);
  if (itr == images_.end()) {
    return "";
  }
  return itr->second;
}

}  // puzzle
