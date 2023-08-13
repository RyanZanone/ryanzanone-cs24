#include "WordList.h"
#include "Point.h"
#include <fstream>
#include <cmath>

WordList::WordList(std::istream& stream) {
    std::string line;
    while (std::getline(stream, line)) {
        bool isLowerCase = true;
        for (char c : line) {
            if (!std::islower(c)) {
                isLowerCase = false;
                break;
            }
        }
        if (isLowerCase) {
            mWords.push_back(line);
        }
    }
}

Heap WordList::correct(const std::vector<Point>& points, size_t maxcount, float cutoff) const {
    Heap suggestions(maxcount);

    for (const std::string& word : mWords) {
        if (word.length() == points.size()) {
            float wordScore = 0.0;
            for (size_t i = 0; i < word.length(); ++i) {
                Point keyLocation = QWERTY[word[i] - 'a']; // Use the QWERTY layout for the character
                float distance = points[i].distanceTo(keyLocation);
                float letterScore = 1.0 / (10.0 * distance * distance + 1.0);
                wordScore += letterScore;
            }
            wordScore /= static_cast<float>(word.length()); // Calculate the average score
            if (wordScore >= cutoff) {
                suggestions.push(word, wordScore);
            }
        }
    }

    return suggestions;
}
