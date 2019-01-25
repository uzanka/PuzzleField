#ifndef __PUZZLE_SCENARIO_AUTO_DETECTOR_H__
#define __PUZZLE_SCENARIO_AUTO_DETECTOR_H__

#include "PuzzleDefine.h"
#include "json/rapidjson.h"
#include "json/document.h"

namespace puzzle {

class ScenarioData {
public:
  typedef std::shared_ptr<ScenarioData> Ptr;

  ScenarioData() {
  }

  ScenarioData(const std::string class_name, const std::string title, const std::string filename)
    : class_name_(class_name), title_(title), filename_(filename) {
  }

  virtual ~ScenarioData() {
  }

public:
  std::string class_name_;
  std::string title_;
  std::string filename_;
};

/*!
 * @brief シナリオ一覧を自動的に作成する.
 */
class ScenarioAutoDetector {
public:
  typedef std::shared_ptr<ScenarioAutoDetector> Ptr;

  /*!
   * @brief コンストラクタ
   */
  ScenarioAutoDetector();

  /*!
   * @brief デストラクタ
   */
  virtual ~ScenarioAutoDetector();

  /*!
   * @brief シナリオ一覧を自動的に作成する.
   */
  bool Detect();

protected:
  void DetectScenario(const std::string class_name);
  void DetectScenarioFiles(const std::string class_name, const std::string path);
  bool Update(rapidjson::Document& doc);

protected:
  std::vector<ScenarioData::Ptr> scenarios_;
  std::map<std::string, int> filename_maps_;
};

}  // puzzle

#endif // __PUZZLE_SCENARIO_AUTO_DETECTOR_H__
