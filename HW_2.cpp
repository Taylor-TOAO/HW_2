// HW_2.cpp : Defines the entry point for the application.
//

#include "HW_2.h"
#include <iostream>
#include <map>
#include <string>
#include <random>

using namespace std;

//Making distnace map in main() backwards compatible
/*struct AirportLocator {
	bool operator() (const pair <string, string>& a, const pair<string, string>& b) const {
		return a.first < b.first || (a.first == b.first && a.second < b.second);
	}
};*/

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
class Airliner : public Plane { //making inherited class public to draw from public members defined in question 2
private:
	string Airline;
public:
	//Constructor
	Airliner(const string& Airline, const string& from, const string& to) : Airline(Airline), Plane(from, to)  {}

	//Virtual deconstructor
	virtual ~Airliner() {}

	virtual string plane_type() override {
		return Airline;
	}

	virtual double time_on_ground() override {
		return draw_from_normal_dist(1800, 600);
	}
};

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

int main()
{
	//Container to for flight distance storage
	map<pair<string, string>, int> Flight_Distance;
	
	//Defining flight distances
	Flight_Distance[make_pair("SCE", "PHL")] = 160;//miles
	Flight_Distance[make_pair("SCE", "ORD")] = 640;//miles
	Flight_Distance[make_pair("SCE", "EWR")] = 220;//miles
	//Flight_Distance[make_pair("PHL", "SCE")] = 160;//miles
	//Flight_Distance[make_pair("ORD", "SCE")] = 640;//miles
	//Flight_Distance[make_pair("EWR", "SCE")] = 220;//miles

	
	//User input for test
	cout << "Please input the desired starting desitination: " << endl;
	string Start_Airport;
	cin >> Start_Airport;
	cout << "Please input the desired destination: " << endl;
	string Destination;
	cin >> Destination;

	
	//Backwards compatible. As I kept doing HW, found out it wasn't necessary....
	/*int distance = 0;
	auto forward_distance = Flight_Distance.find(make_pair(Start_Airport, Destination));
	auto reverse_distance = Flight_Distance.find(make_pair(Destination, Start_Airport));

	if (forward_distance != Flight_Distance.end()) {
		distance = forward_distance->second;
	}
	else if (reverse_distance != Flight_Distance.end()) {
		distance = reverse_distance->second;
	}
	else {
		cout << "Flight distance unknown." << endl;
	}

	cout << "The flight distance between " << Start_Airport << " and " << Destination << " is " << distance << " miles." << endl;*/





	//Testing conditions for Question 1
	if (Flight_Distance.find(make_pair(Start_Airport, Destination)) != Flight_Distance.end()) {
		int distance = Flight_Distance[make_pair(Start_Airport, Destination)];
		cout << "The flight distance between " << Start_Airport << " and " << Destination << " is " << distance << " miles." << endl;
	}
	else {
		cout << "Flight distance unknown." << endl;
	}

	return 0;
}
