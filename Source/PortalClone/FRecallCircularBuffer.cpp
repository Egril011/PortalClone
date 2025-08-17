// Fill out your copyright notice in the Description page of Project Settings.


#include "FRecallCircularBuffer.h"

FRecallCircularBuffer::FRecallCircularBuffer(int _capacity): Capacity(_capacity)
{
	if (Capacity <= 0)
		return;

	Buffer.SetNumZeroed(Capacity);
}

FRecallCircularBuffer::~FRecallCircularBuffer()
{
}

void FRecallCircularBuffer::Push_Head(const FVector& Position, const FQuat& Rotation,
	const float& TimeSec)
{
	Buffer[Head].Position = Position;
	Buffer[Head].Rotation = Rotation;
	Buffer[Head].TimeSeconds = TimeSec;

	Head = (Head + 1) % Capacity;

	if (Count < Capacity)
		Count++;
}

bool FRecallCircularBuffer::GetNewest(int IndexFromNewest, FVector& OutPosition, FQuat& OutRotation,
	float& OutTimeSec) const
{
	if (IndexFromNewest < 0 || IndexFromNewest >= Count)
		return false;

	const int Index = (Head - 1 - IndexFromNewest + Capacity) % Capacity;

	OutPosition = Buffer[Index].Position;
	OutRotation = Buffer[Index].Rotation;
	OutTimeSec = Buffer[Index].TimeSeconds;
	return true;
}

bool FRecallCircularBuffer::IsFull() const
{
	if (Count == Capacity)
		return true;
	
	return false;
}

int FRecallCircularBuffer::GetSize() const
{
	return Count;
}

