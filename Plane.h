/*#ifndef PLANE_H
#define PLANE_H

#include <iostream>
#include <map>
#include <string>
#include <random>


using namespace std;

class Plane {
private:
    double wait_time;
    double pos;
    double vel;
    double distance;
    double loiter_time;
    bool at_SCE;
    string origin;
    string destination;
public:
    //Constructor
    Plane(const string& from, const string& to);

    //Virtual deconstructor
    virtual ~Plane();

    //Members
    void operate(double dt);
    double getPos() const;
    double getVel() const;
    double getLoiterTime() const;
    string getOrigin() const;
    string getDestination() const;
    bool getAtSCE() const;
    void setVel(double newVel);
    void setLoiterTime(double newLoiterTime);
    double distance_to_SCE();
    virtual double time_on_ground();
    virtual string plane_type();
    static double draw_from_normal_dist(double m, double sd);

};

#endif*/