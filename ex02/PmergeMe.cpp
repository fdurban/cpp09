#include <iostream>
#include <deque>
#include <vector>
#include <deque>
#include <ctime>
#include <cstdlib>
#include "PmergeMe.hpp"

PmergeMe::PmergeMe(): comparisonCountVector(0), comparisonCountDeque(0)
{}

PmergeMe::PmergeMe(const PmergeMe &other): comparisonCountVector(other.comparisonCountVector), comparisonCountDeque(other.comparisonCountDeque)
{
}

PmergeMe &PmergeMe::operator=(const PmergeMe &other)
{
	if(this != &other)
	{
		comparisonCountVector = other.comparisonCountVector;
		comparisonCountDeque = other.comparisonCountDeque;
	}
	return (*this);
}

PmergeMe::~PmergeMe()
{}

void PmergeMe::sort(int argc, char **argv)
{
	clock_t startVector;
	clock_t endVector;
	clock_t startDeque;
	clock_t endDeque;
	std::vector<Element> outputVector;
	std::deque<Element> outputDeque;
	std::vector<Element> input = parseInput(argc, argv);
	std::deque<Element> inputDeque = parseInputDeque(argc, argv);
	startVector = clock();
	outputVector = sortWithIndex(input);
	endVector = clock();
	startDeque = clock();
	outputDeque = sortWithIndexDeque(inputDeque);
	endDeque = clock();
	double realTimeVector = (static_cast<double>(endVector - startVector)/ CLOCKS_PER_SEC) * 1000000.0;
	double realTimeDeque = (static_cast<double>(endDeque - startDeque)/ CLOCKS_PER_SEC) * 1000000.0;
	std::cout<<"realTimeVector :"<<realTimeVector<<"\n";
	std::cout<<"realTimeDeque :"<<realTimeDeque<<"\n";
}

PmergeMe::Element PmergeMe::findLoserById(const std::vector< std::pair<size_t, Element> >& map, size_t winner_id) {
    for (size_t i = 0; i < map.size(); ++i) {
        if (map[i].first == winner_id) return map[i].second;
    }
    return Element(-1, 0); // Manejo de error básico
}

PmergeMe::Element PmergeMe::findLoserByIdDeque(const std::deque< std::pair<size_t, Element> >& map, size_t winner_id) {
    for (size_t i = 0; i < map.size(); ++i) {
        if (map[i].first == winner_id) return map[i].second;
    }
    return Element(-1, 0); // Manejo de error básico
}

std::vector<size_t> PmergeMe::generateJacobsthalSequence(size_t num_losers)
{
  std::vector<size_t> sequence;
  if(num_losers == 0) return sequence;
  
  size_t jacob_prev = 1;
  size_t jacob_curr = 3;

  while(jacob_prev < num_losers)
  {
    size_t current_limit = (jacob_curr > num_losers) ? num_losers : jacob_curr;

    for (size_t i = current_limit; i > jacob_prev; --i)
    {
      sequence.push_back(i);
    }
    size_t next_jacob = jacob_curr + 2 * jacob_prev;
    jacob_prev = jacob_curr;
    jacob_curr = next_jacob;
  }
  std::cout<<"Sequence : ";
  for(size_t i = 0; i < sequence.size(); i++)
  {
	  std::cout<<sequence[i]<<" ";
  }
  std::cout<<"\n";
  return sequence;
}


std::deque<size_t> PmergeMe::generateJacobsthalSequenceDeque(size_t num_losers)
{
  std::deque<size_t> sequence;
  if(num_losers == 0) return sequence;
  
  size_t jacob_prev = 1;
  size_t jacob_curr = 3;

  while(jacob_prev < num_losers)
  {
    size_t current_limit = (jacob_curr > num_losers) ? num_losers : jacob_curr;

    for (size_t i = current_limit; i > jacob_prev; --i)
    {
      sequence.push_back(i);
    }
    size_t next_jacob = jacob_curr + 2 * jacob_prev;
    jacob_prev = jacob_curr;
    jacob_curr = next_jacob;
  }
  std::cout<<"Sequence : ";
  for(size_t i = 0; i < sequence.size(); i++)
  {
	  std::cout<<sequence[i]<<" ";
  }
  std::cout<<"\n";
  return sequence;
}

