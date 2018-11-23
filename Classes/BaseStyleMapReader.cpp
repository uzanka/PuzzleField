#include "BaseStyleMapReader.h"

namespace puzzle {

///////////////////////////////////////////////////////////////////////////////
BaseStyleMapReader::BaseStyleMapReader(
  const std::string filename,
  std::vector<FieldMap::Ptr>& maps,
  const int fillvalue)
  : filename_(filename),
    maps_(maps),
    fillvalue_(fillvalue),
    scenario_title_(""),
    scenario_author_("") {
}

///////////////////////////////////////////////////////////////////////////////
BaseStyleMapReader::~BaseStyleMapReader() {
}

///////////////////////////////////////////////////////////////////////////////
std::string BaseStyleMapReader::GetTitle() const {
  return scenario_title_;
}

///////////////////////////////////////////////////////////////////////////////
std::string BaseStyleMapReader::GetAuthor() const {
  return scenario_author_;
}

}  // puzzle
