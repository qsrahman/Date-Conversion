//
//  GregorianDate.h
//  date conversion
//
//  Created by Sami ur Rahman Qazi on 03/02/2013.
//

#ifndef __date_conversion__GregorianDate__
#define __date_conversion__GregorianDate__

extern const char* GregorianDayName[];
extern const char* GregorianMonthName[];

class GregorianDate {
private:
	int year;   // 1...
	int month;  // 1 == January, ..., 12 == December
	int day;    // 1..lastDayOfMonth(month, year)
    	    
public:
	GregorianDate();
    GregorianDate (const tm& dt);
	explicit GregorianDate(int j);
	GregorianDate(int d, int m, int y) : day(d), month(m), year(y) { }

	virtual ~GregorianDate() { }
    
	operator int();
    
    GregorianDate operator++();
	GregorianDate operator++(int);
    
	GregorianDate operator--();
	GregorianDate operator--(int);

    void calendar() const {calendar(month, year);}
    bool isLeapYear() const { return isLeapYear(year);}
	bool isValid() const {return isValid(day, month, year);}

    int lastDayOfMonth() const { return lastDayOfMonth(month, year);}
    
	int getDay() const { return day; }
	int getMonth() const { return month; }
	int getYear() const { return year; }
    
    // static class functions
    static void calendar(int m, int y);
    static bool isLeapYear(int y);
	static bool isValid(int d, int m, int y);
    static int lastDayOfMonth(int m, int y);
};

std::ostream& operator<<(std::ostream& os, const GregorianDate& d);

#endif /* defined(__date_conversion__GregorianDate__) */
