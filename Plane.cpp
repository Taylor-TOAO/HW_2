#include <iostream>
#include <map>
#include <string>
#include <random>
#include "Plane.h"

using namespace std;

class Plane {
protected:
	double wait_time;
private:
	double pos, vel, distance, loiter_time;
	bool at_SCE;
	string origin, destination;
	map<pair<string, string>, int> Flight_Distance;
public:
	//Constructor
	Plane(const string& from, const string& to) : origin(from), destination(to) {

		auto it = Flight_Distance.find(std::make_pair(from, to));

		if (it != Flight_Distance.end()) {
			distance = it->second;
		}
		else {
			std::cerr << "Error: Flight distance not found for " << from << " to " << to << std::endl;
			distance = 0; // Set a default value or handle the error as needed.
		}

		pos = 0;
		vel = 0;
		loiter_time = 0;
		at_SCE = true;
	}

	//Virtual deconstructor
	virtual ~Plane() {}

	void operate(double dt) {
		if (loiter_time != 0)
			loiter_time -= dt;
		else if (wait_time != 0)
			wait_time -= dt;
		else if (pos < distance) {
			pos += vel * dt;
			at_SCE = false;
		}
		else if (destination == "SCE") {
			at_SCE = true;
			double ground_time = time_on_ground();
			pos = 0;
		}
		else {
			swap(origin, destination);
			pos = 0;
		}

	}
	double getpos() {
		return pos;
	}
	double getvel() const {
		return vel;
	}
	double getloiter() const {
		return loiter_time;
	}
	string getorigin() const {
		return origin;
	}
	string getdestination() const {
		return destination;
	}
	bool getat_SCE() const {
		return at_SCE;
	}

	void setVel(double newVel) {
		vel = newVel;
	}

	void setLoiterTime(double newLoiterTime) {
		loiter_time = newLoiterTime;
	}

	//Original distance_to_SCE function from problem 2
	/*double distance_to_SCE() {
		if (at_SCE) {
			return 0;
		}
		else {
			//Using Question 1 to calculate the distance to SCE.
			auto it = Flight_Distance.find(std::make_pair(origin, "SCE"));
			if (it != Flight_Distance.end()) {
				return it->second;
			}
			else {
				//Handles the case where the distance is not found.
				return 0;
			}
		}
	}*/

	//New distance_to_SCE function for problem 3
	double distance_to_SCE() {
		if (destination == "SCE") {
			double diff = distance - pos;
			if (diff < 0) diff = 0;
			return diff;
		}
		else {
			return 0;
		}
	}

	virtual double time_on_ground() {
		return 0;
	}
	virtual string plane_type() {
		return "GA";//Returns General Aviation
	}

	//Random number generator returning a random number from a normal distribution
	static double draw_from_normal_dist(double mean, double standard_deviation) {
		random_device rd;
		mt19937 gen{ rd() };
		normal_distribution<double> d{ mean, standard_deviation };
		return d(gen);
	}
};