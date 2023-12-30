#include "Date.hpp"

bool Date::isNumber(char *number, bool isDouble)
{
	int i = 0;
	int d = 0;
	while (number && number[i])
	{
		if (!isdigit(number[i]))
		{
			if (isDouble)
				if (number[i] == '.' && !d && i != 0 && i != sizeof(number))
				{
					d++;
					i++;
					continue;
				}
			return false;
		}
		i++;
	}
	if (number)
		return true;
	return false;
}

bool isYear(char *year, bool *leap)
{
	if (!Date::isNumber(year, false))
		return false;
	if (strlen(year) != 4)
		throw (Date::WrongFormatException());
	int y = atoi(year);
	if (y < 0)
		return false;
	if ((y % 4) == 0)
		*leap = true;
	return true;
}

int getMonth(char *month)
{
	if (!month || !Date::isNumber(month, false))
		return 0;
	if (strlen(month) != 2)
		throw (Date::WrongFormatException());
	int m = atoi(month);
	if (m <= 0 || m > 12)
		return 0;
	return m;
}

int getDay(char *day)
{
	if (!Date::isNumber(day, false))
		return 0;
	if (strlen(day) != 2)
		throw (Date::WrongFormatException());
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
	if (!Date::isNumber(p, false))
		return false;
	int day = getDay(p);
	if (!day)
		return false;
	int xmonths[7] = {1, 3, 5, 7, 8, 10, 12};
	if (day == 31)
		for (int i = 0; i < 7; i++)
		{
			if (month == xmonths[i])
				break;
			if (i == 6 && month != xmonths[i])
				return false;
		}
	if (month == 2 && day > 28)
	{
		if (day == 29)
			return leap;
		else
			return false;
	}
	return true;
}