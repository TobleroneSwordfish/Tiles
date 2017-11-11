#pragma once
#include "vector"
//could use c++ strings, but I somehow feel like that's cheating when this is meant to be a c course
//this is an adaptation of the Text assignment into c++ classes
class Text
{
public:
    Text();
    Text(char *cString);
    void SetString(char *cString);
    char *GetString();
    void Append(Text *text);
    void Append(char *cString);
    ~Text();
private:
    std::vector<char*> lines;
    //char *array;
    int length;
}