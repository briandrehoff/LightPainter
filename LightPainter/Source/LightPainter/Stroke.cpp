// Fill out your copyright notice in the Description page of Project Settings.

#include "Stroke.h"
#include "Components/SplineMeshComponent.h"

AStroke::AStroke()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(Root);

	StrokeMeshes = CreateDefaultSubobject<UInstancedStaticMeshComponent>("StrokeMeshes");
	StrokeMeshes->SetupAttachment(Root);
}

void AStroke::Update(FVector CursorLocation)
{
	FTransform NewStrokeTransform;
	FVector LocalCursorLocation = GetTransform().InverseTransformPosition(CursorLocation);
	NewStrokeTransform.SetLocation(LocalCursorLocation);
	StrokeMeshes->AddInstance(NewStrokeTransform);

	PreviousCursorLocation = CursorLocation;
}