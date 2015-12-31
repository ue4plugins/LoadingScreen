// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "LoadingScreenPrivatePCH.h"
#include "LoadingScreenSettings.h"

FLoadingScreenDescription::FLoadingScreenDescription()
	: MinimumLoadingScreenDisplayTime(-1)
	, bAutoCompleteWhenLoadingCompletes(true)
	, bMoviesAreSkippable(true)
	, bWaitForManualStop(false)
	, ImageStretch(EStretch::ScaleToFit)
{
}

bool FLoadingScreenDescription::IsValid() const
{
	return MoviePaths.Num() > 0 || Images.Num() > 0;
}

ULoadingScreenSettings::ULoadingScreenSettings(const FObjectInitializer& Initializer)
	: Super(Initializer)
{
}