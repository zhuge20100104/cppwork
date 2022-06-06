#ifndef _NONCOPYABLE_HPP_
#define _NONCOPYABLE_HPP_

class NonCopyable {
    public:
        NonCopyable(const NonCopyable& n) = delete; // deleted
        NonCopyable& operator=(const NonCopyable& n) = delete; // deleted
        NonCopyable() = default; // available
};
#endif