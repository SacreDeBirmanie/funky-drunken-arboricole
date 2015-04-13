# options de compilation
CFLAGS = -g -std=c++11 -pedantic -Wfatal-errors -Wconversion -Wredundant-decls -Wshadow -Wall -Wextra

all : test_Arbre2.exe

%.o : %.cpp %.hpp
	g++ $(CFLAGS) -c -o $@ $< 
	
test_Arbre2.exe : test_Arbre2.cpp
	g++ $(CFLAGS) test_Arbre2.cpp -o test_Arbre2.exe
	
clean :
	@rm *.o *.exe

.PHONY: all clean
