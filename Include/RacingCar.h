/*
	Racing game project - Racing car class

	2019
	Nicolas Bouchard, Timoth�e Guy, Timoth�e Laurent
*/

#ifndef RACINGCAR_H
#define RACINGCAR_H

class RacingCar {

public:
	static const float MAX_SPD_FW;	// Maximum speed forward
	static const float MAX_SPD_BW;	// Maximum speed backward
	static const float ACCEL;		// Acceleration
	static const float ROT_ANGLE;	// Rotation angle

	float x, y, z;		// Current position
	float rotation;		// Current rotation
	float speed;		// Current speed
	bool b_handbrake;	// Handbrake state
	bool dirForward;	// Direction state

public:
	/* Constructor */
	RacingCar(void);

	/* Destructor */
	~RacingCar(void);

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