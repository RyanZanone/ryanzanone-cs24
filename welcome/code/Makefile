SRCS := caprot.cpp

all: caprot

caprot: $(SRCS:.cpp=.o)
	g++ -Wall -Wextra -Werror -std=c++17 $^ -o $@

%.o: %.cpp
	g++ -Wall -Wextra -Werror -std=c++17 -c $< -o $@

clean:
	rm -f $(SRCS:.cpp=.o) caprot

