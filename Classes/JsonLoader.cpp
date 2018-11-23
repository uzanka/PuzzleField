#include "JsonLoader.h"
#include "json/filereadstream.h"
#include "platform/CCFileUtils.h"

namespace puzzle {

///////////////////////////////////////////////////////////////////////////////
JsonLoader::JsonLoader(rapidjson::Document& doc, const std::string filename)
  : doc_(doc),
    filename_(filename) {
}

///////////////////////////////////////////////////////////////////////////////
JsonLoader::~JsonLoader() {
}

///////////////////////////////////////////////////////////////////////////////
bool JsonLoader::Read() {
  std::string path = cocos2d::FileUtils::getInstance()->fullPathForFilename(filename_);
  FILE* fp = fopen(path.c_str(), "rb");
  if (fp == nullptr) {
    return false;
  }

  char buffer[1024];
  rapidjson::FileReadStream rs(fp, buffer, sizeof(buffer));
  doc_.ParseStream(rs);
  fclose(fp);

  if (doc_.HasParseError()) {
    int code = doc_.GetParseError();
    std::size_t offset = doc_.GetErrorOffset();
    return false;
  }

  return true;
}

}  // puzzle
