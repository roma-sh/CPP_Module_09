
#include "BitcoinExchange.hpp"


int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << "usage: ./bitcoin_exchange filename" << std::endl;
		return 1;
	}
	try
	{
		BitcoinExchange exchange("data.csv");
		exchange.handleInputFile(argv[1]);
	}
	catch (const std::exception &e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
		return 1;
	}
	return 0;
}

