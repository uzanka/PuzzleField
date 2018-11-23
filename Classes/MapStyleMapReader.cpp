#include "MapStyleMapReader.h"
#include "StringUtil.h"
#include "json/filereadstream.h"
#include "platform/CCFileUtils.h"

namespace puzzle {

const static std::string kScenarioTitleKey = ";scenario_title:";
const static std::string kScenarioAuthorKey = ";scenario_author:";
const static std::string kTitleKey = ";title:";
const static std::string kAuthorKey = ";author:";

///////////////////////////////////////////////////////////////////////////////
MapStyleMapReader::MapStyleMapReader(const std::string filename, std::vector<FieldMap::Ptr>& maps, const int fillvalue)
  : BaseStyleMapReader(filename, maps, fillvalue) {
}

///////////////////////////////////////////////////////////////////////////////
MapStyleMapReader::~MapStyleMapReader() {
}

///////////////////////////////////////////////////////////////////////////////
void MapStyleMapReader::Read() {
  // ファイルを読み込む.
  cocos2d::FileUtils* fileUtils = cocos2d::FileUtils::getInstance();
  std::string str = fileUtils->getStringFromFile(filename_);
  str = StringUtil::Replace(str, "\r\n", "\n");
  std::vector<std::string> lines;
  StringUtil::Split(str, '\n', lines);

  // Titleを見つけるごとにマップを処理する.
  for (std::size_t i = 0; i < lines.size(); i++) {
    std::string data = lines.at(i);
    if (data.substr(0, kTitleKey.size()) == kTitleKey) {
      i = ReadOneMap(lines, i);
    } else if (data.substr(0, kScenarioTitleKey.size()) == kScenarioTitleKey) {
      scenario_title_ = StringUtil::Trim(data.substr(kScenarioTitleKey.size()));
    } else if (data.substr(0, kScenarioAuthorKey.size()) == kScenarioAuthorKey) {
      scenario_author_ = StringUtil::Trim(data.substr(kScenarioAuthorKey.size()));
    }
  }
}

///////////////////////////////////////////////////////////////////////////////
int MapStyleMapReader::ReadOneMap(const std::vector<std::string>& lines, std::size_t i) {
  int width = 0;
  int height = 0;
  std::string author;
  std::string title;
  std::vector<std::string> field;
  for (; i < lines.size(); i++) {
    std::string data = lines.at(i);
    if (data.substr(0, 1) == ";") {
      if (data.substr(0, kTitleKey.size()) == kTitleKey) {
        title = StringUtil::Trim(data.substr(kTitleKey.size()));
      } else if (data.substr(0, kAuthorKey.size()) == kAuthorKey) {
        author = StringUtil::Trim(data.substr(kAuthorKey.size()));
      }
    } else if (data.empty()) {
      break;
    } else {
      field.push_back(data);
      if (static_cast<int>(data.size()) > width) {
        width = data.size();
      }
      height++;
    }
  }

  ConvertMap(field, width, height, title, author);
  return i;
}

///////////////////////////////////////////////////////////////////////////////
void MapStyleMapReader::ConvertMap(
  std::vector<std::string>& field,
  const int width,
  const int height,
  const std::string title,
  const std::string author) {
  if ((width < 1) || (height < 1)) {
    return;
  }

  FieldMap::Ptr field_map(new FieldMap(width, height, fillvalue_));
  field_map->SetTitle(title);
  field_map->SetAuthor(author);
  for (int y = 0; y < height; y++) {
    std::string data = field.at(y);
    for (int x = 0; x < width; x++) {
      int value = ' ';
      if (x < static_cast<int>(data.size())) {
        value = data[x];
      }
      field_map->Set(x, y, value);
    }
  }
  maps_.push_back(field_map);
}

}  // puzzle
