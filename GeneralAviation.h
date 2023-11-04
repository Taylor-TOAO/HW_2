#ifndef PLANE_H
#define PLANE_H

#include <iostream>
#include <map>
#include <string>
#include <random>
#include "Plane.h"
#include "Plane.cpp"


using namespace std;

class GeneralAviation : public Plane {
public:
	//Constructor
	GeneralAviation(const string& from, const string& to) : Plane(from, to) {}

	//Virtual deconstructor
	virtual ~GeneralAviation() {}

	virtual double time_on_ground(double m, double sd);
	}
};

#endif