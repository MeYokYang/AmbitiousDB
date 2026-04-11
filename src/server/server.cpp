#include "server.h"
#include "list.h"
#include "standard.h"
#include "str.h"

namespace ambitiousdb {
namespace atserver {

} // namespace end: ambitiousdb
} // namespace end: atserver

int main () {
    LinkedList<sint> list;
    for (sint i = 0; i < 100; i++)
    {
        list.insert(100);
    }

    ArrayList<Str> list2;
    for (sint i = 0; i < 100; i++)
    {
        list2.insert(Str("100"));
    }

    return 0;
}
