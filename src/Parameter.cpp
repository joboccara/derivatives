#include "Parameter.hpp"

Parameter::Parameter()
: m_name("")
{
    
}

Parameter::Parameter(std::string name)
: m_name(name)
{
    
}

bool Parameter::operator<(const Parameter& other) const
{
    return m_name < other.m_name;
}

bool Parameter::operator==(const Parameter& other) const
{
    return m_name == other.m_name;
}

bool Parameter::operator!=(const Parameter& other) const
{
    return !(*this == other);
}


