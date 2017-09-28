all:	HsnGenerator.cxx DataObjects/Flux.h DataObjects/Flux.cxx DataObjects/Observables.h DataObjects/Observables.cxx DataObjects/FourMomentum.h DataObjects/SterileNeutrino.cxx DataObjects/SterileNeutrino.h DataObjects/FourMomentum.cxx DataObjects/Channel.h DataObjects/Channel.cxx
	g++ -g -std=c++11  -c HsnGenerator.cxx -o HsnGenerator.o -I. -I$(CLHEP_INC)
	g++ -g -std=c++11  -c DataObjects/FourMomentum.cxx -o DataObjects/FourMomentum.o -I. -I$(CLHEP_INC)
	g++ -g -std=c++11  -c DataObjects/Observables.cxx -o DataObjects/Observables.o -I. -I$(CLHEP_INC)
	g++ -g -std=c++11  -c DataObjects/SterileNeutrino.cxx -o DataObjects/SterileNeutrino.o -I. -I$(CLHEP_INC)
	g++ -g -std=c++11  -c DataObjects/Flux.cxx -o DataObjects/Flux.o -I. -I$(CLHEP_INC)
	g++ -g -std=c++11  -c DataObjects/Channel.cxx -o DataObjects/Channel.o -I. -I$(CLHEP_INC)
	g++ -g -std=c++11  -c Helpers/Helper.cxx -o Helpers/Helper.o -I. -I$(CLHEP_INC)
	g++ -g -std=c++11  -o HsnGenerator HsnGenerator.o DataObjects/FourMomentum.o DataObjects/Observables.o DataObjects/Flux.o DataObjects/Channel.o DataObjects/SterileNeutrino.o Helpers/Helper.o -L$(CLHEP_LIB_DIR) -l$(CLHEP_LIB)
	rm *.o

