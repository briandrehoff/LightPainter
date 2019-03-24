// Fill out your copyright notice in the Description page of Project Settings.

#include "PainterSaveGameIndex.h"
#include "Kismet/GameplayStatics.h"

const FString UPainterSaveGameIndex::SLOT_NAME = "PaintingIndex";

bool UPainterSaveGameIndex::Save()
{
	UE_LOG(LogTemp, Warning, TEXT("Painting Index:"));
	for (FString SlotName : UPainterSaveGameIndex::Load()->GetSlotNames())
	{
		UE_LOG(LogTemp, Warning, TEXT("Painting name: %s"), *SlotName);
	}

	return UGameplayStatics::SaveGameToSlot(this, SLOT_NAME, 0);
}

UPainterSaveGameIndex * UPainterSaveGameIndex::Load()
{
	auto Index = Cast<UPainterSaveGameIndex>(UGameplayStatics::LoadGameFromSlot(SLOT_NAME, 0));
	if (!Index)
	{
		Index = Cast<UPainterSaveGameIndex>(UGameplayStatics::CreateSaveGameObject(StaticClass()));
		Index->Save();
	}

	return Index;
}

void UPainterSaveGameIndex::AddSaveGame(UPainterSaveGame * SaveGame)
{
	SlotNames.Add(SaveGame->GetSlotName());
}