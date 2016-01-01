// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "LoadingScreenPrivatePCH.h"
#include "LoadingScreenSettings.h"

#define LOCTEXT_NAMESPACE "LoadingScreen"

FLoadingScreenDescription::FLoadingScreenDescription()
	: MinimumLoadingScreenDisplayTime(-1)
	, bAutoCompleteWhenLoadingCompletes(true)
	, bMoviesAreSkippable(true)
	, bWaitForManualStop(false)
	, ImageStretch(EStretch::ScaleToFit)
	, LoadingText(LOCTEXT("Loading", "LOADING"))
{
	if ( !UE_SERVER )
	{
		static ConstructorHelpers::FObjectFinder<UFont> RobotoFontObj(TEXT("/Engine/EngineFonts/Roboto"));
		LoadingFont = FSlateFontInfo(RobotoFontObj.Object, 32, FName("Bold"));
	}
}

bool FLoadingScreenDescription::IsValid() const
{
	return MoviePaths.Num() > 0 || Images.Num() > 0;
}

ULoadingScreenSettings::ULoadingScreenSettings(const FObjectInitializer& Initializer)
	: Super(Initializer)
{
	TipWrapAt = 1000.0f;

	if ( !UE_SERVER )
	{
		static ConstructorHelpers::FObjectFinder<UFont> RobotoFontObj(TEXT("/Engine/EngineFonts/Roboto"));
		TipFont = FSlateFontInfo(RobotoFontObj.Object, 20, FName("Normal"));
	}
}

#undef LOCTEXT_NAMESPACE
