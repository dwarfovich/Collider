#include <iostream>
#include <variant>
#include <vector>

struct A { };
struct B { };
struct C { };

struct Collider
{
    void operator()(A const& , A const& ) const { std::cout << "(A, A)\n"; }
    void operator()(B const& , B const& ) const { std::cout << "(B, B)\n"; }
    void operator()(C const& , C const& ) const { std::cout << "(C, C)\n"; }
    void operator()(A const& , B const& ) const { std::cout << "(A, B)\n"; }
    void operator()(B const& , A const& ) const { std::cout << "(B, A)\n"; }
    void operator()(A const& , C const& ) const { std::cout << "(A, C)\n"; }
    void operator()(C const& , A const& ) const { std::cout << "(C, A)\n"; }
    void operator()(C const& , B const& ) const { std::cout << "(C, B)\n"; }
    void operator()(B const& , C const& ) const { std::cout << "(B, C)\n"; }
};

int main()
{
    using CollideVariant = std::variant<A, B, C>;

    auto collidees = std::vector<CollideVariant>();
    collidees.push_back(A{});
    collidees.push_back(B{});
    collidees.push_back(C{});

    for (size_t i = 0; i < collidees.size(); ++i)
        for (auto j = i + 1; j != collidees.size(); ++j)
            std::visit(Collider{}, collidees[i], collidees[j]);
}
