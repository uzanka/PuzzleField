#ifndef __PUZZLE_STYLE_MAP_READER_FACTORY_H__
#define __PUZZLE_STYLE_MAP_READER_FACTORY_H__

#include "PuzzleDefine.h"
#include "BaseStyleMapReader.h"

namespace puzzle {

class StyleMapReaderFactory {
public:
  StyleMapReaderFactory();
  virtual ~StyleMapReaderFactory();

  BaseStyleMapReader::Ptr Create(
    const std::string class_name,
    std::vector<FieldMap::Ptr>& maps,
    const int fillvalue);

  void GetFileTypes(std::vector<std::string>& types);
};

}  // puzzle

#endif  // __PUZZLE_STYLE_MAP_READER_FACTORY_H__
