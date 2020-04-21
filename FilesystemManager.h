#ifndef FILESYSTEM_FILESYSTEMMANAGER_H
#define FILESYSTEM_FILESYSTEMMANAGER_H

#include <string>

namespace fsmanager {
	enum class view_option {
		df, all
	};

	void viewFolder(std::string path, view_option option = view_option::df);

	bool createFolder(std::string path);

	bool renameFolder(std::string oldname, std::string newname);

	bool copyFolder(std::string path_from, std::string path_to);

	bool findFolder(std::string path);

	bool moveFolder(std::string path_from, std::string path_to);

	bool deleteFolder(std::string path);

	bool writeFile(std::string path, const void* buf, __int64_t buflen);

	bool renameFile(std::string oldname, std::string newname);

	bool copyFile(std::string path_from, std::string path_to);

	bool findFile(std::string path);

	bool moveFile(std::string path_from, std::string path_to);

	bool deleteFile(std::string path);
}

#endif //FILESYSTEM_FILESYSTEMMANAGER_H
