#pragma once
#include "Widgets/SWindow.h"
#include "CheckTooler.h"

/**
 * SCheckTool main widget
 */

 /*
 1. 自定义的expandarea 参数是Plugin对象
 2. 自定义ListView 每行参数保存的是Instance
 3. toolbar
 4. 插件对象未检查的状态为灰色，正确为绿色，失败未红色
 
 
 
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

	TSharedPtr<SBorder> GetPluginWidgetByType(UClass* InClass);

private:

	TSharedPtr<class SWrapBox> SectionSelectorBox;
	
	TArray<FName> TabLabels = {TEXT("Validation")};
	TArray<TSharedRef<SCompoundWidget>> WidgetStack;
	TArray<TSharedRef<SCheckBox>> TabStack;
};