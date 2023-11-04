#ifndef AIRPLANE_H
#define AIRPLANE_H

#include <iostream>
#include <map>
#include <string>
#include <random>
#include "Plane.h"

using namespace std;

class Airliner : public Plane { //making inherited class public to draw from public members defined in question 2
private:
	string Airline;
public:
	//Constructor
	Airliner(const string& Airline, const string& from, const string& to) : Airline(Airline), Plane(from, to) {}

	//Virtual deconstructor
	virtual ~Airliner() {}

	virtual string plane_type();
	

	virtual double time_on_ground(double , double sd);
	
};

#endif