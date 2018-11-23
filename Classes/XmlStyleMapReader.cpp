#include "XmlStyleMapReader.h"
#include "StringUtil.h"
#include "tinyxml2/tinyxml2.h"
#include "platform/CCFileUtils.h"

namespace puzzle {

/*
  <SokobanLevels>
    <Title>{title}</Title>
    <Description>{description}</Description>
    <LevelCollection Copyright="{copyright}" MaxWidth="{max width}" MaxHeight="{max height}">
      <Level Id="{id}" Width="{width}" Height="{height}">
        <L>{map string}</L>
        ...
      </Level>
      ...
    </LevelCollection>
  </SokobanLevels>
*/

///////////////////////////////////////////////////////////////////////////////
XmlStyleMapReader::XmlStyleMapReader(const std::string filename, std::vector<FieldMap::Ptr>& maps, const int fillvalue)
  : BaseStyleMapReader(filename, maps, fillvalue) {
}

///////////////////////////////////////////////////////////////////////////////
XmlStyleMapReader::~XmlStyleMapReader() {
}

///////////////////////////////////////////////////////////////////////////////
void XmlStyleMapReader::Read() {
  // ファイルを読み込む.
  cocos2d::FileUtils* fileUtils = cocos2d::FileUtils::getInstance();
  std::string str = fileUtils->getStringFromFile(filename_);

  tinyxml2::XMLDocument doc;
  if (doc.Parse(str.c_str()) != tinyxml2::XML_NO_ERROR) {
    return;
  }

  tinyxml2::XMLElement* SokobanLevelsElement   = doc.FirstChildElement("SokobanLevels");
  tinyxml2::XMLElement* TitleElement           = SokobanLevelsElement->FirstChildElement("Title");
  tinyxml2::XMLElement* DescriptionElement     = SokobanLevelsElement->FirstChildElement("Description");
  tinyxml2::XMLElement* LevelCollectionElement = SokobanLevelsElement->FirstChildElement("LevelCollection");
  tinyxml2::XMLElement* LevelElement           = LevelCollectionElement->FirstChildElement("Level");

  scenario_title_ = StringUtil::Trim(TitleElement->GetText());  // scenario title
  //std::string description = StringUtil::Trim(DescriptionElement->GetText());
  scenario_author_ = StringUtil::Trim(LevelCollectionElement->Attribute("Copyright"));  // author
  //max_width_  = std::stoi(LevelCollectionElement->Attribute("MaxWidth"), nullptr, 10);
  //max_height_ = std::stoi(LevelCollectionElement->Attribute("MaxHeight"), nullptr, 10);

  for (; LevelElement; LevelElement = LevelElement->NextSiblingElement()) {
    // Levelを見つけるごとにマップを処理する.
    ReadOneMap(LevelElement);
  }
}

///////////////////////////////////////////////////////////////////////////////
void XmlStyleMapReader::ReadOneMap(tinyxml2::XMLElement* LevelElement) {
  std::string title = StringUtil::Trim(LevelElement->Attribute("Id"));  // map title
  int width  = std::stoi(LevelElement->Attribute("Width"), nullptr, 10);  // width
  int height = std::stoi(LevelElement->Attribute("Height"), nullptr, 10);  // height

  std::vector<std::string> field;
  auto LElement = LevelElement->FirstChildElement("L");
  for (; LElement; LElement = LElement->NextSiblingElement()) {
    std::string data = LElement->GetText();
    field.push_back(data);
  }

  ConvertMap(field, width, height, title, "");
}

///////////////////////////////////////////////////////////////////////////////
void XmlStyleMapReader::ConvertMap(
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

///////////////////////////////////////////////////////////////////////////////
int XmlStyleMapReader::GetWidth() const {
  int width = 1;
  for (auto field : maps_) {
    if (field->Width() > width) {
      width = field->Width();
    }
  }
  return width;
}

///////////////////////////////////////////////////////////////////////////////
int XmlStyleMapReader::GetHeight() const {
  int height = 1;
  for (auto field : maps_) {
    if (field->Height() > height) {
      height = field->Height();
    }
  }
  return height;
}

}  // puzzle
