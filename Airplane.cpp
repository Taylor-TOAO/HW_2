#include <iostream>
#include <map>
#include <string>
#include <random>
#include "Plane.h"
#include "Airplane.h"
#include "GeneralAviation.h"
#include "GeneralAviation.cpp"

using namespace std;

class Airliner : public Plane { //making inherited class public to draw from public members defined in question 2
private:
	string Airline;
public:
	//Constructor
	Airliner(const string& Airline, const string& from, const string& to) : Airline(Airline), Plane(from, to) {}

	//Virtual deconstructor
	virtual ~Airliner() {}

	virtual string plane_type() override {
		return Airline;
	}

	virtual double time_on_ground() override {
		return draw_from_normal_dist(1800, 600);
	}
};