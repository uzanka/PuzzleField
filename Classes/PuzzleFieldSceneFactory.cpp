#include "PuzzleFieldSceneFactory.h"
#include "PuzzleTitleScene.h"
#include "FruitsFieldScene.h"
#include "SokobanScene.h"
//#include "ReversingFloorScene.h"
//#include "AutoDetectorScene.h"

namespace puzzle {

///////////////////////////////////////////////////////////////////////////////
PuzzleFieldSceneFactory::PuzzleFieldSceneFactory() {
}

///////////////////////////////////////////////////////////////////////////////
PuzzleFieldSceneFactory::~PuzzleFieldSceneFactory() {
}

///////////////////////////////////////////////////////////////////////////////
cocos2d::Scene* PuzzleFieldSceneFactory::Create(
  const std::string class_name,
  const std::string title,
  const std::string filename,
  const int map_index) {
  if (class_name == "Title") {
    return PuzzleTitleScene::createScene();
  } else if (class_name == "FruitsField") {
    return FruitsFieldScene::createScene(title, filename, map_index);
  } else if (class_name == "Sokoban") {
    return SokobanScene::createScene(title, filename, map_index);
  //} else if (class_name == "ReversingFloor") {
  //  return ReversingFloorScene::createScene(title, filename, map_index);
  //} else if (class_name == "Detector") {
  //  return AutoDetectorScene::createScene();
  } else {
    return nullptr;
  }
}

///////////////////////////////////////////////////////////////////////////////
void PuzzleFieldSceneFactory::GetClasses(std::vector<std::string>& classes) {
  classes.push_back("FruitsField");
  classes.push_back("Sokoban");
  //classes.push_back("ReversingFloor");
}

}  // puzzle
