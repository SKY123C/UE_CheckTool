#pragma once
#include "Widgets/SWindow.h"
#include "CheckTooler.h"

/**
 * SCheckTool main widget
 */

class SCheckToolWindow : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SCheckToolWindow)
		{
		}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, TSharedRef<FCheckTooler> InCheckTooler);

	void OnTabClicked(ECheckBoxState NewCheckboxState, int32 TabIndex);

private:

	TSharedPtr<class SWrapBox> SectionSelectorBox;
	
	TArray<FName> TabLabels = { TEXT("Info"), TEXT("Collection"), TEXT("Plugins"), TEXT("Log") };
	TArray<TSharedRef<SCompoundWidget>> WidgetStack;
	TArray<TSharedRef<SCheckBox>> TabStack;
};