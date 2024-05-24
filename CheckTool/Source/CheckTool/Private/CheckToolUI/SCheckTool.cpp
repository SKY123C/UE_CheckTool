#include "SCheckTool.h"
#include "Widgets/Layout/SWrapBox.h"
#include "Widgets/Layout/SGridPanel.h"
#include "Widgets/Input/SSpinBox.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/SFrameRatePicker.h"


void SCheckToolWindow::Construct(const FArguments& InArgs, TSharedRef<FCheckTooler> InCheckTooler)
{
	TSharedPtr<SVerticalBox> Layout;
	ChildSlot
		[
		
			SNew(SVerticalBox)
			+ SVerticalBox::Slot().AutoHeight()
			[
				SAssignNew(SectionSelectorBox, SWrapBox)
				.UseAllottedSize(true)
				.HAlign(EHorizontalAlignment::HAlign_Center)

			]
			+ SVerticalBox::Slot().Padding(0,5,0,0)
			[
				SAssignNew(Layout, SVerticalBox)
			]
		
	];
	for (int Index = 0; Index < TabLabels.Num(); Index++)
	{
		FName Label = TabLabels[Index];
		TMap<FName, TSharedRef<SCheckBox>> TabMap;
		TSharedRef<SCheckBox> CheckBox = SNew(SCheckBox)
										.Style(FAppStyle::Get(), "DetailsView.SectionButton")
										.OnCheckStateChanged(this, &SCheckToolWindow::OnTabClicked, Index)
										[
											SNew(STextBlock)
											.TextStyle(FAppStyle::Get(), "SmallText")
											.Text(FText::FromName(Label))
										];
		TabStack.Add(CheckBox);
		SectionSelectorBox->AddSlot()
			[
				CheckBox
			];
		TSharedRef<SBorder> a =SNew(SBorder)
		[
			SNew(SButton)
			.Text(FText::FromName(Label))
		];
		WidgetStack.Add(a);
		Layout->AddSlot()[a];
	}

}

void SCheckToolWindow::OnTabClicked(ECheckBoxState NewCheckboxState, int32 TabIndex)
{
	if (TabIndex >= TabLabels.Num())
	{
		return;
	}
	for (int Index = 0; Index < TabStack.Num(); Index++)
	{
		TSharedRef<SCheckBox> CheckBox = TabStack[Index];
		auto Widget = WidgetStack[Index];
		if (Index != TabIndex)
		{
			CheckBox->SetIsChecked(ECheckBoxState::Unchecked);
			Widget->SetVisibility(EVisibility::Collapsed);

		}
		else
		{
			CheckBox->SetIsChecked(ECheckBoxState::Checked);
			Widget->SetVisibility(EVisibility::Visible);
		}
			

	}


}
