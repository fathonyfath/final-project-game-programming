#include "Game\game_state.h"

#include "Engine\game_engine.h"
#include "Game\menu_state.h"

#include <glm\gtx\compatibility.hpp>
#include <cmath>

#define TINYC2_IMPL
#include "Engine\Util\tinyc2.h"

GameState GameState::_instance;

void GameState::init(GameEngine* engine) {
	this->camera = new Camera(engine->getScreenWidth(), engine->getScreenHeight());

	this->planeTexture = ResourceManager::getTexture("Player");
	this->planeShadowTexture = ResourceManager::getTexture("PlayerShadow");
	this->pesawatBulletTexture = ResourceManager::getTexture("Bullet");
	this->backgroundTexture = ResourceManager::getTexture("Background");
	this->enemyBoxTexture = ResourceManager::getTexture("EnemyBox");
	this->enemyBoxShadowTexture = ResourceManager::getTexture("EnemyBoxShadow");
	this->bulletImpactTexture = ResourceManager::getTexture("BulletImpact");
	this->enemyBulletTexture = ResourceManager::getTexture("EnemyBullet");
	this->bulletImpactEnemyTexture = ResourceManager::getTexture("EnemyBulletImpact");
	this->targetTexture = ResourceManager::getTexture("Target");
	this->shieldTexture = ResourceManager::getTexture("Shield");
	this->health1Filled = ResourceManager::getTexture("HealthFilled");
	this->health1Empty = ResourceManager::getTexture("HealthEmpty");

	this->health2Filled = ResourceManager::getTexture("HealthFilled");
	this->health2Empty = ResourceManager::getTexture("HealthEmpty");

	this->health3Filled = ResourceManager::getTexture("HealthFilled");
	this->health3Empty = ResourceManager::getTexture("HealthEmpty");

	Shader shader = ResourceManager::getShader("Sprite");

	renderer = new SpriteRenderer(shader);
	camera->updateShaderViewProjection(shader);

	firstState = true;

	this->background = new GameObject(*renderer, backgroundTexture, glm::vec3(520, 620, 0));
	this->background->position = glm::vec3(0, 0, 0);

	// Initialize GameObjects
	planeGameObject = new Plane(*renderer, planeTexture, glm::vec3(40, 40, 0));
	planeGameObject->position = glm::vec3(0, 0, 0);
	planeShadowObject = new GameObject(*renderer, planeShadowTexture, glm::vec3(20, 20, 0));

	durationBetweenSpawn = 2.0f;
	maxWave = 50;
	currentWave = 1;
	currentDuration = durationBetweenSpawn;

	enemies.clear();

	// Shiled etc
	this->shieldObject = new GameObject(*renderer, shieldTexture, glm::vec3(58, 58, 0));
	this->targetObject = new GameObject(*renderer, targetTexture, glm::vec3(44, 43, 0));

	this->gameOverDelay = 3.0f;

	health1Object = new GameObject(*renderer, health1Filled, glm::vec3(19, 18, 0));
	health2Object = new GameObject(*renderer, health2Filled, glm::vec3(19, 18, 0));
	health3Object = new GameObject(*renderer, health3Filled, glm::vec3(19, 18, 0));

	health3Object->position = glm::vec3(-260 + 19, 310 - 18, 0);
	health2Object->position = glm::vec3(-260 + 19 + 22, 310 - 18, 0);
	health1Object->position = glm::vec3(-260 + 19 + 22 + 22, 310 - 18, 0);
}

void GameState::cleanup(GameEngine* engine) {
	delete(this->camera);
	delete(this->renderer);
}

void GameState::pause(GameEngine* engine) {
}

void GameState::resume(GameEngine* engine) {
}

