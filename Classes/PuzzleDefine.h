#ifndef __PUZZLE_DEFINE__
#define __PUZZLE_DEFINE__

#include <string>
#include <map>
#include <vector>
#include <list>
#include <memory>
#include <limits>
#include "cocos2d.h"

namespace puzzle {

const static std::string kPuzzleTitle  = "PuzzleField";  //!< パズル名

#ifdef _DEBUG
#define LOG cocos2d::log
#else
#define LOG(...)
#endif

}  // puzzle

#endif  // __PUZZLE_DEFINE__
