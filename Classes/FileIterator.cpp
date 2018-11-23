#include "FileIterator.h"
#include "StringUtil.h"

namespace puzzle {

///////////////////////////////////////////////////////////////////////////////
FileIterator::FileIterator(const std::string directory, std::vector<std::string>& files)
  : directory_(directory),
    files_(files) {
}

///////////////////////////////////////////////////////////////////////////////
FileIterator::~FileIterator() {
}

///////////////////////////////////////////////////////////////////////////////
void FileIterator::List() {
#ifdef _WINDOWS
  std::wstring wdir = StringUtil::ConvertCode(directory_);

  WIN32_FIND_DATAW FindFileData;
  memset(&FindFileData, 0, sizeof(FindFileData));
  HANDLE hFind = ::FindFirstFileW(wdir.c_str(), &FindFileData);
  if (hFind == INVALID_HANDLE_VALUE) {
    return;
  }
  BOOL bResult = TRUE;
  while (bResult) {
    if ((FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0) {
      std::wstring wfile(FindFileData.cFileName);
      files_.push_back(StringUtil::ConvertCode(wfile));
    }
    bResult = ::FindNextFileW(hFind, &FindFileData);
  };
  ::FindClose(hFind);
#endif
}

}  // puzzle
