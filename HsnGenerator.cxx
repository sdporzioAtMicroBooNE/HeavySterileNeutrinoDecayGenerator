/* Inflight, Event generator for sterile decays at SBL facilities
 *
 * Credit for the code goes to Mark Ross-Lonergan (mark.ross-lonergan@durham.ac.uk)
 * and Peter Ballett (peter.ballett@durham.ac.uk), who originally wrote it.
 *
 * Inflight has been rewritten to be included in the LArSoft code by Davide Porzio
 * (salvatore.porzio@postgrad.manchester.ac.uk).
 *
 * The authors make no guarrentee of the behaviour, stability or bug-free-ness
 * of this code. Use is at own risk.
 */

#include <iostream>
#include <cmath>
#include <vector>
#include <unistd.h>
#include <getopt.h>

#include "DataObjects/FourMomentum.h"
#include "DataObjects/SterileNeutrino.h"
#include "DataObjects/Flux.h"
#include "DataObjects/Observables.h"
#include "DataObjects/Channel.h"
#include "Helpers/Helper.h"
#include "Helpers/Settings.h"

#include "CLHEP/Random/RandomEngine.h"
#include "CLHEP/Random/JamesRandom.h"
#include "CLHEP/Random/RandFlat.h"

// Fcl settings
bool fPrintHepEvt = true;
double fSterileMass = 0.246;
int fDecayChannel = 3;
int fNumberEvents = 5;
std::string fFluxFile = "Fluxes/flux.dat";
double fDistance = 470.; // m 
double fGlobalTimeOffset = 3125;
double fBeamWindow = 1600;
std::vector<double> fBoundariesX;
std::vector<double> fBoundariesY;
std::vector<double> fBoundariesZ;

// AuxFunctions
void CompressSettings(Settings &set){
	set.printHepEvt = fPrintHepEvt;
	set.sterileMass = fSterileMass;
	set.decayChannel = fDecayChannel;
	set.numberEvents = fNumberEvents;
	set.fluxFile = fFluxFile;
	set.distance = fDistance;
	set.globalTimeOffset = fGlobalTimeOffset;
	set.beamWindow = fBeamWindow;
	set.boundariesX = fBoundariesX;
	set.boundariesY = fBoundariesY;
	set.boundariesZ = fBoundariesZ;
}

int main(int argc, char* argv[])
{

	Settings set;
	CompressSettings(set);

	// Random number generator
	// art::ServiceHandle<art::RandomNumberGenerator> rng;
	// CLHEP::HepRandomEngine &engine = rng->getEngine("gen");
	CLHEP::HepJamesRandom engine;
	CLHEP::RandFlat flat(engine);

	// Assign the theoretical parameters of the model (model_params) and the correct decay class (CHAN) depending on the type of decay channel selected in the fhicl file (fDecayChannel)
	std::vector<double> model_params; 
	twoIP_channel *CHAN;
	FillModel(engine, CHAN, model_params, set);

	// Load up the text file and generate a flux class
	FluxFile flux(fFluxFile, fSterileMass);

	for(int i=0; i<fNumberEvents; i++)
	{
		Observables obs; 
		GenerateObservables(engine, CHAN, flux, set, obs);
		if (fPrintHepEvt) obs.PrintHepEvt(i);
	}
	delete CHAN;
	return 0;
}

