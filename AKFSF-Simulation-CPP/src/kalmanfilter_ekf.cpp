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
constexpr double ACCEL_STD = 1.0;
constexpr double GYRO_STD = 0.01/180.0 * M_PI;
constexpr double INIT_VEL_STD = 10.0;
constexpr double INIT_PSI_STD = 45.0/180.0 * M_PI;
constexpr double GPS_POS_STD = 3.0;
constexpr double LIDAR_RANGE_STD = 3.0;
constexpr double LIDAR_THETA_STD = 0.02;


void KalmanFilter::handleLidarMeasurements(const std::vector<LidarMeasurement>& dataset, const BeaconMap& map){
    // 逐个雷达地标点进行处理
    for(auto const& meas: dataset) {
        handleLidarMeasurement(meas, map);
    }
}

void KalmanFilter::handleLidarMeasurement(LidarMeasurement meas, const BeaconMap& map){
    if(isInitialised()) {
        VectorXd state = getState();
        MatrixXd cov = getCovariance();

        // 根据地标点的id,获取地标点的数据，包括px,py
        BeaconData map_beacon = map.getBeaconWithId(meas.id);
        if(meas.id != -1 && map_beacon.id != -1) {
            // 获取当前雷达地标的度量值
            VectorXd z = Vector2d::Zero();
            z << meas.range, meas.theta;

            // 使用雷达地标的 H(x)方程，预测地标
            VectorXd z_hat = Vector2d::Zero();
            double delta_x = map_beacon.x - state(0);
            double delta_y = map_beacon.y - state(1);
            double zhat_range = sqrt(delta_x* delta_x + delta_y * delta_y);
            double zhat_theta = wrapAngle(atan2(delta_y, delta_x) - state(2));
            z_hat << zhat_range, zhat_theta;

            // 度量模型传播矩阵，雅可比阵
            MatrixXd H = MatrixXd(2, 4);
            // 雅可比阵还是那个矩阵，但是 求偏导数的顺序应该是 x,y,sai,v
            H << -delta_x/zhat_range, -delta_y/zhat_range, 0, 0, delta_y/zhat_range/zhat_range, -delta_x/zhat_range/zhat_range, -1, 0;

            // 生成雷达度量模型噪声协方差矩阵
            MatrixXd R = Matrix2d::Zero();
            R(0, 0) = LIDAR_RANGE_STD * LIDAR_RANGE_STD;
            R(1, 1) = LIDAR_THETA_STD * LIDAR_THETA_STD;

            // 计算度量值和预测值误差, innovation
            VectorXd y = z - z_hat;
            MatrixXd S = H * cov * H.transpose() +R; 
            MatrixXd K = cov * H.transpose() * S.inverse();

            y(1) = wrapAngle(y(1)); 
            state = state + K*y;
            cov = (Matrix4d::Identity() - K*H) * cov;
        }

        setState(state);
        setCovariance(cov);
    }
}

// -------------------------------------------------- //

void KalmanFilter::predictionStep(GyroMeasurement gyro, double dt)
{
    if (isInitialised())
    {
        VectorXd state = getState();
        MatrixXd cov = getCovariance();

        // Implement The Kalman Filter Prediction Step for the system in the  
        // section below.
        // Hint: You can use the constants: ACCEL_STD
        // ----------------------------------------------------------------------- //
        // ENTER YOUR CODE HERE
        double x = state(0);
        double y = state(1);
        double psi = state(2);
        double V = state(3);

        // 根据delta_t 和 陀螺仪更新状态
        double x_new = x + dt * V * cos(psi);
        double y_new = y + dt * V * sin(psi);
        // gyro.psi_dot 角速度
        double psi_new = wrapAngle(psi + dt* gyro.psi_dot);
        // 速度的数值不变
        double V_new = V;
        state << x_new, y_new, psi_new, V_new;

        // 生成F雅可比阵
        // 这个F的生成规则需要注意，和课件里面讲的不一样
        // 按x,y,psi,V的顺序生成
        MatrixXd F = Matrix4d::Zero();
        F << 1, 0, -dt*V*sin(psi), dt*cos(psi), 0, 1, dt*V*cos(psi), dt*sin(psi), 0, 0, 1, 0, 0, 0, 0, 1; 

        // 生成Q矩阵
        MatrixXd Q = Matrix4d::Zero();
        Q(2, 2) = dt*dt* GYRO_STD * GYRO_STD;
        Q(3, 3) = dt*dt* ACCEL_STD * ACCEL_STD;

        cov = F*cov* F.transpose() + Q;
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
        VectorXd z = Vector2d::Zero();
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
        cov = (Matrix4d::Identity() - K*H) * cov;
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
            cov(2, 2) = INIT_PSI_STD * INIT_PSI_STD;
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
    // 如果初始化了，直接把当前的VehicleState返回
    if (isInitialised())
    {
        VectorXd state = getState(); // STATE VECTOR [X,Y,PSI,V,...]
        return VehicleState(state[0],state[1],state[2],state[3]);
    }
    // 否则返回空的VehicleState
    return VehicleState();
}

