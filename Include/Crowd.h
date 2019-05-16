/*
	Racing game project - Patch class
	Represents a crowd (vector of spectators)
	2019
	Nicolas Bouchard, Timothée Guy, Timothée Laurent
*/
#include <vector>

#include <Spectator.h>

#ifndef ____CROWD____
#define ____CROWD____

using namespace std;

class Crowd {

protected:
	vector<Spectator> spectators;

public:
	/* Constructors */
	Crowd(vector<Spectator> spectators);

	Crowd(Crowd *c1);

	Crowd(void);

	/* Destructor */
	~Crowd(void);

	/* Update spectators*/
	void update(void);

	/* Draw */
	void draw(void);

	/* Getters */
	vector<Spectator> getSpectators(void);
};

#endif // Crowd
