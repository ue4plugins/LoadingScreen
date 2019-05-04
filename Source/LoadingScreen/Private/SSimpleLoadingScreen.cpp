// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "SSimpleLoadingScreen.h"

#include "Widgets/SOverlay.h"
#include "Widgets/SBoxPanel.h"
#include "Widgets/Layout/SScaleBox.h"
#include "Widgets/Layout/SSpacer.h"
#include "Widgets/Layout/SBorder.h"
#include "Widgets/Layout/SSafeZone.h"
#include "Widgets/Layout/SDPIScaler.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Images/SImage.h"
#include "Widgets/Images/SThrobber.h"
#include "Engine/Texture2D.h"
#include "Engine/UserInterfaceSettings.h"
#include "Slate/DeferredCleanupSlateBrush.h"

#define LOCTEXT_NAMESPACE "LoadingScreen"

/////////////////////////////////////////////////////
// SSimpleLoadingScreen

static float PointSizeToSlateUnits(float PointSize)
{
	//FreeTypeConstants::HorizontalDPI = 96;
	const float SlateFreeTypeHorizontalResolutionDPI = 96.0f;
	const float FreeTypeNativeDPI = 72.0f;
	const float PixelSize = PointSize * (SlateFreeTypeHorizontalResolutionDPI / FreeTypeNativeDPI);

	return PixelSize;
}

void SSimpleLoadingScreen::Construct(const FArguments& InArgs, const FLoadingScreenDescription& InScreenDescription)
{
	const ULoadingScreenSettings* Settings = GetDefault<ULoadingScreenSettings>();

	const FSlateFontInfo& TipFont = Settings->TipFont;
	const FSlateFontInfo& LoadingFont = Settings->LoadingFont;

	TSharedRef<SOverlay> Root = SNew(SOverlay);

	// If there's an image defined
	if ( InScreenDescription.Images.Num() > 0 )
	{
		const int32 ImageIndex = FMath::RandRange(0, InScreenDescription.Images.Num() - 1);
		const FStringAssetReference& ImageAsset = InScreenDescription.Images[ImageIndex];
		UObject* ImageObject = ImageAsset.TryLoad();
		if ( UTexture2D* LoadingImage = Cast<UTexture2D>(ImageObject) )
		{
			LoadingScreenBrush = FDeferredCleanupSlateBrush::CreateBrush(LoadingImage);

			Root->AddSlot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				SNew(SBorder)
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				.BorderBackgroundColor(InScreenDescription.BackgroundColor)
				.BorderImage(FCoreStyle::Get().GetBrush("WhiteBrush"))
				[
					SNew(SScaleBox)
					.Stretch(InScreenDescription.ImageStretch)
					[
						SNew(SImage)
						.Image(LoadingScreenBrush.IsValid() ? LoadingScreenBrush->GetSlateBrush() : nullptr)
					]
				]
			];
		}
	}

	TSharedRef<SWidget> TipWidget = SNullWidget::NullWidget;
	if ( Settings->Tips.Num() > 0 )
	{
		const int32 TipIndex = FMath::RandRange(0, Settings->Tips.Num() - 1);

		TipWidget = SNew(STextBlock)
			.WrapTextAt(Settings->TipWrapAt)
			.Font(TipFont)
			.Text(Settings->Tips[TipIndex]);
	}
	else
	{
		// Need to use a spacer when being rendered on another thread, incrementing the SNullWidget will
		// lead to shared ptr crashes.
		TipWidget = SNew(SSpacer);
	}

	Root->AddSlot()
	.HAlign(HAlign_Fill)
	.VAlign(VAlign_Bottom)
	[
		SNew(SBorder)
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.BorderBackgroundColor(InScreenDescription.TipBackgroundColor)
		.BorderImage(FCoreStyle::Get().GetBrush("WhiteBrush"))
		[
			SNew(SSafeZone)
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Bottom)
			.IsTitleSafe(true)
			[
				SNew(SDPIScaler)
				.DPIScale(this, &SSimpleLoadingScreen::GetDPIScale)
				[
					SNew(SHorizontalBox)

					+ SHorizontalBox::Slot()
					.Padding(FMargin(25, 0.0f, 0, 0))
					.VAlign(VAlign_Center)
					.AutoWidth()
					[
						SNew(SCircularThrobber)
						.Radius(PointSizeToSlateUnits(LoadingFont.Size) / 2.0f)
					]

					+ SHorizontalBox::Slot()
					.Padding(FMargin(40.0f, 0.0f, 0, 0))
					.AutoWidth()
					.VAlign(VAlign_Center)
					[
						SNew(STextBlock)
						.Text(InScreenDescription.LoadingText)
						.Font(LoadingFont)
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
					.VAlign(VAlign_Center)
					.Padding(FMargin(10.0f))
					[
						TipWidget
					]
				]
			]
		]
	];

	ChildSlot
	[
		Root
	];
}

float SSimpleLoadingScreen::GetDPIScale() const
{
	const FVector2D& DrawSize = GetCachedGeometry().ToPaintGeometry().GetLocalSize();
	const FIntPoint Size((int32)DrawSize.X, (int32)DrawSize.Y);
	return GetDefault<UUserInterfaceSettings>()->GetDPIScaleBasedOnSize(Size);
}

#undef LOCTEXT_NAMESPACE