void GameState::handleEvents(GameEngine * engine) {
	glm::vec3 mousePos = camera->screenToWorldSpace(engine->getMousePos());
	planeGameObject->mousePositionToWorld = mousePos;

	if (engine->leftMouseDown() && canShot && planeGameObject->health > 0) {
		shoot(planeGameObject->position, planeGameObject->rotation);
		engine->playBeam();
		canShot = false;
	}

	if (engine->rightMouseDown() && planeGameObject->health > 0) {
		getAndUpdateNearestEnemyPlane();
	}
}

void GameState::update(GameEngine * engine) {
	if (firstState) {
		cooldown = 0.1f;
		firstState = false;
		return;
	}

	if (!canShot) {
		if (currentTime < cooldown) {
			currentTime += engine->getDeltaReadOnly();
		} else {
			currentTime = 0.0f;
			canShot = true;
		}
	}

	updateLevelWave(engine->getDeltaReadOnly());

	planeGameObject->update(engine);
	planeShadowObject->rotation = planeGameObject->rotation;
	planeShadowObject->position.x = planeGameObject->position.x - 20.0f;
	planeShadowObject->position.y = planeGameObject->position.y - 20.0f;


	// Enemy gameObject
	for (unsigned int i = 0; i < enemies.size(); ++i) {
		EnemyPlane* enemyGameObject = enemies[i];
		GameObject* enemyShadow = enemiesShadow[i];
		enemyGameObject->update(engine);
		enemyShadow->rotation = enemyGameObject->rotation;
		enemyShadow->position.x = enemyGameObject->position.x - 20.0f;
		enemyShadow->position.y = enemyGameObject->position.y - 20.0f;
	}

	// Bullet gameObject
	for (unsigned int i = 0; i < bullets.size(); ++i) {
		Bullet* bulletGameObject = bullets[i];
		if ((bulletGameObject->position.x > 400.0f || bulletGameObject->position.x < -400.0f) ||
			(bulletGameObject->position.y > 400.0f || bulletGameObject->position.y < -400.0f)) {
			bullets.erase(bullets.begin() + i);
		}
	}

	for (unsigned int i = 0; i < bullets.size(); ++i) {
		Bullet* bulletGameObject = bullets[i];
		bulletGameObject->update(engine);
	}

	for (unsigned int i = 0; i < bulletsToPlayer.size(); ++i) {
		Bullet* bulletGameObject = bulletsToPlayer[i];
		if ((bulletGameObject->position.x > 400.0f || bulletGameObject->position.x < -400.0f) ||
			(bulletGameObject->position.y > 400.0f || bulletGameObject->position.y < -400.0f)) {
			bulletsToPlayer.erase(bulletsToPlayer.begin() + i);
		}
	}

	for (unsigned int i = 0; i < bulletsToPlayer.size(); ++i) {
		Bullet* bulletGameObject = bulletsToPlayer[i];
		bulletGameObject->update(engine);
	}


	// Collision Check Bullet to EnemyPlane
	for (unsigned int i = 0; i < enemies.size(); ++i) {
		EnemyPlane* enemyGameObject = enemies[i];
		for (unsigned int j = 0; j < bullets.size(); ++j) {
			Bullet* bulletGameObject = bullets[j];
			int collisionCheck = c2CircletoCircle(enemyGameObject->collider, bulletGameObject->collider);
			if (collisionCheck) {
				BulletImpact* impact = new BulletImpact(*renderer, this->bulletImpactTexture, glm::vec3(12, 23, 0));
				impact->position = bulletGameObject->position;
				impact->rotation = bulletGameObject->rotation;
				bulletImpacts.push_back(impact);

				bullets.erase(bullets.begin() + j);
				engine->playHit();
				enemyGameObject->health--;
				if (enemyGameObject->health <= 0) {
					engine->playExplosion();
					enemyGameObject->isDead = true;
					enemyPlaneDestroyed(enemyGameObject->position, enemyGameObject->rotation);
					enemies.erase(enemies.begin() + i);
					enemiesShadow.erase(enemiesShadow.begin() + i);
				}
			}
		}
	}

	// Collision check between enemy to player
	for (unsigned int i = 0; i < enemies.size(); ++i) {
		EnemyPlane* enemyGameObject = enemies[i];
		int collisionCheck = c2CircletoCircle(planeGameObject->collider, enemyGameObject->collider);
		if (collisionCheck && !planeGameObject->shieldActive) {
			engine->playHit();
			planeGameObject->resetShiled();
			planeGameObject->health--;
			if (planeGameObject->health <= 0) {
				engine->playExplosion();
			}
		}
	}

	// Collision check between enemy bullet to player
	for (unsigned int i = 0; i < bulletsToPlayer.size(); ++i) {
		Bullet* bulletToPlayer = bulletsToPlayer[i];
		int collisionCheck = c2CircletoCircle(planeGameObject->collider, bulletToPlayer->collider);
		if (collisionCheck) {
			BulletImpact* impact = new BulletImpact(*renderer, this->bulletImpactEnemyTexture, glm::vec3(17, 10, 0));
			impact->position = bulletToPlayer->position;
			impact->rotation = bulletToPlayer->rotation;
			bulletImpacts.push_back(impact);

			bulletsToPlayer.erase(bulletsToPlayer.begin() + i);
			if (!planeGameObject->shieldActive) {
				engine->playHit();
				planeGameObject->resetShiled();
				planeGameObject->health--;
				if (planeGameObject->health <= 0) {
					engine->playExplosion();
				}
			}
		}
	}

	for (unsigned int i = 0; i < bulletImpacts.size(); ++i) {
		BulletImpact* bulletImpact = bulletImpacts[i];
		bulletImpact->update(engine);

		if (!bulletImpact->isActive) {
			bulletImpacts.erase(bulletImpacts.begin() + i);
		}
	}

	if (planeGameObject->currentTarget != NULL) {
		EnemyPlane* enemy = (EnemyPlane*) planeGameObject->currentTarget;
		if (enemy->isDead) {
			getAndUpdateNearestEnemyPlane();
		}
	}

	// Sync shield position
	shieldObject->position = planeGameObject->position;

	// Sync target position
	if (planeGameObject->currentTarget != NULL) {
		targetObject->position = planeGameObject->currentTarget->position;
	}

	if (planeGameObject->health <= 0) {
		gameOverDelay -= engine->getDeltaReadOnly();
	}
	if (gameOverDelay <= 0.0f) {
		engine->popState();
		engine->changeState(MenuState::instance());
	}

	if (planeGameObject->health == 3) {
		health1Object->setSprite(health1Filled);
		health2Object->setSprite(health2Filled);
		health3Object->setSprite(health3Filled);
	} else if (planeGameObject->health == 2) {
		health1Object->setSprite(health1Empty);
		health2Object->setSprite(health2Filled);
		health3Object->setSprite(health3Filled);
	} else if (planeGameObject->health == 1) {
		health1Object->setSprite(health1Empty);
		health2Object->setSprite(health2Empty);
		health3Object->setSprite(health3Filled);
	} else if (planeGameObject->health == 0) {
		health1Object->setSprite(health1Empty);
		health2Object->setSprite(health2Empty);
		health3Object->setSprite(health3Empty);
	} else {
		health1Object->setSprite(health1Empty);
		health2Object->setSprite(health2Empty);
		health3Object->setSprite(health3Empty);
	}
}

