#include "SokobanScene.h"

namespace puzzle {

///////////////////////////////////////////////////////////////////////////////
void SokobanScene::OnKeyPressedUp() {
  OnMove(0, -1, TargetInfo::kVecUp);
}

///////////////////////////////////////////////////////////////////////////////
void SokobanScene::OnKeyPressedDown() {
  OnMove(0, 1, TargetInfo::kVecDown);
}

///////////////////////////////////////////////////////////////////////////////
void SokobanScene::OnKeyPressedLeft() {
  OnMove(-1, 0, TargetInfo::kVecLeft);
}

///////////////////////////////////////////////////////////////////////////////
void SokobanScene::OnKeyPressedRight() {
  OnMove(1, 0, TargetInfo::kVecRight);
}

///////////////////////////////////////////////////////////////////////////////
void SokobanScene::OnKeyPressedEnter() {
}

///////////////////////////////////////////////////////////////////////////////
void SokobanScene::OnKeyPressedSpace() {
}

///////////////////////////////////////////////////////////////////////////////
void SokobanScene::OnKeyPressedEscape() {
  StopPuzzle();
  EscapePuzzle();
}

///////////////////////////////////////////////////////////////////////////////
void SokobanScene::OnMove(const int vx, const int vy, const int vec) {
  // 主人公の方向を変更する.
  player_.vec_ = vec;
  cocos2d::Sprite* sprite = sprite_mapper_->Get(player_.x_, player_.y_);
  sprite->setSpriteFrame(cocos2d::Sprite::create(Vec2Image(player_.vec_))->getSpriteFrame());

  int value1 = sprite_mapper_->GetMap()->Get(player_.x_ + vx, player_.y_ + vy);
  int value2 = sprite_mapper_->GetMap()->Get(player_.x_ + vx + vx, player_.y_ + vy + vy);

  if ((value1 == kValueSpace) || (value1 == kValueGoal)) {
    MovePlayer(vx, vy);
  } else if ((value1 == kValueBox) || (value1 == kValueBoxOnGoal)) {
    if ((value2 == kValueSpace) || (value2 == kValueGoal)) {
      MoveBox(vx, vy);
    }
  }
}

///////////////////////////////////////////////////////////////////////////////
void SokobanScene::MovePlayer(const int vx, const int vy) {
  int value0 = sprite_mapper_->GetMap()->Get(player_.x_, player_.y_);
  int value1 = sprite_mapper_->GetMap()->Get(player_.x_ + vx, player_.y_ + vy);

  cocos2d::Sprite* sprite0 = sprite_mapper_->Get(player_.x_, player_.y_);
  if (value0 == kValuePlayerOnGoal) {
    sprite_mapper_->GetMap()->Set(player_.x_, player_.y_, kValueGoal);
  } else {
    sprite_mapper_->GetMap()->Set(player_.x_, player_.y_, kValueSpace);
  }
  sprite_mapper_->Set(player_.x_, player_.y_, nullptr);

  player_.x_ += vx;
  player_.y_ += vy;

  if (value1 == kValueGoal) {
    sprite_mapper_->GetMap()->Set(player_.x_, player_.y_, kValuePlayerOnGoal);
  } else {
    sprite_mapper_->GetMap()->Set(player_.x_, player_.y_, kValuePlayer);
  }
  sprite_mapper_->Set(player_.x_, player_.y_, sprite0);

  auto action = cocos2d::MoveTo::create(0.05f, scaler_->GetDisplayPosition(player_.x_, player_.y_));
  auto callback = cocos2d::CallFuncN::create([this](Ref *sender) {
    SetInputEventEnabled(true);
    OnCheckComplete();
  });
  auto seq = cocos2d::Sequence::create(action, callback, nullptr);
  SetInputEventEnabled(false);
  sprite0->runAction(seq);
}

///////////////////////////////////////////////////////////////////////////////
void SokobanScene::MoveBox(const int vx, const int vy) {
  int value0 = sprite_mapper_->GetMap()->Get(player_.x_, player_.y_);
  int value1 = sprite_mapper_->GetMap()->Get(player_.x_ + vx, player_.y_ + vy);
  int value2 = sprite_mapper_->GetMap()->Get(player_.x_ + vx + vx, player_.y_ + vy + vy);

  cocos2d::Sprite* sprite0 = sprite_mapper_->Get(player_.x_, player_.y_);
  if (value0 == kValuePlayerOnGoal) {
    sprite_mapper_->GetMap()->Set(player_.x_, player_.y_, kValueGoal);
  } else {
    sprite_mapper_->GetMap()->Set(player_.x_, player_.y_, kValueSpace);
  }
  sprite_mapper_->Set(player_.x_, player_.y_, nullptr);

  player_.x_ += vx;
  player_.y_ += vy;

  cocos2d::Sprite* sprite1 = sprite_mapper_->Get(player_.x_, player_.y_);
  if (value1 == kValueBoxOnGoal) {
    sprite_mapper_->GetMap()->Set(player_.x_, player_.y_, kValuePlayerOnGoal);
    player_.fixed_++;
  } else {
    sprite_mapper_->GetMap()->Set(player_.x_, player_.y_, kValuePlayer);
  }
  sprite_mapper_->Set(player_.x_, player_.y_, sprite0);

  if (value2 == kValueGoal) {
    sprite_mapper_->GetMap()->Set(player_.x_ + vx, player_.y_ + vy, kValueBoxOnGoal);
    player_.fixed_--;
  } else {
    sprite_mapper_->GetMap()->Set(player_.x_ + vx, player_.y_ + vy, kValueBox);
  }
  sprite_mapper_->Set(player_.x_ + vx, player_.y_ + vy, sprite1);

  auto action1 = cocos2d::MoveTo::create(0.05f, scaler_->GetDisplayPosition(player_.x_, player_.y_));
  auto action2 = cocos2d::MoveTo::create(0.05f, scaler_->GetDisplayPosition(player_.x_ + vx, player_.y_ + vy));
  auto callback = cocos2d::CallFuncN::create([this](Ref *sender) {
    SetInputEventEnabled(true);
    OnCheckComplete();
  });
  auto seq1 = cocos2d::Sequence::create(action1, callback, nullptr);
  auto seq2 = cocos2d::Sequence::create(action2, nullptr);
  SetInputEventEnabled(false);
  sprite0->runAction(seq1);
  sprite1->runAction(seq2);
}

}  // puzzle
