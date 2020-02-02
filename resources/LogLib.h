#ifndef DOWNLOADLIBLARY_LOGLIB_H
#define DOWNLOADLIBLARY_LOGLIB_H

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
    bool additiveOldFile = false;
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
     * @brief Setting behaviour when run app. Adding to old file new lines or createnew empty file.
     * @param additiveOldFiles 0 - creating new file; 1 - adding new lines to old file
     */
    void setAdditiveOldFiles(bool additiveOldFiles);

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


class LogLib {
private:
    LogLibFiles lFiles;
    unsigned int level = 3;
    /*
    * 0 - no loging
    * 1 - only errors
    * 2 - log important things with start and shutdown
    * 3 - loging all
    */

    time_t actTime;
    struct tm actTimeStr;

    void addNewLine(string);
    bool blockedSetting = false;
    bool showDate = true;
    bool l1ToConsole = false, l2ToConsole = false, l3ToConsole = false;
public:
    static const unsigned short NO_LOGING = 0, LOG_ERRORS = 1, LOG_WARNINGS = 2, LOG_ALL = 3;

    LogLib();

    /**
     * @brief Set level of logging.
     * @param level level of logging (0 - no logging, 1 - log only errors, 2 - log errors and important things, 3 - log all).
     * Higher level contain lower levels.
     */
    void setLoggingLevel(int);

    /**
     * @brief Add new line to log file.
     * @brief Information on level 1 (errors).
     * @param text Text to add
     */
    void addNewLineL1(string);

    /**
     * @brief Add new line to log file.
     * @brief Information on level 2 (important things)
     * @param text Text to add
     */
    void addNewLineL2(string);

    /**
     * @brief Add new line to log file.
     * @brief Information on level 3 (everything else than on level 1 and 2)
     * @param text Text to add
     */
    void addNewLineL3(string);

    /**
     * @brief Set max size of log file
     * @param maxFileSize max size of file in KB
     */
    void setMaxFileSizeKB(size_t maxFileSize);

    /**
     * @brief Set max size of log file
     * @param maxFileSize max size of file in MB
     */
    void setMaxFileSizeMB(size_t maxFileSize);

    /**
     * @brief Set amount to keep old files
     * @param max_keeped_files (default 5) amount of keeped log files
     */
    void setAmountOldFiles(unsigned short max_keeped_files = 5);

    /**
     * @brief Save path to directory, where log file is keeped
     * @param logPath Path to directoryinitLogging where log was saved
     */
    void setLogDirPath(const string &logDirPath);

    /**
     * @brief Save log file name
     * @param logName name of logfile
     */
    void setLogName(const string &logName);

    /**
     * @brief Setting behaviour when file is too big.
     * @param override true - is removing begin of file; false - creating new file (previous is name like old files)
     */
    void setOverSizeFileBehaviour(bool override);

    /**
     * @brief Setting behaviour when run app. Adding to old file new lines or createnew empty file.
     * @param additiveToOldLog 0 - creating new file; 1 - adding new lines to old file
     */
    void setNewLogBehaviour(bool additiveToOldLog = 0);

    /**
     * @brief Setting flag to write date on begin every line
     * @param showDate true - show date; flase - no date
     */
    void setShowDate(bool showDate);

    /**
     * @brief Initialize to logging.
     * @brief You must run it before start logging and after setting options.
     */
    void initLogging();

    /**
     * @brief Enable/disable writing in console level 1 alert (default disabled)
     * @param l1ToConsole 
     */
    void setL1ToConsole(bool l1ToConsole);

    /**
     * @brief Enable/disable writing in console level 2 alert (default disabled)
     * @param l2ToConsole 
     */
    void setL2ToConsole(bool l2ToConsole);

    /**
     * @brief Enable/disable writing in console level 3 alert (default disabled)
     * @param l3ToConsole 
     */
    void setL3ToConsole(bool l3ToConsole);

    /**
     * @brief Enable/disable writing in console all levels alert (default disabled)
     * @param log 
     */
    void setAllLogToConsole(bool log);
};


#endif //DOWNLOADLIBLARY_LOGLIB_H
