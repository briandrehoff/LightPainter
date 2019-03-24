// Fill out your copyright notice in the Description page of Project Settings.

#include "PaintingGridCard.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/StereoLayerFunctionLibrary.h"

void UPaintingGridCard::SetPaintingName(FString NewPaintingName)
{
	PaintingName = NewPaintingName;

	SlotName->SetText(FText::FromString(PaintingName));

	CardButton->OnClicked.AddDynamic(this, &UPaintingGridCard::CardButtonClicked);
}

void UPaintingGridCard::CardButtonClicked()
{
	//UStereoLayerFunctionLibrary::ShowSplashScreen(); // This is required to prevent the long hang that happens when you open the level
	UGameplayStatics::OpenLevel(GetWorld(), "Canvas", true, "SlotName=" + PaintingName);
}