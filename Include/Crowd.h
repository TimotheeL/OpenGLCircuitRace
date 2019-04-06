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

class Crowd {

protected:
	std::vector<Spectator> spectators;

public:

	/* Constructors */
	Crowd(std::vector<Spectator> spectators);
	Crowd(Crowd *c1);
	Crowd(void);

	/* Destructor */
	~Crowd(void);

	/* Update spectators*/
	void update(void);

	/* OpenGL code to draw the crowd */
	void draw(void);

	/* Getters */
	std::vector<Spectator> getSpectators(void);
};

#endif // Crowd
