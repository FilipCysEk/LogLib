//
// Created by cysiu on 13.09.2019.
//

#include "../include/LogLib.h"

LogLib::LogLib() {
}

void LogLib::setLoggingLevel(int level) {
    this->level = level;
}

void LogLib::addNewLineL1(string text) {
    if (level >= 1 && level != 0) {
        addNewLine(text);
        if(l1ToConsole)
            cout << text << endl;
    }
}

void LogLib::addNewLineL2(string text) {
    if (level >= 2 && level != 0) {
        addNewLine(text);
        if(l2ToConsole)
            cout << text << endl;
    }
}

void LogLib::addNewLineL3(string text) {
    if (level >= 3 && level != 0){
        addNewLine(text);
        if(l3ToConsole)
            cout << text << endl;
    }
}

void LogLib::addNewLine(string text) {
    if (level > 0) {
        if (blockedSetting) {
            if (showDate) {
                time(&actTime);
                actTimeStr = *localtime(&actTime);
                char temp[25];
                strftime(temp, 25, "[%Y-%m-%d] %H:%M:%S", &actTimeStr);
                //printf("%s\t%s\n", temp, text.c_str());
                lFiles.writeLine((string) temp + "\t" + text);
            } else {
                lFiles.writeLine(text);
            }
        } else
            throw "Not initialized logging function";
    }
}

void LogLib::setMaxFileSizeKB(size_t maxFileSize) {
    if (!blockedSetting) lFiles.setMaxFileSize(maxFileSize * 1024);
}

void LogLib::setMaxFileSizeMB(size_t maxFileSize) {
    if (!blockedSetting) lFiles.setMaxFileSize(maxFileSize * 1024 * 1024);
}

void LogLib::setAmountOldFiles(unsigned short max_keeped_files) {
    if (!blockedSetting) lFiles.setAmountOldLogFiles(max_keeped_files);
}

void LogLib::setLogDirPath(const string &logDirPath) {
    if (!blockedSetting) lFiles.setLogDirPath(logDirPath);
}

void LogLib::setLogName(const string &logName) {
    if (!blockedSetting) lFiles.setLogFileName(logName);
}

void LogLib::setOverSizeFileBehaviour(bool override) {
    lFiles.setOverSizeFileBehaviour(override);
}

void LogLib::setShowDate(bool showDate) {
    this->showDate = showDate;
}

void LogLib::initLogging() {
    blockedSetting = true;
    if (level > 0)
        lFiles.initLogging();
}

void LogLib::setL1ToConsole(bool l1ToConsole) {
    this->l1ToConsole = l1ToConsole;
}

void LogLib::setL2ToConsole(bool l2ToConsole) {
    this->l2ToConsole = l2ToConsole;
}

void LogLib::setL3ToConsole(bool l3ToConsole) {
    this->l3ToConsole = l3ToConsole;
}

void LogLib::setAllLogToConsole(bool log) {
    l1ToConsole = log;
    l2ToConsole = log;
    l3ToConsole = log;
}
