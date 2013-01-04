//
// main.cpp 
// This sample code demonstrates how to use the C++ classes in order
// to determine satellite position and look angles.
//
// mfh 11/2010
//
#include "stdafx.h"

#include <iostream>
#include <fstream>

#include <stdio.h>
#include "cTLE.h"
#include "cEci.h"
#include "cOrbit.h"
#include "cSite.h"

#include "time.h"

#include "query_parser.h"


// 
// This namespace contains all the OrbitTools classes; be sure
// to include this namespace.
using namespace Zeptomoby::OrbitTools;


double DiffTimeMinutes(const cJulian &time1, const cJulian &time2)
{
	return time1.SpanMin(time2);
}


time_t AddTime(const time_t &time, const double minutes)
{
	cJulian time_julian(time);
	time_julian.AddMin(minutes);

	return time_julian.ToTime();
}

void TimeToStr(const time_t &time, char *str)
{
	struct tm *date;
	date = localtime(&time); 
	strftime(str, 255, "%Y-%m-%d %H:%M:%S", date);
}


void PrintOrbitsPlaneText(const cTle &tle, const double interval_minutes = 1.0, const double start_minutes = 0.0, const double terminal_minutes = 1440.0)
{
	std::cout << "# SATELITE:   " << tle.Name() << std::endl;
	std::cout << "# TLE LINE 1: " << tle.Line1() << std::endl;
	std::cout << "# TLE LINE 2: " << tle.Line2() << std::endl;

	// get cTLE parameters field
	// FLD_EPOCHYEAR, // Epoch: Last two digits of year
	// FLD_EPOCHDAY,  // Epoch: Fractional Julian Day of year
	double tle_year = tle.GetField(cTle::FLD_EPOCHYEAR) + 2000.0; // Add 2000 year
	double tle_day  = tle.GetField(cTle::FLD_EPOCHDAY);

	// Create TLE time (by Julian form)
	cJulian tle_julian(tle_year, tle_day);

	// Create current time
	time_t current_time = time(NULL);

	// Create current time (by Julian form)
	cJulian current_julian(current_time);

	// Calc differential minutes
	double diff = DiffTimeMinutes(current_julian, tle_julian);

	// Create an Orbit object using the SGP4 Tle object.
	cOrbit orbitSGP4(tle);

	// Calculate orbit data 
	// FROM current time TO current time + 1440 [min]
	for(double d = start_minutes; d<terminal_minutes; d=d+interval_minutes)
	{
		cGeoTime geo = orbitSGP4.GetPosition(diff+d).ToGeoTime();

		time_t result_time = AddTime(current_time, d);

		char str[256];
		TimeToStr(result_time, str);

		printf("%s %.6f %.6f\n", 
			str,
			geo.LatitudeDeg(),
			geo.LongitudeDeg()
			);
	}
	// */

}



