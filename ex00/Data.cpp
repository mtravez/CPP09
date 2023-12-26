#include "Data.hpp"
#include "Date.hpp"

float getExhange(std::string str)
{
	char data[str.size() + 1];
	char *p;

	strncpy(data, str.c_str(), sizeof(data));
	p = strtok(data, ",");
	p = strtok(NULL, ",");
	float exRate = strtod(p, NULL);
	if (errno == ERANGE)
	{
		std::cerr << "Error: wrong input => " << data << std::endl;
		return -1.0;
	}
	if (exRate < 0)
	{
		std::cerr << "Error: not a positive number" << std::endl;
		return -1.0;
	}
	return exRate;
}

Data::Data() : std::map<std::string, float>(){
	std::ifstream dataFile("data.csv");
	if (!dataFile)
		throw (UnavailableDataException());
	std::string line;
	if (!std::getline(dataFile, line))
	{
		dataFile.close();
		return;
	}
	while (std::getline(dataFile, line))
	{
		std::string date;
		char data[line.size() + 1];
		char *p;
		strncpy(data, line.c_str(), sizeof(data));
		p = strtok(data, ",");
		if (Date::isDateCorrect(p))
			date.assign(p);
		else
		{
			std::cerr << "Error: bad input => " << p << std::endl;
			continue;
		}
		float exRate = getExhange(line);
		if (exRate < 0)
		{
			continue;
		}
		this->insert(std::make_pair(date, exRate));
	}
	dataFile.close();
	return;
}

Data::Data(const Data &data) : std::map<std::string, float>(data){return;}

Data::~Data(){}

Data &Data::operator=(const Data &data) {
	(void) data;
	return *this;
}

Data::iterator Data::getClosest(std::string key) {
	Data::iterator closestKey = this->lower_bound(key);
	if (closestKey != this->begin() && closestKey->first.compare(key))
		--closestKey;
	return closestKey;
}