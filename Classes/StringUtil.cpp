#include "StringUtil.h"
#include <codecvt> 

namespace puzzle {

///////////////////////////////////////////////////////////////////////////////
StringUtil::StringUtil() {
}

///////////////////////////////////////////////////////////////////////////////
StringUtil::~StringUtil() {
}

///////////////////////////////////////////////////////////////////////////////
std::string StringUtil::Replace(std::string target, const std::string before, const std::string after) {
  std::string::size_type pos(target.find(before));
  while (pos != std::string::npos) {
    target.replace(pos, before.length(), after);
    pos = target.find(before, pos + after.length());
  }
  return target;
}

///////////////////////////////////////////////////////////////////////////////
int StringUtil::Split(const std::string target, const char delimiter, std::vector<std::string>& lines) {
  std::istringstream stream(target);
  std::string data;
  while (std::getline(stream, data, delimiter)) {
    lines.push_back(data);
  }
  return (int)lines.size();
}

///////////////////////////////////////////////////////////////////////////////
std::string StringUtil::TrimLeft(std::string target) {
  static const char* trimChars = " \t\v\r\n";
  std::string::size_type left = target.find_first_not_of(trimChars);
  if (left != std::string::npos) {
    target = target.substr(left);
  }
  return target;
}

///////////////////////////////////////////////////////////////////////////////
std::string StringUtil::TrimRight(std::string target) {
  static const char* trimChars = " \t\v\r\n";
  std::string::size_type right = target.find_last_not_of(trimChars);
  if (right != std::string::npos) {
    target = target.substr(0, right + 1);
  }
  return target;
}

///////////////////////////////////////////////////////////////////////////////
std::string StringUtil::Trim(std::string target) {
  return TrimLeft(TrimRight(target));
}

///////////////////////////////////////////////////////////////////////////////
std::string StringUtil::Left(std::string target, const std::size_t length) {
  if (length >= target.size()) {
    return target;
  }
  return target.substr(0, length);
}

///////////////////////////////////////////////////////////////////////////////
std::string StringUtil::Right(std::string target, const std::size_t length) {
  if (length >= target.size()) {
    return target;
  }
  return target.substr(target.size() - length);
}

///////////////////////////////////////////////////////////////////////////////
std::string StringUtil::Mid(std::string target, const std::size_t offset, const std::size_t length) {
  if (offset >= target.size()) {
    return "";
  }
  if (length == std::string::npos) {
    return target.substr(offset);
  }
  if ((offset + length) >= target.size()) {
    return target.substr(offset);
  }
  return target.substr(offset, length);
}

///////////////////////////////////////////////////////////////////////////////
std::string StringUtil::Hex2(const char ch) {
  int value = ch & 0xFF;
  char buffer[4];
  sprintf(buffer, "%02x", value);
  std::string text(buffer);
  return text;
}

///////////////////////////////////////////////////////////////////////////////
std::string StringUtil::ConvertCode(const std::wstring utf16) {
  std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> cv;
  return cv.to_bytes(utf16);
}

///////////////////////////////////////////////////////////////////////////////
std::wstring StringUtil::ConvertCode(const std::string utf8) {
  std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> cv;
  return cv.from_bytes(utf8);
}

}  // puzzle
