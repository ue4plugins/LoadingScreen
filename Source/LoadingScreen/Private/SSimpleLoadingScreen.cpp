// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "LoadingScreenPrivatePCH.h"

#include "SScaleBox.h"
#include "SSafeZone.h"
#include "SThrobber.h"

#include "SSimpleLoadingScreen.h"

#define LOCTEXT_NAMESPACE "LoadingScreen"

/////////////////////////////////////////////////////
// SSimpleLoadingScreen

void SSimpleLoadingScreen::Construct(const FArguments& InArgs, const FLoadingScreenDescription& InScreenDescription)
{
	const ULoadingScreenSettings* Settings = GetDefault<ULoadingScreenSettings>();

	TSharedRef<SOverlay> Root = SNew(SOverlay);

	if ( InScreenDescription.Images.Num() > 0 )
	{
		int32 ImageIndex = FMath::RandRange(0, InScreenDescription.Images.Num() - 1);
		const FStringAssetReference& ImageAsset = InScreenDescription.Images[ImageIndex];
		UObject* ImageObject = ImageAsset.TryLoad();
		if ( UTexture2D* LoadingImage = Cast<UTexture2D>(ImageObject) )
		{
			FVector2D Size = FVector2D(LoadingImage->GetSizeX(), LoadingImage->GetSizeY());
			LoadingScreenBrush = MakeShareable(new FLoadingScreenBrush(LoadingImage, Size, FName(*ImageAsset.ToString())));

			Root->AddSlot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				SNew(SScaleBox)
				.Stretch(InScreenDescription.ImageStretch)
				[
					SNew(SImage)
					.Image(LoadingScreenBrush.Get())
				]
			];
		}
	}

	TSharedRef<SWidget> TipWidget = SNullWidget::NullWidget;
	if ( Settings->Tips.Num() > 0 )
	{
		int32 TipIndex = FMath::RandRange(0, Settings->Tips.Num() - 1);

		TipWidget = SNew(STextBlock)
			.WrapTextAt(500.0f)
			.Text(Settings->Tips[TipIndex]);
	}

	Root->AddSlot()
	.HAlign(HAlign_Fill)
	.VAlign(VAlign_Bottom)
	[
		SNew(SBorder)
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.BorderBackgroundColor(FLinearColor(0, 0, 0, 0.75))
		.BorderImage(FCoreStyle::Get().GetBrush("WhiteBrush"))
		[
			SNew(SSafeZone)
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Bottom)
			.IsTitleSafe(true)
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.Padding(FMargin(25.0f, 0.0f, 0, 0))
				.AutoWidth()
				.VAlign(VAlign_Center)
				[
					SNew(STextBlock)
					.Text(LOCTEXT("Loading", "LOADING"))
				]

				+ SHorizontalBox::Slot()
				.Padding(FMargin(40, 0.0f, 0, 0))
				.VAlign(VAlign_Center)
				.AutoWidth()
				[
					SNew(SThrobber)
					.NumPieces(10)
					.Animate(SThrobber::Horizontal)
				]

				+ SHorizontalBox::Slot()
				.FillWidth(1)
				.HAlign(HAlign_Fill)
				[
					SNew(SSpacer)
					.Size(FVector2D(1.0f, 1.0f))
				]

				+ SHorizontalBox::Slot()
				.AutoWidth()
				.HAlign(HAlign_Right)
				[
					TipWidget
				]
			]
		]
	];

	ChildSlot
	[
		Root
	];
}

#undef LOCTEXT_NAMESPACE