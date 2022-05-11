#include <boost/variant.hpp>

#include <iostream>
#include <vector>
#include <string>

#include <cassert>

void example1();
void example2();

int main(int argc, char* argv[]) {
	using my_var_t = boost::variant<int, const char*, std::string>;
	std::vector<my_var_t> some_values;
	some_values.emplace_back(10);
	some_values.emplace_back("Hello there!");
	some_values.emplace_back(std::string("Wow!"));

	std::string& s = boost::get<std::string>(some_values.back());
	s += " That is great!\n";
	std::cout << s;

	example1();
	example2();
}


void example1() {
	// 使用boost::blank 来指示当前variant变量是否为空
	boost::variant<boost::blank, int, const char*, std::string> var;
	// 当前指向blank, var变量为空
	assert(var.which() == 0);
	var = "Hello, dear reader";
	assert(var.which() != 0);
}

void example2() {
	boost::variant<int, std::string> variable(0);

	int s1 = boost::get<int>(variable);
	int* s2 = boost::get<int>(&variable);

	assert(s1 == 0);
	assert(s2);
	assert(*s2 == 0);
}
