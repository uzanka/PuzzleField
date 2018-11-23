#include "MapManager.h"

namespace puzzle {

///////////////////////////////////////////////////////////////////////////////
MapManager& MapManager::getInstance() {
  static MapManager instance_;
  return instance_;
}

///////////////////////////////////////////////////////////////////////////////
MapManager::MapManager() {
}

///////////////////////////////////////////////////////////////////////////////
MapManager::~MapManager() {
  scenarios_.clear();
}

///////////////////////////////////////////////////////////////////////////////
bool MapManager::Initialize() {
  scenarios_.clear();
  return true;
}

///////////////////////////////////////////////////////////////////////////////
MapReader::Ptr MapManager::GetScenario(const std::string class_name, const std::string filename) {
  std::map<std::string, MapReader::Ptr>::iterator itr = scenarios_.find(filename);
  if (itr != scenarios_.end()) {
    return itr->second;
  }

  MapReader::Ptr scenario = Read(class_name, filename);
  if (scenario == nullptr) {
    return nullptr;
  }
  scenarios_.insert(std::make_pair(filename, scenario));
  return scenario;
}

///////////////////////////////////////////////////////////////////////////////
MapReader::Ptr MapManager::Read(const std::string class_name, const std::string filename) {
  MapReader::Ptr scenario(new MapReader(class_name, filename));
  if (!scenario->Read()) {
    return nullptr;
  }
  return scenario;
}

}  // puzzle
