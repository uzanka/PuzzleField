#include "FieldMap.h"

namespace puzzle {

///////////////////////////////////////////////////////////////////////////////
FieldMap::FieldMap(const int width, const int height, const int value)
  : width_(width),
    height_(height),
    field_map_(nullptr),
    title_(""),
    author_("") {
  if (width_ <= 0) width_ = 1;
  if (height_ <= 0) height_ = 1;
  field_map_ = new int[width_ * height_];
  Clear(value);
}

///////////////////////////////////////////////////////////////////////////////
FieldMap::~FieldMap() {
  if (field_map_ != nullptr) {
    delete[] field_map_;
    field_map_ = nullptr;
  }
}

///////////////////////////////////////////////////////////////////////////////
int FieldMap::Width() const {
  return width_;
}

///////////////////////////////////////////////////////////////////////////////
int FieldMap::Height() const {
  return height_;
}

///////////////////////////////////////////////////////////////////////////////
int FieldMap::Get(const int x, const int y) const {
  if (y < 0 || y >= height_) return -1;
  if (x < 0 || x >= width_) return -1;
  return field_map_[y * width_ + x];
}

///////////////////////////////////////////////////////////////////////////////
void FieldMap::Set(const int x, const int y, const int value) {
  if (y < 0 || y >= height_) return;
  if (x < 0 || x >= width_) return;
  field_map_[y * width_ + x] = value;
}

///////////////////////////////////////////////////////////////////////////////
void FieldMap::Clear(const int value) {
  for (int y = 0; y < height_; y++) {
    for (int x = 0; x < width_; x++) {
      Set(x, y, value);
    }
  }
}

///////////////////////////////////////////////////////////////////////////////
bool FieldMap::Find(const int value, int& rx, int& ry) {
  for (int y = 0; y < height_; y++) {
    for (int x = 0; x < width_; x++) {
      if (Get(x, y) == value) {
        rx = x;
        ry = y;
        return true;
      }
    }
  }
  return false;
}

///////////////////////////////////////////////////////////////////////////////
int FieldMap::Find(const int value, std::vector<std::pair<int, int>>& xy) {
  for (int y = 0; y < height_; y++) {
    for (int x = 0; x < width_; x++) {
      if (Get(x, y) == value) {
        xy.push_back(std::pair<int, int>(x, y));
      }
    }
  }
  return (int)xy.size();
}

///////////////////////////////////////////////////////////////////////////////
void FieldMap::SetTitle(const std::string title) {
  title_ = title;
}

///////////////////////////////////////////////////////////////////////////////
std::string FieldMap::GetTitle() const {
  return title_;
}

///////////////////////////////////////////////////////////////////////////////
void FieldMap::SetAuthor(const std::string author) {
  author_ = author;
}

///////////////////////////////////////////////////////////////////////////////
std::string FieldMap::GetAuthor() const {
  return author_;
}

///////////////////////////////////////////////////////////////////////////////
FieldMap::Ptr FieldMap::ExpandMap(FieldMap::Ptr src, const int width, const int height, const int value) {
  int max_width = width;
  int max_height = height;
  int offset_x = (max_width - src->Width()) / 2;
  int offset_y = (max_height - src->Height()) / 2;

  // マップのほうが大きい場合はマップのサイズにしてセンタリングする.
  if ((src->Width() > max_width) || (src->Height() > max_height)) {
    int wide = src->Width();
    if (src->Height() > wide) {
      wide = src->Height();
    }
    max_width = wide;
    max_height = wide;
    offset_x = (max_width - src->Width()) / 2;
    offset_y = (max_height - src->Height()) / 2;
  }

  FieldMap::Ptr dst(new FieldMap(max_width, max_height, value));
  for (int y = 0; y < src->Height(); y++) {
    for (int x = 0; x < src->Width(); x++) {
      dst->Set(x + offset_x, y + offset_y, src->Get(x, y));
    }
  }
  dst->SetTitle(src->GetTitle());
  dst->SetAuthor(src->GetAuthor());

  return dst;
}

}  // puzzle
