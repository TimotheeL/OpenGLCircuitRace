/*
Racing game project - Checker class
Represents a checker pattern (start line)
2019
Nicolas Bouchard, Timothée Guy, Timothée Laurent
*/

#ifndef ____CHECKER____
#define ____CHECKER____

class Checker {

private:

public:

	/* Constructors */
	Checker();
	Checker(Checker *p1);

	/* Destructor */
	~Checker(void);

	/* OpenGL code to draw the checker pattern */
	void draw(void);

	/* Print */
	//void print(void);

	/* Getters */
};

#endif // Checker