// Fill out your copyright notice in the Description page of Project Settings.

#include "PaintingPicker.h"
#include "PaintingGrid.h"
#include "PaintingGridCard.h"
#include "ActionBar.h"

#include "Saving/PainterSaveGameIndex.h"
#include "Saving/PainterSaveGame.h"

// Sets default values
APaintingPicker::APaintingPicker()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(Root);

	PaintingGrid = CreateDefaultSubobject<UWidgetComponent>("PaintingGrid");
	PaintingGrid->SetupAttachment(GetRootComponent());

	ActionBar = CreateDefaultSubobject<UWidgetComponent>("ActionBar");
	ActionBar->SetupAttachment(GetRootComponent());
}

void APaintingPicker::BeginPlay()
{
	Super::BeginPlay();

	UActionBar* ActionBarWidget = Cast<UActionBar>(ActionBar->GetUserWidgetObject());
	if (ActionBarWidget)
	{
		ActionBarWidget->SetParentPicker(this);
	}

	RefreshSlots();
}

void APaintingPicker::RefreshSlots()
{
	UPaintingGrid* PaintingGridWidget = Cast<UPaintingGrid>(PaintingGrid->GetUserWidgetObject());
	if (!PaintingGridWidget) return;

	int32 Index = 0;
	for (FString SlotName : UPainterSaveGameIndex::Load()->GetSlotNames())
	{
		PaintingGridWidget->AddPainting(Index, SlotName);
		++Index;
	}
}

void APaintingPicker::AddPainting()
{
	UPainterSaveGame::Create();

	RefreshSlots();
}

void APaintingPicker::ToggleDeleteMode()
{
	UE_LOG(LogTemp, Warning, TEXT("Delete mode toggle pressed"));
}