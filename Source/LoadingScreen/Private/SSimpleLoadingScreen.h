// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "SCompoundWidget.h"
#include "LoadingScreenSettings.h"

class FDeferredCleanupSlateBrush;

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
	TSharedPtr<FDeferredCleanupSlateBrush> LoadingScreenBrush;
	float LastComputedDPIScale;
};
