#include "ValueManager.h"

namespace puzzle {

///////////////////////////////////////////////////////////////////////////////
ValueManager& ValueManager::getInstance() {
  static ValueManager instance_;
  return instance_;
}

///////////////////////////////////////////////////////////////////////////////
ValueManager::ValueManager() {
}

///////////////////////////////////////////////////////////////////////////////
ValueManager::~ValueManager() {
  values_.clear();
}

///////////////////////////////////////////////////////////////////////////////
bool ValueManager::Initialize() {
  values_.clear();
  return true;
}

///////////////////////////////////////////////////////////////////////////////
void ValueManager::SetString(const std::string key, const std::string value) {
  Remove(key);
  values_.insert(std::make_pair(key, value));
}

///////////////////////////////////////////////////////////////////////////////
void ValueManager::SetInt(const std::string key, const int value) {
  SetString(key, std::to_string(value));
}

///////////////////////////////////////////////////////////////////////////////
void ValueManager::SetFloat(const std::string key, const float value) {
  SetString(key, std::to_string(value));
}

///////////////////////////////////////////////////////////////////////////////
std::string ValueManager::GetString(const std::string key, const std::string default_value) {
  auto itr = values_.find(key);
  if (itr == values_.end()) {
    return default_value;
  }
  return itr->second;
}

///////////////////////////////////////////////////////////////////////////////
int ValueManager::GetInt(const std::string key, const int default_value) {
  std::string strvalue = GetString(key);
  if (strvalue.empty()) {
    return default_value;
  }
  std::size_t idx = std::string::npos;
  int value = std::stoi(strvalue, &idx, 10);
  if (idx != strvalue.size()) {
    return default_value;
  }
  return value;
}

///////////////////////////////////////////////////////////////////////////////
float ValueManager::GetFloat(const std::string key, const float default_value) {
  std::string strvalue = GetString(key);
  if (strvalue.empty()) {
    return default_value;
  }
  std::size_t idx = std::string::npos;
  float value = std::stof(strvalue, &idx);
  if (idx != strvalue.size()) {
    return default_value;
  }
  return value;
}

///////////////////////////////////////////////////////////////////////////////
void ValueManager::Remove(const std::string key) {
  auto itr = values_.find(key);
  if (itr == values_.end()) {
    return;
  }
  values_.erase(itr);
}

}  // puzzle
