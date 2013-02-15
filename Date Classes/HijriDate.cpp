//
//  HijriDate.cpp
//  date conversion
//
//  Created by Sami ur Rahman Qazi on 03/02/2013.
//

#include <iostream>
#include <iomanip>
#include "HijriDate.h"

const char* HijriDayName[] = {
                "Yaumul Ahad", "Yaumul Ithnain", " Yaumu Zulatha", " Yaumul Arbi'a",
                "Yaumul Khamees", "Yaumul Jumma", "Yaumu Sabt"
              };

const char* HijriMonthName[] = {
                    "Muharram", "Safar", "Rabi` ul-Awal", "Rabi` ul-Thaani",
                    "Jumaada ul-Awal", "Jumaada ul-Thaani", "Rajab", "Sha`ban",
                    "Ramadan", "Shawwal", "Zul al-Qi`dah", "Zul al-Hijjah"
                 };

// Absolute date of start of Islamic calendar
// 19 Jul 622 C.E or 16 July 622 (Julian Calendar) = 1 Muharram 1 A.H.
// JDN = 1948439.5

//const int HijriEpoch = 1948440;
const int HijriEpoch = 227014;

// Computes the Hijri date from the absolute date.
HijriDate::HijriDate(int d)
{
    if (d <= HijriEpoch) { // Date is pre-Hijri
        month = 0;
        day = 0;
        year = 0;
    }
    else {
        // Search forward year by year from approximate year
        year = (d - HijriEpoch) / 355;
        while (d >= HijriDate(1, 1, year + 1))
            year++;
        // Search forward month by month from Muharram
        month = 1;
        while (d > HijriDate(LastDayOfMonth(), month, year))
            month++;
        day = d - HijriDate(1, month, year) + 1;
    }
}

// Computes the absolute date from the Hijri date.
HijriDate::operator int()
{
    return (day                      // days so far this month
            + 29 * (month - 1)       // days so far...
            + month/2                //            ...this year
            + 354 * (year - 1)       // non-leap days in prior years
            + (3 + (11 * year)) / 30 // leap days in prior years
            + HijriEpoch);         // days before start of calendar
}

// True if year is an Hijri leap year
bool HijriDate::isLeapYear(int y)
{
    return ((((11 * y) + 14) % 30) < 11) ? true : false;
}

// Last day in month during year on the Hijri calendar.
int HijriDate::LastDayOfMonth(int m, int y)
{
    return (((m % 2) == 1) || ((m == 12) && isLeapYear(y))) ? 30 : 29;
}

void HijriDate::calendar(int m, int y)
{
	int cal[6][7] = {0};
    
    std::cout << "\n\t\t"
              << HijriMonthName[m - 1] << " "
              << y << " A.H" << std::endl;
    
    int dow = HijriDate(1, m, y) % 7;
    int ldm = LastDayOfMonth(m, y);
    
    int d = 1;
    for (int c = dow; c < 7; c++) {
        cal[0][c] = d++;
    }
    for (int r = 1; r < 6; r++) {
        for (int c = 0; c < 7 && d <= ldm; c++) {
            cal[r][c] = d++;
        }
    }
    
    std::cout << "\n\tAhd\tIth\tZul\tArb\tKha\tJum\tSab" << std::endl;
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

std::ostream& operator<<(std::ostream& os, const HijriDate& d)
{
    os << std::setfill('0');
	os << std::setw(2) << d.getDay() << "/"
       << std::setw(2) << d.getMonth() << "/"
       << std::setw(4) << d.getYear();

	return os;
}
