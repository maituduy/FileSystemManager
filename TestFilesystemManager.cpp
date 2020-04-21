#include <iostream>
#include <fstream>
#include "FilesystemManager.h"

#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;
fs::path temp_path = fs::temp_directory_path();

void test_create_folder() {
    fsmanager::createFolder(temp_path/"root/a/b/c");
    fsmanager::createFolder(temp_path/"root/d/e");
}

void test_rename_folder() {
    fsmanager::renameFolder(temp_path/"root/a", temp_path/"root/new_a");
    fsmanager::renameFolder(temp_path/"root/d/e", temp_path/"root/d/new_e");
}

void test_copy_folder() {
    fsmanager::copyFolder(temp_path/"root/new_a", temp_path/"root/copy_a");
}

void test_move_folder() {
    fsmanager::moveFolder(temp_path/"root/d/new_e", temp_path/"root/new_a");
}

void test_find_folder() {
    std::cout << fsmanager::findFolder(temp_path/"root/copy_a/b/c") << std::endl;
    std::cout << fsmanager::findFolder(temp_path/"not_exist") << std::endl;
}

void test_view_folder() {
    fsmanager::viewFolder(temp_path/"root", fsmanager::view_option::all);
}

void test_write_file() {
    std::string test1 = "Test1";
    const char* c1 = test1.c_str();
    const auto str_size = test1.size();
    fsmanager::writeFile(temp_path/"root/d/test1.txt", c1, str_size);

    // wirte zip file
    std::ifstream infile ("3/tk.pdf",std::ifstream::binary);
    infile.seekg (0, infile.end);
    long size = infile.tellg();
    infile.seekg (0);

    // allocate memory for file content
    char* buffer = new char[size];

    // read content of infile
    infile.read (buffer,size);
}

int main() {

    test_create_folder();
    test_rename_folder();
    test_copy_folder();
    test_move_folder();
    test_write_file();

    test_view_folder();
    test_find_folder();
    fsmanager::deleteFolder(temp_path/"root");
    return 0;
}