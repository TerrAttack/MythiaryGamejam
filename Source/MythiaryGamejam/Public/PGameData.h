// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */

enum class Direction : uint8
{
	INVALID = 7		UMETA(DisplayName = "INVALID"),
	FORWARD = 0		UMETA(DisplayName = "FORWARD"),
	RIGHT = 1		UMETA(DisplayName = "RIGHT"),
	BACK = 2		UMETA(DisplayName = "BACK"),
	LEFT = 3		UMETA(DisplayName = "LEFT"),
	DOWN = 4		UMETA(DisplayName = "DOWN"),
	UP = 5			UMETA(DisplayName = "UP")
};

static TMap<Direction, FVector> Directions
{
	{Direction::FORWARD, {1,0, 0}},
	{Direction::RIGHT, {0,1, 0}},
	{Direction::BACK, {-1,0, 0}},
	{Direction::LEFT, {0,-1, 0}},
	{Direction::DOWN, {0,0, -1}},
	{Direction::UP, {0,0, 1}},
};

class MYTHIARYGAMEJAM_API PGameData
{
public:
	PGameData();
	~PGameData();
};
