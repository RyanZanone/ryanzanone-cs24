#include "WordList.h"
#include <cmath>

WordList::WordList(std::istream& stream) {
    std::string word;
    while (stream >> word) {
        bool valid = true;
        for (char c : word) {
            if (!islower(c)) {
                valid = false;
                break;
            }
        }
        if (valid) {
            mWords.push_back(word);
        }
    }
}

Heap WordList::correct(const std::vector<Point>& points, size_t maxcount, float cutoff) const {
    Heap resultHeap(maxcount);
    
    for (const std::string& word : mWords) {
        if (word.length() != points.size()) {
            continue;
        }
        
        float totalScore = 0.0;
        for (size_t i = 0; i < points.size(); ++i) {
            float dx = points[i].x - QWERTY[word[i] - 'a'].x;
            float dy = points[i].y - QWERTY[word[i] - 'a'].y;
            float distance = std::sqrt(dx * dx + dy * dy);
            float score = 1.0 / (10 * distance * distance + 1);
            totalScore += score;
        }
        
        float averageScore = totalScore / static_cast<float>(word.length());
        if (averageScore >= cutoff) {
            resultHeap.pushpop(word, averageScore);
        }
    }
    
    return resultHeap;
}