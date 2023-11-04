#include "HW_2.h"
#include <iostream>
#include <map>
#include <string>
#include <random>
#include "Plane.h"
#include "Plane.cpp"
#include "Airplane.h"
#include "Airplane.cpp"
#include "GeneralAviation.h"

using namespace std;


class GeneralAviation : public Plane {
public:
	//Constructor
	GeneralAviation(const string& from, const string& to) : Plane(from, to) {}

	//Virtual deconstructor
	virtual ~GeneralAviation() {}

	virtual double time_on_ground() override {
		return draw_from_normal_dist(600, 60);
	}
};