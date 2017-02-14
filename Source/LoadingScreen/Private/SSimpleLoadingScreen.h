// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "SCompoundWidget.h"
#include "LoadingScreenSettings.h"

/**
* Special brush to prevent garbage collection
*/
struct FLoadingScreenBrush : public FSlateDynamicImageBrush, public FGCObject
{
	FLoadingScreenBrush(class UTexture2D* InTexture, const FVector2D& InImageSize, const FName InImagePath)
		: FSlateDynamicImageBrush(InTexture, InImageSize, InImagePath)
	{
	}

	virtual void AddReferencedObjects(FReferenceCollector& Collector) override
	{
		if ( ResourceObject )
		{
			Collector.AddReferencedObject(ResourceObject);
		}
	}
};

class SSimpleLoadingScreen : public SCompoundWidget
{
public:

	SLATE_BEGIN_ARGS(SSimpleLoadingScreen) {}

	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, const FLoadingScreenDescription& ScreenDescription);

	virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;

private:
	float GetDPIScale() const;
	
private:
	TSharedPtr<FLoadingScreenBrush> LoadingScreenBrush;
	float LastComputedDPIScale;
};
