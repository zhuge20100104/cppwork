#ifndef _DLL_PARSER_H_
#define _DLL_PARSER_H_

#include <windows.h>
#include <string>
#include <functional>
#include <map>
#include <iostream>
#include <exception>
using std::cout;
using std::endl;
using std::map;
using std::string;

class DLLParser {
    public:
        DLLParser() {}
        ~DLLParser() {
            Unload();
        }


        bool Load(const string& dllPath) {
            m_hMod = LoadLibrary(LPCTSTR(dllPath.c_str()));

            if(nullptr == m_hMod) {
                cout << "LoadLibrary failed" << endl;
                return false;
            }
            return true;
        }

        template <typename T, typename ... Args>
        typename std::result_of<std::function<T>(Args...)>::type 
        ExecuteFunc(const string& funcName, Args&& ... args) {
            auto f = GetFunction<T>(funcName);
            if(f == nullptr) {
                string s = "Can not find this function " + funcName;
                throw std::logic_error(s); 
            }
            return f(std::forward<Args>(args)...);
        }
    
    private:
        bool Unload() {
            // 说明已经被卸载
            if(m_hMod == nullptr) {
                return true;
            }

            auto b = FreeLibrary(m_hMod);
            // 说明free失败
            if(!b) {
                return false;
            }

            m_hMod = nullptr;
            return true;
        }

        template <typename T> 
        T* GetFunction(const string& funcName) {
            auto funcIt = m_map.find(funcName);
            if(funcIt != m_map.end()) {
                auto func = funcIt->second;
                return (T*)func;
            }

            auto addr = GetProcAddress(m_hMod, funcName.c_str());
            m_map.emplace(funcName, addr);
            return (T*)addr;
        }

    private:
        HMODULE m_hMod;
        map<string, FARPROC> m_map;
};

#endif