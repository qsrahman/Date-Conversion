//
//  GregorianDate.cpp
//  date conversion
//
//  Created by Sami ur Rahman Qazi on 03/02/2013.
//

#include <iostream>
#include <iomanip>
#include <ctime>
#include "GregorianDate.h"

const char* GregorianDayName[] = {
                            "Sunday", "Monday", "Tuesday", "Wednesday",
                            "Thursday", "Friday", "Saturday"
                        };

const char* GregorianMonthName[] = {
                            "January", "February", "March", "April",
                            "May", "June", "July", "August",
                            "September", "October", "November", "December"
                          };

// Default constructor
GregorianDate::GregorianDate()
{
    long time_val;
    struct tm *dt;
    
	time((time_t *)&time_val);
	dt = localtime((time_t *)&time_val);
    
	day = dt->tm_mday;
	month = dt->tm_mon + 1;
	year = dt->tm_year + 1900;
}

GregorianDate::GregorianDate(const tm& dt)
{
    day		= dt.tm_mday;
    month	= dt.tm_mon + 1;
    year	= dt.tm_year + 1900;
}

const int GregorianEpoch = 1721425;

// Computes the Gregorian date from the absolute date.
GregorianDate::GregorianDate(int d)
{    
    // Search forward year by year from approximate year
//    year = (d - GregorianEpoch) / 366;
    year = d / 366;
    while (d >= GregorianDate(1, 1, year + 1))
        year++;

    // Search forward month by month from January
    month = 1;
    while (d > GregorianDate(lastDayOfMonth(), month, year))
        month++;

    day = d - GregorianDate(1, month, year) + 1;
}

// Computes the absolute date from the Gregorian date.
// "Absolute date" means the number of days elapsed since the Gregorian date
// Sunday, December 31, 1 BC. (Since there was no year 0, the year following
// 1 BC is 1 AD.) Thus the Gregorian date January 1, 1 AD is absolute date number 1.
GregorianDate::operator int()
{
	static int DaysSoFar[] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365};
    	
	// days this month
    int JDN = day;
    
	// add days in prior months this year
	JDN += DaysSoFar[month - 1] + (isLeapYear() ? 1 : 0);

//    for (int m = month - 1; m > 0; m--) // days in prior months this year
//        JDN += lastDayOfMonth(m, year);

    return
        (JDN                    // days this year
         + 365 * (year - 1)   // days in previous years ignoring leap days
         + (year - 1)/4       // Julian leap days before this year...
         - (year - 1)/100     // ...minus prior century years...
         + (year - 1)/400);   // ...plus prior years divisible by 400
//         + GregorianEpoch);
}

bool GregorianDate::isLeapYear(int y)
{
    return  ((y >= 1582) ?
            ((y % 4 == 0  &&  y % 100 != 0)  ||  (y % 400 == 0) ):
             (y % 4 == 0) );
}

// Compute the last date of the month for the Gregorian calendar.
int GregorianDate::lastDayOfMonth(int m, int y)
{
	switch (m) {
		case 2: return ((((y % 4) == 0) && ((y % 100) != 0)) || ((y % 400) == 0)) ? 29 : 28;
		case 4:
		case 6:
		case 9:
		case 11: return 30;
		default: return 31;
	}
}

// print month calendar
void GregorianDate::calendar(int m, int y)
{
	int cal[6][7] = {0};
        
    std::cout << "\n\t\t"
              << GregorianMonthName[m - 1] << " "
              << y << " C.E" << std::endl;
    
    int dow = GregorianDate(1, m, y) % 7;
    int ldm = lastDayOfMonth(m, y);
    
    int d = 1;
    for (int c = dow; c < 7; c++) {
        cal[0][c] = d++;
    }
    for (int r = 1; r < 6; r++) {
        for (int c = 0; c < 7 && d <= ldm; c++) {
            cal[r][c] = d++;
        }
    }
    
    std::cout << "\n\tSun\tMon\tThu\tWed\tThr\tFri\tSat" << std::endl;
    for (int r = 0; r < 6; r++) {
        for (int c = 0; c < 7; c++) {
            if (cal[r][c]) {
                std::cout << "\t" << std::setw(2) << cal[r][c];
            }
            else {
                std::cout << "\t";
            }
        }
        std::cout << std::endl;
    }    
}

std::ostream& operator<<(std::ostream& os, const GregorianDate& d)
{
    os << std::setfill('0');
	os << std::setw(2) << d.getDay() << "/"
       << std::setw(2) << d.getMonth() << "/"
       << std::setw(4) << d.getYear();

	return os;
}
