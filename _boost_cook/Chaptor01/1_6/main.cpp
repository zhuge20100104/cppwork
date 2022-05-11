#include <boost/variant.hpp>

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using cell_t = boost::variant<int, float, std::string>;
using db_row_t = std::vector<cell_t>;

db_row_t get_row(const char* /*query*/) {
	db_row_t row;
	row.emplace_back(10);
	row.emplace_back(10.1f);
	row.emplace_back("hello again");
	return row;
}

struct db_sum_visitor: public boost::static_visitor<double> {
	double operator() (int value) const {
		return value;
	}

	double operator() (float value) const {
		return value;	
	}

	double operator() (const std::string& /*value*/) const {
		return 0.0;
	}
};

int main(int argc, char* argv[]) {
	db_row_t row = get_row("Query: please give me some row");
	double res = 0.0;
	
	std::for_each(row.begin(), row.end(), [&res](const auto& cell) {
				res += boost::apply_visitor(db_sum_visitor(), cell);
			});

	std::cout << "数据库行中数字值的总和是: " << res << std::endl;
}

