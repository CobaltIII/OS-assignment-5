EXE=vector matrix

all: clean $(EXE)

%: %.cpp
	g++ -O3 -std=c++11 -o $@ $^ -lpthread

clean:
	rm -rf $(EXE) 2>/dev/null
	
execute:
	./vector 
	./vector 3
	./vector 4
	./vector 5
	./vector 6
	./vector 7
	./vector 8
	./vector 9
	./vector 10
	
