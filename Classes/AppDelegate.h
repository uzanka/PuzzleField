#ifndef _PUZZLE_APP_DELEGATE_H_
#define _PUZZLE_APP_DELEGATE_H_

#include "PuzzleDefine.h"

/*!
 * @brief The cocos2d Application.
 * @details
 * Private inheritance here hides part of interface from Director.
 */
class AppDelegate : private cocos2d::Application {
public:
  /*!
   * @brief Constructor
   */
  AppDelegate();

  /*!
   * @brief Destructor
   */
  virtual ~AppDelegate();

  /*!
   * @brief Initialize glContextAttrs.
   * @details
   * If you want a different context, modify the value of glContextAttrs.
   * It will affect all platforms.
   */
  virtual void initGLContextAttrs();

  /*!
   * @brief Implement Director and Scene init code here.
   * @return true  Initialize success, app continue.
   * @return false Initialize failed, app terminate.
   */
  virtual bool applicationDidFinishLaunching();

  /*!
   * @brief Called when the application moves to the background.
   * @details
   * This function will be called when the app is inactive.
   * Note, when receiving a phone call it is invoked.
   */
  virtual void applicationDidEnterBackground();

  /*!
   * @brief Called when the application reenters the foreground.
   * @details
   * This function will be called when the app is active again.
   */
  virtual void applicationWillEnterForeground();

  /*!
   * @brief Initialize puzzle.
   * @details
   * Initialize before startup puzzle game.
   * - ScenarioManager : list of puzzle games.
   * - MapManager      : cache scenario maps.
   * - ResultManager   : save game results.
   * - ValueManager    : temporary game parameter between scenes.
   */
  void InitializePuzzle();

  /*!
   * @brief Get original resolution size.
   * @return resolution size
   */
  cocos2d::Size GetDesignResolutionSize() const;
  cocos2d::Size GetSmallResolutionSize() const;
  cocos2d::Size GetMediumResolutionSize() const;
  cocos2d::Size GetLargeResolutionSize() const;

  void AutoDetectPuzzleScenes();
};

#endif  // _PUZZLE_APP_DELEGATE_H_
