// HW_2.cpp : Defines the entry point for the application.

#include "HW_2.h"
#include <iostream>
#include <map>
#include <string>
#include <random>
#include <chrono>
#include <thread>
#include <vector>
#include "HW2_Visualizer.h" //Question 8
#include "Plane.h"


using namespace std;

//Making distance map in main() backwards compatible (turns out, not necessary)
/*struct AirportLocator {
	bool operator() (const pair <string, string>& a, const pair<string, string>& b) const {
		return a.first < b.first || (a.first == b.first && a.second < b.second);
	}
};*/

//Question 2 and 3
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
		
		pair<string, string> airportpair = make_pair(origin, destination);
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
	
	//Flowchart Question 3
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

	void setWaitTime(double newWaitTime) { 
		wait_time = newWaitTime;
	}
		

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
		return "GA";
	}

	//Random number generator returning a random number from a normal distribution Question3 
	static double draw_from_normal_dist(double mean, double standard_deviation) {
		random_device rd;
		mt19937 gen{ rd() };
		normal_distribution<double> d{ mean, standard_deviation };
		return d(gen);
	}
};

//Question 4
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

//Question 4
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

//Question 6
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

		//Flowchart Question 6		
		while (i < registered_planes.size())
		{
			landed_planes += registered_planes[i]->getat_SCE();
			i++;
		}
		if (landed_planes >= MAX_LANDED_PLANE_NUM)
		{
			i = 0;
			if (i < registered_planes.size())
				for (; i < registered_planes.size(); i++) {
					registered_planes[i];
					Plane* plane = registered_planes[i];
					if (plane->getat_SCE() == 0 && plane->distance_to_SCE() <= AIRSPACE_DISTANCE && plane->getloiter() == 0) {
						plane->setLoiterTime(100);
					}
				}
		}		
	}
};
	
int main(int argc, char** argv)//Question 8
{
	//Question 8/
	HW2_VIZ viz;	
	
	//Container for flight distance storage Question 1
	map<pair<string, string>, int> Flight_Distance;
	
	//Defining flight distances Question 1
	Flight_Distance[make_pair("SCE", "PHL")] = 160;//miles
	Flight_Distance[make_pair("SCE", "ORD")] = 640;//miles
	Flight_Distance[make_pair("SCE", "EWR")] = 220;//miles
	
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

	//Set the speed of each airplane according to the table Question 5
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

	//Question 7
	ATC atc;
	atc.register_plane(AA1);
	atc.register_plane(AA2);
	atc.register_plane(UA1);
	atc.register_plane(UA2);
	atc.register_plane(GA1);
	atc.register_plane(GA2);
	atc.register_plane(GA3);

	double timeStep = 10;
	
	//Question 5 and 7
	while (true) {
		
		AA1.operate(timeStep);;
		AA2.operate(timeStep);
		UA1.operate(timeStep);
		UA2.operate(timeStep);
		GA1.operate(timeStep);
		GA2.operate(timeStep);
		GA3.operate(timeStep);

		//Question 7
		atc.control_traffic();

		//Question 8
		viz.visualize_plane(AA1.plane_type(), AA1.getorigin(), AA1.getdestination(), AA1.getpos());

		//Positions of all airplanes at each time step
		cout << "AA1 Position: " << AA1.getpos() << " miles" << endl;
		cout << "AA2 Position: " << AA2.getpos() << " miles" << endl;
		cout << "UA1 Position: " << UA1.getpos() << " miles" << endl;
		cout << "UA2 Position: " << UA2.getpos() << " miles" << endl;
		cout << "GA1 Position: " << GA1.getpos() << " miles" << endl;
		cout << "GA2 Position: " << GA2.getpos() << " miles" << endl;
		cout << "GA3 Position: " << GA3.getpos() << " miles" << endl;

		//Pauser
		//this_thread::sleep_for(chrono::milliseconds(1000));

		//Question 8
		viz.update(10);
	}

	return 0;
}
