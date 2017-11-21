#include "Text.h"
#include "string.h"

Text::Text()
{
    //array = "";
}

Text::Text(char *cString)
{
    SetString(cString);
}

Text::~Text()
{
    //delete lines;
}

// void Text::SetString(char *cString)
// {
//     length = strlen(cString);
//     delete [] array;
//     array = new char[length];
//     strcpy(array, cString);
// }

void Text::Append(Text *text)
{
    Append(text->GetString());
}
void Text::Append(char *cString)
{
    length = strlen(cString);
    char *temp;
    strcpy(temp, array);
    delete [] array;
    array = new char[length];
    strcpy(array, temp);
    strcat(array, cString);
}

void Text::AppendLine(char *cString)
{
    
}

char *Text::GetString()
{
    return array;
}