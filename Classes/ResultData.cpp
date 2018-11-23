#include "ResultData.h"
#include "StringUtil.h"

namespace puzzle {

///////////////////////////////////////////////////////////////////////////////
ResultData::ResultData(const std::string title)
  : dirty_(false),
    title_(title),
    completed_(false),
    key_("") {
  key_ = MakeKey(title_);
}

///////////////////////////////////////////////////////////////////////////////
ResultData::~ResultData() {
}

///////////////////////////////////////////////////////////////////////////////
std::string ResultData::GetKey() {
  return key_;
}

///////////////////////////////////////////////////////////////////////////////
std::string ResultData::MakeKey(const std::string title) {
  std::string key = kPuzzleTitle;
  for (std::size_t index = 0; index < title_.size(); index++) {
    key += StringUtil::Hex2(title_[index]);
  }
  return key;
}

}  // puzzle
