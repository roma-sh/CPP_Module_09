
#include "BitcoinExchange.hpp"


int main(int argc, char **argv)
{
	(void)argv;
	if (argc != 2)
	{
		std::cerr << "usage: ./bitcoin_exchange filename" << std::endl;
		return 1;
	}
	BitcoinExchange exchange("data.csv");
	exchange.handleInputFile(argv[1]);
	return 0;
}
