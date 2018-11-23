#include "ResultManager.h"
#include "json/stringbuffer.h"
#include "json/writer.h"

namespace puzzle {

///////////////////////////////////////////////////////////////////////////////
ResultManager& ResultManager::getInstance() {
  static ResultManager instance_;
  return instance_;
}

///////////////////////////////////////////////////////////////////////////////
ResultManager::ResultManager() {
}

///////////////////////////////////////////////////////////////////////////////
ResultManager::~ResultManager() {
  results_.clear();
}

///////////////////////////////////////////////////////////////////////////////
bool ResultManager::Initialize() {
  results_.clear();
  return true;
}

///////////////////////////////////////////////////////////////////////////////
ResultData::Ptr ResultManager::GetResult(const std::string title) {
  ResultData::Ptr result;
  auto itr = results_.find(title);
  if (itr != results_.end()) {
    result = itr->second;
  } else {
    result = Read(title);
    if (result != nullptr) {
      results_.insert(std::make_pair(title, result));
    }
  }
  return result;
}

///////////////////////////////////////////////////////////////////////////////
ResultData::Ptr ResultManager::Read(const std::string title) {
  ResultData::Ptr result(new ResultData(title));

  auto userDefault = cocos2d::UserDefault::getInstance();
  std::string data = userDefault->getStringForKey(result->GetKey().c_str(), "");

  rapidjson::Document doc;
  doc.Parse(data.c_str());
  if (doc.HasParseError()) {
    return result;
  }

  //result->title_ = doc["title"].GetString();
  result->completed_ = doc["completed"].GetBool();
  const rapidjson::Value& cleared = doc["cleared"];
  for (rapidjson::SizeType index = 0; index < cleared.Size(); index++) {
    result->cleared_.push_back(cleared[index].GetInt());
  }

  return result;
}

///////////////////////////////////////////////////////////////////////////////
void ResultManager::Flush() {
  for (auto itr : results_) {
    if (itr.second->dirty_) {
      Flush(itr.second);
    }
  }
}

///////////////////////////////////////////////////////////////////////////////
void ResultManager::Flush(ResultData::Ptr result) {
  rapidjson::Document doc;
  doc.SetObject();
  rapidjson::Document::AllocatorType& allocator = doc.GetAllocator();

  rapidjson::Value title(rapidjson::kStringType);
  title.SetString(result->title_.c_str(), allocator);

  rapidjson::Value completed(rapidjson::kFalseType);
  completed.SetBool(result->completed_);

  rapidjson::Value cleared(rapidjson::kArrayType);
  for (std::size_t index = 0; index < result->cleared_.size(); index++) {
    cleared.PushBack<int>(result->cleared_[index], allocator);
  }

  doc.AddMember("title", title, allocator);
  doc.AddMember("completed", completed, allocator);
  doc.AddMember("cleared", cleared, allocator);

  std::string json = GetJsonString(doc);

  auto userDefault = cocos2d::UserDefault::getInstance();
  userDefault->setStringForKey(result->GetKey().c_str(), json);
  userDefault->flush();

  result->dirty_ = false;
}

///////////////////////////////////////////////////////////////////////////////
void ResultManager::SetCleared(const std::string title, const int index) {
  if (IsCleared(title, index)) {
    return;
  }
  ResultData::Ptr result = GetResult(title);
  result->cleared_.push_back(index);
  result->dirty_ = true;
}

///////////////////////////////////////////////////////////////////////////////
bool ResultManager::IsCleared(const std::string title, const int index) {
  ResultData::Ptr result = GetResult(title);
  for (auto no : result->cleared_) {
    if (index == no) {
      return true;
    }
  }
  return false;
}

///////////////////////////////////////////////////////////////////////////////
void ResultManager::SetCompleted(const std::string title) {
  ResultData::Ptr result = GetResult(title);
  result->completed_ = true;
  result->dirty_ = true;
}

///////////////////////////////////////////////////////////////////////////////
bool ResultManager::IsCompleted(const std::string title) {
  ResultData::Ptr result = GetResult(title);
  return result->completed_;
}

///////////////////////////////////////////////////////////////////////////////
int ResultManager::GetMinumumUnClearedIndex(const std::string title, const int first) {
  ResultData::Ptr result = GetResult(title);
  int index = first;
  for (; index < std::numeric_limits<int>::max(); index++) {
    if (!IsCleared(title, index)) {
      break;
    }
  }
  return index;
}

///////////////////////////////////////////////////////////////////////////////
std::string ResultManager::GetJsonString(rapidjson::Document& doc) {
  rapidjson::StringBuffer buffer;
  rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
  doc.Accept(writer);
  std::string json(buffer.GetString());
  return json;
}

}  // puzzle
