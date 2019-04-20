#include "fonction.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdarg.h>



 int allCharsDigit(const char * const s)
{
  const char * c;

  for (c = s; *c != '\0'; c++) {
    if (isspace(*c)) {
      continue;
    }

    if (!isdigit(*c)) {
      return 0;
    }
  }

  return 1;
}


 int isDivisible(const int year, const int i)
{
  return (year % i) == 0;
}

 int testLeapYear(const int year)
{
  return (isDivisible(year, 4) && !isDivisible(year, 100)) || (isDivisible(year, 400));
}

 int countLeapYears(const int startYear, const int endYear, int * const isLeapYear)
{
  int i;
  int totalLeapYears = 0;

  for (i = startYear; i <= endYear; i++) {
    if (testLeapYear(i)) {
      totalLeapYears++;
    }
  }

  *isLeapYear = testLeapYear(endYear);

  return totalLeapYears;
}





int get_offset(int month ,int year){
    int isLeapyear;
    int offset;
    int sum = year-referenceYear;
    sum += referenceYearFirstDays[month - 1];
    sum += countLeapYears(referenceYear, year, &isLeapyear);
    offset = sum%7;
    return offset;
}
