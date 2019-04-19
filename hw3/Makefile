CFLAGS = -O3 -Wall -std=c++11
CFLAGS = -g -Wall -std=c++11

remainder: remainder.cpp
	@echo "Compiling Remainder..."
	g++ -o $@ remainder.cpp $(CFLAGS)
	ln -f -s remainder a.out
	@echo "Done."

admission: admissionList.cpp admissionSys.o
	@echo "Compiling Admission List..."
	g++ -o $@ admissionList.cpp admissionSys.o $(CFLAGS)
	ln -f -s admission a.out
	@echo "Done."

admissionSys.o: admissionSys.h admissionSys.cpp
	g++ -c admissionSys.h admissionSys.cpp $(CFLAGS)


clean:
	rm -f *.o *.h.gch ./a.out remainder admission
	@echo "Done."