/*
	Racing game project - Racing car class

	Represents a racing car, with all its properties

	2019
	Nicolas Bouchard, Timothee Guy, Timothee Laurent
*/

#ifndef ____RACINGCAR____
#define ____RACINGCAR____

#include <Position.h>
#include <BoundingBox.h>
#include <Object.h>
#include <TrackPart.h>
#include "BRT.h"

class RacingCar : public Object {

public:
	static const float MAX_SPD_FW;	// Maximum speed forward
	static const float MAX_SPD_BW;	// Maximum speed backward
	static const float ACCEL;		// Acceleration
	static const float ROT_ANGLE;	// Rotation rate

private:
	Position startpos;
	
	float camangle;

	bool handbrakeState;	// Handbrake state

	float speed;			// Speed

public:
	/* Constructors */
	RacingCar(float clength, float cwidth, float cheight, Position *pos);

	RacingCar(float clength, float cwidth, float cheight);

	RacingCar(RacingCar *rc);

	RacingCar(void);

	/* Destructor */
	virtual ~RacingCar(void);

	/* Getters */
	float getSpeed(void);
	float getCamangle(void);
	bool getHandbrakeState(void);
	Position *getStartPos(void);
	
	/*Draw */
	virtual void draw(void);

	/* Input handling */
	void handleInputs(bool *keyStates, bool *specialKeyStates);

	/* Movement handling */
	void handleMovement(double deltaTime);

	void setCamera(bool autoRotate);

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

	/* Collision handling */
	virtual void collision(Object *o);
	virtual void collision(TrackPart *tp);
	virtual void collision(BRT *brt);
};

#endif