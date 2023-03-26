#include "vector3.hpp"

#include <Arduino.h>


double Vector3::getDistance(Vector3 from, Vector3 to)
{
    double dx = from.x - to.x;
    double dy = from.y - to.y;
    double dz = from.z - to.z;

    return sqrt(dx * dx + dy * dy + dz * dz);
}

Vector3 Vector3::operator+(const Vector3 &b) const
{
    return {x + b.x, y + b.y, z + b.z};
}