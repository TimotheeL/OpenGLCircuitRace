/*
	Racing game project - Racing car class

	2019
	Nicolas Bouchard, Timothee Guy, Timothee Laurent
*/

#ifndef RACINGCAR_H
#define RACINGCAR_H

#include <Position.h>
#include <BoundingBox.h>
#include <Object.h>

class RacingCar : public Object {

public:
	static const float MAX_SPD_FW;	// Maximum speed forward
	static const float MAX_SPD_BW;	// Maximum speed backward
	static const float ACCEL;		// Acceleration
	static const float ROT_ANGLE;	// Rotation rate

private:
	bool handbrakeState;	// Handbrake state
	bool dirForward;		// Direction state

	float speed;			// Speed

public:
	/* Constructors */
	RacingCar(float clength, float cwidth, float cheight, float cx, float cy, float cz);

	RacingCar(float clength, float cwidth, float cheight);

	RacingCar(RacingCar *rc);

	RacingCar(void);

	/* Destructor */
	virtual ~RacingCar(void);

	/* Getters */
	float getSpeed(void);

	bool getHandbrakeState(void);
	bool getDirForward(void);
	
	/*Draw */
	virtual void draw(void);

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