#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
#include <iterator>
#include <regex>

class BitcoinExchange
{
	public:
		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange &other);
		BitcoinExchange &operator=(const BitcoinExchange &other);
		~BitcoinExchange();
		BitcoinExchange(std::string filename);

		double getExchangeRate(std::string date) const;
		void printData() const;
		void handleInputFile(std::string filename);

	private:
		std::map<std::string, double> _data;
		std::string _filename;
};

bool validDate(std::string date);
bool validValue(std::string rate);
bool isLeapYear(int year);