std::vector<PmergeMe::Element> PmergeMe::sortWithIndex(std::vector<Element> &currentSeq)
{
  if(currentSeq.size() == 1)
    return currentSeq;
  size_t n = currentSeq.size();
  if(n <= 1) return currentSeq;
  std::vector<Element> winners;
  std::vector<std::pair<size_t, Element > > local_losers_map;

  bool hasStraggler = (n % 2 != 0);
  Element straggler;

  std::vector<Element>::iterator it = currentSeq.begin();
  for(size_t i = 0; i < n / 2; ++i)
  {
    Element first = *it;
    std::advance(it,1);
    Element second = *it;
    std::advance(it,1);
    if(second < first)
    {
      winners.push_back(first);
      local_losers_map.push_back(std::make_pair(first.id, second));
    }
    else
    {
      winners.push_back(second);
      local_losers_map.push_back(std::make_pair(second.id, first));
    }
  }
  if(hasStraggler)
  {
	  straggler = *it;
	  std::cout<<"straggler: "<<straggler.value<<"\n";
  }
  //Aqui empieza la recursividad
  std::vector<Element> mainChain = sortWithIndex(winners);
  //reasignamos los ids porque a cada nivel con los perdedores introducidos la lista ordenada crece
  //std::cout<<"winners ids in order: ";
  std::vector<size_t> winners_ids_in_order;
  for(size_t i = 0; i < mainChain.size(); ++i)
  {
    winners_ids_in_order.push_back(mainChain[i].id);
    //std::cout<<winners_ids_in_order[i]<<" ";
  }
  std::cout<<"\n";
  //Aqui empieza la insercion de pending dentro de la mainchain que se hace tambien de forma recursiva
  Element b1 = findLoserById(local_losers_map, mainChain[0].id);
  mainChain.insert(mainChain.begin(), b1);
  //Ya se ha insertado el primer elemento mas pequeno ahora empieza jacobsthal
  std::vector<size_t> insert_seq = generateJacobsthalSequence(local_losers_map.size());

  int added_count = 1;
  for(size_t i = 0; i < insert_seq.size(); ++ i)
  {
    size_t b_index = insert_seq[i];
    //std::cout<<"b_index "<<b_index<<"\n";
    size_t winner_id = winners_ids_in_order[b_index - 1];
    //std::cout<<"winner_id :"<<winner_id<<"\n";;
    Element loser_to_insert = findLoserById(local_losers_map, winner_id);
    //std::cout<<"Loser to insert: "<<loser_to_insert.value<<"\n";
    size_t search_area = b_index + added_count - 1; 
    std::vector<Element>::iterator end_of_search = mainChain.begin();
    std::advance(end_of_search, search_area);

    std::vector<Element>::iterator insert_pos = std::lower_bound(mainChain.begin(), end_of_search, loser_to_insert);
    mainChain.insert(insert_pos, loser_to_insert);
    ++added_count;
  }
  std::cout<<"mainChain: ";
  for(size_t i = 0; i < mainChain.size(); ++i)
  {
    std::cout<<mainChain[i].value<<" ";
  }
  if (hasStraggler) {
    // El straggler no tiene ganador asociado.
    // Por lo tanto, su límite de búsqueda es toda la cadena principal.
    std::vector<Element>::iterator end_of_search = mainChain.end();
    std::vector<Element>::iterator insert_pos = std::lower_bound(mainChain.begin(), end_of_search, straggler);
    mainChain.insert(insert_pos, straggler);
}
  std::cout<<"\n-----------------------\n";
   return mainChain;
}

