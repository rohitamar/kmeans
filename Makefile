main:
	g++ -Wall -Werror -pedantic -std=c++20 -o main main.cpp

clean:
	del /Q /F "./data/"