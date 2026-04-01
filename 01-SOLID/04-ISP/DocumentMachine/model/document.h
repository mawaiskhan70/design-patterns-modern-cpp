#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <string>

using namespace std;
class Document
{
public:
    string m_name;
    string m_content;
    Document(const string& name, const string& content);
};

#endif // DOCUMENT_H
