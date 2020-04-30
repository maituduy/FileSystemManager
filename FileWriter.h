#ifndef FILESYSTEM_FILEWRITER_H
#define FILESYSTEM_FILEWRITER_H

#include <string>
#include <utility>
#include <vector>
#include <atomic>

namespace fsmanager {
    struct file {
        std::string name;
        void *buf;
        __int64_t buflen;

        file(std::string name, void *buf, __int64_t buflen) :name(std::move(name)), buf(buf), buflen(buflen){

        }
    };

    struct AtomicCounter {
        std::atomic<int> value;

        AtomicCounter() : value(0) {}

        void increment(){
            ++value;
        }

        void decrement(){
            --value;
        }

        int get(){
            return value.load();
        }

        void reset() {
            value = 0;
        }
    };

    class FileWriter {
    public:
        FileWriter(const std::vector<file>& files, const std::vector<std::string>& folders);

        bool write_on_multi_threads();

        void _write_one(const file& f, const std::string& folder, int file_index);

        void _write_many(const file &f, const std::vector<std::string>& folders, int file_index);


    private:
        std::vector<file> files;
        std::vector<std::string> folders;

        std::vector<AtomicCounter*> count;
        AtomicCounter* count_file;

    };
}


#endif //FILESYSTEM_FILEWRITER_H
