#ifndef SOLVE_LOG_H
#define SOLVE_LOG_H

#include <list>

struct SolveLog
{
	std::list<double>* norms;
	double time;
	int iterations;

	SolveLog()
	{
		time = 0.0;
		iterations = 0;
		norms = new std::list<double>();
	}

	~SolveLog()
	{
		delete norms;
	}

	friend std::ostream& operator<<(std::ostream& os, const SolveLog& log)
	{
		os << "Time: " << log.time << "s\n";
		os << "Norm: " << log.norms->back() << "\n";
		os << "Iter: " << log.iterations << "\n";

		return os;
	}
};

#endif