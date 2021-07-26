#ifndef COLLIDEES_H
#define COLLIDEES_H

#include "collider.hpp"

#define ALLOW_COLLIDER_VISIT                                        \
    virtual void visit(Collider& c) override { c.collide(*this); }; \
    virtual void visit(Collider& c, Base& rhs) override { c.collide(*this, rhs); };

struct Base
{
    virtual void visit(Collider& c)              = 0;
    virtual void visit(Collider& c, Base& other) = 0;
};

struct A : Base
{
    ALLOW_COLLIDER_VISIT;
};

struct B : Base
{
    ALLOW_COLLIDER_VISIT;
};

struct C : Base
{
    ALLOW_COLLIDER_VISIT;
};
#endif // COLLIDEES_H
