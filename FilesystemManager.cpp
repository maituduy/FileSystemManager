#include "FilesystemManager.h"

#include <experimental/filesystem>
#include <iostream>
#include <fstream>

namespace fs = std::experimental::filesystem;

namespace fsmanager {

    void viewFolder(std::string path, view_option option) {

      for (const auto &entry : fs::directory_iterator(path)) {
        std::cout << entry.path() << std::endl;

        if (option == view_option::all)
          if (fs::is_directory(entry.path()))
            viewFolder(entry.path(), option);
      }
    }

    bool createFolder(std::string path) {
      return fs::create_directories(path);
    }

    bool renameFolder(std::string oldname, std::string newname) {
      if (!fs::is_directory(oldname))
        return false;

      std::error_code errorCode;
      fs::rename(oldname, newname, errorCode);
      return !errorCode.value();
    }

    bool copyFolder(std::string path_from, std::string path_to) {
      if (!fs::is_directory(path_from))
        return false;

      std::error_code errorCode;
      fs::copy(path_from, path_to, fs::copy_options::recursive, errorCode);
      return !errorCode.value();
    }

    bool findFolder(std::string path) {
      return fs::is_directory(path);
    }

    bool moveFolder(std::string path_from, std::string path_to) {
      return renameFolder(path_from, fs::path(path_to) / fs::path(path_from).filename());
    }

    bool deleteFolder(std::string path) {
      return fs::is_directory(path) & fs::remove_all(path);
    }

    bool writeFile(std::string path, const void *buf, __int64_t buflen) {

      std::ofstream ofs(path, std::ofstream::binary);
      if (ofs) {
        ofs.write(static_cast<const char *>(buf), buflen);
        ofs.close();
        return true;
      } else
          std::cout << "Cannot create file\n";
      return false;
    }

    bool renameFile(std::string oldname, std::string newname) {
      if (!fs::is_regular_file(oldname))
        return false;

      std::error_code errorCode;
      fs::rename(oldname, newname, errorCode);
      return !errorCode.value();
    }

    bool copyFile(std::string path_from, std::string path_to) {
      if (!fs::is_regular_file(path_from))
        return false;

      std::error_code errorCode;
      fs::copy(path_from, path_to, errorCode);
      return !errorCode.value();
    }

    bool findFile(std::string path) {
      return fs::is_regular_file(path);
    }

    bool moveFile(std::string path_from, std::string path_to) {
      return renameFile(path_from, fs::path(path_to) / fs::path(path_from).filename());
    }

    bool deleteFile(std::string path) {
      if (fs::is_regular_file(path))
        return fs::remove(path);
      return false;
    }


}
