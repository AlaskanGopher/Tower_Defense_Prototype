// Assets.cpp

#include "Assets.hpp"

#include <string>

#include "whereami.h"

std::string get_dirname(std::string path) {
	int last_slash = path.rfind('/');
#ifdef _WIN32
	int last_backslash = path.rfind('\\');
	if (last_backslash > last_slash) {
		last_slash = last_backslash;
	}
#endif
	if (last_slash != std::string::npos) {
		return path.substr(0, last_slash);
	}
	return "";
}

std::string get_exe_path() {
	int len = wai_getExecutablePath(nullptr, 0, nullptr);
	char *buf = new char[len + 1];
	wai_getExecutablePath(buf, len, nullptr);
	buf[len] = '\0';
	std::string path = buf;
	delete[] buf;
	return path;
}

std::string get_assets_path() {
	return get_dirname(get_exe_path()) + "/assets";
}