void GameState::draw(GameEngine * engine) {
	glViewport(0, 0, engine->getScreenWidth(), engine->getScreenHeight());
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	background->render();

	// Render all shadow
	if (planeGameObject->health > 0) {
		planeShadowObject->render();
	}

	for (unsigned int i = 0; i < enemiesShadow.size(); ++i) {
		GameObject* enemyShadow = enemiesShadow[i];
		enemyShadow->render();
	}

	for (unsigned int i = 0; i < bullets.size(); ++i) {
		Bullet* bulletGameObject = bullets[i];
		bulletGameObject->render();
	}

	for (unsigned int i = 0; i < bulletsToPlayer.size(); ++i) {
		Bullet* bulletToPlayer = bulletsToPlayer[i];
		bulletToPlayer->render();
	}

	for (unsigned int i = 0; i < enemies.size(); ++i) {
		EnemyPlane* enemyGameObject = enemies[i];
		enemyGameObject->render();
	}

	if (planeGameObject->health > 0) {
		planeGameObject->render();
	}

	for (unsigned int i = 0; i < bulletImpacts.size(); ++i) {
		BulletImpact* bulletImpact = bulletImpacts[i];
		bulletImpact->render();
	}

	if (planeGameObject->currentTarget != NULL) {
		targetObject->render();
	}

	if (planeGameObject->shieldActive && planeGameObject->health > 0) {
		shieldObject->render();
	}

	health1Object->render();
	health2Object->render();
	health3Object->render();

	glDisable(GL_BLEND);
}

