#pragma once
#include "vector"
//could use c++ strings, but I somehow feel like that's cheating when this is meant to be a c course
//this is an adaptation of the Text assignment into c++ classes with some extra sprinklings
class Text
{
public:
    Text();
    Text(char *cString);
    void SetString(char *cString);
    char *GetString();
    void Append(Text *text);
    void AppendToLast(char *cString);
    void AppendLine(char *cString);
    ~Text();
private:
    std::vector<char*> lines;
    //char *array;
    int length;
}