#include "FileWriter.h"

#include <thread>
#include <utility>
#include <experimental/filesystem>
#include <iostream>
#include "FilesystemManager.h"

namespace fs = std::experimental::filesystem;

namespace fsmanager {

    FileWriter::FileWriter(const std::vector<file>& files, const std::vector<std::string>& folders): files(files), folders(folders) {

        count_file = new AtomicCounter();
        for (int i = 0; i < this->files.size(); ++i)
            count.emplace_back(new AtomicCounter());

    }

    bool FileWriter::write_on_multi_threads() {
        std::thread threads_for_files[files.size()];
        count_file->reset();

        for (int i = 0; i < files.size(); ++i) {
            count[i]->reset();
            threads_for_files[i] = std::thread(&FileWriter::_write_many, this, files[i], folders, i);
        }

        for (int i = 0; i < files.size(); ++i)
            threads_for_files[i].join();

        return count_file->get() == files.size();
    }

    void FileWriter::_write_one(const file& f, const std::string& folder, int file_index) {

        if (writeFile(fs::path(folder) / f.name, f.buf, f.buflen))
            this->count[file_index]->increment();
    }

    void FileWriter::_write_many(const file &f, const std::vector<std::string>& folders, int file_index) {
        int folders_size = folders.size();
        std::thread threads_for_folders[folders_size];

        for (int i = 0; i < folders_size; ++i)
            threads_for_folders[i] = std::thread(&FileWriter::_write_one, this, f, folders[i], file_index);

        for (int i = 0; i < folders_size; ++i)
            threads_for_folders[i].join();

        if (count[file_index]->get() == folders_size)
            count_file->increment();
    }

}

