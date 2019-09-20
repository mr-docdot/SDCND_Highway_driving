#ifndef _EGO_VEHICLE_H_
#define _EGO_VEHICLE_H_

#include "PTG.h"
#include "helpers.h"
#include <vector>
#include <list>
#include <cmath>
#include <algorithm>
#include "spline.h"

using std::vector;
using std::list;

class ego_vehicle {
  public:
    ego_vehicle();
    ~ego_vehicle();
    // This is a test method in order to test the comunication with the simulator
    vector<vector<double>> getCircularTraj(double x0, double y0, double th0, double v0, 
        const vector<double> &previousXpoints, const vector<double> &previousYpoints);
    
    vector<vector<double>> PTGkeepLineTraj(double x0, double y0, double th0, double v0, 
        const vector<double> &previousXpoints, const vector<double> &previousYpoints, 
        const vector<double> &mapsS, const vector<double> &mapsX, const vector<double> &mapsY);

    vector<vector<double>> SplineTraj(double x0, double y0, double th0, 
        const vector<double> &previousXpoints, const vector<double> &previousYpoints, 
        const vector<double> &mapsS, const vector<double> &mapsX, const vector<double> &mapsY);

    void changeTrajectory(const vector<double> &previousXpoints, double s0, double endPathS, const vector<vector<double>> &otherCars);

    vector<vector<double>> trajXYToFrenet(const vector<double> &xPoints, const vector<double> &yPoints, 
        const vector<double> &thPoints, const vector<double> &mapsX, const vector<double> &mapsY);
    
    vector<vector<double>> trajFrenetToXY(const vector<double> &sPoints, const vector<double> &dPoints,
        const vector<double> &mapsS, const vector<double> &mapsX, const vector<double> &mapsY);

    vector<double> getVelocity(const vector<double> &posPoints);

    vector<double> getAcceleration(const vector<double> &velPoints);
    
    vector<double> getThetasFromXY(const vector<double> &xPoints, const vector<double> &yPoints);

    bool getVehicleAhead(double lastPathSize, const vector<vector<double>> &otherVehicles, 
                        unsigned int lane, vector<double> &vehicleFound);

    bool getVehicleBehind(const vector<vector<double>> &otherVehicles, 
                          unsigned int lane, vector<double> &vehicleFound);

    vector<double> getKinematicsOfLane(double lastPathSize, const vector<vector<double>> &otherVehicles, unsigned int lane);

    vector<double> keepLaneTraj(double lastPathSize, const vector<vector<double>> &otherVehicles);


  private:
    PTG ptg;

    const double TIME_STEP = 0.020; // Every simulator cycle is 20ms long, so the position points are
                                    // separated 20ms apart.
    const unsigned int UPDATE_RATE = 5;

    const double S_POS_STEP = 0.44; // The car will drive on every TIME_STEP (20 ms) 0.44 m if the speed 
                                          // is equal to 22 m/s (49.2126 MPH) so this is used as a standard value
                                          // to generate trajectories.

    const unsigned int TRAJ_LENGTH = 50;   // The standard generated trajectory has 100 points

    const double SPEED_LIMIT = 22.0;        // The speed limit is the end speed value used in order to generate trajectories
                                            // This value is in m/s and is equal to 49.2126 MPH

    const double DESIRED_ACC = 1.0;
    const double DESIRED_JERK = 2.0;
    const double DISTANCE_BUFFER = 30.0;

    const double MAX_ACCEL = 10.0;
    const double MAX_JERK = 10.0;

    unsigned int current_cycle; 

    double current_speed_s;
    double current_speed_d;
    double current_acc_s;
    double current_acc_d;
    unsigned int current_lane;
    double current_pos_s;

    double target_speed_xy;
    double current_speed_xy;
    double target_acc_xy;
    double current_acc_xy;
    

};

#endif // _EGO_VEHICLE_H_