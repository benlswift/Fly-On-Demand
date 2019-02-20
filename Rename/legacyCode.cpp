// Rename.cpp : Defines the entry point for the console application.
//
//Author: Ben Swift
//FLY FM Mixcloud Uploader

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <time.h>
#include <string>

using namespace std;
void scriptWriter(string,int,string,string,string);
string getDay(int);
string getName(string,string,string,string);
string corrections(string);
string stationName = "FLYFM";
string audioFilePath = "../Logged\\ Audio"; 
//audio files must be in audioFilePath/year/month/day/show.mp3
string scheduleFilePath = "E:\\schedule files";
int main()
{
	bool hasRun = false;
	while (1) {
		time_t theTime = time(NULL);
		struct tm *aTime = localtime(&theTime);
		string name;
		string date;
		string fly;
		string time;
		string filename;
		int day = aTime->tm_mday;
		int month = aTime->tm_mon + 1; // Month is 0 – 11
		int year = aTime->tm_year + 1900; // Year is # years since 1900
		int hour = aTime->tm_hour;
		int min = aTime->tm_min;
		int dayOfWeek = aTime->tm_wday;
		string theDay = std::to_string(day);
		string theMonth = std::to_string(month);
		string theYear = std::to_string(year);
		string theHour = std::to_string(hour - 1);
		string dayName = getDay(dayOfWeek);
		cout << "Mixcloud Uploader running..." << endl;
		theDay = corrections(theDay);
		theMonth = corrections(theMonth);
		theHour = corrections(theHour);
		date = theDay + theMonth + theYear;
		//fly = "-FLYFM-";
		//time = theHour + "00";
		name = theHour + "00" + "-" + stationName + "-" + date + ".mp3";
		filename = audioFilePath + "/" + theYear + "/" + theMonth + "/" + theDay + "/" + name;
		//cout << filename << endl;
		//bool textOut = false;
		if (hour > 10 && hour < 22) {
			if (min == 02 && hasRun == false) {
				scriptWriter(filename, dayOfWeek, theHour, theMonth, theDay);
				system("upload.sh");
				cout << "Show uploaded" << endl;
				hasRun = true;
			}


			else if (min != 02)
			{
				//if (hasRun == false)
				//{
				cout << "Mixcloud Uploader... waiting..." << endl;
				hasRun = false;
				//}
			}
		}
			//bool t = false;
			else
			{
				//if (t == false)
				//{
				cout << "Mixcloud Uploader... sleeping" << endl;
				hasRun = true;
				//}
			}
		
	}
    return 0;
}

void scriptWriter(string filename, int dayOfWeek,string hour,string month, string day)
{
	ofstream script;
	script.open("upload.sh");
	script << "curl -F mp3=@" << filename <<" \\\n";//add in slashes at end
	script << "\t " << getName(getDay(dayOfWeek),hour,month,day) << "\n";
	/*script << "\t -F \"tags-0-tag=Test\" \\\n";
	script << "\t -F \"tags-1-tag=API\" \\\n";
    script << "\t -F \"sections-0-chapter=Introduction\" \\\n";
    script << "\t -F \"sections-0-start_time=0\" \\\n";
    script << "\t -F \"sections-1-zartist=Artist Name\" \\\n";
	script << "\t -F \"sections-1-song=Song Title\" \\\n";
	script << "\t -F \"sections-1-start_time=10\" \\\n";
	script << "\t -F \"description=My test upload\" \\\n";*/
	script << "\t https://api.mixcloud.com//upload/?access_token=qKz48A8ht5UQZsrK5kWVtLr59ppvsxF7";
}

string getDay(int dayOfWeek)
{
	string day;
	switch (dayOfWeek) {
	case 1: day = "Monday";
		break;       
	case 2: day = "Tuesday";
		break;
	case 3: day = "Wednesday";
		break;
	case 4: day = "Thursday";
		break;
	case 5: day = "Friday";
		break;
	case 6: day = "Saturday";
		break;
	case 0: day = "Sunday";
		break;
	}
	return day;
}

string getName(string day, string time,string theMonth,string theDay)
{
	//-F "name=API Upload" \ 
	string filepath = scheduleFilePath + "/" + day + ".txt";
	ifstream schedule(filepath);
	string name;
	string showName;
	while (schedule)
	{
		getline(schedule, name);
		if (name == time)
		{
			getline(schedule, name);
			cout << name << endl;
			break;
		}
	}

	showName = "-F \"name=" + name + " " + theDay + "\\" + theMonth +  "\" \\";
	return showName;
}

string corrections(string dayOrMonth) {
	//int n = stoi(dayOrMonth);
	//while (n < 10)
	//{
	//	dayOrMonth = "0" + dayOrMonth;
	//}
	if (dayOrMonth == "1")
	{
		//dayOrMonth = "0" + dayOrMonth; //use this instead
		dayOrMonth = "01";
	}
	else if (dayOrMonth == "2")
	{
		dayOrMonth = "02";
	}
	else if (dayOrMonth == "3")
	{
		dayOrMonth = "03";
	}
	else if (dayOrMonth == "4")
	{
		dayOrMonth = "04";
	}
	else if (dayOrMonth == "5")
	{
		dayOrMonth = "05";
	}
	else if (dayOrMonth == "6")
	{
		dayOrMonth = "06";
	}
	else if (dayOrMonth == "7")
	{
		dayOrMonth = "07";
	}
	else if (dayOrMonth == "8")
	{
		dayOrMonth = "08";
	}
	else if (dayOrMonth == "9")
	{
		dayOrMonth = "09";
	}
	return dayOrMonth;
}

bool runTime()
{
	int nextTrigger = 0;
	return false;
}
