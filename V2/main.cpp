#include <iostream>

struct A;
struct B;
struct C;

void collide(A const& , A const& ) { std::cout << "(A, A)\n"; }
void collide(B const& , B const& ) { std::cout << "(B, B)\n"; }
void collide(C const& , C const& ) { std::cout << "(C, C)\n"; }
void collide(A const& , B const& ) { std::cout << "(A, B)\n"; }
void collide(B const& , A const& ) { std::cout << "(B, A)\n"; }
void collide(A const& , C const& ) { std::cout << "(A, C)\n"; }
void collide(C const& , A const& ) { std::cout << "(C, A)\n"; }
void collide(C const& , B const& ) { std::cout << "(C, B)\n"; }
void collide(B const& , C const& ) { std::cout << "(B, C)\n"; }

struct CollisionDispatcherBase
{
    virtual void collide(A const& other) const = 0;
    virtual void collide(B const& other) const = 0;
    virtual void collide(C const& other) const = 0;
};

template<class T>
struct CollisionDispatcher : CollisionDispatcherBase
{
    CollisionDispatcher(T const& t): t(t) { }

    T const& t;

    void collide(A const& other) const override { ::collide(t, other); };
    void collide(B const& other) const override { ::collide(t, other); };
    void collide(C const& other) const override { ::collide(t, other); };
};

struct Shape
{
    virtual ~Shape() {}

    virtual void visit(Shape const& other) const = 0;
    virtual void visit(CollisionDispatcherBase const& c) const = 0;
};

struct A : Shape
{
    void visit(Shape const& other) const override { auto c = CollisionDispatcher<A>{ *this }; other.visit(c); }
    void visit(CollisionDispatcherBase const& c) const override { c.collide(*this); }
};

struct B : Shape
{
    void visit(Shape const& other) const override { auto c = CollisionDispatcher<B>{ *this }; other.visit(c); }
    void visit(CollisionDispatcherBase const& c) const override { c.collide(*this); }
};

struct C : Shape
{
    void visit(Shape const& other) const override { auto c = CollisionDispatcher<C>{ *this }; other.visit(c); }
    void visit(CollisionDispatcherBase const& c) const override { c.collide(*this); }
};

#include <vector>
#include <memory>

int main()
{
    auto colliders = std::vector<std::unique_ptr<Shape>>();
    colliders.push_back(std::make_unique<A>());
    colliders.push_back(std::make_unique<B>());
    colliders.push_back(std::make_unique<C>());

    for (auto i = std::size_t{ 0 }; i != colliders.size() - 1; ++i)
        for (auto j = i + 1; j != colliders.size(); ++j)
            colliders[i]->visit(*colliders[j]);
}
