#include <boost/any.hpp>

#include <vector>
#include <string>
#include <typeinfo>
#include <algorithm>
#include <iostream>

using cell_t = boost::any;
using db_row_t = std::vector<cell_t>;

db_row_t get_row(const char* /*query*/) {
	db_row_t row;
	row.emplace_back(10);
	row.emplace_back(10.1f);
	row.emplace_back(std::string("Hello, again"));
	return row;
}

struct db_sum {
	private:
		double& sum_;
	
	public:
		explicit db_sum(double& sum): sum_(sum) {}

		void operator() (const cell_t& value) {
			// 只处理一行中的int和float，进行加和操作
			const std::type_info& ti = value.type();
			if(ti == typeid(int)) {
				sum_ += boost::any_cast<int>(value);
			}else if(ti == typeid(float)) {
				sum_ += boost::any_cast<float>(value);
			}
		}
};


int main(int argc, char* argv[]) {
	db_row_t row = get_row("Give me a row please!");
	double res = 0.0;
	std::for_each(row.begin(), row.end(), db_sum(res));
	std::cout << "数据库行中的所有数字总和为: " << res << std::endl;
}
