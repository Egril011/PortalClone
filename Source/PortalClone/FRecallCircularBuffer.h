// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class PORTALCLONE_API FRecallCircularBuffer
{
public:
	explicit FRecallCircularBuffer(int _capacity);
	~FRecallCircularBuffer();

	// To save the variables and push to the next index
	void Push_Head(const FVector& Position, const FQuat& Rotation,
		const float& TimeSec);

	// Get the Position and Rotation from the new or old index  
	bool  GetNewest(int IndexFromNewest, FVector& OutPosition, FQuat& OutRotation,
		float& OutTimeSec) const;
	
	bool IsFull() const;
	int GetSize() const;
	void Clear();

private:
	struct FCircularBufferSave
	{
		float TimeSeconds;
		FVector Position;
		FQuat Rotation;
	};
	
	int Capacity = 0;
	int Head = 0;
	int Count = 0;
	TArray<FCircularBufferSave> Buffer;
};
