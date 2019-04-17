CFLAGS = -O3 -Wall -std=c++11
CFLAGS = -g -Wall -std=c++11

remainder: remainder.cpp
	@echo "Compiling Remainder..."
	g++ -o $@ remainder.cpp $(CFLAGS)
	ln -f -s remainder a.out
	@echo "Done."

admission: admissionList.cpp
	@echo "Compiling Admission List..."
	g++ -o $@ admissionList.cpp $(CFLAGS)
	ln -f -s admission a.out
	@echo "Done."
clean:
	rm -f *.o *.h.gch ./a.out remainder admission
	@echo "Done."