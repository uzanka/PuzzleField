#include "ClassReader.h"
#include "JsonLoader.h"
#include "ScenarioManager.h"

namespace puzzle {

///////////////////////////////////////////////////////////////////////////////
ClassReader::ClassReader(const std::string class_name)
  : class_name_(class_name),
    title_(""),
    author_(""),
    fontname_("fonts/arial.ttf"),
    fill_value_(0) {
}

///////////////////////////////////////////////////////////////////////////////
ClassReader::~ClassReader() {
  images_.clear();
}

///////////////////////////////////////////////////////////////////////////////
bool ClassReader::Read() {
  rapidjson::Document doc;
  std::string class_filename = "class_" + class_name_ + ".json";
  JsonLoader loader(doc, class_filename);
  if (!loader.Read()) {
    return false;
  }

  if (doc.HasMember("title")) {
    title_ = doc["title"].GetString();
  }
  if (doc.HasMember("author")) {
    author_ = doc["author"].GetString();
  }
  if (doc.HasMember("fontname")) {
    fontname_ = doc["fontname"].GetString();
  } else {
    fontname_ = ScenarioManager::getInstance().GetFontName();
  }
  if (doc.HasMember("fillvalue")) {
    if (doc["fillvalue"].IsInt()) {
      fill_value_ = doc["fillvalue"].GetInt();
    } else {
      std::string value = doc["fillvalue"].GetString();
      if (value.size() >= 1) {
        fill_value_ = value[0];
      }
    }
  }

  const rapidjson::Value& doc_images = doc["images"];
  for (int i = 0; i < (int)doc_images.Size(); i++) {
    const rapidjson::Value& doc_image = doc_images[i];
    int key = 0;
    if (doc_image["value"].IsInt()) {
      key = doc_image["value"].GetInt();
    } else {
      std::string value = doc_image["value"].GetString();
      if (value.size() >= 1) {
        key = value[0];
      }
    }

    std::string filename = doc_image["filename"].GetString();
    images_.insert(std::make_pair(key, filename));
  }

  return true;
}

///////////////////////////////////////////////////////////////////////////////
std::string ClassReader::GetTitle() const {
  return title_;
}

///////////////////////////////////////////////////////////////////////////////
std::string ClassReader::GetAuthor() const {
  return author_;
}

///////////////////////////////////////////////////////////////////////////////
void ClassReader::GetImages(std::map<int, std::string>& images) {
  images = images_;
}

///////////////////////////////////////////////////////////////////////////////
std::string ClassReader::GetFontName() const {
  return fontname_;
}

///////////////////////////////////////////////////////////////////////////////
int ClassReader::GetFillValue() const {
  return fill_value_;
}

}  //puzzle
