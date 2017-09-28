#ifndef STERILE_SETTINGS_H_
#define STERILE_SETTINGS_H_

typedef struct Settings{
	bool printHepEvt;
	double sterileMass;
	int decayChannel;
	int numberEvents;
	std::string fluxFile;
	double distance;
	double globalTimeOffset;
	double beamWindow;
	std::vector<double> boundariesX;
	std::vector<double> boundariesY;
	std::vector<double> boundariesZ;
} Settings;

#endif