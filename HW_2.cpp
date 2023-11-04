// HW_2.cpp : Defines the entry point for the application.
//

#include "HW_2.h"
#include <iostream>
#include <map>
#include <string>
#include <random>
#include <chrono>
#include <thread>
//#include "Plane.h"
//#include "Plane.cpp"
//#include "Airplane.h"
//#include "Airplane.cpp"
//#include "GeneralAviation.h"
//#include "GeneralAviation.cpp"

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
		
		pair<string, string> airportpair = make_pair(origin, destination);//not sure if origin, destination is inside argument or from/to
		Flight_Distance[make_pair("SCE", "PHL")] = 160;
		Flight_Distance[make_pair("SCE", "ORD")] = 640;
		Flight_Distance[make_pair("SCE", "EWR")] = 220;
		distance = Flight_Distance[airportpair];
		

		pos = 0;
		vel = 0;
		loiter_time = 0;
		wait_time = 0;
		at_SCE = true;
	}

	//Virtual deconstructor
	virtual ~Plane() {}
	
	void operate(double dt) {
		
		if (loiter_time != 0) {
			loiter_time -= dt;
		}
		else if (wait_time != 0) {
			wait_time -= dt;
		}
		else if (pos < distance) {
			pos += vel * dt;
			at_SCE = false;
		}
		else if (destination == "SCE") {
			at_SCE = true;
			double ground_time = time_on_ground();
			pos = 0;
			if (destination != "SCE") {
				swap(origin, destination);
				ground_time = time_on_ground(); 
				pos = 0;
			}
		}
		else {
			swap(origin, destination);
			pos = 0;
			double ground_time = time_on_ground();
			if (destination == "SCE") {
				at_SCE = true;
				ground_time = time_on_ground();
				pos = 0;
			}
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

	void setWaitTime(double newWaitTime) { //wasn't included but I am pretty sure it is needed
		wait_time = newWaitTime;
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
		if (Plane::destination == "SCE") {
			double diff = distance - Plane::pos;
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

class ATC {
private:
	vector<Plane*> registered_planes;
	const int MAX_LANDED_PLANE_NUM = 2;
	const int AIRSPACE_DISTANCE = 50;

public:
	//Constructor
	ATC() : MAX_LANDED_PLANE_NUM(2), AIRSPACE_DISTANCE(50) {}

	//Deconstructor
	~ATC() {}

	void register_plane(Plane& plane) {
		registered_planes.push_back(&plane);
	}

	//Air traffic control function
	void control_traffic() {
		int landed_planes = 0;
		int i = 0;

		//Stuck here on flowchart in Question 6
		/*
		while (i < registered_planes.size())
		{
			landed_planes += registered_planes[i]->at_SCE;
			i++;
		}
		if (landed_planes >= MAX_LANDED_PLANE_NUM)
		{
			i = 0;
			if (i < registered_planes.size())
				for()
		}
		else if
			break;*/
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

	
	//User input for test, Problem 1
	/*cout << "Please input the desired starting desitination: " << endl;
	string Start_Airport;
	cin >> Start_Airport;
	cout << "Please input the desired destination: " << endl;
	string Destination;
	cin >> Destination;*/

	
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

	//Instantiate seven objects representing aircraft
	Airliner AA1("AA", "SCE", "PHL");
	Airliner AA2("AA", "SCE", "ORD");
	Airliner UA1("UA", "SCE", "ORD");
	Airliner UA2("UA", "SCE", "EWR");
	GeneralAviation GA1("SCE", "PHL");
	GeneralAviation GA2("SCE", "EWR");
	GeneralAviation GA3("SCE", "ORD");

	//Set the speed of each airplane according to the table
	AA1.setVel(470);
	AA2.setVel(500);
	UA1.setVel(515);
	UA2.setVel(480);
	GA1.setVel(140);
	GA2.setVel(160);
	GA3.setVel(180);

	AA1.setLoiterTime(0);
	AA2.setLoiterTime(0);
	UA1.setLoiterTime(0);
	UA2.setLoiterTime(0);
	GA1.setLoiterTime(0);
	GA2.setLoiterTime(0);
	GA3.setLoiterTime(0);

	AA1.setWaitTime(0);
	AA2.setWaitTime(0);
	UA1.setWaitTime(0);
	UA2.setWaitTime(0);
	GA1.setWaitTime(0);
	GA2.setWaitTime(0);
	GA3.setWaitTime(0);
	

	double timeStep = 0.3;

	while (true) {
		
		AA1.operate(timeStep);
		AA2.operate(timeStep);
		UA1.operate(timeStep);
		UA2.operate(timeStep);
		GA1.operate(timeStep);
		GA2.operate(timeStep);
		GA3.operate(timeStep);

		//Positions of all airplanes at each time step
		cout << "AA1 Position: " << AA1.getpos() << " miles" << endl;
		cout << "AA2 Position: " << AA2.getpos() << " miles" << endl;
		cout << "UA1 Position: " << UA1.getpos() << " miles" << endl;
		cout << "UA2 Position: " << UA2.getpos() << " miles" << endl;
		cout << "GA1 Position: " << GA1.getpos() << " miles" << endl;
		cout << "GA2 Position: " << GA2.getpos() << " miles" << endl;
		cout << "GA3 Position: " << GA3.getpos() << " miles" << endl;

		//Pauser
		this_thread::sleep_for(chrono::milliseconds(1000));
	}



	//Testing conditions for Question 1
	/*if (Flight_Distance.find(make_pair(Start_Airport, Destination)) != Flight_Distance.end()) {
		int distance = Flight_Distance[make_pair(Start_Airport, Destination)];
		cout << "The flight distance between " << Start_Airport << " and " << Destination << " is " << distance << " miles." << endl;
	}
	else {
		cout << "Flight distance unknown." << endl;
	}*/

	return 0;
}
