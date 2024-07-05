#include "SCheckTool.h"
#include "Widgets/Layout/SWrapBox.h"
#include "Widgets/Layout/SGridPanel.h"
#include "Widgets/Input/SSpinBox.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/SFrameRatePicker.h"
#include "CheckToolEditorSubsystem.h"
#include "PropertyEditorModule.h"
#include "IDetailsView.h"


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

		
		TSharedPtr<SVerticalBox> ExpandLayout;
		TSharedRef<SBorder> a = SNew(SBorder)
		[
			SAssignNew(ExpandLayout, SVerticalBox)
		];
		WidgetStack.Add(a);
		Layout->AddSlot()[a];

		FPropertyEditorModule& PropertyEditorModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
		UCheckToolEditorSubsystem* System = GEditor->GetEditorSubsystem<UCheckToolEditorSubsystem>();
		TArray<UCheckToolPlugin*> PluginList = System->GetPlugins();
		for (auto Plugin : PluginList)
		{
			FDetailsViewArgs DetailsViewArgs(false, false, false, FDetailsViewArgs::HideNameArea);
			DetailsViewArgs.bAllowSearch = false;
			TSharedRef<IDetailsView> DetailsWidget = PropertyEditorModule.CreateDetailView(DetailsViewArgs);
			DetailsWidget->SetObject(Plugin);
			TSharedRef<SExpandableArea> Area = SNew(SExpandableArea)
			.BodyContent()[DetailsWidget]
			.HeaderContent()
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.VAlign(VAlign_Center)
				[
					SNew(STextBlock)
					.Text(FText::FromString(Plugin->DisplayLabel))
					.Font(FAppStyle::Get().GetFontStyle("NormalFontBold"))
				]
				+ SHorizontalBox::Slot()
				.VAlign(VAlign_Center)
				.HAlign(HAlign_Right)
				.AutoWidth()
				[
					SNew(SButton)
						.ButtonStyle(FAppStyle::Get(), "SimpleButton")
						.ContentPadding(FMargin(1, 0))
						[
							SNew(SImage)
								.Image(FAppStyle::Get().GetBrush("Icons.PlusCircle"))
								.ColorAndOpacity(FSlateColor::UseForeground())
						]
				]
			];
			ExpandLayout->AddSlot()
				[
					Area
			];
		}
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

TSharedPtr<SBorder> SCheckToolWindow::GetPluginWidgetByType(UClass* InClass)
{
	
	TSharedPtr<SVerticalBox> ExpandLayout;
	FPropertyEditorModule& PropertyEditorModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	TSharedRef<SBorder> a = SNew(SBorder)
	[
		SAssignNew(ExpandLayout, SVerticalBox)
	];
	UCheckToolEditorSubsystem* System = GEditor->GetEditorSubsystem<UCheckToolEditorSubsystem>();
	TArray<UCheckToolPlugin*> PluginList = System->GetPlugins(InClass);
	for (auto Plugin : PluginList)
	{
		


	}

	return TSharedPtr<SBorder>();
}
