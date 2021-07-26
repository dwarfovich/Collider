#include "collider.hpp"
#include "collidees.hpp"

void Collider::collide(Base& base) {}

void Collider::callOtherToVisit(Base& other) {
    other.visit(*this);
}
