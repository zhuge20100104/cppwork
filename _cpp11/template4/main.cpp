#include <iostream>
#include <vector>

template <class T>
class PrettyPrinter {
    private:
        T* m_pData;
    
    public:
        PrettyPrinter(T* data): m_pData {data} {

        }

        void Print() {
            std::cout << "{"  << *m_pData << "}" << std::endl;
        }

        T* GetData() {
            return m_pData;
        }
};

// std::vector<std::vector<int>>类型的 成员函数 Print模板特化
template <>
void PrettyPrinter<std::vector<std::vector<int>>>::Print() {
    std::cout << "{\n";
    for(const auto& in_v: *m_pData) {
        std::cout << "  " << "{";
        auto i = 0;
        auto size = in_v.size()-1;
        for(const auto& ele: in_v) { 
            // 最后一个元素不打,
            if(i < size)
                std::cout << ele << ", ";
            else 
                std::cout << ele;
            ++i;
        }
        std::cout << "}\n";
    }
    std::cout << "}\n";
}

int main(int argc, char* argv[]) {
    std::vector<std::vector<int>> v {{1,2,3}, {4,5,6}};
    PrettyPrinter<std::vector<std::vector<int>>> pv{&v};
    pv.Print();
}