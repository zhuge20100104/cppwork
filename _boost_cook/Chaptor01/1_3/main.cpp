#include <boost/any.hpp>

#include <iostream>
#include <string>
#include <vector>

void example();

int main(int argc, char* argv[]) {
	std::vector<boost::any> some_values;
	some_values.emplace_back(10);
	const char* cstr = "Hello, there!";
	some_values.emplace_back(cstr);
	some_values.emplace_back(std::string("Wow!"));

	std::string& s = boost::any_cast<std::string&>(some_values.back());
	s += " That is great!\n";
	std::cout << s;

	// 调用前项声明的example函数
	example();
}

void example() {
	boost::any variable(std::string("Hello world!"));
	
	std::string s1 = boost::any_cast<std::string>(variable);
	std::string* s2 = boost::any_cast<std::string>(&variable);
	// 避免出现未使用的变量
	(void)s1;
	(void)s2;
}
