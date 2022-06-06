#ifndef _FREDRIC_CAR_H_
#define _FREDRIC_CAR_H_

class car {
    float fuel;
    float speed;
    int passengers;
public:
    car();

    car(float fuel_);

    ~car();

    void fill_fuel(float amount);
    void accelerate();
    
    void brake();
 
    void add_passengers(int count);

    void dashboard();

};

#endif