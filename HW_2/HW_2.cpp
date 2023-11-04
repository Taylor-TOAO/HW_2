// HW_2.cpp : Defines the entry point for the application.
//

#include "HW_2.h"
#include <iostream>
#include <map>
#include <string>

using namespace std;

//Making map in main() backwards compatible
struct AirportLocator {
	bool operator() (const pair <string, string>& a, const pair<string, string>& b) const {
		return a.first < b.first || (a.first == b.first && a.second < b.second);
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

	int distance = 0;
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

	cout << "The flight distance between " << Start_Airport << " and " << Destination << " is " << distance << " miles." << endl;





	/*//Testing conditions
	if (Flight_Distance.find(make_pair(Start_Airport, Destination)) != Flight_Distance.end()) {
		int distance = Flight_Distance[make_pair(Start_Airport, Destination)];
		cout << "The flight distance between " << Start_Airport << " and " << Destination << " is " << distance << " miles." << endl;
	}
	else {
		cout << "Flight distance unknown." << endl;
	}*/

	return 0;
}
