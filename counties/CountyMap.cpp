#include "CountyMap.h"
#include "County.h"
#include <vector>

CountyMap::CountyMap(vector<County> counties, vector<vector<bool>> adjMatrix) {
    this->counties = counties;
    this->adjacencyMatrix = adjMatrix;
}

CountyMap::CountyMap(const CountyMap& other) {
    this->counties = other.counties;
    this->adjacencyMatrix = other.adjacencyMatrix;
}

CountyMap::~CountyMap() {
    // TODO
}

County CountyMap::getCounty(int index) {
    if (index >= 0 && index < counties.size()) {
        return counties[index];
    } else {
        return County();
    }
}

int CountyMap::getNumCounties() {
    return static_cast<int>(counties.size());
}

bool CountyMap::countyAdjacency(int index1, int index2) {
    if (index1 >= 0 && index1 < static_cast<int>(counties.size()) &&
        index2 >= 0 && index2 < static_cast<int>(counties.size())) {
        return adjacencyMatrix[index1][index2];
    } 
    else {
        return false;
    }
}

bool CountyMap::checkValidItinerary(vector<int> itinerary) {
    if (itinerary.empty()) {
        return false; // An empty itinerary is not valid.
    }

    for (size_t i = 0; i < itinerary.size() - 1; i++) {
        int currentCounty = itinerary[i];
        int nextCounty = itinerary[i + 1];

        if (!countyAdjacency(currentCounty, nextCounty)) {
            return false; // Counties in the itinerary must be adjacent.
        }
    }

    return true;
}

vector<int> CountyMap::getAdjacentCounties(int index) {
    if (index >= 0 && index < static_cast<int>(counties.size())) {
        return adjacencyList.at(index);
    } else {
        return std::vector<int>();
    }
}

// helper functions may follow
