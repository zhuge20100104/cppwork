#ifndef _ASPECT_HPP_
#define _ASPECT_HPP_

#include <type_traits>
#include <boost/noncopyable.hpp>

// 这个HAS_MEMBER宏比较复杂
// 首先作者为什么要定义一个宏呢，因为需要在std::enable_if中调用这个宏确定是否存在成员
// 如果存在成员，则调用对应的函数，std::enable_if需要在编译器在函数体外调用，不能写成函数
// 其次这个宏干了什么呢？
// 它定义了一个结构体
// 里面有两个重载的成员函数
// 一个是int类型的
// 另一个是任意参数类型的，名字都叫Check
// 然后这个结构体中还有一个枚举值
// 是调用Check函数的结果
// 其中Check<T>(0)会先调用 Check<int>，如果发现T中有member成员，则会继续走
// 逗号表达式，返回std::true_type
// 如果T中没有member成员，说明第一个重载不成立
// 走第二个任意参数的重载
// 返回std::false_type 

#define HAS_MEMBER(member) \
template <typename T, typename ... Args>struct has_member_##member\
{\
    private: \
             template <typename U> static auto Check(int) -> decltype(std::declval<U>().member(std::declval<Args>()...), std::true_type()); \
             template <typename U> static std::false_type Check(...); \
    public: \
             enum {value = std::is_same<decltype(Check<T>(0)), std::true_type>::value }; \
};

// 使用前面定义的宏，定义has_member_Before和has_member_After类结构体
HAS_MEMBER(Before)
HAS_MEMBER(After)

// 设置Aspect类不可拷贝
template <typename Func, typename ... Args> 
struct Aspect: boost::noncopyable {
    public:
        Aspect(Func&& f):m_func(std::forward<Func>(f))  {
        
        }
       
        // 模板可变参数 递归调用的结束函数，也是递归调用过程中调用的函数
        // 某个切面有Before有After
        template<typename T> 
        typename std::enable_if<has_member_Before<T,Args...>::value && has_member_After<T,Args...>::value>::type Invoke(Args&& ...args, T&& aspect) {
            aspect.Before(std::forward<Args>(args)...);
            m_func(std::forward<Args>(args)...);
            aspect.After(std::forward<Args>(args)...);
        }

        // 模板可变参数 递归调用的结束函数，也是递归调用过程中调用的函数
        // 某个切面有Before没有After
        template<typename T> 
        typename std::enable_if<has_member_Before<T,Args...>::value && !has_member_After<T,Args...>::value>::type Invoke(Args&& ...args, T&& aspect) {
            aspect.Before(std::forward<Args>(args)...);
            m_func(std::forward<Args>(args)...);
        }
        
        // 模板可变参数 递归调用的结束函数，也是递归调用过程中调用的函数
        // 某个切面没有Before有After
        template<typename T> 
        typename std::enable_if<!has_member_Before<T,Args...>::value && has_member_After<T,Args...>::value>::type Invoke(Args&& ...args, T&& aspect) {
            m_func(std::forward<Args>(args)...);
            aspect.After(std::forward<Args>(args)...);
        }
        
        // 模板递归展开的中间态
        // 每次展开一个Aspect，剩余的继续是可变参数
        template <typename Head, typename ... Tail>
        void Invoke(Args&& ... args, Head&& headAspect, Tail&& ... tailAspect) {
            headAspect.Before(std::forward<Args>(args)...);
            // 这一句比较蛋疼，要看懂，递归展开，一次展开一个headAspect，
            // 直到只剩一个为止，调用上面的三个终止函数
            // 然后从递归栈里面逐一取回各个Aspect
            // 分门别类的调用上面的三个函数
            Invoke(std::forward<Args>(args)..., std::forward<Tail>(tailAspect)...);
            headAspect.After(std::forward<Args>(args)...);
        }

    private:
        Func m_func; // 被切面的函数
};

template <typename T> using identity_t = T;

// AOP的辅助函数，简化调用
template <typename ... AP, typename ... Args, typename Func>
void Invoke(Func&& f, Args&& ... args) {
    Aspect<Func, Args...> asp(std::forward<Func>(f));
    asp.Invoke(std::forward<Args>(args)..., identity_t<AP>()...);
}
#endif
