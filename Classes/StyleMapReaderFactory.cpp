#include "StyleMapReaderFactory.h"
#include "JsonStyleMapReader.h"
#include "MapStyleMapReader.h"
#include "XmlStyleMapReader.h"
#include "StringUtil.h"

namespace puzzle {

///////////////////////////////////////////////////////////////////////////////
StyleMapReaderFactory::StyleMapReaderFactory() {
}

///////////////////////////////////////////////////////////////////////////////
StyleMapReaderFactory::~StyleMapReaderFactory() {
}

///////////////////////////////////////////////////////////////////////////////
BaseStyleMapReader::Ptr StyleMapReaderFactory::Create(
  const std::string filename,
  std::vector<FieldMap::Ptr>& maps,
  const int fillvalue) {
  BaseStyleMapReader::Ptr reader = nullptr;
  if (StringUtil::Right(filename, 5) == ".json") {
    JsonStyleMapReader::Ptr json_style_reader(new JsonStyleMapReader(filename, maps, fillvalue));
    reader = json_style_reader;
  } else if (StringUtil::Right(filename, 4) == ".map") {
    MapStyleMapReader::Ptr map_style_reader(new MapStyleMapReader(filename, maps, fillvalue));
    reader = map_style_reader;
  } else if ((StringUtil::Right(filename, 4) == ".xml")
          || (StringUtil::Right(filename, 4) == ".slc")) {
    XmlStyleMapReader::Ptr xml_style_reader(new XmlStyleMapReader(filename, maps, fillvalue));
    reader = xml_style_reader;
  }
  return reader;
}

///////////////////////////////////////////////////////////////////////////////
void StyleMapReaderFactory::GetFileTypes(std::vector<std::string>& types) {
  types.push_back(".json");
  types.push_back(".map");
  types.push_back(".xml");
  types.push_back(".slc");
}

}  // puzzle
