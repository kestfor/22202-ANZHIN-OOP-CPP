#include <iostream>
#include <string>
#include <tuple>
#include <fstream>
#include "CSVParser.cpp"
#include "CSVParser.h"

using namespace std;

//compile time end of recursion
template <size_t I=0, typename  Ch, typename  Tr, typename... Args>
typename enable_if<I == sizeof...(Args), void>::type
printTuple(std::basic_ostream<Ch, Tr>& os, tuple<Args...> const &t) {
    return;
}

//compile time recursion for tuple print
template <size_t I=0, typename  Ch, typename  Tr, typename... Args>
typename enable_if<(I < sizeof...(Args)), void>::type
printTuple(std::basic_ostream<Ch, Tr>& os, tuple<Args...> const &t) {
    os << get<I>(t) << ' ';
    printTuple<I + 1, Ch, Tr, Args...>(os, t);
}

//tuple print
template<class Ch, class Tr, class... Args>
std::basic_ostream<Ch, Tr>& operator<<(std::basic_ostream<Ch, Tr>& os, std::tuple<Args...> const &t) {
    printTuple(os, t);
    return os;
}

int main() {
    ifstream file("test.txt");
    CSVParser<int, double, string> parser(file, 0, ';', '"');
    try {
        for (const auto &item : parser) {
            cout << item << endl;
        }
    } catch (BasicException &err) {
        cerr << err.what() << endl;
        return err.code();
    }
}