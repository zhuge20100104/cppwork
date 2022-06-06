#include "object_pool.hpp"
#include <iostream>
using std::cout;
using std::endl;

// MySQL连接器类
class MySQLConn: NonCopyable {
    public:
        MySQLConn(string url, string username, string password): mURL(url), mUser(username), mPass(password) {}

        void ExecSQL(const string& sql) {
            cout << "Exec: [" << sql << "]" << endl;
        }

    private:    
        MySQLConn() = delete;
        string mURL;
        string mUser;
        string mPass;
};

int main() {
    ObjectPool<MySQLConn> p;
    p.Init(5, "jdbc:mysql", "root", "root");
    shared_ptr<MySQLConn> conn = p.Get();
    conn->ExecSQL("insert into stu(id, name, score) values(1, '张三', 78.5);");
    
}
