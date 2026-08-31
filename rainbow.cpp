#include<vector>
#include<string>
#include<fstream>
#include<iostream>
#include<cmath>
#include<unordered_map>
#include<cstring>
#include<unordered_set>
#define EXIT_CODE_INSUFFICIENT_ARGS   1
#define EXIT_CODE_INVALID_ARGS        2
#define EXIT_CODE_UNKNOWN             128
#define CL_MODES__MODE_TOKS           0
#define CL_MODES__MODE_CHARS          1
#define CL_MODES__MODE_WORDS          2
#define CL_MODES__MODE_SCHARS         3
#define CL_MODES__MODE_FILES_INDIV    0
#define CL_MODES__MODE_FILES_COLL     1
#define CL_MODES__MODE_CASE_AWARE     0
#define CL_MODES__MODE_CASE_AGNOSTIC  1
#define CL_MODES__MODE_KEEP_CONTENTS  0
#define CL_MODES__MODE_CLEAR_CONTENTS 1
char makeLower(const char& ch){return char(int(ch) + (32*(int(ch) >= 65 && int(ch) <= 90)));}
std::string makeLower(const std::string& str){
    std::string res;
    for(const char& ch: str){
        res += makeLower(ch);
    }
    return res;
}
void copyFileToString(const std::string& filename, std::string& reserved, const bool clear){
    std::string buffer;
    if(clear == true){
    reserved = "";
    }
    std::ifstream opened(filename);
    while(getline(opened, buffer)){
        reserved += buffer + " ";
    }
    reserved.pop_back();
    opened.close();
}
void writeData(const std::string& filename, const std::unordered_map<std::string, size_t>& data){
    std::ofstream opened(filename, std::ios::app);
    size_t ctr = 0;
    for(const auto& x: data){
        opened << x.first << " " << x.second << "\n";
    }
    opened.close();
}
void writeData(const std::string& filename, const std::string& header, const std::unordered_map<std::string, size_t>& data){
    std::ofstream opened(filename, std::ios::app);
    size_t ctr = 0;
    opened << header << "\n";
    for(const auto& x: data){
        opened << x.first << " " << x.second << "\n";
    }
    opened.close();
}
std::string getFirstChars(const char* str, const size_t& num){
    std::string res = "";
    for(size_t i=0; i<num; i++){
        res += str[i];
    }
    return res;
};
std::string chopChars(const char* str, const size_t& place){
    std::string res = "";
    for(size_t i=place; i<strlen(str); i++){
        res += str[i];
    }
    return res;
};
std::vector<std::string> __attribute__((always_inline)) inline tokenizeString(const std::string& str,const std::unordered_set<char> goal){
    std::vector<std::string> tokenized; std::string curString = ""; std::string str_ = str + char(0); size_t ctr = 0;
    while(ctr < str.size()){
        curString = curString + str[ctr];
        if(goal.contains(str_[ctr+1]) or str_[ctr+1] == char(0)){
            while(goal.contains(str_[ctr+1])){ctr = ctr + 1;}
            tokenized.push_back(curString); curString = "";
            }
            ctr = ctr + 1;
    }
    return tokenized;
}
std::vector<std::string> __attribute__((always_inline)) inline extractLines(const std::string& filename){
    std::vector<std::string> res;
    std::string buffer;
    std::ifstream opened(filename);
    while(getline(opened, buffer)){
        res.push_back(buffer);
    }
    return res;
}
static int safeAtoi(const std::string& str){
    return std::atoi(str.c_str());
}
static int safeAtoi(const char* str){
    return std::atoi(str);
}
int main(int argc, char** argv){
    std::unordered_set<char> customTracked = {};
    std::unordered_set<char> tokenizeChars = {};
    std::unordered_map<std::string, size_t> data;
    std::vector<std::string> tokenized;
    bool writeSeparately;
    size_t fileCountOutput = 0;
    size_t fileCountInput  = 0;
    std::string buffer;
    int arg1 = safeAtoi(argv[1]);
    int arg2 = safeAtoi(argv[2]);
    int arg3 = safeAtoi(argv[3]);
    int arg4 = safeAtoi(argv[4]);
    std::vector<std::string> filenames = {};
    std::string outputFileName;
    std::string fileData;
    std::ios_base::openmode flag = std::ios::app;
    if(arg4 == CL_MODES__MODE_CLEAR_CONTENTS){
        flag = std::ios::trunc;
    }
    if(argc >= 3){
    if(arg2 == CL_MODES__MODE_FILES_INDIV){
        writeSeparately = true;
    } else if (arg2 == CL_MODES__MODE_FILES_COLL){
        writeSeparately = false;
    } else {
        goto failUnknown;
    }
    for(size_t i=1; i<argc; i++){
        if(getFirstChars(argv[i], 6) == "input="){
            fileCountInput += 1;
            filenames.emplace_back(chopChars(argv[i], 6));
        }
        if(getFirstChars(argv[i], 7) == "output="){
            fileCountOutput += 1;
            outputFileName = chopChars(argv[i], 7);
        }
    }
    if(arg1 > 0){
        if(fileCountInput == 0 || fileCountOutput != 1){
            goto failInvalid;
        }
    } else if(arg1 == 0){
        if(fileCountInput == 0){
            goto failInvalid;
        }
    } else {
        goto failUnknown;
    }
    std::ofstream finalOutputFile(outputFileName, flag);
    if(arg1 == CL_MODES__MODE_TOKS){
        std::cout << "What are the characters you want to use to tokenize the file(s)?\n";
        std::cin >> buffer;
        for(size_t i=0; i<buffer.size(); i++){
            if(!(tokenizeChars.contains(buffer.at(i)))){
                 tokenizeChars.insert(buffer.at(i));
            }
        }
        if(writeSeparately == true){
            for(const auto& selectedFilename: filenames){
                data = {};
                copyFileToString(selectedFilename, fileData, true);
                tokenized = tokenizeString(fileData, tokenizeChars);
                if(arg3 == CL_MODES__MODE_CASE_AWARE){
                    for(const auto& x: tokenized){
                        data[x] += 1;
                    }
                } else if(arg3 == CL_MODES__MODE_CASE_AGNOSTIC){
                    for(const auto& x: tokenized){
                        data[makeLower(x)] += 1;
                    }
                }
                writeData(selectedFilename, "Data for " + selectedFilename + ":", data);
            }
            finalOutputFile.close();
            goto success;
        } else if(writeSeparately == false){
            for(const auto& selectedFilename: filenames){
                copyFileToString(selectedFilename, fileData, false);
            }
            tokenized = tokenizeString(fileData, tokenizeChars);
            if(arg3 == CL_MODES__MODE_CASE_AWARE){
                for(const auto& x: tokenized){
                    data[x] += 1;
                }
            } else if(arg3 == CL_MODES__MODE_CASE_AGNOSTIC){
                for(const auto& x: tokenized){
                    data[makeLower(x)] += 1;
                }
            }
            writeData(outputFileName, data);
            finalOutputFile.close();
            goto success;
        }
        } else if (arg1 == CL_MODES__MODE_CHARS) {
            if(writeSeparately == false){
            for(const auto& selectedFilename: filenames){
                copyFileToString(selectedFilename, fileData, false);
            }
            if(arg3 == CL_MODES__MODE_CASE_AWARE){
                for(size_t i=0; i<fileData.size(); i++){
                    data[std::string() + fileData[i]] += 1;
                }
            } else if(arg3 == CL_MODES__MODE_CASE_AGNOSTIC){
                for(size_t i=0; i<fileData.size(); i++){
                    data[std::string() + makeLower(fileData[i])] += 1;
                }
            }
            writeData(outputFileName, data);
            } else if (writeSeparately == true) {
                for(const auto& selectedFilename: filenames){
                data = {};    
                copyFileToString(selectedFilename, fileData, true);
                if(arg3 == CL_MODES__MODE_CASE_AWARE){
                    for(size_t i=0; i<fileData.size(); i++){
                        data[std::string() + fileData[i]] += 1;
                    }
                } else if(arg3 == CL_MODES__MODE_CASE_AGNOSTIC){
                    for(size_t i=0; i<fileData.size(); i++){
                        data[std::string() + makeLower(fileData[i])] += 1;
                    }
                }
                writeData(outputFileName, "Data for " + selectedFilename + ":", data);
                }
                goto success;
            }
        } else if(arg1 == CL_MODES__MODE_WORDS) {
            if(writeSeparately == false){
            for(const auto& selectedFilename: filenames){
                copyFileToString(selectedFilename, fileData, false);
            }
            tokenized = tokenizeString(fileData, {'.', '0', '1', '2', '3', '4', '5', '6','7', '8', '9', ':', ';', '-', '+','/', '*','\"', '@', '#', '$','&', ' ', '!', '?', '<', '>', '{','}', '[', ']', '|', '^'});
            for(size_t i=0; i<tokenized.size(); i++){
                if(arg3 == CL_MODES__MODE_CASE_AWARE){
                    data[tokenized.at(i)] += 1;
                } else if(arg3 == CL_MODES__MODE_CASE_AGNOSTIC){
                    data[makeLower(tokenized.at(i))] += 1;
                }
            }
            writeData(outputFileName, data);
            finalOutputFile.close();
            } else if(writeSeparately == true){
                for(const auto& selectedFilename: filenames){
                    copyFileToString(selectedFilename, fileData, true);
                    data = {};
                    tokenized = tokenizeString(fileData, {'0', '1', '2', '3', '4', '5', '6','7', '8', '9', ':', ';', '-', '+','/', '*','\'','\"', '@', '#', '$','&', ' ', '!', '?', '<', '>', '{','}', '[', ']', '|', '^'});
                    if(arg3 == CL_MODES__MODE_CASE_AWARE){
                        for(const auto& x: tokenized){
                            data[x] += 1;
                        }
                    } else if(arg3 == CL_MODES__MODE_CASE_AGNOSTIC) {
                        for(const auto& x: tokenized){
                            data[makeLower(x)] += 1;
                        }
                    }
                    writeData(outputFileName, "Data for " + selectedFilename + ":", data);
                }
            }
        } else if(arg1 == CL_MODES__MODE_SCHARS) {
            if(writeSeparately == false){
            std::cout << "What are the characters you want to track?\n";
            std::cin >> buffer;
            for(const auto& selectedFilename: filenames){
                copyFileToString(selectedFilename, fileData, false);
            }
            if(arg3 == CL_MODES__MODE_CASE_AWARE){
                for(size_t i=0; i<buffer.size(); i++){
                    if(!(customTracked.contains(buffer.at(i)))){
                        customTracked.insert(buffer.at(i));
                    }
                }
            } else if(arg3 == CL_MODES__MODE_CASE_AGNOSTIC){
                for(size_t i=0; i<buffer.size(); i++){
                    if(!(customTracked.contains(makeLower(buffer.at(i))))){
                        customTracked.insert(makeLower(buffer.at(i)));
                    }
                }
            }
            if(arg3 == CL_MODES__MODE_CASE_AWARE){
                for(size_t i=0; i<fileData.size(); i++){
                    if(customTracked.contains(fileData[i])){
                        data[std::string() + fileData[i]] += 1;
                    }
                }
            } else if(arg3 == CL_MODES__MODE_CASE_AGNOSTIC){
                for(size_t i=0; i<fileData.size(); i++){
                    if(customTracked.contains(makeLower(fileData[i]))){
                        data[std::string() + makeLower(fileData[i])] += 1;
                    }
                } 
            }
            writeData(outputFileName, data);
            finalOutputFile.close();
            goto success;
            } else if(writeSeparately == true) {
                std::cout << "What are the characters you want to track?\n";
                    std::cin >> buffer;
                    if(arg3 == CL_MODES__MODE_CASE_AWARE){
                        for(size_t i=0; i<buffer.size(); i++){
                            if(!(customTracked.contains(buffer.at(i)))){
                                customTracked.insert(buffer.at(i));
                            }
                        }
                    } else if(arg3 == CL_MODES__MODE_CASE_AGNOSTIC){
                        for(size_t i=0; i<buffer.size(); i++){
                            if(!(customTracked.contains(makeLower(buffer.at(i))))){
                                customTracked.insert(makeLower(buffer.at(i)));
                            }
                        }
                    }
                for(const auto& selectedFilename: filenames){
                    data = {};
                    copyFileToString(selectedFilename, fileData, true);
                    if(arg3 == CL_MODES__MODE_CASE_AWARE){
                        for(size_t i=0; i<fileData.size(); i++){
                            if(customTracked.contains(fileData[i])){
                                data[std::string() + fileData[i]] += 1;
                            }
                        }
                    } else if(arg3 == CL_MODES__MODE_CASE_AGNOSTIC){
                        for(size_t i=0; i<fileData.size(); i++){
                            if(customTracked.contains(makeLower(fileData[i]))){
                                data[std::string() + makeLower(fileData[i])] += 1;
                            }
                        }
                    }
                    writeData(outputFileName, "Data for " + selectedFilename + ":", data);
                }
                finalOutputFile.close();
                goto success;
                }
            }else { goto failUnknown; } } else {
        goto failNotEnoughArgs;
    }
    {success:
    return 0;
    }
    {failNotEnoughArgs:
    std::cout << "Too few arguments";
    return EXIT_CODE_INSUFFICIENT_ARGS;}
    {failInvalid:
    std::cout << "Invalid file arguments";
    return EXIT_CODE_INVALID_ARGS;}
    {failUnknown:
    std::cout << "Unknown";
    return EXIT_CODE_UNKNOWN;}
}