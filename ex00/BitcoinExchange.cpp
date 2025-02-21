#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &original)
{
	_data = original._data;
	_filename = original._filename;
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &original)
{
	if (this != &original)
	{
		_data = original._data;
		_filename = original._filename;
	}
	return *this;
}

BitcoinExchange::~BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(std::string filename)
{
	_filename = filename;
	std::ifstream file(filename);
	if (!file.is_open())
		throw std::runtime_error("Could not open database file");

	std::string line;

	while (std::getline(file, line))
	{
		if (line.empty() || line == "date,exchange_rate")
			continue;

		// Parse the line (date,exchange_rate)
		std::istringstream ss(line);
		/*
		A std::istringstream allows us to treat a string as an input stream,
		similar to how we use std::cin to read user input. This is useful when we want to parse the string
		into smaller components (like separating the date and the rate in this case).
		*/
		std::string date, rate_Str;

		if (std::getline(ss, date, ',') && std::getline(ss, rate_Str))
		//Reads characters from the ss stream until a delimiter (,) is encountered.
		//Reads the rest of the stream (from the current cursor position to the end of the line) and stores it in rate_Str
		{
			try
			{
				double rate = std::stof(rate_Str); // Convert the rate to a double
				_data[date] = rate; // Store in the map
			}
			catch (const std::exception &e)
			{
				std::cerr << "Error parsing line: " << line << std::endl;
			}
		}
	}
	file.close();
}

void BitcoinExchange::printData() const
{
	for (auto it = _data.begin(); it != _data.end(); it++) // auto +11 standard
		std::cout << it->first << " " << it->second << std::endl;
}

double BitcoinExchange::getExchangeRate(std::string date) const
{
	auto it = _data.find(date); // find searches for the key date in the map not in the value
	if (it == _data.end())
	{
		it = _data.lower_bound(date); // returns the first element that is not less than date (>= date)
		if (it == _data.begin())
			throw std::runtime_error("Date not found in database or less than the earliest date");
		it--;
	}
	return it->second;
}

void BitcoinExchange::handleInputFile(std::string filename)
{
	double input_value = 0;
	bool valid_Date;
	bool valid_Rate;
	std::ifstream file(filename);
	if (!file.is_open())
		throw std::runtime_error("Could not open input file");
	std::string line;

	while (std::getline(file, line))
	{
		if (line.empty())
			continue;
		if (line != "date | value")
		{
			std::cout <<"\"date | value\" line is missing or not correct in the input file"<< std::endl;
			exit(1);
		}
		else
			break;
	}


	while (std::getline(file, line))
	{

		std::istringstream ss(line);
		std::string input_date, input_value_str;

		if (std::getline(ss, input_date, '|') && std::getline(ss, input_value_str))
		{
			valid_Date = validDate(input_date);
			valid_Rate = validValue(input_value_str);
			if (valid_Date && valid_Rate)
			{
				input_value = std::stod(input_value_str);
				// std::cout<<"the number is : "<<input_value<<std::endl;
				if (input_value < 0)
					std::cerr << "Error: not a positive number." << std::endl;
				else if (input_value >= 1000)
					std::cerr << "Error: number too large." << std::endl;
				else
				{
					try
					{
						std::cout << input_date << " => " << input_value_str << " = " << getExchangeRate(input_date) * input_value << std::endl;
					}
					catch (const std::exception &e)
					{
						std::cerr << "Error: " << e.what() << std::endl;
					}
				}
			}
			else if (!valid_Date)
			{
				if (input_date.empty())
					std::cerr << "Error: missing date." << std::endl;
				else
					std::cerr << "Error: incorrect date => " << input_date << std::endl;
			}
			else if (!valid_Rate)
			{
				if (input_value_str.empty())
					std::cerr << "Error: missing value." << std::endl;
				else
					std::cerr << "Error: incorrect value => " << input_value_str << std::endl;
			}
		}
		else
			std::cerr << "Error: bad input => " << line << std::endl;
	}
	file.close();
}

bool validDate(std::string date)
{
	std::regex dateFormat("^\\s*\\d{4}-\\d{2}-\\d{2}\\s*$");
	/*
	^ and $: Ensure the entire string matches the pattern.
	$ : Ensures that no extra characters appear after the matched pattern.
	\\s*:
	Matches zero or more whitespace characters (\s stands for whitespace).
	Adding \\s* at the beginning allows leading spaces.
	Adding \\s* at the end allows trailing spaces.
	\d{4}-\d{2}-\d{2}: Matches the core date format YYYY-MM-DD.
	*/
	if (!std::regex_match(date, dateFormat))
		return false;
	int year = std::stoi(date.substr(0, 4));
	int month = std::stoi(date.substr(5, 2));
	int day = std::stoi(date.substr(8, 2));
	if ((month < 1 || month > 12) || (year > 2025 || year < 2008))
		return false;
	int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	if (isLeapYear(year))
		daysInMonth[1] = 29; // February has 29 days in a leap year
	if (day < 1 || day > daysInMonth[month - 1]) // Check if the day is valid for the month
		return false;
	return true;
}

bool isLeapYear(int year)
{
	return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

bool validValue(std::string rate)
{
	std::regex rateFormat("^\\s*-?\\d+(\\.\\d+)?\\s*$");
	/*
	^ and $: Match the start and end of the string.
	\\s*: Matches optional spaces before and after the number.
	-?: Allows an optional minus sign (-) for negative numbers.
	\\d+: Matches one or more digits (whole number part).
	(\\.\\d+)?: Matches an optional dot (.) followed by one or more digits (decimal part).
	\\s*: Allows optional spaces after the number.
	*/
	if (!std::regex_match(rate, rateFormat))
		return false;
	return true;
}
