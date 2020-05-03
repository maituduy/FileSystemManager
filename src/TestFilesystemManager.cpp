#include <iostream>
#include <fstream>
#include "ManagerFileSystem/FileWriter.h"
#include "ManagerFileSystem/FilesystemManager.h"
#include <chrono>
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;
fs::path temp_path = fs::temp_directory_path();

void test_create_folder() {
    fsmanager::createFolder(temp_path / "root/a/b/c");
    fsmanager::createFolder(temp_path / "root/d/e");
}

void test_rename_folder() {
    fsmanager::renameFolder(temp_path / "root/a", temp_path / "root/new_a");
    fsmanager::renameFolder(temp_path / "root/d/e", temp_path / "root/d/new_e");
}

void test_copy_folder() {
    fsmanager::copyFolder(temp_path / "root/new_a", temp_path / "root/copy_a");
}

void test_move_folder() {
    fsmanager::moveFolder(temp_path / "root/d/new_e", temp_path / "root/new_a");
}

void test_find_folder() {
    std::cout << fsmanager::findFolder(temp_path / "root/copy_a/b/c") << std::endl;
    std::cout << fsmanager::findFolder(temp_path / "not_exist") << std::endl;
}

void test_view_folder() {
    fsmanager::viewFolder(temp_path / "root", fsmanager::view_option::all);
}

void test_write_file() {
    std::string test1 = "Test1";
    const char *c1 = test1.c_str();
    const auto str_size = test1.size();
    fsmanager::writeFile(temp_path / "root/d/test1.txt", c1, str_size);

    // wirte zip file
//  std::ifstream infile("myzip.zip", std::ifstream::binary);
//  infile.seekg(0, infile.end);
//  long size = infile.tellg();
//  infile.seekg(0);
//
//  // allocate memory for file content
//  char *buffer = new char[size];
//
//  // read content of infile
//  infile.read(buffer, size);
//  std::chrono::time_point<std::chrono::system_clock> start, end;
//  start = std::chrono::system_clock::now();
//  fsmanager::writeFile(temp_path / "root/d/test2.zip", buffer, size);
//  end = std::chrono::system_clock::now();
//
//  std::chrono::duration<double> elapsed_seconds = end - start;
//  std::time_t end_time = std::chrono::system_clock::to_time_t(end);
//
//  std::cout << "finished computation at " << std::ctime(&end_time)
//            << "elapsed time: " << elapsed_seconds.count() << "s\n";
//  infile.close();
}

void test_rename_file() {
    fsmanager::renameFile(temp_path / "root/d/test1.txt", temp_path / "root/d/test_new.txt");
}

void test_copy_file() {
    fsmanager::copyFile(temp_path / "root/d/test_new.txt", temp_path / "root/new_a/new_e");
}

void test_find_file() {
    bool ok = fsmanager::findFile(temp_path / "root/new_a/new_e/test_new.txt");
    if (ok)
        std::cout << temp_path / "root/new_a/new_e/test_new.txt" << " existed\n";
    else
        std::cout << temp_path / "root/new_a/new_e/test_new.txt" << " not exist\n";

}

void test_move_file() {
    fsmanager::moveFile(temp_path / "root/d/test_new.txt", temp_path / "root/new_a/b");
}

void test_delete_file() {
    fsmanager::deleteFile(temp_path / "root/new_a/new_e/test_new.txt");
}

std::pair<char*, u_long> read_buffer(const std::string &path) {
    std::ifstream infile(path, std::ifstream::binary);
    infile.seekg(0, infile.end);
    u_long size = infile.tellg();
    infile.seekg(0);

    // allocate memory for file content
    char *buffer = new char[size];

    // read content of infile
    infile.read(buffer, size);
    return std::make_pair(buffer, size);
}

int main() {
    std::string n1 = "Test1";
    fsmanager::file f1("Test1.txt", (void *) n1.c_str(), n1.size());

    std::string n2 = "Test2";
    fsmanager::file f2("Test2.txt", (void *) n1.c_str(), n1.size());

    auto n3 = read_buffer("/home/mxw/Downloads/cmake-3.17.1.tar.gz"); // Read File
    fsmanager::file f3("Test3.tar.gz", n3.first, n3.second);

    std::vector<fsmanager::file> files = {f1, f2, f3};
    std::vector<std::string> folders = {"a", "b"};

    fsmanager::FileWriter fw(files, folders);
    std::cout << "Return Value: " << fw.write_on_multi_threads();

//  test_create_folder();
//  test_rename_folder();
//  test_copy_folder();
//  test_move_folder();
//
//  test_write_file();
//  test_rename_file();
//  test_copy_file();
//  test_move_file();
//  test_delete_file();
//
//  test_view_folder();
//  test_find_folder();
//  test_find_file();
//
//  fsmanager::deleteFolder(temp_path / "root");
    return 0;
}