void GameState::getAndUpdateNearestEnemyPlane() {
	if (enemies.empty()) {
		planeGameObject->setTarget(NULL);
		return;
	}
	GameObject* nearest = enemies[0];
	for (unsigned int i = 0; i < enemies.size(); ++i) {
		EnemyPlane* enemyGameObject = enemies[i];
		float oldDistance = glm::distance(planeGameObject->position, nearest->position);
		float newDistance = glm::distance(planeGameObject->position, enemyGameObject->position);
		if (newDistance < oldDistance) {
			nearest = enemyGameObject;
		}
	}
	planeGameObject->setTarget(nearest);
}

void GameState::updateLevelWave(float deltaTime) {
	if (enemies.empty()) {
		if (currentDuration > 0.0f) {
			currentDuration -= deltaTime;
		} else {
			currentDuration = durationBetweenSpawn;
			for (int i = 0; i < currentWave; ++i) {
				EnemyPlane* enemyPlane = new EnemyPlane(*renderer, enemyBoxTexture, glm::vec3(20, 20, 0));
				GameObject* enemyShadow = new GameObject(*renderer, enemyBoxShadowTexture, glm::vec3(10, 10, 0));
				enemies.push_back(enemyPlane);
				enemiesShadow.push_back(enemyShadow);
			}
			if (currentWave < maxWave) {
				currentWave++;
			}

			planeGameObject->resetShiled();
			getAndUpdateNearestEnemyPlane();
		}
	}
}

void GameState::shoot(glm::vec3 position, float rotation) {
	Bullet* bullet = new Bullet(*renderer, pesawatBulletTexture, glm::vec3(5, 9, 0), 2000.0f);
	bullet->position = position;
	bullet->rotation = rotation;
	bullets.push_back(bullet);
}

void GameState::enemyPlaneDestroyed(glm::vec3 position, float rotation) {
	float dir1 = rotation;
	float dir2 = rotation + 90.0f;
	float dir3 = rotation + 180.0f;
	float dir4 = rotation + 270.0f;

	Bullet* dir1Bullet = new Bullet(*renderer, enemyBulletTexture, glm::vec3(5, 9, 0), 200.0f);
	dir1Bullet->position = position;
	dir1Bullet->rotation = dir1;
	Bullet* dir2Bullet = new Bullet(*renderer, enemyBulletTexture, glm::vec3(5, 9, 0), 200.0f);
	dir2Bullet->position = position;
	dir2Bullet->rotation = dir2;
	Bullet* dir3Bullet = new Bullet(*renderer, enemyBulletTexture, glm::vec3(5, 9, 0), 200.0f);
	dir3Bullet->position = position;
	dir3Bullet->rotation = dir3;
	Bullet* dir4Bullet = new Bullet(*renderer, enemyBulletTexture, glm::vec3(5, 9, 0), 200.0f);
	dir4Bullet->position = position;
	dir4Bullet->rotation = dir4;
	bulletsToPlayer.push_back(dir1Bullet);
	bulletsToPlayer.push_back(dir2Bullet);
	bulletsToPlayer.push_back(dir3Bullet);
	bulletsToPlayer.push_back(dir4Bullet);
}
