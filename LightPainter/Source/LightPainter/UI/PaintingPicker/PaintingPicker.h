// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WidgetComponent.h"
#include "PaintingGrid.h"

#include "PaintingPicker.generated.h"

UCLASS()
class LIGHTPAINTER_API APaintingPicker : public AActor
{
	GENERATED_BODY()
	
public:	
	APaintingPicker();
	void AddPainting();
	void ToggleDeleteMode();

protected:
	virtual void BeginPlay() override;

private:
	void RefreshSlots();
	int32 GetNumberOfPages() const;
	UPaintingGrid* GetPaintingGrid() const { return Cast<UPaintingGrid>(PaintingGrid->GetUserWidgetObject()); }

	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere)
	UWidgetComponent* PaintingGrid;

	UPROPERTY(VisibleAnywhere)
	UWidgetComponent* ActionBar;

};
