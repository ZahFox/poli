#include <vector>
#include <list>
#include "notes.h"
#include "templates.h"

namespace Notes {

using Tuple1 = tuple<double, uint64_t, const char *>;
using Tuple2 = tuple<double, double, double, bool>;

void CompareTypes()
{
    if (pair_comparer(1, 1, 2, 2, 3, 3, 4, 4))
    {
        std::cout << "Pair Comparer: All Pairs Matched" << std::endl;
    }
    else
    {
        std::cout << "Pair Comparer: Matching Failed" << std::endl;
    }
}

void CustomTuples()
{
    Tuple1 t1(12.2, 42, "big");
    auto t10 = tuple_get<0>(t1);
    auto t12 = tuple_get<2>(t1);

    Tuple2 t2(12.0, 33.0, 42.0, true);
    auto t23 = tuple_get<3>(t2);

    std::cout << "Tuple1's 1st elem is " << t10 << std::endl;
    std::cout << "Tuple1's 3rd elem is " << t12 << std::endl;
    std::cout << "Tuple2's 4th elem is " << t23 << std::endl;
}

void PrintContainers()
{
    std::vector<float> V1 = {2.12, 3.45, 6.77};
    std::list<const char *> V2 = {"alice", "bob", "carl"};
    print_container(V1);
    print_container(V2);
}

void PrintInitMessage()
{
    std::cout << "Notes Module Was Initialized" << std::endl;
}

void Init()
{
    PrintInitMessage();
    CompareTypes();
    CustomTuples();
    PrintContainers();
}

} // namespace Notes
