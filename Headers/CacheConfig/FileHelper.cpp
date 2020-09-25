#include <fstream>
#include <string>

#ifndef FILE_HELP_H
#define FILE_HELP_H
    class FileHelper
    {
        private:
            std::ifstream input;
            std::string filepath;
            std::streampos currentPos;
            int 
        public:
            FileHelper(const std::string &);
            ~FileHelper();
            void readChunck();
    };
    
    FileHelper::FileHelper(const std::string & path)
        :filepath(path)
    {
        currentPos = 0;
    }
    
    FileHelper::~FileHelper()
    {
    }

    void FileHelper::readChunck(){
        input.open(filepath, std::ios::in);
        input.seekg(currentPos);
        while(currentPos != currentPos + (1000 * ) )
    }
    
#endif