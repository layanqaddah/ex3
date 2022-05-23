#include "HealthPoints.h"
#include <iostream>

HealthPoints::HealthPoints(int maxHp): m_maxHp(maxHp),m_healthPoints(maxHp)
{
    if(m_healthPoints<=0)
    {
        throw HealthPoints::InvalidArgument();
    }
}



HealthPoints operator+(const int healthPoints1, const HealthPoints& healthPoints2)
{
    HealthPoints newHp = healthPoints2;
    newHp += healthPoints1;
    return newHp;
}


HealthPoints operator+(const HealthPoints& healthPoints1, const int healthPoints2)
{
    HealthPoints newHp = healthPoints1;
    newHp += healthPoints2;
    return newHp;
}

//////////////////////////////////////////////////////////////////////////////////////////////////
/*HealthPoints operator-(const int healthPoints1, const HealthPoints& healthPoints2)
{
    HealthPoints newHp = healthPoints2;
    newHp -= healthPoints1;
    return newHp;
}*/


HealthPoints operator-(const HealthPoints& healthPoints1, const int healthPoints2)
{
    return healthPoints1 + (-healthPoints2);
}


HealthPoints& HealthPoints::operator+=(const int healthPoint)
{
    m_healthPoints += healthPoint;
    m_healthPoints = (m_healthPoints>m_maxHp)? m_maxHp:m_healthPoints;
    m_healthPoints = (m_healthPoints<0)? 0:m_healthPoints;
    return *this;
}

HealthPoints& HealthPoints::operator-=(const int healthPoint)
{
    return *this+=-healthPoint;
}


std::ostream& operator<<(std::ostream& os, const HealthPoints& healthPoint)
{
    os << healthPoint.m_healthPoints << "(" << healthPoint.m_maxHp << ")";
    return os;
}



bool operator==(const HealthPoints& healthPoint1,const HealthPoints& healthPoint2)
{
    return (healthPoint1.m_healthPoints==healthPoint2.m_healthPoints);
}
bool operator!=(const HealthPoints& healthPoint1,const HealthPoints& healthPoint2)
{
    return !(healthPoint1==healthPoint2);
}
bool operator<(const HealthPoints& healthPoint1,const HealthPoints& healthPoint2)
{
    return (healthPoint1.m_healthPoints<healthPoint2.m_healthPoints);
}
bool operator>(const HealthPoints& healthPoint1,const HealthPoints& healthPoint2)
{
    return (healthPoint2<healthPoint1);
}
bool operator<=(const HealthPoints& healthPoint1,const HealthPoints& healthPoint2)
{
    return !(healthPoint1>healthPoint2);
}
bool operator>=(const HealthPoints& healthPoint1,const HealthPoints& healthPoint2)
{
    return healthPoint2<=healthPoint1;
}



