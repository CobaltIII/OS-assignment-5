EXE=vector matrix

all: clean $(EXE)

%: %.cpp
	g++ -O3 -std=c++11 -o $@ $^ -lpthread

clean:
	rm -rf $(EXE) 2>/dev/null
	
execute:
	./vector 

	./vector 4
	./vector 8
	./vector 10 500

	./matrix 

	./matrix 4
	./matrix 8
	./matrix 10 500

	
