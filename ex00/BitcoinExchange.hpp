#include <string>
#include <map>

class BitcoinExchange
{
	private:
		std::map<std::string, double> database;
		bool	isLeapYear(int year);
		bool	isValidDate(int year, int month, int day);
		bool	parsePrice(const std::string &price);
		bool	parseDate(const std::string & date);
		bool	parseInput(const std::string &line, char divider, bool databaseFilled);
	public:
		void	processfile(std::string infile , std::string header, char divider, bool databaseFilled);
};