std::deque<PmergeMe::Element> PmergeMe::sortWithIndexDeque(std::deque<Element> &currentSeq)
{
  if(currentSeq.size() == 1)
    return currentSeq;
  size_t n = currentSeq.size();
  if(n <= 1) return currentSeq;
  std::deque<Element> winners;
  std::deque<std::pair<size_t, Element > > local_losers_map;

  bool hasStraggler = (n % 2 != 0);
  Element straggler;

  std::deque<Element>::iterator it = currentSeq.begin();
  for(size_t i = 0; i < n / 2; ++i)
  {
    Element first = *it;
    std::advance(it,1);
    Element second = *it;
    std::advance(it,1);
    if(second < first)
    {
      winners.push_back(first);
      local_losers_map.push_back(std::make_pair(first.id, second));
    }
    else
    {
      winners.push_back(second);
      local_losers_map.push_back(std::make_pair(second.id, first));
    }
  }
  //Aqui va lo impreso de abajo
  if(hasStraggler)
  {
	  straggler = *it;
	  std::cout<<"straggler: "<<straggler.value<<"\n";
  }
  //Aqui empieza la recursividad
  std::deque<Element> mainChain = sortWithIndexDeque(winners);
  //reasignamos los ids porque a cada nivel con los perdedores introducidos la lista ordenada crece
  std::cout<<"winners ids in order: ";
  std::deque<size_t> winners_ids_in_order;
  for(size_t i = 0; i < mainChain.size(); ++i)
  {
    winners_ids_in_order.push_back(mainChain[i].id);
    std::cout<<winners_ids_in_order[i]<<" ";
  }
  std::cout<<"\n";
  //Aqui empieza la insercion de pending dentro de la mainchain que se hace tambien de forma recursiva
  Element b1 = findLoserByIdDeque(local_losers_map, mainChain[0].id);
  mainChain.insert(mainChain.begin(), b1);
  //Ya se ha insertado el primer elemento mas pequeno ahora empieza jacobsthal
  std::deque<size_t> insert_seq = generateJacobsthalSequenceDeque(local_losers_map.size());

  int added_count = 1;
  for(size_t i = 0; i < insert_seq.size(); ++ i)
  {
    size_t b_index = insert_seq[i];
    //std::cout<<"b_index "<<b_index<<"\n";
    size_t winner_id = winners_ids_in_order[b_index - 1];
    //std::cout<<"winner_id :"<<winner_id<<"\n";;
    Element loser_to_insert = findLoserByIdDeque(local_losers_map, winner_id);
    //std::cout<<"Loser to insert: "<<loser_to_insert.value<<"\n";
    size_t search_area = b_index + added_count - 1; 
    std::deque<Element>::iterator end_of_search = mainChain.begin();
    std::advance(end_of_search, search_area);

    std::deque<Element>::iterator insert_pos = std::lower_bound(mainChain.begin(), end_of_search, loser_to_insert);
    mainChain.insert(insert_pos, loser_to_insert);
    ++added_count;
  }
  std::cout<<"mainChain: ";
  for(size_t i = 0; i < mainChain.size(); ++i)
  {
    std::cout<<mainChain[i].value<<" ";
  }
  if (hasStraggler) {
    // El straggler no tiene ganador asociado.
    // Por lo tanto, su límite de búsqueda es toda la cadena principal.
    std::deque<Element>::iterator end_of_search = mainChain.end();
    std::deque<Element>::iterator insert_pos = std::lower_bound(mainChain.begin(), end_of_search, straggler);
    mainChain.insert(insert_pos, straggler);
}
   std::cout<<"\n-----------------------\n";
   return mainChain;
}

void PmergeMe::validateInput(const std::string &str)
{
  long num;

  if(str.empty())
    throw std::runtime_error("Error, arguments empty");
  for(size_t i = 0; i < str.length(); ++ i)
  {
    if(!std::isdigit(str[i]))
      throw std::runtime_error("Error, digits");
  }
  std::istringstream iss(str);
  iss >> num;
  if(num <=0 || num > 2147483647)
    throw std::runtime_error("Error");
}

std::vector<PmergeMe::Element> PmergeMe::parseInput(int argc, char **argv)
{
  int num;
  std::vector<Element> result;
  size_t id_counter = 0;
  try
  {
    for(int i = 1; i < argc; ++i)
    {
      std::string arg(argv[i]);
      validateInput(arg);
      std::istringstream iss(arg);
      iss >> num;
      result.push_back(Element(num,id_counter++));
    }
  }
  catch(std::exception &e)
  {
    std::cerr << e.what() <<"\n";
    std::exit(1);
  }
  return (result);
}


std::deque<PmergeMe::Element> PmergeMe::parseInputDeque(int argc, char **argv)
{
  int num;
  std::deque<Element> result;
  size_t id_counter = 0;
  try
  {
    for(int i = 1; i < argc; ++i)
    {
      std::string arg(argv[i]);
      validateInput(arg);
      std::istringstream iss(arg);
      iss >> num;
      result.push_back(Element(num,id_counter++));
    }
  }
  catch(std::exception &e)
  {
    std::cerr << e.what() <<"\n";
    std::exit(1);
  }
  return (result);
}

/*
  std::cout<<"Winners :";
  for(size_t i = 0; i < winners.size(); ++i)
  {
	  std::cout<<winners[i].value<<" ";
  }
  std::cout<<"\n";
  std::cout<<"Winners ids :";
  for(size_t i = 0; i < winners.size(); ++i)
  {
	  std::cout<<winners[i].id<<" ";
  }
  std::cout<<"\n";
  std::cout<<"Losers: ";
  for(size_t i = 0; i < local_losers_map.size(); ++ i)
  {
	  std::cout<<local_losers_map[i].second.value<<" ";
  }
  std::cout<<"\n";
*/
