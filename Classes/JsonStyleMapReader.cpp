#include "MapReader.h"
#include "JsonLoader.h"
#include "ScenarioManager.h"
#include "JsonStyleMapReader.h"

namespace puzzle {

///////////////////////////////////////////////////////////////////////////////
JsonStyleMapReader::JsonStyleMapReader(const std::string filename, std::vector<FieldMap::Ptr>& maps, const int fillvalue)
  : BaseStyleMapReader(filename, maps, fillvalue) {
}

///////////////////////////////////////////////////////////////////////////////
JsonStyleMapReader::~JsonStyleMapReader() {
}

///////////////////////////////////////////////////////////////////////////////
void JsonStyleMapReader::Read() {
  rapidjson::Document doc;
  JsonLoader loader(doc, filename_);
  if (!loader.Read()) {
    return;
  }

  if (doc.HasMember("title")) {
    scenario_title_ = doc["title"].GetString();
  }
  if (doc.HasMember("author")) {
    scenario_author_ = doc["author"].GetString();
  }

  const rapidjson::Value& json_phases = doc["phases"];
  if (json_phases.IsArray()) {
    for (rapidjson::SizeType i = 0; i < json_phases.Size(); i++) {
      const rapidjson::Value& json_phase = json_phases[i];
      ReadOneMap(json_phase);
    }
  }
}

///////////////////////////////////////////////////////////////////////////////
void JsonStyleMapReader::ReadOneMap(const rapidjson::Value& json_phase) {
  FieldMap::Ptr field_map = nullptr;
  const rapidjson::Value& json_map = json_phase["map"];
  if (json_map.Size() == 0) {
    return;
  }
  if (json_map[0].IsInt()) {
    int width = json_phase["width"].GetInt();
    int height = json_phase["height"].GetInt();
    if (json_map.Size() != width * height) {
      return;
    }
    FieldMap::Ptr field(new FieldMap(width, height));
    field_map = field;
    for (int y = 0; y < height; y++) {
      for (int x = 0; x < width; x++) {
        field_map->Set(x, y, json_map[y * width + x].GetInt());
      }
    }
  } else if (json_map[0].IsString()) {
    int width = 1;
    int height = static_cast<int>(json_map.Size());
    std::vector<std::string> lines;
    for (rapidjson::SizeType index = 0; index < json_map.Size(); index++) {
      std::string data = json_map[index].GetString();
      lines.push_back(data);
      if (static_cast<int>(data.size()) > width) {
        width = data.size();
      }
    }
    field_map = ConvertMap(lines, width, height);
    if (field_map == nullptr) {
      return;
    }
  } else {
    return;
  }

  if (json_phase.HasMember("title")) {
    field_map->SetTitle(json_phase["title"].GetString());
  }

  if (json_phase.HasMember("author")) {
    field_map->SetTitle(json_phase["author"].GetString());
  }

  maps_.push_back(field_map);
}

///////////////////////////////////////////////////////////////////////////////
FieldMap::Ptr JsonStyleMapReader::ConvertMap(
  std::vector<std::string>& lines,
  const int width,
  const int height) {
  FieldMap::Ptr field_map(new FieldMap(width, height, fillvalue_));
  for (int y = 0; y < height; y++) {
    std::string data = lines.at(y);
    for (int x = 0; x < width; x++) {
      int value = ' ';
      if (x < static_cast<int>(data.size())) {
        value = data[x];
      }
      field_map->Set(x, y, value);
    }
  }
  return field_map;
}

}  //puzzle
