Heap WordList::correct(const std::vector<Point>& points, size_t maxcount, float cutoff) const {
    Heap suggestions(maxcount);

    for (const std::string& word : mWords) {
        if (word.length() == points.size()) {
            float wordScore = 0.0;
            for (size_t i = 0; i < word.length(); ++i) {
                Point keyLocation = QWERTY[word[i] - 'a']; // Use the QWERTY layout for the character
                float dx = points[i].x - keyLocation.x;
                float dy = points[i].y - keyLocation.y;
                float distance = std::sqrt(dx * dx + dy * dy); // Calculate Euclidean distance
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
