#ifndef _FREDRIC_BASE_MEMBER_PAIR_HPP_
#define _FREDRIC_BASE_MEMBER_PAIR_HPP_

// Base 是空基类的模板
template <typename Base, typename Member>
class BaseMemberPair: public Base {
    private:
        Member member;
    
    public:
        BaseMemberPair(Base const& b, Member const& m): Base(b), member(m) {
        }

        Base const& first() const {
            return static_cast<Base const&>(*this);
        }

        Base& first() {
            return static_cast<Base&>(*this);
        }

        Member const& second() const {
            return static_cast<Member const&>(member);
        }

        Member& second() {
            return static_cast<Member>(member);
        }
};
#endif