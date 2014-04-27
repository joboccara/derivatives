#pragma once

#include <string>

class Parameter
{
public:
    Parameter();
    Parameter(std::string name);
    bool operator<(const Parameter&) const;
    bool operator==(const Parameter&) const;
    bool operator!=(const Parameter&) const;
private:
    std::string m_name;
};


