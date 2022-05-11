#ifndef _FREDRIC_MEMBER_REF_COUNT_HPP_
#define _FREDRIC_MEMBER_REF_COUNT_HPP_

template <typename ObjectT,
          typename CountT,
          CountT ObjectT::*CountP>
class MemberReferenceCount {
    public: 
        void init(ObjectT* object) {
            object->*CountP = 1;
        }

        // dispose不需要做额外操作
        void dispose (ObjectT*) {

        }

        void increment(ObjectT* object) {
            ++object->*CountP;
        }

        void decrement(ObjectT* object) {
            --object->*CountP;
        }


        bool is_zero(ObjectT* object) {
            return object->*CountP == 0; 
        }
};

#endif