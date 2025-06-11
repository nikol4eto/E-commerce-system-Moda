#pragma once
#include "Config.h"
void replaceLineInFile(const String filename, int targetLine, const String newLine) {
    ifstream inputFile(filename.data);
    ofstream tempFile("temp.txt");

    if (!inputFile || !tempFile) {
        cout << "Error opening file.\n";
        return;
    }

    char buffer[1024];
    int currentLine = 1;

    while (inputFile.getline(buffer, sizeof(buffer))) {
        if (currentLine == targetLine) {
            tempFile.write(newLine.data, strlen(newLine.data));
            tempFile.put('\n');
        }
        else {
            tempFile.write(buffer, strlen(buffer));
            tempFile.put('\n');
        }
        currentLine++;
    }

    // If the target line was beyond EOF, pad with empty lines
    while (currentLine <= targetLine) {
        if (currentLine == targetLine) {
            tempFile.write(newLine.data, strlen(newLine.data));
        }
        tempFile.put('\n');
        currentLine++;
    }

    inputFile.close();
    tempFile.close();

    remove(filename.data);
    rename("temp.txt", filename.data);
}

void deleteLineFromFile(const String filename, int targetLine) {
    ifstream inputFile(filename.data);
    ofstream tempFile("temp.txt");

    if (!inputFile || !tempFile) {
        cout << "Error opening file.\n";
        return;
    }

    char buffer[1024];
    int currentLine = 1;

    while (inputFile.getline(buffer, sizeof(buffer))) {
        if (currentLine != targetLine) {
            tempFile.write(buffer, strlen(buffer));
            tempFile.put('\n');
        }
        currentLine++;
    }

    inputFile.close();
    tempFile.close();

    // Replace the original file
    remove(filename.data);
    rename("temp.txt", filename.data);
}