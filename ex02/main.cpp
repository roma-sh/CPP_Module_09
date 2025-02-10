#include "PmergeMe.tpp"

// we will validate teh arguments here using regex

void validate_format(std::vector<std::string> arguments)
{
	std::regex re(R"(^[+-]?\d+$)"); // R is for raw string to avoid escaping the backslashes
	for (std::vector<std::string>::iterator it = arguments.begin(); it != arguments.end(); it++)
	{
		if (!std::regex_match(*it, re))
		{
			std::cerr << "Error: Only positive integers are allowed." << std::endl;
			exit (1);
		}
	}
}

void validateArgs(int argc, char **argv, std::vector<std::string> &arguments)
{
	double num;

	if (argc < 2)
	{
		std::cerr << "Usage: " << argv[0] << " [Random positive numbers]" << std::endl;
		exit (1);
	}
	if (argc == 2)
	{
		std::istringstream iss(argv[1]);
		std::string num;
		while (iss >> num)
			arguments.push_back(num);
	}
	else
	{
		for (int i = 1; i < argc; i++)
			arguments.push_back(argv[i]);
	}
	validate_format(arguments);
	for (std::vector<std::string>::iterator it = arguments.begin(); it != arguments.end(); it++)
	{
		try
		{
			num = std::stod(*it);
		}
		catch(const std::exception& e)
		{
			std::cerr << "Error: Only positive integers are allowed." << std::endl;
			exit (1);
		}

		if (num < 0 || num >= INT_MAX || num <= INT_MIN)
		{
			std::cerr << "Error: Only positive integers are allowed." << std::endl;
			exit (1);
		}
	}
}

int main(int argc, char **argv)
{
	std::vector<std::string> arguments;
	validateArgs(argc, argv, arguments);
	PmergeMe pm;
	pm.fillVector(arguments);
	pm.fillDeque(arguments);

	std::cout << "Before: ";
	pm.printVector();
	clock_t start = clock();
	// to_do: pm.sortVector();
	clock_t end = clock();
	std::cout << "After: ";
	pm.printVector();

	double elapsed = double(end - start) / CLOCKS_PER_SEC * 1000000;
	std::cout << "Time taken to sort vector: " << elapsed << "us" << std::endl;


	std::cout << std::endl;
	std::cout << std::endl;

	std::cout << "Before: ";
	pm.printDeque();
	start = clock();
	// to_do: pm.sortDeque();
	end = clock();
	std::cout << "After: ";
	pm.printDeque();
	elapsed = double(end - start) / CLOCKS_PER_SEC * 1000000;
	std::cout << "Time taken to sort deque: " << elapsed << "us" << std::endl;


	return 0;
}
