#include "DirectoryIterator.h"
#include "StringUtil.h"

namespace puzzle {

///////////////////////////////////////////////////////////////////////////////
DirectoryIterator::DirectoryIterator(const std::string directory, std::vector<std::string>& dirs)
  : directory_(directory),
    dirs_(dirs) {
}

///////////////////////////////////////////////////////////////////////////////
DirectoryIterator::~DirectoryIterator() {
}

///////////////////////////////////////////////////////////////////////////////
void DirectoryIterator::List() {
#ifdef _WINDOWS
  std::wstring wdir = StringUtil::ConvertCode(directory_ + "/*.*");

  WIN32_FIND_DATAW FindFileData;
  memset(&FindFileData, 0, sizeof(FindFileData));
  HANDLE hFind = ::FindFirstFileW(wdir.c_str(), &FindFileData);
  if (hFind == INVALID_HANDLE_VALUE) {
    return;
  }
  BOOL bResult = TRUE;
  while (bResult) {
    if ((FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0) {
      std::wstring wfile(FindFileData.cFileName);
      std::string filename = StringUtil::ConvertCode(wfile);
      if (filename != "." && filename != "..") {
        dirs_.push_back(filename);
      }
    }
    bResult = ::FindNextFileW(hFind, &FindFileData);
  };
  ::FindClose(hFind);
#endif
}

}  // puzzle
