#include "collidees.hpp"
#include "collider.hpp"

using namespace std;

int main()
{
    Collider collider;

       auto a = std::make_unique<A>();
       auto b = std::make_unique<B>();
       auto c = std::make_unique<C>();

       a->visit(collider, *b);
       a->visit(collider, *c);
       c->visit(collider, *b);
       c->visit(collider, *a);
       b->visit(collider, *a);

       return 0;
}
