// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "SScaleBox.h"

#include "LoadingScreenSettings.generated.h"

USTRUCT(BlueprintType)
struct LOADINGSCREEN_API FLoadingScreenDescription
{
	GENERATED_USTRUCT_BODY()

	FLoadingScreenDescription();

	/** The minimum time that a loading screen should be opened for, -1 if there is no minimum time. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Loading)
	float MinimumLoadingScreenDisplayTime;

	/** If true, the loading screen will disappear as soon as all movies are played and loading is done. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Loading)
	bool bAutoCompleteWhenLoadingCompletes;

	/** If true, movies can be skipped by clicking the loading screen as long as loading is done. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Loading)
	bool bMoviesAreSkippable;

	/** If true, movie playback continues until Stop is called. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Loading)
	bool bWaitForManualStop;

	/**  Should we show the images/tips/loading text?  Generally you'll want to set this to false if you just want to show a movie. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Display)
	bool bShowUIOverlay;

	/**  */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Display)
	FText LoadingText;

	/**  */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Display)
	FSlateFontInfo LoadingFont;

	/** The movie paths local to the game's Content/Movies/ directory we will play. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Movies)
	TArray<FString> MoviePaths;

	/** The texture display while in the loading screen on top of the movie. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Images, meta=(AllowedClasses="Texture2D"))
	TArray<FStringAssetReference> Images;

	/** The scaling type to apply to images. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Images)
	TEnumAsByte<EStretch::Type> ImageStretch;
};

/**
 * Settings for the simple loading screen plugin.
 */
UCLASS(config=Game, defaultconfig, meta=(DisplayName="Loading Screen"))
class LOADINGSCREEN_API ULoadingScreenSettings : public UDeveloperSettings
{
	GENERATED_UCLASS_BODY()

public:

	/** The startup screen for the project. */
	UPROPERTY(config, EditAnywhere, Category=Screens)
	FLoadingScreenDescription StartupScreen;

	/** The default load screen between maps. */
	UPROPERTY(config, EditAnywhere, Category=Screens)
	FLoadingScreenDescription DefaultScreen;

	/** The font to display the tips in. */
	UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category=Advice)
	FSlateFontInfo TipFont;

	/** The size of the tip before it's wrapped to the next line. */
	UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category=Advice)
	float TipWrapAt;

	/** The tips to display on the load screen. */
	UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category=Advice)
	TArray<FText> Tips;
};
