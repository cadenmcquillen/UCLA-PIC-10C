#include "specialize_deque.h"
#include <iostream>
int main() {
pic10c::deque<int> d;
d.push_back(4);
d.push_back(5);
d.push_front(3);
for (auto i : d) {
std::cout << i << ' ';
}
std::cout << '\n';
d.push_front(2);
d.push_front(0);
d.push_back(7);
d[2] = 1;
d[d.size() - 1] = 6;
d.pop_back();
d.pop_front();
for (auto i : d) {
std::cout << i << ' ';
}
std::cout << '\n';
std::cout << "sum: " << sum(d) << '\n';
pic10c::deque<bool> b;
b.push_back(true);
b.push_back(true);
b.push_back(true);
b.push_back(true);
b.push_front(false);
for (auto i = b.begin(), e = b.end(); i != e; ++i) {
std::cout << *i << ' ';
}
std::cout << '\n';
b.push_front(false);
b.push_front(false);
b.push_front(false);
b.push_back(true);
b.pop_back();
b.push_front(true);
b.push_back(false);
b[b.size() - 2] = false;
for (auto i = b.begin(), e = b.end(); i != e; ++i) {
std::cout << *i << ' ';
}
std::cout << '\n';
// sum(b); // <-- COMPILER ERROR
return 0;
}
