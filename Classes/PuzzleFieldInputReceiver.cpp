#include "PuzzleFieldScene.h"

namespace puzzle {

///////////////////////////////////////////////////////////////////////////////
void PuzzleFieldScene::AddKeyboardEventListener() {
  cocos2d::EventListenerKeyboard* listener = cocos2d::EventListenerKeyboard::create();

  listener->onKeyPressed = [this](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
    if (keyCode != cocos2d::EventKeyboard::KeyCode::KEY_NONE) {
      DeleteRepeatTimer();
      OnKeyPressed(keyCode);
      SetRepeatTimer(keyCode);
    }
  };

  listener->onKeyReleased = [this](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
    if (keyCode != cocos2d::EventKeyboard::KeyCode::KEY_NONE) {
      DeleteRepeatTimer();
      OnKeyReleased(keyCode);
    }
  };

  this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

///////////////////////////////////////////////////////////////////////////////
void PuzzleFieldScene::AddTouchEventListener() {
  cocos2d::EventListenerTouchAllAtOnce* listener = cocos2d::EventListenerTouchAllAtOnce::create();
  listener->setEnabled(true);
  listener->onTouchesBegan = CC_CALLBACK_2(PuzzleFieldScene::onTouchesBegan, this);
  listener->onTouchesEnded = CC_CALLBACK_2(PuzzleFieldScene::onTouchesEnded, this);

  this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

///////////////////////////////////////////////////////////////////////////////
void PuzzleFieldScene::SetRepeatTimer(cocos2d::EventKeyboard::KeyCode keyCode) {
  DeleteRepeatTimer();
  if (repeatable_) {
    if (keyCode != cocos2d::EventKeyboard::KeyCode::KEY_NONE) {
      if (keyCode != cocos2d::EventKeyboard::KeyCode::KEY_ENTER) {
        repeat_key_code_ = keyCode;
        this->schedule(schedule_selector(PuzzleFieldScene::OnRepeatTimer), repeat_interval_, CC_REPEAT_FOREVER, repeat_delay_);
      }
    }
  }
}

///////////////////////////////////////////////////////////////////////////////
void PuzzleFieldScene::DeleteRepeatTimer() {
  if (repeat_key_code_ != cocos2d::EventKeyboard::KeyCode::KEY_NONE) {
    repeat_key_code_ = cocos2d::EventKeyboard::KeyCode::KEY_NONE;
    this->unschedule(schedule_selector(PuzzleFieldScene::OnRepeatTimer));
  }
}

///////////////////////////////////////////////////////////////////////////////
void PuzzleFieldScene::OnRepeatTimer(float frame) {
  if (repeatable_) {
    if (input_event_enabled_) {
      if (repeat_key_code_ != cocos2d::EventKeyboard::KeyCode::KEY_NONE) {
        if (this->getEventDispatcher()->isEnabled()) {
          OnKeyPressed(repeat_key_code_);
        }
      }
    }
  }
}

///////////////////////////////////////////////////////////////////////////////
void PuzzleFieldScene::OnKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode) {
  switch (keyCode) {
  case cocos2d::EventKeyboard::KeyCode::KEY_8:
  case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
  case cocos2d::EventKeyboard::KeyCode::KEY_KP_UP:
  case cocos2d::EventKeyboard::KeyCode::KEY_DPAD_UP:
    OnKeyPressedUp();
    break;
  case cocos2d::EventKeyboard::KeyCode::KEY_2:
  case cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW:
  case cocos2d::EventKeyboard::KeyCode::KEY_KP_DOWN:
  case cocos2d::EventKeyboard::KeyCode::KEY_DPAD_DOWN:
    OnKeyPressedDown();
    break;
  case cocos2d::EventKeyboard::KeyCode::KEY_4:
  case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
  case cocos2d::EventKeyboard::KeyCode::KEY_KP_LEFT:
  case cocos2d::EventKeyboard::KeyCode::KEY_DPAD_LEFT:
    OnKeyPressedLeft();
    break;
  case cocos2d::EventKeyboard::KeyCode::KEY_6:
  case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
  case cocos2d::EventKeyboard::KeyCode::KEY_KP_RIGHT:
  case cocos2d::EventKeyboard::KeyCode::KEY_DPAD_RIGHT:
    OnKeyPressedRight();
    break;
  case cocos2d::EventKeyboard::KeyCode::KEY_ENTER:
  case cocos2d::EventKeyboard::KeyCode::KEY_KP_ENTER:
  case cocos2d::EventKeyboard::KeyCode::KEY_RETURN:
    OnKeyPressedEnter();
    break;
  case cocos2d::EventKeyboard::KeyCode::KEY_SPACE:
    OnKeyPressedSpace();
    break;
  case cocos2d::EventKeyboard::KeyCode::KEY_ESCAPE:
    OnKeyPressedEscape();
    break;
  default:
    //OnKeyPressedOther(keyCode);
    break;
  }
}

///////////////////////////////////////////////////////////////////////////////
void PuzzleFieldScene::OnKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode) {
}

///////////////////////////////////////////////////////////////////////////////
void PuzzleFieldScene::SetRepeatable(const bool flag) {
  repeatable_ = flag;
  if (!repeatable_) {
    DeleteRepeatTimer();
  }
}

///////////////////////////////////////////////////////////////////////////////
void PuzzleFieldScene::SetInputEventEnabled(const bool enable) {
  input_event_enabled_ = enable;
}

///////////////////////////////////////////////////////////////////////////////
void PuzzleFieldScene::onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event) {
  for (auto itr = touches.cbegin(); itr != touches.cend(); ++itr) {
    cocos2d::Touch* touch = *itr;
    cocos2d::Vec2 location = touch->getLocation();
    LOG("began (x, y)=(%f, %f)", location.x, location.y);
    //if (screen_pad_->IsTouchPad(location)) {
    //  OnKeyPressed(screen_pad_->Get4Way());
    //}
  }
}

///////////////////////////////////////////////////////////////////////////////
void PuzzleFieldScene::onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event) {
  for (auto itr = touches.cbegin(); itr != touches.cend(); ++itr) {
    cocos2d::Touch* touch = *itr;
    cocos2d::Vec2 location = touch->getLocation();
    LOG("ended (x, y)=(%f, %f)", location.x, location.y);
  }
}

}  // puzzle
