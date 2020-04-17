#ifndef FS_H
#define FS_H

#include<fstream>

using namespace std;

// this namespace is used to house the fileSystem functions needed in the compiler.
// e.g:
//     read_file
//     write_file
namespace fs {

    inline string read_file(string file_name) {
        std::ifstream file(file_name);
        file.seekg(0, std::ios::end);
        size_t size = file.tellg();
        std::string data(size, ' ');
        file.seekg(0);
        file.read(&data[0], size);

        return data;
    }

};

#endif