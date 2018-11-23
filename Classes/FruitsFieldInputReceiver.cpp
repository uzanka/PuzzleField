#include "FruitsFieldScene.h"

namespace puzzle {

///////////////////////////////////////////////////////////////////////////////
void FruitsFieldScene::OnKeyPressedUp() {
  OnMove(0, -1, TargetInfo::kVecUp);
}

///////////////////////////////////////////////////////////////////////////////
void FruitsFieldScene::OnKeyPressedDown() {
  OnMove(0, 1, TargetInfo::kVecDown);
}

///////////////////////////////////////////////////////////////////////////////
void FruitsFieldScene::OnKeyPressedLeft() {
  OnMove(-1, 0, TargetInfo::kVecLeft);
}

///////////////////////////////////////////////////////////////////////////////
void FruitsFieldScene::OnKeyPressedRight() {
  OnMove(1, 0, TargetInfo::kVecRight);
}

///////////////////////////////////////////////////////////////////////////////
void FruitsFieldScene::OnKeyPressedEnter() {
}

///////////////////////////////////////////////////////////////////////////////
void FruitsFieldScene::OnKeyPressedSpace() {
  switch (player_.vec_) {
  case TargetInfo::kVecDown:
    OnAction(0, 1, player_.vec_);
    break;
  case TargetInfo::kVecLeft:
    OnAction(-1, 0, player_.vec_);
    break;
  case TargetInfo::kVecRight:
    OnAction(1, 0, player_.vec_);
    break;
  case TargetInfo::kVecUp:
    OnAction(0, -1, player_.vec_);
    break;
  }
}

///////////////////////////////////////////////////////////////////////////////
void FruitsFieldScene::OnKeyPressedEscape() {
  StopPuzzle();
  EscapePuzzle();
}

///////////////////////////////////////////////////////////////////////////////
void FruitsFieldScene::OnMove(const int vx, const int vy, const int vec) {
  // 主人公の方向を変更する.
  player_.vec_ = vec;
  cocos2d::Sprite* sprite = sprite_mapper_->Get(player_.x_, player_.y_);
  sprite->setSpriteFrame(cocos2d::Sprite::create(Vec2Image(player_.vec_))->getSpriteFrame());

  int value = sprite_mapper_->GetMap()->Get(player_.x_ + vx, player_.y_ + vy);

  if (value == kValueSpace || value == kValueFruits) {
    sprite_mapper_->GetMap()->Set(player_.x_, player_.y_, kValueSpace);
    sprite_mapper_->Set(player_.x_, player_.y_, nullptr);
    player_.x_ += vx;
    player_.y_ += vy;
    cocos2d::Sprite* old_sprite = sprite_mapper_->Get(player_.x_, player_.y_);
    if (old_sprite != nullptr) {
      sprite_mapper_->GetMap()->Set(player_.x_, player_.y_, kValueSpace);
      sprite_mapper_->Delete(player_.x_, player_.y_);
    }
    if (value == kValueFruits) {
      player_.fixed_--;
    }
    sprite_mapper_->GetMap()->Set(player_.x_, player_.y_, kValuePlayer);
    sprite_mapper_->Set(player_.x_, player_.y_, sprite);

    //sprite->setPosition(scaler_->GetDisplayPosition(player_.x_, player_.y_));
    auto action = cocos2d::MoveTo::create(0.05f, scaler_->GetDisplayPosition(player_.x_, player_.y_));
    auto callback = cocos2d::CallFuncN::create([this](Ref *sender) {
      SetInputEventEnabled(true);
      OnCheckComplete();
    });
    auto seq = cocos2d::Sequence::create(action, callback, nullptr);
    SetInputEventEnabled(false);
    sprite->runAction(seq);
  }
}

///////////////////////////////////////////////////////////////////////////////
void FruitsFieldScene::OnAction(const int vx, const int vy, const int vec) {
  int value1 = sprite_mapper_->GetMap()->Get(player_.x_ + vx, player_.y_ + vy);
  int value2 = sprite_mapper_->GetMap()->Get(player_.x_ + vx + vx, player_.y_ + vy + vy);  // overflow = 0

  if (vec == value1 && value2 != kValueSpace) {
    switch (value1) {
    case kValueArrowDown:
      if (value2 != kValueArrowUp) {
        DeleteBlock(player_.x_ + vx, player_.y_ + vy);
      }
      break;
    case kValueArrowLeft:
      if (value2 != kValueArrowRight) {
        DeleteBlock(player_.x_ + vx, player_.y_ + vy);
      }
      break;
    case kValueArrowRight:
      if (value2 != kValueArrowLeft) {
        DeleteBlock(player_.x_ + vx, player_.y_ + vy);
      }
      break;
    case kValueArrowUp:
      if (value2 != kValueArrowDown) {
        DeleteBlock(player_.x_ + vx, player_.y_ + vy);
      }
      break;
    }
  } else {
    switch (value1) {
    case kValueArrowDown:
      MoveBlock(player_.x_ + vx, player_.y_ + vy, 0, 1, value1);
      break;
    case kValueArrowLeft:
      MoveBlock(player_.x_ + vx, player_.y_ + vy, -1, 0, value1);
      break;
    case kValueArrowRight:
      MoveBlock(player_.x_ + vx, player_.y_ + vy, 1, 0, value1);
      break;
    case kValueArrowUp:
      MoveBlock(player_.x_ + vx, player_.y_ + vy, 0, -1, value1);
      break;
    }
  }
}

///////////////////////////////////////////////////////////////////////////////
void FruitsFieldScene::MoveBlock(const int x, const int y, const int vx, const int vy, const int vec) {
  int count = 0;
  int ax = x;
  int ay = y;
  for(;;) {
    int value = sprite_mapper_->GetMap()->Get(ax + vx, ay + vy);
    if (value != kValueSpace) {
      break;
    }
    ax += vx;
    ay += vy;
    count++;
  }
  if (count == 0) {
    return;
  }

  cocos2d::Sprite* sprite = sprite_mapper_->Get(x, y);
  sprite_mapper_->GetMap()->Set(x, y, kValueSpace);
  sprite_mapper_->Set(x, y, nullptr);
  sprite_mapper_->GetMap()->Set(ax, ay, vec);
  sprite_mapper_->Set(ax, ay, sprite);

  auto action = cocos2d::MoveTo::create(0.05f * count, scaler_->GetDisplayPosition(ax, ay));
  auto callback = cocos2d::CallFuncN::create([this](Ref *sender) {
    SetInputEventEnabled(true);
  });
  auto seq = cocos2d::Sequence::create(action, callback, nullptr);
  SetInputEventEnabled(false);
  sprite->runAction(seq);
}

///////////////////////////////////////////////////////////////////////////////
void FruitsFieldScene::DeleteBlock(const int x, const int y) {
  sprite_mapper_->GetMap()->Set(x, y, kValueSpace);
  sprite_mapper_->Delete(x, y);
}

}  // puzzle
