#include "MapReader.h"
#include "JsonLoader.h"
#include "ScenarioManager.h"
#include "StyleMapReaderFactory.h"
#include "StringUtil.h"

namespace puzzle {

///////////////////////////////////////////////////////////////////////////////
MapReader::MapReader(const std::string class_name, const std::string filename)
  : class_name_(class_name),
    filename_(filename),
    max_width_(1),
    max_height_(1) {
}

///////////////////////////////////////////////////////////////////////////////
MapReader::~MapReader() {
  maps_.clear();
}

///////////////////////////////////////////////////////////////////////////////
bool MapReader::Read() {
  maps_.clear();

  // ゲームクラスを読み込む.
  if (!ReadClass()) {
    return false;
  }

  // マップを読み込む.
  StyleMapReaderFactory factory;
  BaseStyleMapReader::Ptr reader = factory.Create(filename_, maps_, GetFillValue());
  if (reader == nullptr) {
    return false;
  }
  reader->Read();

  // width,heightを計算する.
  max_width_ = 1;
  max_height_ = 1;
  for (auto itr : maps_) {
    FieldMap::Ptr field = itr;
    if (max_width_ < field->Width()) {
      max_width_ = field->Width();
    }
    if (max_height_ < field->Height()) {
      max_height_ = field->Height();
    }
  }

  return true;
}

///////////////////////////////////////////////////////////////////////////////
bool MapReader::ReadClass() {
  ClassReader::Ptr reader(new ClassReader(class_name_));
  class_reader_ = reader;
  if (!class_reader_->Read()) {
    return false;
  }
  return true;
}

///////////////////////////////////////////////////////////////////////////////
FieldMap::Ptr MapReader::Get(const int index) {
  if ((index < 1) || (index > static_cast<int>(maps_.size()))) {
    return nullptr;
  }

  return maps_[index - 1];
}

///////////////////////////////////////////////////////////////////////////////
std::string MapReader::GetTitle() const {
  return class_reader_->GetTitle();
}

///////////////////////////////////////////////////////////////////////////////
std::string MapReader::GetAuthor() const {
  return class_reader_->GetAuthor();
}

///////////////////////////////////////////////////////////////////////////////
int MapReader::GetMaxWidth() const {
  return max_width_;
}

///////////////////////////////////////////////////////////////////////////////
int MapReader::GetMaxHeight() const {
  return max_height_;
}

///////////////////////////////////////////////////////////////////////////////
void MapReader::GetImages(std::map<int, std::string>& images) {
  class_reader_->GetImages(images);
}

///////////////////////////////////////////////////////////////////////////////
std::string MapReader::GetFontName() const {
  return class_reader_->GetFontName();
}

///////////////////////////////////////////////////////////////////////////////
int MapReader::GetFillValue() const {
  return class_reader_->GetFillValue();
}

///////////////////////////////////////////////////////////////////////////////
int MapReader::GetMapCount() {
  return static_cast<int>(maps_.size());
}

}  //puzzle
