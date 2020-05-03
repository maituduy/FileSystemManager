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
        FileWriter(std::vector<file>  files, std::vector<std::string>  folders);

        bool write_on_multi_threads();

    private:
        std::vector<file> files;
        std::vector<std::string> folders;

        bool _write_one(const file& f, const std::string& folder);

        bool _write_many(const file &f);

    };
}


#endif //FILESYSTEM_FILEWRITER_H
