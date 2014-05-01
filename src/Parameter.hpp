#pragma once

#include <string>

namespace algo_diff
{

class Parameter
{
public:
    Parameter();
    Parameter(const char *name);
    Parameter(const std::string& name);
    bool operator<(const Parameter&) const;
    bool operator==(const Parameter&) const;
    bool operator!=(const Parameter&) const;
private:
    std::string m_name;
};

} // namespace algo_diff

