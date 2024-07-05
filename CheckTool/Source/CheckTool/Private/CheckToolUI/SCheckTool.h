#pragma once
#include "Widgets/SWindow.h"
#include "CheckTooler.h"

/**
 * SCheckTool main widget
 */

 /*
 1. �Զ����expandarea ������Plugin����
 2. �Զ���ListView ÿ�в����������Instance
 3. toolbar
 4. �������δ����״̬Ϊ��ɫ����ȷΪ��ɫ��ʧ��δ��ɫ
 
 
 
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