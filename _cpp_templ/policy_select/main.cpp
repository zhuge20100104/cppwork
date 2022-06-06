#include <iostream>

template <typename Base, int D>
class Discriminator: public Base {};

// Setters里面就是一些个Policy, 按照从后往前的顺序，进行Override
template <typename Setter1, typename Setter2, typename Setter3, typename Setter4>
class PolicySelector: public Discriminator<Setter1, 1>,
                        public Discriminator<Setter2, 2>,
                        public Discriminator<Setter3, 3>,
                        public Discriminator<Setter4, 4> {
};


// Default Polices
class DefaultPolicy1 {};

class DefaultPolicy2 {};

class DefaultPolicy3 {
    public:
        static void doPrint() {
            std::cout << "DefaultPolicy3::doPrint()\n";
        }
};

class DefaultPolicy4 {};

// Define Default Polies as P1, P2, P3, P4
class DefaultPolicies {
    public:
        using P1 = DefaultPolicy1;
        using P2 = DefaultPolicy2;
        using P3 = DefaultPolicy3;
        using P4 = DefaultPolicy4;
};

// Default Policy Args 其实就是Default Polices的别名，用于参数传递
// 为了避免在PolicySelector中多次继承 Default Policy,采用了虚继承
class DefaultPolicyArgs: virtual public DefaultPolicies {};

// 使用类模板 重写 Default Policy 值
template <typename Policy>
class Policy1_is : virtual public DefaultPolicies {
    public:
        using P1 = Policy;
};

template <typename Policy>
class Policy2_is : virtual public DefaultPolicies {
    public:
        using P2 = Policy;
};

template <typename Policy>
class Policy3_is : virtual public DefaultPolicies {
    public:
        using P3 = Policy;
};

template <typename Policy>
class Policy4_is : virtual public DefaultPolicies {
    public:
        using P4 = Policy;
};

// 选择policy的调用类
template <typename PolicySetter1 = DefaultPolicyArgs,
            typename PolicySetter2 = DefaultPolicyArgs,
            typename PolicySetter3 = DefaultPolicyArgs,
            typename PolicySetter4 = DefaultPolicyArgs>
class BreadSlicer {
    using Policies = PolicySelector<PolicySetter1, PolicySetter2, PolicySetter3, PolicySetter4>;

    public:
        void print() {
            Policies::P3::doPrint();
        }
}; 

// 定义一个自定义的 Policy
class CustomPolicy {
    public:
        static void doPrint() {
            std::cout << "CustomPolicy::doPrint()\n";
        }
};

int main(int argc, char* argv[]) {
    BreadSlicer<> bc1;
    bc1.print();

    BreadSlicer<Policy3_is<CustomPolicy>> bc2;
    bc2.print();

    return EXIT_SUCCESS;
}