#include "rdb.h"

bool integerAttribute ::operator==(const Attr &right)
{
    const integerAttribute *rightInt = dynamic_cast<const integerAttribute *>(&right);
    if (rightInt != nullptr)
    {
        return this->value == rightInt->value;
    }
    return false;
}
bool integerAttribute ::operator!=(const Attr &right)
{
    return !(*this == right);
}
bool integerAttribute ::operator<(const Attr &right)
{
    const integerAttribute *rightInt = dynamic_cast<const integerAttribute *>(&right);
    if (rightInt != nullptr)
    {
        return this->value < rightInt->value;
    }
    return false;
}
bool integerAttribute ::operator<=(const Attr &right)
{
    return (*this < right || *this == right);
}
bool integerAttribute ::operator>(const Attr &right)
{
    const integerAttribute *rightInt = dynamic_cast<const integerAttribute *>(&right);
    if (rightInt != nullptr)
    {
        return this->value > rightInt->value;
    }
    return false;
}
bool integerAttribute ::operator>=(const Attr &right)
{
    return (*this > right || *this == right);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool floatAttribute ::operator==(const Attr &right)
{
    const floatAttribute *rightInt = dynamic_cast<const floatAttribute *>(&right);
    if (rightInt != nullptr)
    {
        return this->value == rightInt->value;
    }
    return false;
}
bool floatAttribute ::operator!=(const Attr &right)
{
    return !(*this == right);
}
bool floatAttribute ::operator<(const Attr &right)
{
    const floatAttribute *rightInt = dynamic_cast<const floatAttribute *>(&right);
    if (rightInt != nullptr)
    {
        return this->value < rightInt->value;
    }
    return false;
}
bool floatAttribute ::operator<=(const Attr &right)
{
    return (*this < right || *this == right);
}
bool floatAttribute ::operator>(const Attr &right)
{
    const floatAttribute *rightInt = dynamic_cast<const floatAttribute *>(&right);
    if (rightInt != nullptr)
    {
        return this->value > rightInt->value;
    }
    return false;
}
bool floatAttribute ::operator>=(const Attr &right)
{
    return (*this > right || *this == right);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool stringAttribute ::operator==(const Attr &right)
{
    const stringAttribute *rightStr = dynamic_cast<const stringAttribute *>(&right);
    if (rightStr != nullptr)
    {
        return this->value == rightStr->value;
    }
    return false;
}

bool stringAttribute ::operator!=(const Attr &right)
{
    const stringAttribute *rightStr = dynamic_cast<const stringAttribute *>(&right);
    if (rightStr != nullptr)
    {
        return this->value != rightStr->value;
    }
    return false;
}

bool stringAttribute ::operator<(const Attr &right)
{
    const stringAttribute *rightStr = dynamic_cast<const stringAttribute *>(&right);
    if (rightStr != nullptr)
    {
        return this->value < rightStr->value;
    }
    return false;
}

bool stringAttribute ::operator<=(const Attr &right)
{
    return (*this < right || *this == right);
}

bool stringAttribute ::operator>(const Attr &right)
{
    const stringAttribute *rightStr = dynamic_cast<const stringAttribute *>(&right);
    if (rightStr != nullptr)
    {
        return this->value > rightStr->value;
    }
    return false;
}

bool stringAttribute ::operator>=(const Attr &right)
{
    return (*this > right || *this == right);
}