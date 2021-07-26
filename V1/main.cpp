#include <iostream>

struct A;
struct B;
struct C;

void collide(A const&, A const&)
{
    std::cout << "(A, A)\n";
}
void collide(B const&, B const&)
{
    std::cout << "(B, B)\n";
}
void collide(C const&, C const&)
{
    std::cout << "(C, C)\n";
}
void collide(A const&, B const&)
{
    std::cout << "(A, B)\n";
}
void collide(B const&, A const&)
{
    std::cout << "(B, A)\n";
}
void collide(A const&, C const&)
{
    std::cout << "(A, C)\n";
}
void collide(C const&, A const&)
{
    std::cout << "(C, A)\n";
}
void collide(C const&, B const&)
{
    std::cout << "(C, B)\n";
}
void collide(B const&, C const&)
{
    std::cout << "(B, C)\n";
}

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
    CollisionDispatcher(T& t, Collider& c) : t { t }, c_ { c } {}

    T&              t;
    const Collider& c_;

    void collide(A& other) const override { c_.collide(t, other); }
    void collide(B& other) const override { c_.collide(t, other); }
    void collide(C& other) const override { c_.collide(t, other); }
};

struct Base
{
    virtual ~Base() {}

    virtual void visit(Base& other, Collider& c)         = 0;
    virtual void visit(CollisionDispatcherBase const& c) = 0;
};

struct A : Base
{
    void visit(Base& other, Collider& c) override
    {
        auto d = CollisionDispatcher<A> { *this, c };
        other.visit(d);
    }
    void visit(CollisionDispatcherBase const& c) override { c.collide(*this); }
};

struct B : Base
{
    void visit(Base& other, Collider& c) override
    {
        auto d = CollisionDispatcher<B> { *this, c };
        other.visit(d);
    }
    void visit(CollisionDispatcherBase const& c) override { c.collide(*this); }
};

struct C : Base
{
    void visit(Base& other, Collider& c) override
    {
        auto d = CollisionDispatcher<C> { *this, c };
        other.visit(d);
    }
    void visit(CollisionDispatcherBase const& c) override { c.collide(*this); }
};

#include <vector>
#include <memory>

int main()
{
    Collider c;
    auto     a = std::make_unique<A>();
    auto     b = std::make_unique<B>();
    a->visit(*b, c);
    //    auto     collidees = std::vector<std::unique_ptr<Base>>();
    //    collidees.push_back(std::make_unique<A>());
    //    collidees.push_back(std::make_unique<B>());
    //    collidees.push_back(std::make_unique<C>());

    //    for (auto i = std::size_t { 0 }; i != collidees.size() - 1; ++i)
    //        for (auto j = i + 1; j != collidees.size(); ++j)
    //            collidees[i]->visit(*collidees[j], c);
}

void Collider::collide(A& a, A& a2) const
{}

void Collider::collide(A& a, B& b) const
{}

void Collider::collide(A& a, C& c) const
{}

void Collider::collide(C& a, A& c) const
{}

void Collider::collide(B& b, C& c) const
{}

void Collider::collide(C& b, B& c) const
{}

void Collider::collide(B& b, A& c) const
{}

void Collider::collide(B& b, B& c) const
{}

void Collider::collide(C& b, C& c) const
{}
