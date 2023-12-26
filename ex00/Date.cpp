#include "Date.hpp"

bool isNumber(char *number)
{
	int i = 0;
	while (number && number[i])
	{
		if (!isdigit(number[i]))
			return false;
		i++;
	}
	if (number)
		return true;
	return false;
}

bool isYear(char *year, bool *leap)
{
	if (!isNumber(year))
		return false;
	int y = atoi(year);
	if (y < 0)
		return false;
	if ((y % 4) == 0)
		*leap = true;
	return true;
}

int getMonth(char *month)
{
	if (!month || !isNumber(month))
		return 0;
	int m = atoi(month);
	if (m <= 0 || m > 12)
		return 0;
	return m;
}

int getDay(char *day)
{
	if (!isNumber(day))
		return 0;
	int d = atoi(day);
	if (d <= 0 || d > 31)
		return 0;
	return d;
}

bool Date::isDateCorrect(std::string str) {
	char *p;
	bool leap = false;
	char date[str.size() + 1];
	strncpy(date, str.c_str(), sizeof(date));
	p = strtok(date, "-");
	if (!isYear(p, &leap))
		return false;
	p = strtok(NULL, "-");
	int month = getMonth(p);
	if (!month)
		return false;
	p = strtok(NULL, "-");
//	std::cout << p << std::endl;
	if (!isNumber(p))
		return false;
	int day = getDay(p);
	if (!day)
		return false;
	int xmonths[7] = {1, 3, 5, 7, 8, 10, 12};
	if (day == 31)
		if (std::find(std::begin(xmonths), std::end(xmonths), month) == std::end(xmonths))
			return false;
	if (month == 2 && day > 28)
	{
		if (day == 29)
			return leap;
		else
			return false;
	}
	return true;
}