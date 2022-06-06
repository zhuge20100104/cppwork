#ifndef _FREDRIC_SUM_POLICY_HPP_
#define _FREDRIC_SUM_POLICY_HPP_

class sum_policy {
    public:
        template <typename T1, typename T2>
        static void accumulate(T1& total, T2 const& val) {
            total += val;
        }
};

#endif