#include "ScenarioAutoDetector.h"
#include "PuzzleFieldSceneFactory.h"
#include "FruitsFieldScene.h"
#include "SokobanScene.h"
#include "FileIterator.h"
#include "DirectoryIterator.h"
#include "StyleMapReaderFactory.h"
#include "platform/CCFileUtils.h"
#include "JsonLoader.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include "ScenarioManager.h"
#include "json/filewritestream.h"
#include "json/writer.h"
#include "json/prettywriter.h"

namespace puzzle {

///////////////////////////////////////////////////////////////////////////////
ScenarioAutoDetector::ScenarioAutoDetector() {
}

///////////////////////////////////////////////////////////////////////////////
ScenarioAutoDetector::~ScenarioAutoDetector() {
}

///////////////////////////////////////////////////////////////////////////////
bool ScenarioAutoDetector::Detect() {
  scenarios_.clear();
  filename_maps_.clear();

  rapidjson::Document doc;
  JsonLoader loader(doc, kPuzzleFieldFileName);
  if (!loader.Read()) {
    return false;
  }

  // 登録済みマップを作成する.
  const rapidjson::Value& scenarios = doc["scenarios"];
  for (std::size_t index = 0; index < scenarios.Size(); index++) {
    const rapidjson::Value& scenario = scenarios[index];
    std::string filename = scenario["filename"].GetString();
    filename_maps_.insert(std::make_pair(filename, 0));
  }

  PuzzleFieldSceneFactory factory;
  std::vector<std::string> classes;
  factory.GetClasses(classes);
  for (std::string class_name : classes) {
    if (class_name == "Detector") {
      continue;
    }
    DetectScenario(class_name);
  }

  return Update(doc);
}

///////////////////////////////////////////////////////////////////////////////
void ScenarioAutoDetector::DetectScenario(const std::string class_name) {
  // クラス/user/配下のファイルを探す.
  //std::string path = cocos2d::FileUtils::getInstance()->fullPathForFilename(class_name);
  std::string path = cocos2d::FileUtils::getInstance()->getDefaultResourceRootPath() + "/" + class_name + "/" + "user";
  DetectScenarioFiles(class_name, path);
}

///////////////////////////////////////////////////////////////////////////////
void ScenarioAutoDetector::DetectScenarioFiles(const std::string class_name, const std::string path) {
  std::vector<std::string> files;
  FileIterator itr(path, files);
  itr.List();
  for (std::string file : files) {
    std::string relative_path = class_name + "/user/" + file;
    if (filename_maps_.find(relative_path) != filename_maps_.end()) {
      continue;
    }

    std::string filename = path + "/" + file;
    StyleMapReaderFactory factory;
    std::vector<FieldMap::Ptr> maps;
    BaseStyleMapReader::Ptr reader = factory.Create(filename, maps, 0);
    if (reader == nullptr) {
      continue;
    }
    reader->Read();
    std::string title = reader->GetTitle();
    if (title.empty()) {
      continue;
    }
    ScenarioData::Ptr data(new ScenarioData(class_name, title, relative_path));
    scenarios_.push_back(data);
  }
}

///////////////////////////////////////////////////////////////////////////////
bool ScenarioAutoDetector::Update(rapidjson::Document& doc) {
  bool update = false;
  rapidjson::Value& scenarios = doc["scenarios"];
  rapidjson::Document::AllocatorType& allocator = doc.GetAllocator();
  for (std::size_t index = 0; index < scenarios_.size(); index++) {
    rapidjson::Value class_name(rapidjson::kStringType);
    class_name.SetString(scenarios_[index]->class_name_.c_str(), allocator);
    rapidjson::Value title(rapidjson::kStringType);
    title.SetString(scenarios_[index]->title_.c_str(), allocator);
    rapidjson::Value filename(rapidjson::kStringType);
    filename.SetString(scenarios_[index]->filename_.c_str(), allocator);

    rapidjson::Value scenario(rapidjson::kObjectType);
    scenario.AddMember("class", class_name, allocator);
    scenario.AddMember("title", title, allocator);
    scenario.AddMember("filename", filename, allocator);
    scenarios.PushBack(scenario, allocator);
    update = true;
  }

  if (!update) {
    return false;
  }

  std::string path = cocos2d::FileUtils::getInstance()->fullPathForFilename(kPuzzleFieldFileName);
  FILE* fp = fopen(path.c_str(), "wb");
  if (fp == nullptr) {
    return false;
  }

  char buffer[1024];
  rapidjson::FileWriteStream ws(fp, buffer, sizeof(buffer));
  rapidjson::PrettyWriter<rapidjson::FileWriteStream> writer(ws);
  writer.SetIndent(' ', 2);
  doc.Accept(writer);
  fclose(fp);

  return true;
}

}  // puzzle
