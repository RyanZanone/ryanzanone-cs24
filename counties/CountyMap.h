#ifndef COUNTYMAP_H
#define COUNTYMAP_H

#include <vector>
#include "County.h"

using namespace std;

class CountyMap {
	private:
		//storage requirement: O(e), e = number of edges between counties
		//add private variables here
	    std::vector<County> counties;
		std::vector<std::vector<bool>> adjacencyMatrix;
    	std::vector<std::vector<int>> adjacencyList;

		void buildAdjacencyList();
	public:
		//constructor
		//performance: O(n^2), n = number of counties
		CountyMap(vector<County> counties, vector<vector<bool>> adjacencyMatrix);

		CountyMap(const CountyMap& other) ;

		~CountyMap();

		//performance: O(1)
		County getCounty(int countyID);

		//performance: O(1)
		bool countyAdjacency(int countyID1, int countyID2);

		//performance: O(1)
		int getNumCounties();
		
		//performance: O(n), n = number of counties
		vector<int> getAdjacentCounties(int countyID);

		//performance: O(n), n = number of counties in the itinerary
		bool checkValidItinerary(vector<int> itinerary);
};

#endif