void PrintOrbitsJSON(const cTle &tle, map<string, string> query, const double interval_minutes = 1.0, const double start_minutes = 0.0, const double terminal_minutes = 1440.0)
{
	printf("content-type: application/javascript; charset=UTF-8\n");
	printf("\n");    

	// get cTLE parameters field
	// FLD_EPOCHYEAR, // Epoch: Last two digits of year
	// FLD_EPOCHDAY,  // Epoch: Fractional Julian Day of year
	double tle_year = tle.GetField(cTle::FLD_EPOCHYEAR) + 2000.0; // Add 2000 year
	double tle_day  = tle.GetField(cTle::FLD_EPOCHDAY);

	// Create TLE time (by Julian form)
	cJulian tle_julian(tle_year, tle_day);

	// Create current time
	time_t current_time = time(NULL);

	// Create current time (by Julian form)
	cJulian current_julian(current_time);

	// Calc differential minutes
	double diff = DiffTimeMinutes(current_julian, tle_julian);

	// Create an Orbit object using the SGP4 Tle object.
	cOrbit orbitSGP4(tle);

	// Calculate orbit data 
	// FROM current time TO current time + 1440 [min]
	if( query["callback"].length() > 0 )
	{
		std::cout << query["callback"] << "(";
	}
	else
	{
		std::cout << "jsonp" << "(";
	}

	std::cout << "{" << std::endl;
	std::cout << "\"sateliteName\" : \""<< tle.Name() <<"\"," << std::endl;
	{
		char str[256];
		TimeToStr(current_time, str);
		std::cout << "\"currentDate\" : \"";
		printf("%s", str);
		std::cout << "\"," << std::endl;
	}


	std::cout << "\"intervalMinutes\" : \""<< interval_minutes << "\"," << std::endl;
	std::cout << "\"dataNum\" : \""<<  terminal_minutes / interval_minutes << "\"," << std::endl;
	std::cout << "\"tleLine1\" : \""+tle.Line1()+"\"," << std::endl;
	std::cout << "\"tleLine2\" : \""+tle.Line2()+"\"," << std::endl;
	std::cout << "\"algorithm\" : \""<< "SGP4" <<"\"," << std::endl;
	std::cout << "\"library\" : \""<< "OrbitTools (http://www.zeptomoby.com/satellites/)" <<"\"," << std::endl;

	std::cout << "\"orbits\" : [" << std::endl; 

	for(double d = start_minutes; d<terminal_minutes; d=d+interval_minutes)
	{

		cGeoTime geo = orbitSGP4.GetPosition(diff+d).ToGeoTime();

		time_t result_time = AddTime(current_time, d);

		char str[256];
		TimeToStr(result_time, str);

		printf("{\"date\" : \"%s\", \"latitude\" : \"%.6f\", \"longitude\" : \"%.6f\", \"altitude\" : \"%.6f\" }", 
			str,
			geo.LatitudeDeg(),
			geo.LongitudeDeg(),
			geo.AltitudeKm()
			);

		if(d+interval_minutes < terminal_minutes)
			printf(",");
		else
			printf("]");


		printf("\n");
	}
	//printf("]\n");
	printf("})\n");
}


//////////////////////////////////////////////////////////////////////////////
int main(int argc, char* argv[])
{
	// flag variables
	const int JSON_TEXT  = 1;
	const int PLANE_TEXT = 2; 


	std::string request_method;
	if( getenv( "REQUEST_METHOD" ) != NULL ){ 
		request_method = getenv( "REQUEST_METHOD" );  
	}


	std::map<string, string> query;


 	if ( request_method == "GET" )  
 	{
 		std::string query_string;    
 		if( getenv( "QUERY_STRING" ) != NULL ){ 			
	 		query_string = getenv( "QUERY_STRING" );  
	 		query = query_parser(query_string);
 		}
 	}

	// set flag
	int flag = JSON_TEXT;
	//int flag = PLANE_TEXT;

	// TWO LINE Elements (ISS at 2013/1/1)
	string satelite_name = "GOSAT (ISS)";
	string tle_line_1    = "1 25544U 98067A   13001.52012361  .00016717  00000-0  10270-3 0  9002";
	string tle_line_2    = "2 25544  51.6441 216.2888 0015668 109.9671 250.3170 15.51850049  8742";


	if( query["tleid"].length() > 0 )
	{
		std::string filename = "tle/"+query["tleid"]+".tle";
		ifstream ifs(filename.c_str());
		string line;

		if(ifs.fail()) {
			std::cerr << "Error: TLE File do not exist.\n";
			exit(0);
		}
		
		if(ifs && getline(ifs, line)) { satelite_name = line; }
		if(ifs && getline(ifs, line)) { tle_line_1    = line; }
		if(ifs && getline(ifs, line)) { tle_line_2    = line; }

		ifs.close();
	}
	else
	{
		ifstream ifs("tle/iss.tle");
		string line;

		if(ifs.fail()) {
			std::cerr << "Error: TLE File do not exist.\n";
			exit(0);
		}
		
		if(ifs && getline(ifs, line)) { satelite_name = line; }
		if(ifs && getline(ifs, line)) { tle_line_1    = line; }
		if(ifs && getline(ifs, line)) { tle_line_2    = line; }

		ifs.close();
	}


// /*
	// Create TLE data
	cTle tle(satelite_name, tle_line_1, tle_line_2);

	switch(flag)
	{
	case PLANE_TEXT:
		// Print Orbits data
		PrintOrbitsPlaneText(tle, 1.0, 0.0, 1440.0);
		break;

	case JSON_TEXT:
		// Print Orbits data (JSON)
		PrintOrbitsJSON(tle, query, 0.2, 0.0, 60.0);
		break;
	}
// */
}


