//
//  HijriDate.h
//  date conversion
//
//  Created by Sami ur Rahman Qazi on 03/02/2013.
//

#ifndef __date_conversion__HijriDate__
#define __date_conversion__HijriDate__

extern const char* HijriDayName[];
extern const char* HijriMonthName[];

class HijriDate {
private:
	int year;   // 1...
	int month;  // 1..13 (12 in a common year)
	int day;    // 1..lastDayOfMonth(month,year)
	
public:
    HijriDate() : day(1), month(1), year(1) { }
	HijriDate(int d, int m, int y) : day(d), month(m), year(y) { }
	
	// Computes the Islamic date from the absolute date.
	explicit HijriDate(int jdn);

	virtual ~HijriDate() { }

	// Computes the absolute date from the Islamic date.
	operator int();
        
	// True if year is an Islamic leap year
	bool isLeapYear() const {return isLeapYear(year);}
    
    void calendar() const {calendar(month, year);}
    
	// Last day in month during year on the Islamic calendar.
	int LastDayOfMonth() const { return LastDayOfMonth(month, year);}
	
	int getDay() const { return day; }
	int getMonth() const { return month; }
	int getYear() const { return year; }
    
    // static functions
    static void calendar(int m, int y);
	static bool isLeapYear(int y);
	static int LastDayOfMonth(int m, int y);
};

std::ostream& operator<<(std::ostream& os, const HijriDate& d);

#endif /* defined(__date_conversion__HijriDate__) */
