//
// Created by cysiu on 17.09.2019.
//

#ifndef LOGLIB_LOGLIBFILES_H
#define LOGLIB_LOGLIBFILES_H

#include <iostream>
#include <string>
#include <experimental/filesystem>
#include <fstream>

using namespace std;
namespace fs = experimental::filesystem;

class LogLibFiles{
private:
    fs::path logDirPath = "";
    string fileName = "";
    string fileExtension = "";
    size_t maxFileSize = 1024 * 1024;
    bool overrideToBigFile = false;
    unsigned short maxLogFiles = 0;
    ofstream logFileStream;

    string getFileNameWithExtension();
    string getPathAndName();
    bool createCopyOldLogFiles();

    /**
     * @brief Checking and trying reopen file if is closed
     * @return
     */
    bool checkFileOpen();

public:
    LogLibFiles();
    ~LogLibFiles();

    /**
     * @brief Setting max allowed size of log file
     * @param maxFileSize size of file in Bytes
     */
    void setMaxFileSize(size_t maxFileSize);

    /**
     * @brief Setting path to dir, where log is keeped
     * @param logDirPath path to dir for logs absolute or relatives
     */
    void setLogDirPath(string logDirPath);

    /**
     * @brief Setting log file name
     * @param fileName name of log file
     */
    void setLogFileName(const string fileName);

    /**
     * @brief Creating copies of old log files and delete last if is too much
     * @param maxOfCopies number of copies
     */
    void setAmountOldLogFiles(unsigned short maxOfCopies);

    /**
     * @brief Setting behaviour when file is too big.
     * @param override true - is removing begin of file; false - creating new file (previous is name like old files)
     */
    void setOverSizeFileBehaviour(bool override);

    /**
     * @brief Initialize and prepare vars (like open fstream).
     */
     void initLogging();

     /**
      * @brief write text to file
      * @param text text to write in file
      */
     void writeLine(string text);
};

#endif //LOGLIB_LOGLIBFILES_H
