// Fill out your copyright notice in the Description page of Project Settings.

#include "PaintingPicker.h"
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
	UE_LOG(LogTemp, Warning, TEXT("Number of pages: %d"), GetNumberOfPages());

	if (!GetPaintingGrid()) return;

	GetPaintingGrid()->AddPaginationDot(true);
	GetPaintingGrid()->AddPaginationDot(false);
	GetPaintingGrid()->AddPaginationDot(false);

	GetPaintingGrid()->ClearPaintings();

	int32 Index = 0;
	for (FString SlotName : UPainterSaveGameIndex::Load()->GetSlotNames())
	{
		GetPaintingGrid()->AddPainting(Index, SlotName);
		++Index;
	}
}

int32 APaintingPicker::GetNumberOfPages() const
{
	if (!GetPaintingGrid()) return 0;
	int32 TotalNumberOfSlots = UPainterSaveGameIndex::Load()->GetSlotNames().Num();
	int32 SlotsPerPage = GetPaintingGrid()->GetNumberOfSlots();
	return FMath::CeilToInt((float) TotalNumberOfSlots / SlotsPerPage);
}

void APaintingPicker::AddPainting()
{
	UPainterSaveGame::Create();

	RefreshSlots();
}

void APaintingPicker::ToggleDeleteMode()
{
	if (!GetPaintingGrid()) return;

	GetPaintingGrid()->ClearPaintings();
}