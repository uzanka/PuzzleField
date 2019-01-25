#include "ScenarioManager.h"
#include "JsonLoader.h"
#include "MapManager.h"

namespace puzzle {

///////////////////////////////////////////////////////////////////////////////
ScenarioManager& ScenarioManager::getInstance() {
  static ScenarioManager instance_;
  return instance_;
}

///////////////////////////////////////////////////////////////////////////////
ScenarioManager::ScenarioManager() {
}

///////////////////////////////////////////////////////////////////////////////
ScenarioManager::~ScenarioManager() {
}

///////////////////////////////////////////////////////////////////////////////
bool ScenarioManager::Initialize() {
  JsonLoader loader(doc_, kPuzzleFieldFileName);
  return loader.Read();
}

///////////////////////////////////////////////////////////////////////////////
std::string ScenarioManager::GetTitle() const {
  return doc_["title"].GetString();
}

///////////////////////////////////////////////////////////////////////////////
int ScenarioManager::GetWidth() const {
  return doc_["width"].GetInt();
}

///////////////////////////////////////////////////////////////////////////////
int ScenarioManager::GetHeight() const {
  return doc_["height"].GetInt();
}

///////////////////////////////////////////////////////////////////////////////
int ScenarioManager::GetCount() const {
  const rapidjson::Value& scenarios = doc_["scenarios"];
  return scenarios.Size();
}

///////////////////////////////////////////////////////////////////////////////
bool ScenarioManager::GetScenario(const int index, std::string& title, std::string& filename, int& maps, std::string& class_name) const {
  if ((index < 1) || (index > GetCount())) {
    return false;
  }
  const rapidjson::Value& scenarios = doc_["scenarios"];
  const rapidjson::Value& scenario = scenarios[index - 1];
  title = scenario["title"].GetString();
  filename = scenario["filename"].GetString();
  class_name = scenario["class"].GetString();
  MapReader::Ptr reader = MapManager::getInstance().GetScenario(class_name, filename);
  maps = reader->GetMapCount();
  return true;
}

///////////////////////////////////////////////////////////////////////////////
std::string ScenarioManager::GetScenarioTitle(const int index) const {
  if ((index < 1) || (index > GetCount())) {
    return false;
  }
  const rapidjson::Value& scenarios = doc_["scenarios"];
  const rapidjson::Value& scenario = scenarios[index - 1];
  std::string title = scenario["title"].GetString();
  return title;
}

///////////////////////////////////////////////////////////////////////////////
int ScenarioManager::GetScenarioMapCount(const int index) {
  if ((index < 1) || (index > GetCount())) {
    return false;
  }
  const rapidjson::Value& scenarios = doc_["scenarios"];
  const rapidjson::Value& scenario = scenarios[index - 1];
  std::string filename = scenario["filename"].GetString();
  std::string class_name = scenario["class"].GetString();
  MapReader::Ptr reader = MapManager::getInstance().GetScenario(class_name, filename);
  int maps = reader->GetMapCount();
  return maps;
}

///////////////////////////////////////////////////////////////////////////////
std::string ScenarioManager::GetFontName() const {
  if (!doc_.HasMember("fontname")) {
    return "fonts/arial.ttf";
  }
  return doc_["fontname"].GetString();
}

///////////////////////////////////////////////////////////////////////////////
bool ScenarioManager::GetAutoDetect() const {
  if (!doc_.HasMember("auto_detect")) {
    return false;
  }
  return doc_["auto_detect"].GetBool();
}

}  // puzzle
