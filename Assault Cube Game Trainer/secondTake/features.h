#pragma once
#define PI 3.14159f
#define radians(degrees) (degrees * (( PI / 180.0f)))

#include <Windows.h>
#include "structs and globals.h"
#include <math.h>
#include <vadefs.h>

void updateDistance(RelativeEntity* enemy) {
	enemy->relativeX = enemy->entity->head.x - myself->head.x;
	enemy->relativeY = enemy->entity->head.y - myself->head.y;
	enemy->relativeZ = enemy->entity->head.z - myself->head.z;

	enemy->distanceFromMe = (float)sqrt(pow(enemy->relativeX, 2) + pow(enemy->relativeY, 2));
}

void applyAimbot(uintptr_t playerAmount) {
	static RelativeEntity relativeEntities[32] = { 0 };

	for (uintptr_t i = 0; i < playerAmount; i++) {
		playerList = (EntityList*)(*(uintptr_t*)(baseAddress + 0x18AC04));
		//update current entry
		RelativeEntity* entry = &relativeEntities[i];
		entry->entity = &playerList->entities[i];
		updateDistance(entry);

		//check if closest is null
		if (closestEntity.entity == NULL) {
			closestEntity.entity = entry->entity;
			updateDistance(&closestEntity);
		}

		if (entry->distanceFromMe < closestEntity.distanceFromMe && entry->distanceFromMe != 0) {
			closestEntity.entity = entry->entity;
			updateDistance(&closestEntity);
		}
		updateDistance(&closestEntity);
	}

	if (closestEntity.entity && closestEntity.entity->isDead)
		return;

	//calculate new pitch
	float pitchResult = (float)atan2(closestEntity.relativeZ, closestEntity.distanceFromMe);
	pitchResult *= (180 / PI);

	//calculate new yaw
	float yawResult = (float)atan2(closestEntity.relativeY, closestEntity.relativeX);
	yawResult = (yawResult * 180 / PI);
	yawResult += 90;

	myself->pitch = pitchResult;
	myself->yaw = yawResult;
}

void fly(float flySpeed) {
	if (GetAsyncKeyState('W')) {
		float yawRadians = radians(myself->yaw) - 1.57f;
		float pitchRadians = radians(myself->pitch);

		if (myself->pitch <= -89) {
			myself->body.z -= (float)(flySpeed * sin(yawRadians));
		}
		else if (myself->pitch >= 89) {
			myself->body.z += (float)(flySpeed * sin(yawRadians));
		}
		else {
			myself->body.y += (float)(flySpeed * sin(yawRadians));
			myself->body.x += (float)(flySpeed * cos(yawRadians));
			myself->body.z += (float)(flySpeed * sin(pitchRadians));
		}
	}

	if (GetAsyncKeyState('A')) {
		float radians = radians(myself->yaw) - 3.14f;

		myself->body.y += (float)(flySpeed * sin(radians));
		myself->body.x += (float)(flySpeed * cos(radians));
	}

	if (GetAsyncKeyState('D')) {
		float radians = radians(myself->yaw);

		myself->body.y += (float)(flySpeed * sin(radians));
		myself->body.x += (float)(flySpeed * cos(radians));
	}

	if (GetAsyncKeyState('S')) {
		float yawRadians = radians(myself->yaw) + 1.57f;
		float pitchRadians = radians(myself->pitch);

		if (myself->pitch <= -87)
			myself->body.z += (float)(flySpeed * sin(yawRadians));
		else if (myself->pitch >= 87) {
			myself->body.z -= (float)(flySpeed * sin(yawRadians));
		}
		else {
			myself->body.y += (float)(flySpeed * sin(yawRadians));
			myself->body.x += (float)(flySpeed * cos(yawRadians));
			myself->body.z -= (float)(flySpeed * sin(pitchRadians));
		}
	}
}

