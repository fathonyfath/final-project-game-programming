#include "Game\bullet_impact.h"

void BulletImpact::update(GameEngine * engine) {
	if (duration < maxDuration) {
		duration += engine->getDeltaReadOnly();
	} else {
		isActive = false;
	}
}
