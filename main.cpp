#include <iostream>
#include <fstream>
#include <string>

void Getline(std::ifstream& file, std::string& line, char delimiter) {
    char sym;
    line = "";
    while (file.get(sym) and sym != delimiter) {
        line += sym;
    }
}

void ShowError(const std::string& message) {
    std::cerr << message << '\n';
    exit(EXIT_FAILURE);
}

long long CountLinesInFile(const std::string& kFileName, char delimiter) {
    std::ifstream file(kFileName);
    if (!file) {
        ShowError("An error has occured.");
    }
    long long lineCount = 0;
    std::string line;
    while (getline(file, line, delimiter)) {
        lineCount++;
    }
    file.close();
    return lineCount;
}

void Print(const std::string& kFileName, int lines_print, bool is_tail, char delimiter) {
    std::ifstream file(kFileName);
    std::string line;
    long long lines_in_file = CountLinesInFile(kFileName, delimiter);
    long long count = 0;
    if (!file) {
        ShowError("An error has occured.");
    }
    if (CountLinesInFile(kFileName, delimiter) < lines_print) {
        lines_print = -1;
    }
    if (!is_tail) {
        if (lines_print == -1) {
            while (count < lines_in_file) {
                Getline(file, line, delimiter);
                std::cout << line << '\n';
                count++;
            }
        }
        if (lines_print > 0) {
            while (count < lines_print) {
                Getline(file,line,delimiter);
                std::cout << line << '\n';
                count++;
            }
        }
    }
    if (is_tail) {
        if (lines_print == -1) {
            while (count < lines_in_file) {
                Getline(file, line, delimiter);
                std::cout << line << '\n';
                count++;
            }
        }
        if (lines_print > 0) {
            int flag = 0;
            while (count < lines_print) {
                Getline(file, line, delimiter);
                flag++;
                if (flag > lines_in_file - lines_print) {
                    std::cout << line << '\n';
                    count++;
                }
            }
        }
    }
}

int main(int argc, char* argv[]) {
    std::string filename;
    int lines_print = -1;
    bool is_tail = false;
    char delimiter = '\n';
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "-l" or arg == "--lines=") {
            if (i + 1 < argc) {
                lines_print = std::atoi(argv[i + 1]);
                ++i;
            }
        }
        if (arg == "-t" or arg == "--tail") {
            is_tail = true;
        }
        if (arg == "-d" or arg == "--delimiter") {
            if (i + 1 < argc) {
                delimiter = argv[i + 1][0];
                ++i;
            }
        } else {
            filename = arg;
        }
    }
    if (filename.empty()) {
        ShowError("File name is not specified.");
    }
    Print(filename, lines_print, is_tail, delimiter);
    return 0;
}
