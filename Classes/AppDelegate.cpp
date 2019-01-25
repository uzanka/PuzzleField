#include "AppDelegate.h"
#include "PuzzleTitleScene.h"
#include "ValueManager.h"
#include "ScenarioManager.h"
#include "MapManager.h"
#include "ResultManager.h"
#include "ScenarioAutoDetector.h"

//#define USE_AUDIO_ENGINE 1
#if USE_AUDIO_ENGINE
#include "audio/include/AudioEngine.h"
using namespace cocos2d::experimental;
#endif

///////////////////////////////////////////////////////////////////////////////
AppDelegate::AppDelegate() {
}

///////////////////////////////////////////////////////////////////////////////
AppDelegate::~AppDelegate() {
#if USE_AUDIO_ENGINE
  cocos2d::AudioEngine::end();
#endif
}

///////////////////////////////////////////////////////////////////////////////
void AppDelegate::initGLContextAttrs() {
  // set OpenGL context attributes: red,green,blue,alpha,depth,stencil,multisamplesCount
  GLContextAttrs glContextAttrs = { 8, 8, 8, 8, 24, 8, 0 };
  cocos2d::GLView::setGLContextAttrs(glContextAttrs);
}

///////////////////////////////////////////////////////////////////////////////
// if you want to use the package manager to install more packages,  
// don't modify or remove this function
static int register_all_packages() {
  return 0;  // flag for packages manager
}

///////////////////////////////////////////////////////////////////////////////
bool AppDelegate::applicationDidFinishLaunching() {
  InitializePuzzle();

  cocos2d::Size designResolutionSize = GetDesignResolutionSize();
  cocos2d::Size smallResolutionSize = GetSmallResolutionSize();
  cocos2d::Size mediumResolutionSize = GetMediumResolutionSize();
  cocos2d::Size largeResolutionSize = GetLargeResolutionSize();

  // initialize director
  cocos2d::Director* director = cocos2d::Director::getInstance();
  cocos2d::GLView* glview = director->getOpenGLView();
  if(!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
    glview = cocos2d::GLViewImpl::createWithRect(puzzle::kPuzzleTitle, cocos2d::Rect(0, 0, designResolutionSize.width, designResolutionSize.height));
#else
    glview = cocos2d::GLViewImpl::create(puzzle::kPuzzleTitle);
#endif
    director->setOpenGLView(glview);
  }

  // turn on display FPS
  director->setDisplayStats(true);

  // set FPS. the default value is 1.0/60 if you don't call this
  director->setAnimationInterval(1.0f / 60);

  // Set the design resolution
  glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::NO_BORDER);
  cocos2d::Size frameSize = glview->getFrameSize();
  if (frameSize.height > mediumResolutionSize.height) {
    // if the frame's height is larger than the height of medium size.
    director->setContentScaleFactor(MIN(largeResolutionSize.height/designResolutionSize.height, largeResolutionSize.width/designResolutionSize.width));
  } else if (frameSize.height > smallResolutionSize.height) {
    // if the frame's height is larger than the height of small size.
    director->setContentScaleFactor(MIN(mediumResolutionSize.height/designResolutionSize.height, mediumResolutionSize.width/designResolutionSize.width));
  } else {
    // if the frame's height is smaller than the height of medium size.
    director->setContentScaleFactor(MIN(smallResolutionSize.height/designResolutionSize.height, smallResolutionSize.width/designResolutionSize.width));
  }

  register_all_packages();

  AutoDetectPuzzleScenes();

  // create a scene. it's an autorelease object
  cocos2d::Scene* scene = puzzle::PuzzleTitleScene::createScene();

  // run
  director->runWithScene(scene);

#ifndef _DEBUG
    // 左下のデバッグ情報を非表示にする.
  director->setDisplayStats(false);
#endif
  return true;
}

///////////////////////////////////////////////////////////////////////////////
void AppDelegate::applicationDidEnterBackground() {
  cocos2d::Director::getInstance()->stopAnimation();

#if USE_AUDIO_ENGINE
  cocos2d::AudioEngine::pauseAll();
#endif
}

///////////////////////////////////////////////////////////////////////////////
void AppDelegate::applicationWillEnterForeground() {
  cocos2d::Director::getInstance()->startAnimation();

#if USE_AUDIO_ENGINE
  cocos2d::AudioEngine::resumeAll();
#endif
}

///////////////////////////////////////////////////////////////////////////////
void AppDelegate::InitializePuzzle() {
  puzzle::ValueManager::getInstance().Initialize();
  puzzle::ScenarioManager::getInstance().Initialize();
  puzzle::MapManager::getInstance().Initialize();
  puzzle::ResultManager::getInstance().Initialize();

  puzzle::ValueManager::getInstance().Remove("PuzzleTitleScene::scenario_index");
  puzzle::ValueManager::getInstance().Remove("PuzzleTitleScene::map_index");
  puzzle::ValueManager::getInstance().Remove("PuzzleTitleScene::selector");
}

///////////////////////////////////////////////////////////////////////////////
cocos2d::Size AppDelegate::GetDesignResolutionSize() const {
  return cocos2d::Size(
    puzzle::ScenarioManager::getInstance().GetWidth() * 32,
    puzzle::ScenarioManager::getInstance().GetHeight() * 32);
}

///////////////////////////////////////////////////////////////////////////////
cocos2d::Size AppDelegate::GetSmallResolutionSize() const {
  return GetDesignResolutionSize();
}
///////////////////////////////////////////////////////////////////////////////
cocos2d::Size AppDelegate::GetMediumResolutionSize() const {
  return cocos2d::Size(1024, 768);
}
///////////////////////////////////////////////////////////////////////////////
cocos2d::Size AppDelegate::GetLargeResolutionSize() const {
  return cocos2d::Size(2048, 1536);
}

///////////////////////////////////////////////////////////////////////////////
void AppDelegate::AutoDetectPuzzleScenes() {
  if (puzzle::ScenarioManager::getInstance().GetAutoDetect()) {
    // 新たに追加されたマップを取り込む.
    puzzle::ScenarioAutoDetector detector;
    if (detector.Detect()) {
      puzzle::ScenarioManager::getInstance().Initialize();
    }
  }
}
