// structs and globals.h
// global variables at the end of the file

#pragma once
#include <stdbool.h>
#include <stdint.h>
#include <vadefs.h>

typedef struct {
	float x, y;
} vec2;

typedef struct {
	float x, y, z;
} vec3;

typedef struct {
	char pad_0000[4]; //0x0000
	vec3 head; //0x0004
	char pad_0010[24]; //0x0010
	vec3 body; //0x0028
	float yaw; //0x0038
	float pitch; //0x0034
	float roll; //0x003C
	float upwardsForce; //0x0040
	char pad_0044[12]; //0x0044
	float currHeadHeight; //0x0050
	float headHeightCourched; //0x0054
	char pad_0058[30]; //0x0058
	bool isDead; //0x0076
	char pad_0077[117]; //0x0077
	uint32_t health; //0x00EC
	char pad_00F0[276]; //0x00F0
	char name[16]; //0x0204
	char pad_0214[248]; //0x0214
	int32_t team; //0x030C
}Entity;

typedef struct {
	uintptr_t address;
	int total_offsets;
	int offsets[5];
}Pointer;

typedef struct {
	Entity* entity;
	float relativeX;
	float relativeY;
	float relativeZ;
	float distanceFromMe;
}
RelativeEntity;

typedef struct {
	char pad_0000[4]; //0x0000a
	Entity* entities; //0x0004
}EntityList;

EntityList* playerList;
Entity* myself;
uintptr_t baseAddress;
RelativeEntity closestEntity;
