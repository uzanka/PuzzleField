#ifndef __PUZZLE_PUZZLE_FIELD_SCENE_FACTORY_H__
#define __PUZZLE_PUZZLE_FIELD_SCENE_FACTORY_H__

#include "PuzzleDefine.h"

namespace puzzle {

class PuzzleFieldSceneFactory {
public:
  PuzzleFieldSceneFactory();
  virtual ~PuzzleFieldSceneFactory();

  cocos2d::Scene* Create(
    const std::string class_name,
    const std::string title,
    const std::string filename,
    const int map_index);

  void GetClasses(std::vector<std::string>& classes);
};

}  // puzzle

#endif  // __PUZZLE_PUZZLE_FIELD_SCENE_FACTORY_H__
