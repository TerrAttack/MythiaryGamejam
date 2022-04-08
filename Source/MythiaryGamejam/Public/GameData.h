// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */

enum class Direction : uint8 {
	BACK = 0		UMETA(DisplayName = "BACK"),
	FORWARD = 1		UMETA(DisplayName = "FORWARD"),
	LEFT = 2		UMETA(DisplayName = "LEFT"),
	RIGHT = 3		UMETA(DisplayName = "RIGHT"),
	DOWN = 5		UMETA(DisplayName = "DOWN"),
	UP = 6			UMETA(DisplayName = "UP")
};

static TMap<Direction, FVector> Directions
{
	{Direction::BACK, {-1,0, 0}},
	{Direction::FORWARD, {1,0, 0}},
	{Direction::LEFT, {0,-1, 0}},
	{Direction::RIGHT, {0,1, 0}},
	{Direction::DOWN, {0,0, -1}},
	{Direction::UP, {0,0, 1}},
};

class MYTHIARYGAMEJAM_API GameData
{
public:
	GameData();
	~GameData();
};
