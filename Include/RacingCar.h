/*
	Racing game project - Racing car class

	2019
	Nicolas Bouchard, Timothee Guy, Timothee Laurent
*/

#ifndef RACINGCAR_H
#define RACINGCAR_H

#include <Position.h>

class RacingCar {

public:
	static const float MAX_SPD_FW;	// Maximum speed forward
	static const float MAX_SPD_BW;	// Maximum speed backward
	static const float ACCEL;		// Acceleration
	static const float ROT_ANGLE;	// tiresAngle angle

private:
	Position pos;		// Position
	float tiresAngle;	// Current tiresAngle
	float speed;		// Current speed
	bool handbrakeState;	// Handbrake state
	bool dirForward;	// Direction state

public:
	/* Constructors */
	RacingCar(float cx, float cy, float cz);

	RacingCar(RacingCar *rc);

	RacingCar(void);

	/* Destructor */
	~RacingCar(void);

	/* Getters */
	Position getPos(void);

	float getTiresAngle(void);
	float getSpeed(void);

	bool getHandbrakeState(void);
	bool getDirForward(void);
	
	/*Draw */
	void draw(void);

	/* Input handling */
	void handleInputs(bool *keyStates, bool *specialKeyStates);

	/* Movement handling */
	void handleMovement(double deltaTime);

	/* Forward */
	void forward(float distance);

	/* Backward */
	void backward(float distance);

	/* Turn right */
	void turnRight(float degrees);

	/* Turn left */
	void turnLeft(float degrees);

	/* Use the handbrake */
	void handbrake();

	/* Reset car's properties */
	void reset();
};

#endif