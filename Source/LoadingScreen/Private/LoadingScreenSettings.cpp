// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "LoadingScreenPrivatePCH.h"
#include "LoadingScreenSettings.h"

#define LOCTEXT_NAMESPACE "LoadingScreen"

FLoadingScreenDescription::FLoadingScreenDescription()
	: MinimumLoadingScreenDisplayTime(-1)
	, bAutoCompleteWhenLoadingCompletes(true)
	, bMoviesAreSkippable(true)
	, bWaitForManualStop(false)
	, bShowUIOverlay(true)
	, LoadingText(LOCTEXT("Loading", "LOADING"))
	, ImageStretch(EStretch::ScaleToFit)
{
	if ( !IsRunningDedicatedServer() )
	{
		static ConstructorHelpers::FObjectFinder<UFont> RobotoFontObj(TEXT("/Engine/EngineFonts/Roboto"));
		LoadingFont = FSlateFontInfo(RobotoFontObj.Object, 32, FName("Bold"));
	}
}

ULoadingScreenSettings::ULoadingScreenSettings(const FObjectInitializer& Initializer)
	: Super(Initializer)
{
	TipWrapAt = 1000.0f;

	if ( !IsRunningDedicatedServer() )
	{
		static ConstructorHelpers::FObjectFinder<UFont> RobotoFontObj(TEXT("/Engine/EngineFonts/Roboto"));
		TipFont = FSlateFontInfo(RobotoFontObj.Object, 20, FName("Normal"));
	}
}

#undef LOCTEXT_NAMESPACE
