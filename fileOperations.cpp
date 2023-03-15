#include "fileOperations.h"

void writeToLog(string message) {
    ofstream logFile;
    logFile.open("../log.txt", ios::app);
    logFile << message << endl;
    logFile.close();
}
