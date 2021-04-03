//
// Created by cysiu on 17.09.2019.
//

#include "../include/LogLibFiles.h"

LogLibFiles::LogLibFiles() {}

void LogLibFiles::setMaxFileSize(size_t maxFileSize) {
    this->maxFileSize = maxFileSize;
}

string LogLibFiles::getFileNameWithExtension(){
    return fileName + fileExtension;
}

string LogLibFiles::getPathAndName(){
    return logDirPath.string() + fileName + fileExtension;
}

void LogLibFiles::setLogDirPath(string logDirPath) {
    if (logDirPath.find('\\') == string::npos) {
        if (logDirPath.size() != 0) {
            //Passed absolute path?
            if (!(logDirPath[0] == '/' || (logDirPath[1] == ':' && logDirPath[2] == '/'))) {
                logDirPath = fs::current_path().string() + '/' + logDirPath;
            }
            //Checking last sign is /
            if (logDirPath[logDirPath.size() - 1] == '/')
                this->logDirPath = logDirPath;
            else {
                this->logDirPath += "/";
            }
        } else {
            this->logDirPath = fs::current_path().string() + '/';
        }
    } else {
        throw "Unexcepted \\ in path";
    }
}

void LogLibFiles::setLogFileName(const string fileName){
    if (fileName.find('\\') == string::npos && fileName.find('/') == string::npos) {

        bool extension = true;
        for(int i = fileName.size() - 1; i >= 0 ; i--){
            if(extension){
                if(fileName[i] == '.') {
                    extension = false;
                }
                fileExtension = fileName[i] + fileExtension;
            } else {
                this->fileName = fileName[i] + this->fileName;
            }
        }
        if(extension){
            this->fileName = fileExtension;
            fileExtension = "";
        }
    } else {
        throw "Unexcepted \\ or / in filename";
    }
}

void LogLibFiles::setAmountOldLogFiles(unsigned short maxOfCopies){
    maxLogFiles = maxOfCopies;
}

bool LogLibFiles::createCopyOldLogFiles(){
    fs::path pathDir = logDirPath;

    if (fs::exists(pathDir) && fs::is_directory(pathDir)) {
        struct fileInDir {
            string name;
            string extension;
            string oldNumber;
        } readedFile;
        //string fname, fext, oldnum;
        //Name, extension, old number
        vector<fileInDir> dirLogFileList;

        //Getting all files of log
        for (auto &entry : fs::directory_iterator(pathDir)) {
            readedFile.name = entry.path().stem().string();
            readedFile.extension = entry.path().extension().string();
            readedFile.oldNumber = "";

            //Checking that name is correct
            if (fileName.compare(0, fileName.size(), readedFile.name, 0, fileName.size()) == 0 &&
                fileExtension.compare(readedFile.extension) == 0) {
                if (this->getFileNameWithExtension().size() ==
                    readedFile.name.size() + readedFile.extension.size()) {
                    dirLogFileList.push_back(readedFile);
                } else if (fileName.size() + 5 <= readedFile.name.size()) {
                    if (readedFile.name.compare(fileName.size(), 4, ".old") == 0) {
                        bool flgCorrect = true;
                        for (int i = fileName.size() + 4; i < readedFile.name.size(); i++) {
                            if (!(readedFile.name[i] >= '0' && readedFile.name[i] <= '9'))
                                flgCorrect = false;
                            else
                                readedFile.oldNumber = readedFile.oldNumber + readedFile.name[i];
                        }
                        if (flgCorrect) {
                            dirLogFileList.push_back(readedFile);
                        }
                    }
                }
            }
        }

        if(dirLogFileList.size() > 0) {
            //Ordering
            int it = 0;

            //Check existing no old file and place it on the first position
            if (dirLogFileList[0].oldNumber != "") {
                for (int i = 1; i < dirLogFileList.size(); i++) {
                    if (dirLogFileList[i].oldNumber == "") {
                        swap(dirLogFileList[0], dirLogFileList[i]);
                        it = 1;
                        break;
                    }
                }
            }

            //Ordering rest
            while (it < dirLogFileList.size() - 1) {
                for (int itj = it + 1; itj < dirLogFileList.size(); itj++) {
                    if (dirLogFileList[it].oldNumber > dirLogFileList[itj].oldNumber)
                        swap(dirLogFileList[it], dirLogFileList[itj]);
                }
                it++;
            }

            //Deleting old file
            if (dirLogFileList.size() > maxLogFiles) {
                for (int i = maxLogFiles; i < dirLogFileList.size(); i++) {
                    fs::remove(logDirPath.string() + dirLogFileList[i].name + dirLogFileList[i].extension);
                }
            }

            //Renaming files
            if (dirLogFileList[0].oldNumber == "") {
                for (int i = ((dirLogFileList.size() > maxLogFiles) ? maxLogFiles : dirLogFileList.size()) - 1;
                     i >= 0; i--) {
                    fs::rename(logDirPath.string() + dirLogFileList[i].name + dirLogFileList[i].extension,
                               logDirPath.string() + fileName + ".old" + to_string(i) + fileExtension);
                }
            }
        }
        return true;
    } else {
        return false;
        throw "Path no exist or not is directory";
    }
}

void LogLibFiles::setOverSizeFileBehaviour(bool override){
    overrideToBigFile = override;
}

void LogLibFiles::initLogging(){
    if(fileName == "" || logDirPath == ""){
        cout <<"Throwing";
        throw "Not set filename or path";

    } else {
        if(additiveOldFile){
            logFileStream.open(this->getPathAndName(), fstream::out | fstream::app);
        } else
        if(this->createCopyOldLogFiles()) {
            logFileStream.open(this->getPathAndName(), fstream::out);
        }
    }
}

bool LogLibFiles::checkFileOpen(){
    if(logFileStream.is_open() && fs::exists(this->getPathAndName()))
        return true;
    else {
        logFileStream.open(this->getPathAndName(), fstream::out | fstream::app);
        return logFileStream.is_open();
    }
}

void LogLibFiles::writeLine(string text){
    if(this->checkFileOpen()){
        logFileStream<<text <<endl;
    }
}

LogLibFiles::~LogLibFiles() {
    logFileStream.close();
}

void LogLibFiles::setAdditiveOldFiles(bool additiveOldFiles) {
    additiveOldFile = additiveOldFiles;
}
