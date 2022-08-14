#include <algorithm>
#include <iostream>
#include <map>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

// raw pointer实现 Singleton模板
template<typename T>
class Singleton{
public:
	template <typename... Args>
	static T* Instance(Args&&... args){
		if (m_pInstance == nullptr)
			m_pInstance = new T(std::forward<Args>(args)...);
		return m_pInstance;
	}

	static T* GetInstance(){
		if (m_pInstance == nullptr)
			throw std::logic_error("the instance is not init,please initialize the instance first");
		return m_pInstance;
	}

	static void DestroyInstance()
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}

private:
	Singleton(void);
	virtual ~Singleton(void);
	Singleton(const Singleton&);
	Singleton& operator=(const Singleton&);
private:
	static T* m_pInstance;
};

template<class T>
T* Singleton<T>::m_pInstance = nullptr;


// 引用实现Singleton模板
template<typename T>
class SingletonR{
public:
	template <typename... Args>
	static T& GetInstance(Args&&... args){
        static T instance(std::forward<Args>(args)...);
		return instance;
	}

private:
	SingletonR(void);
	virtual ~SingletonR(void);
	SingletonR(const SingletonR&);
	SingletonR& operator=(const SingletonR&);
};

struct A{
    A() {
       ++val;
    }
    
    int get_val() {
        return val;
    }
private:
    static int val;
};

int A::val = 0; 

int main(int argc, char* argv[]) {
    auto a = Singleton<A>::Instance();
    cout << a->get_val() << endl;

    auto b = Singleton<A>::GetInstance();
    cout << b->get_val() << endl;

    auto c = Singleton<A>::GetInstance();
    cout << c->get_val() << endl;
    
    Singleton<A>::DestroyInstance();

    auto d = SingletonR<A>::GetInstance();
    cout << d.get_val() << endl;
    auto e = SingletonR<A>::GetInstance();
    cout << e.get_val() << endl;
    auto f = SingletonR<A>::GetInstance();
    cout << f.get_val() << endl;

    return EXIT_SUCCESS;
}