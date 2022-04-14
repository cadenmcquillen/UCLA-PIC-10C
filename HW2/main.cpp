#include "bst.h"
#include "Timer.h"
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<utility>
// bah class can be made many different ways -- test for emplace
struct bah {
int i, j, k;
constexpr bah(int _i = 0, int _j = 0, int _k = 0) : i(_i), j(_j), k(_k) {}
};
constexpr bool operator<(const bah& b1, const bah& b2) {
return std::tie(b1.i, b1.j, b1.k) < std::tie(b2.i, b2.j, b2.k);
}
std::ostream& operator<<(std::ostream& out, const bah& b) {
return out << '[' << b.i << ' ' << b.j << ' ' << b.k << ']';
}
// compares reversed strings
bool rev_str(std::string s1, std::string s2) {
std::reverse(s1.begin(), s1.end());
std::reverse(s2.begin(), s2.end());
return s1 < s2;
}
int main() {
    
pic10c::bst<int> a;
{
pic10c::bst<int> b;
b.insert(1);
b.insert(3);
a = std::move(b);
}
a.insert(2);
for (auto i : a) { std::cout << i << '\n'; }
// standard case
pic10c::bst<int> b1;
b1.insert(3);
b1.insert(4);
b1.insert(0);
    
    //std::cout<< b1.find(0, b1.getroot()).getCurrentPos()->getvalue();
// print the values: requires proper iterators for range-for
std::cout << "b1:\n";
for (const auto& i : b1) {
std::cout << i << '\n';
}
 
pic10c::bst<std::string, bool (*)(std::string, std::string)> b2(rev_str);
b2.emplace(3, 'a');
b2.insert("aaa"); // duplicate!
b2.insert("zzzzzzzza");
b2.insert("aaaaaaaaz");
//std::cout<< b2.find("zzzzzzzza" , b2.getroot()).getCurrentPos()->getvalue();
//assert(b2.find("zzzzzzzza123" , b2.getroot()).getCurrentPos() == nullptr);
b2.emplace(6, 'm');
auto b3 = b2;
std::cout << "b3:\n";
for (const auto& s : b3) { // print b3, copy of b2
std::cout << s << '\n';
}

auto b4 = std::move(b3); // move construct b4 from b3...
std::cout << "size b3 " << b3.size() << '\n';
std::cout << "size b4 " << b4.size() << '\n';
std::cout << "iterator stuff:\n";
pic10c::bst<std::string, decltype(&rev_str)>::iterator it =
b4.begin();
std::cout << *it << '\n';
std::cout << it->size() << '\n';
b4.erase(it);
std::cout << "b4:\n";
for (const auto& s : b4) { // no more "aaa"
std::cout << s << '\n';
}
    
// test emplace here
pic10c::bst<bah> bahs;
bahs.emplace();
bahs.emplace(1);
bahs.emplace(-1, 7);
bahs.emplace(0, 9, 146);
for (const bah& b : bahs) {
std::cout << b << '\n';
}
     
constexpr size_t small_n = 50;
constexpr size_t big_n = 5000;
std::vector<double> vals_to_insert;
vals_to_insert.reserve(big_n);
for (size_t i = 0; i < big_n; ++i) {
vals_to_insert.push_back(std::rand() / (RAND_MAX + 1.));
}
simple_timer::timer<'u'> clock;
{
pic10c::bst<double> timed_tree;
clock.tick();
for (size_t i = 0; i < small_n; ++i) {
timed_tree.insert(vals_to_insert[i]);
}
auto small_insert = clock.tock();
std::cout << "small insert: " << small_insert << '\n';
clock.tick();
}
auto small_destruct = clock.tock();
std::cout << "small destruct: " << small_destruct << '\n';
{
pic10c::bst<double> timed_tree;
clock.tick();
for (size_t i = 0; i < big_n; ++i) {
timed_tree.insert(vals_to_insert[i]);
}
auto big_insert = clock.tock();
std::cout << "big insert: " << big_insert << '\n';
clock.tick();
}
auto big_destruct = clock.tock();
std::cout << "big destruct: " << big_destruct << '\n';
// now test copying preserves structure
pic10c::bst<double> rands;
for (size_t i = 0; i < big_n; ++i) {
rands.insert(vals_to_insert[i]);
}
auto rands2 = rands;
double tot = 0, tot2 = 0;
clock.tick();
for (double d : rands) {
tot += d;
}
auto rands_time = clock.tock();
clock.tick();
for (double d : rands) {
tot += d;
}
auto rands2_time = clock.tock();
std::cout << "times are " << rands_time << ' ' << rands2_time << '\n';
  
  
return 0;
}

