#include <iostream>

using namespace std;

struct A;
struct B;
struct C;

struct Collider
{
    void collide(A& a, A& a2) const;
    void collide(A& a, B& b) const;
    void collide(A& a, C& c) const;
    void collide(C& a, A& c) const;
    void collide(B& b, C& c) const;
    void collide(C& b, B& c) const;
    void collide(B& b, A& c) const;
    void collide(B& b, B& c) const;
    void collide(C& b, C& c) const;
};

struct CollisionDispatcherBase
{
    virtual void collide(A& other) const = 0;
    virtual void collide(B& other) const = 0;
    virtual void collide(C& other) const = 0;
};

template<class T>
struct CollisionDispatcher : CollisionDispatcherBase
{
    CollisionDispatcher(T& first, Collider& collider) : first_ { first }, collider_ { collider } {}

    T&              first_;
    const Collider& collider_;

    void collide(A& other) const override { collider_.collide(first_, other); }
    void collide(B& other) const override { collider_.collide(first_, other); }
    void collide(C& other) const override { collider_.collide(first_, other); }
};

struct Base
{
    virtual ~Base() {}

    virtual void collideWith(Base& other, Collider& c)   = 0;
    virtual void accept(const CollisionDispatcherBase& c) = 0;
};

struct A : Base
{
    void collideWith(Base& other, Collider& c) override
    {
        auto d = CollisionDispatcher<A> { *this, c };
        other.accept(d);
    }
    void accept(CollisionDispatcherBase const& c) override { c.collide(*this); }
};

struct B : Base
{
    void collideWith(Base& other, Collider& c) override
    {
        auto d = CollisionDispatcher<B> { *this, c };
        other.accept(d);
    }
    void accept(CollisionDispatcherBase const& c) override { c.collide(*this); }
};

struct C : Base
{
    void collideWith(Base& other, Collider& c) override
    {
        auto d = CollisionDispatcher<C> { *this, c };
        other.accept(d);
    }
    void accept(CollisionDispatcherBase const& c) override { c.collide(*this); }
};

#include <vector>
#include <memory>

int main()
{
    Collider collider;
    auto     a = std::make_unique<A>();
    auto     b = std::make_unique<B>();
    auto     c = std::make_unique<C>();
    a->collideWith(*b, collider);
    a->collideWith(*c, collider);
    b->collideWith(*c, collider);
}

void Collider::collide(A& a, A& a2) const
{}

void Collider::collide(A& a, B& b) const
{
    cout << "(a, b)\n";
}

void Collider::collide(A& a, C& c) const
{
    cout << "(a, c)\n";
}

void Collider::collide(C& a, A& c) const
{}

void Collider::collide(B& b, C& c) const
{
    cout << "(b, c)\n";
}

void Collider::collide(C& b, B& c) const
{}

void Collider::collide(B& b, A& c) const
{}

void Collider::collide(B& b, B& c) const
{}

void Collider::collide(C& b, C& c) const
{}
