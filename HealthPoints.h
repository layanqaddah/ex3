#ifndef HW3_HEALTHPOINTS_H
#define HW3_HEALTHPOINTS_H

#include<iostream>
class HealthPoints
{
public:
    HealthPoints(int maxHp=100);
    ~HealthPoints()=default;
    HealthPoints(const HealthPoints&)=default;
    HealthPoints& operator=(const HealthPoints&)=default;

    HealthPoints& operator+=(const int healthPoint);
    HealthPoints& operator-=(const int healthPoint);

    class InvalidArgument{};
private:
    int m_maxHp;
    int m_healthPoints;

    friend std::ostream& operator<<(std::ostream&, const HealthPoints& healthPoint);
    friend bool operator==(const HealthPoints& healthPoint1,const HealthPoints& healthPoint2);
    friend bool operator<(const HealthPoints& healthPoint1,const HealthPoints& healthPoint2);
};


HealthPoints operator+(const int healthPoint1, const HealthPoints& healthPoints2);
HealthPoints operator+(const HealthPoints& healthPoint1, const int healthPoints2);
//HealthPoints operator-(const int healthPoint1, const HealthPoints& healthPoints2);
HealthPoints operator-(const HealthPoints& healthPoint1, const int healthPoints2);
bool operator!=(const HealthPoints& healthPoint1,const HealthPoints& healthPoint2);
bool operator<=(const HealthPoints& healthPoint1,const HealthPoints& healthPoint2);
bool operator>(const HealthPoints& healthPoint1,const HealthPoints& healthPoint2);
bool operator>=(const HealthPoints& healthPoint1,const HealthPoints& healthPoint2);

#endif HW3_HEALTHPOINTS_H