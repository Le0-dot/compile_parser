#include <iostream>
#include <string_view>

#include "ll1_parser.hpp"

using namespace std;
using namespace std::string_literals;

int main()
{
    compiler_parser::ll1_parser::parser p{"3 * (1 + 2) + 4"sv};
    cout << p.parse() << endl;
    return 0;
}
