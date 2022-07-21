// ------------------------------------------------------------------------------- //
// Advanced Kalman Filtering and Sensor Fusion Course - Linear Kalman Filter
//
// ####### STUDENT FILE #######
//
// Usage:
// -Rename this file to "kalmanfilter.cpp" if you want to use this code.

#include "kalmanfilter.h"
#include "utils.h"

// -------------------------------------------------- //
// YOU CAN USE AND MODIFY THESE CONSTANTS HERE
constexpr bool INIT_ON_FIRST_PREDICTION = false;
constexpr double INIT_POS_STD = 0;
constexpr double INIT_VEL_STD = 15;
constexpr double ACCEL_STD = 0.1;
constexpr double GPS_POS_STD = 3.0;
// -------------------------------------------------- //

void KalmanFilter::predictionStep(double dt)
{
    // 以随意值设置初始化状态
    if (!isInitialised() && INIT_ON_FIRST_PREDICTION)
    {
        // Implement the State Vector and Covariance Matrix Initialisation in the
        // section below if you want to initialise the filter WITHOUT waiting for
        // the first measurement to occur. Make sure you call the setState() /
        // setCovariance() functions once you have generated the initial conditions.
        // Hint: Assume the state vector has the form [X,Y,VX,VY].
        // Hint: You can use the constants: INIT_POS_STD, INIT_VEL_STD
        // ----------------------------------------------------------------------- //
        // ENTER YOUR CODE HERE
            VectorXd state = Vector4d::Zero();
            MatrixXd cov = Matrix4d::Zero();
            
            // 假定初始位置是 px, py [0, 0]
            // 初始速度是5m/s， 沿 45度角方向
            state << 0, 0, 5.0*cos(M_PI)/4, 5.0*sin(M_PI)/4;
            // 初始位置协方差
            double const init_pos_std = INIT_POS_STD;
            // 初始速度协方差
            double const init_vel_std = INIT_VEL_STD;

            cov(0, 0) = init_pos_std * init_pos_std;
            cov(1, 1) = init_pos_std * init_pos_std;
            cov(2, 2) = init_vel_std * init_vel_std;
            cov(3, 3) = init_vel_std * init_vel_std;

            setState(state);
            setCovariance(cov);
        // ----------------------------------------------------------------------- //
    }

    if (isInitialised())
    {
        VectorXd state = getState();
        MatrixXd cov = getCovariance();

        // Implement The Kalman Filter Prediction Step for the system in the  
        // section below.
        // Hint: You can use the constants: ACCEL_STD
        // ----------------------------------------------------------------------- //
        // ENTER YOUR CODE HERE

        MatrixXd F = Matrix4d();
        F << 1, 0, dt, 0, 0, 1, 0, dt, 0, 0, 1, 0, 0, 0, 0, 1;
        MatrixXd Q = Matrix2d::Zero();
        Q(0, 0) = (ACCEL_STD * ACCEL_STD);
        Q(1, 1) = (ACCEL_STD * ACCEL_STD);

        MatrixXd L =MatrixXd(4, 2);
        L << (0.5*dt*dt), 0, 0, (0.5*dt*dt), dt, 0, 0, dt;

        state = F * state;
        cov = F*cov*F.transpose() + L*Q*L.transpose();
        // ----------------------------------------------------------------------- //
        setState(state);
        setCovariance(cov);
    }
}

void KalmanFilter::handleGPSMeasurement(GPSMeasurement meas)
{
    if(isInitialised())
    {
        // 前一步的预估值
        VectorXd state = getState();
        // 前一步预估值的协方差
        MatrixXd cov = getCovariance();

        // Implement The Kalman Filter Update Step for the GPS Measurements in the 
        // section below.
        // Hint: Assume that the GPS sensor has a 3m (1 sigma) position uncertainty.
        // Hint: You can use the constants: GPS_POS_STD
        // ----------------------------------------------------------------------- //
        // ENTER YOUR CODE HERE 

        // 当前度量值
        VectorXd z = Vector2d();
        // 当前预估值 前面的矩阵， 2行4列，用于提取预估值中的px, py
        MatrixXd H = MatrixXd(2, 4);
        // GPS噪声矩阵
        MatrixXd R = Matrix2d::Zero();

        z << meas.x, meas.y;
        H << 1, 0, 0, 0, 0, 1, 0, 0;
        R(0, 0) = GPS_POS_STD * GPS_POS_STD;
        R(1, 1) = GPS_POS_STD * GPS_POS_STD;

        // 前一步的预估值
        VectorXd z_hat = H* state;
        // 度量值与前一步 预估值之间的差异, innovation
        VectorXd y = z - z_hat;

        // 当前 innovation的协方差  = 前一步预估值的协方差 + GPS度量值的协方差 = Matrix2d
        // 这个公式可以从y的公式使用线性代数推导  
        MatrixXd S = H * cov * H.transpose() + R;
        // cov 多大程度相信前一步的预测值， S 多大程度相信GPS的度量值
        // 这是一个增益矩阵，用来计算新的预测值
        // H 是原先老的 预测值的系数矩阵
        MatrixXd K = cov * H.transpose() * S.inverse();
        
        // 计算新的预测值
        state = state + K*y;
        // 计算新的预测值的协方差
        cov = (MatrixXd::Identity(4, 4) - K*H) * cov;
        // ----------------------------------------------------------------------- //

        setState(state);
        setCovariance(cov);
    }
    else
    {
        // Implement the State Vector and Covariance Matrix Initialisation in the
        // section below. Make sure you call the setState/setCovariance functions
        // once you have generated the initial conditions.
        // Hint: Assume the state vector has the form [X,Y,VX,VY].
        // Hint: You can use the constants: GPS_POS_STD, INIT_VEL_STD
        // ----------------------------------------------------------------------- //
        // ENTER YOUR CODE HERE
        // 使用GPS的位置值和标准差进行初始化
            VectorXd state = Vector4d::Zero();
            MatrixXd cov = Matrix4d::Zero();

            state(0) = meas.x;
            state(1) = meas.y;

            cov(0, 0) = GPS_POS_STD * GPS_POS_STD;
            cov(1, 1) = GPS_POS_STD * GPS_POS_STD;
            cov(2, 2) = INIT_VEL_STD * INIT_VEL_STD;
            cov(3, 3) = INIT_VEL_STD * INIT_VEL_STD;

            setState(state);
            setCovariance(cov);
        // ----------------------------------------------------------------------- //
    }        
}

Matrix2d KalmanFilter::getVehicleStatePositionCovariance()
{
    Matrix2d pos_cov = Matrix2d::Zero();
    MatrixXd cov = getCovariance();
    if (isInitialised() && cov.size() != 0){pos_cov << cov(0,0), cov(0,1), cov(1,0), cov(1,1);}
    return pos_cov;
}

VehicleState KalmanFilter::getVehicleState()
{
    if (isInitialised())
    {
        VectorXd state = getState(); // STATE VECTOR [X,Y,VX,VY]
        double psi = std::atan2(state[3],state[2]);
        double V = std::sqrt(state[2]*state[2] + state[3]*state[3]);
        return VehicleState(state[0],state[1],psi,V);
    }
    return VehicleState();
}

void KalmanFilter::predictionStep(GyroMeasurement gyro, double dt){predictionStep(dt);}
void KalmanFilter::handleLidarMeasurements(const std::vector<LidarMeasurement>& dataset, const BeaconMap& map){}
void KalmanFilter::handleLidarMeasurement(LidarMeasurement meas, const BeaconMap& map){}

