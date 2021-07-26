#ifndef COLLIDER_HPP
#define COLLIDER_HPP


#include <memory>
#include <iostream>

#define ADD_REVERSE_COLLISION(A, B)                    \
    template<>                                         \
    inline void Collider::performCollision(B& b, A& a) \
    {                                                  \
        performCollision(a, b);                        \
    }

#define CALL_COLLIDER_FOR(CLASS) \
    void collide(CLASS& a) { collider.performCollision<T, CLASS>(static_cast<T&>(base), a); }

struct Base;
struct A;
struct B;
struct C;
struct Collider;

struct HelperBase
{
    HelperBase(Base& base_, Collider& collider_) : base { base_ }, collider { collider_ } {}
    virtual ~HelperBase() = default;

    virtual void collide(A& base) = 0;
    virtual void collide(B& base) = 0;
    virtual void collide(C& base) = 0;

    Base&     base;
    Collider& collider;
};

template<typename T>
struct Helper;

struct Collider
{
    void collide(Base& base);

    template<typename T>
    void collide(T& t)
    {
        if (helper) {
            helper->collide(t);
        }
    }

    template<typename T>
    void collide(T& t, Base& other)
    {
        helper = std::make_unique<Helper<T>>(t, *this);
        callOtherToVisit(other);
    }

    void callOtherToVisit(Base& other);

    template<typename T1, typename T2>
    void performCollision(T1& base, T2& rhs)
    {
        std::cout << "No collision handler\n";
    }

    std::unique_ptr<HelperBase> helper;
};

template<typename T>
struct Helper : HelperBase
{
    Helper(T& base, Collider& c) : HelperBase { base, c } {}

    CALL_COLLIDER_FOR(A);
    CALL_COLLIDER_FOR(B);
    CALL_COLLIDER_FOR(C);
};

template<>
inline void Collider::performCollision(A& a, B& b)
{
    std::cout << "Colliding a and b\n";
}
ADD_REVERSE_COLLISION(A, B);

template<>
inline void Collider::performCollision(B& b1, B& b2)
{
    std::cout << "Colliding b1 and b2\n";
}

template<>
inline void Collider::performCollision(A& a, C& c)
{
    std::cout << "Colliding a and c\n";
}
ADD_REVERSE_COLLISION(A, C);

template<>
inline void Collider::performCollision(B& b, C& c)
{
    std::cout << "Colliding b and c\n";
}
ADD_REVERSE_COLLISION(B, C);

#endif // COLLIDER_HPP
