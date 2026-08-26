#include <string>
#include <map>

class BitcoinExchange
{
	private:
		std::map<std::string, double> database;
		bool	isLeapYear(int year);
		bool	isValidDate(int year, int month, int day);
		bool	parsePrice(const std::string &price, float &outValue, float min, float max);
		bool	parseDate(const std::string & date);
		bool	parseInput(const std::string &line, char divider, bool databaseFilled);
	public:
		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange &other);
		BitcoinExchange &operator=(const BitcoinExchange &other);
		~BitcoinExchange();
		void	processfile(std::string infile);
		void	loadDatabase(const std::string &filename);
};
