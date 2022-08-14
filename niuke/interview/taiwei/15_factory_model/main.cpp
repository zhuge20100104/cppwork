#include <algorithm>
#include <iostream>
#include <map>
#include <sstream>
#include <stack>
#include <string>
#include <vector>
#include <memory>

using namespace std;

string const SnowFlakeName = "snowflake";
string const AuroraName = "aurora";

struct Engine{
    virtual void query() = 0;
    virtual ~Engine() {};
};

struct SnowflakeEngine: public Engine {
    void query() override {
        cout << "Snowflake db query" << endl;
    }
};

struct AuroraEngine: public Engine {
    void query() override {
        cout << "Aurora db query" << endl;
    }
};

struct EngineFactory {
    static map<string, shared_ptr<Engine>> engines;
    
    static shared_ptr<Engine> get_engine(string const& engine_name) {
        return engines[engine_name];
    }
};

map<string, shared_ptr<Engine>>  EngineFactory::engines {
    {SnowFlakeName, std::make_shared<SnowflakeEngine>()},
    {AuroraName, std::make_shared<AuroraEngine>()}
};

int main(int argc, char* argv[]) {  
    auto sf_engine = EngineFactory::get_engine(SnowFlakeName);
    sf_engine->query();
    
    auto aurora_engine = EngineFactory::get_engine(AuroraName);
    aurora_engine->query();
    return EXIT_SUCCESS;
}