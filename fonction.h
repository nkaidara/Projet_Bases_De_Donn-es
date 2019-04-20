#ifndef FONCTION_H_INCLUDED
#define FONCTION_H_INCLUDED
static const int daysInMonth[] = {
  31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
  };


static const int referenceYearFirstDays[] = {
  0, 3, 3, 6, 1, 4, 6, 2, 5, 0, 3, 5
};


static const int firstDayOfMonth = 1;

static const int referenceYear = 1703;



int allCharsDigit(const char * const s);
int isDivisible(const int year, const int i);
int testLeapYear(const int year);
int countLeapYears(const int startYear, const int endYear, int * const isLeapYear);
int printMonth(int month, int year, int offset, int isLeapYear);
int get_offset(int month, int year);





#endif // FONCTION_H_INCLUDED
