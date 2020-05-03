#include "ManagerFileSystem/FileWriter.h"

#include <experimental/filesystem>
#include <iostream>
#include <future>
#include <utility>

#include "ManagerFileSystem/FilesystemManager.h"

namespace fs = std::experimental::filesystem;

namespace fsmanager {

    FileWriter::FileWriter(std::vector<file>  files, std::vector<std::string>  folders): files(std::move(files)), folders(std::move(folders)) {
    }

    bool FileWriter::write_on_multi_threads() {
        std::vector<std::future<bool>> threads_for_files;

        size_t count_file = 0;

        for (auto&& f: files)
            threads_for_files.push_back(std::async(std::launch::async, &FileWriter::_write_many, this, f));

        for (auto&& tff: threads_for_files)
            count_file += tff.get();

        return count_file == files.size();
    }

    bool FileWriter::_write_one(const file& f, const std::string& folder) {

        return writeFile(fs::path(folder) / f.name, f.buf, f.buflen);
    }

    bool FileWriter::_write_many(const file &f) {
        std::vector<std::future<bool>> threads_for_folders;

        size_t count_folder = 0;

        for (auto&& folder: folders)
            threads_for_folders.push_back(std::async(std::launch::async, &FileWriter::_write_one, this, f, folder));

        for (auto&& tff: threads_for_folders)
            count_folder += tff.get();

        return count_folder == folders.size();
    }

}

