#ifndef _FREDRIC_CAR_H_
#define _FREDRIC_CAR_H_

class Car {
    // 非静态成员初始化在构造函数初始化之后，会自动插入到构造函数初始化后面
    private:
        float fuel {0}; // 车当前的油量
        float speed {0}; // 车当前的速度
        int passengers {0};  //乘客个数

        int arr[5] {1, 2, 3};
        char* p{}; // 默认以 nullptr 初始化指针
    public:
        Car();
        Car(float amount);
        void fill_fuel(float amount); //加油
        void accelerate(); // 加速
        void brake(); // 停车
        void add_passengers(int count); // 乘客上车
        void dashboard(); // 仪表盘，显示车况
        ~Car();
};
#endif