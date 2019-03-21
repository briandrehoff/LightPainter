// Fill out your copyright notice in the Description page of Project Settings.

#include "PainterSaveGame.h"
#include "Kismet/GameplayStatics.h"

UPainterSaveGame * UPainterSaveGame::Create()
{
	return Cast<UPainterSaveGame>(UGameplayStatics::CreateSaveGameObject(StaticClass()));;
}

bool UPainterSaveGame::Save()
{
	return UGameplayStatics::SaveGameToSlot(this, "Test", 0);
}

UPainterSaveGame * UPainterSaveGame::Load()
{
	return Cast<UPainterSaveGame>(UGameplayStatics::LoadGameFromSlot("Test", 0));
}