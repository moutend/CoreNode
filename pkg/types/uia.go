//go:generate stringer -type=UIAEvent
//go:generate stringer -type=UIAControlType
package types

// UIAEvent represents UI Automation Event Identifiers.
// Fore more details, see the ooficial document on MSDN.
//
// https://docs.microsoft.com/en-us/windows/win32/winauto/uiauto-event-ids
type UIAEvent int

const (
	UIA_ActiveTextPositionChangedEventId                 UIAEvent = 20032
	UIA_AsyncContentLoadedEventId                        UIAEvent = 20006
	UIA_AutomationFocusChangedEventId                    UIAEvent = 20005
	UIA_AutomationPropertyChangedEventId                 UIAEvent = 20004
	UIA_ChangesEventId                                   UIAEvent = 20034
	UIA_Drag_DragCancelEventId                           UIAEvent = 20027
	UIA_Drag_DragCompleteEventId                         UIAEvent = 20028
	UIA_Drag_DragStartEventId                            UIAEvent = 20026
	UIA_DropTarget_DragEnterEventId                      UIAEvent = 20029
	UIA_DropTarget_DragLeaveEventId                      UIAEvent = 20030
	UIA_DropTarget_DroppedEventId                        UIAEvent = 20031
	UIA_HostedFragmentRootsInvalidatedEventId            UIAEvent = 20025
	UIA_InputDiscardedEventId                            UIAEvent = 20022
	UIA_InputReachedOtherElementEventId                  UIAEvent = 20021
	UIA_InputReachedTargetEventId                        UIAEvent = 20020
	UIA_Invoke_InvokedEventId                            UIAEvent = 20009
	UIA_LayoutInvalidatedEventId                         UIAEvent = 20008
	UIA_LiveRegionChangedEventId                         UIAEvent = 20024
	UIA_MenuClosedEventId                                UIAEvent = 20007
	UIA_MenuModeEndEventId                               UIAEvent = 20019
	UIA_MenuModeStartEventId                             UIAEvent = 20018
	UIA_MenuOpenedEventId                                UIAEvent = 20003
	UIA_NotificationEventId                              UIAEvent = 20035
	UIA_Selection_InvalidatedEventId                     UIAEvent = 20013
	UIA_SelectionItem_ElementAddedToSelectionEventId     UIAEvent = 20010
	UIA_SelectionItem_ElementRemovedFromSelectionEventId UIAEvent = 20011
	UIA_SelectionItem_ElementSelectedEventId             UIAEvent = 20012
	UIA_StructureChangedEventId                          UIAEvent = 20002
	UIA_SystemAlertEventId                               UIAEvent = 20023
	UIA_Text_TextChangedEventId                          UIAEvent = 20015
	UIA_Text_TextSelectionChangedEventId                 UIAEvent = 20014
	UIA_TextEdit_ConversionTargetChangedEventId          UIAEvent = 20033
	UIA_TextEdit_TextChangedEventId                      UIAEvent = 20032
	UIA_ToolTipClosedEventId                             UIAEvent = 20001
	UIA_ToolTipOpenedEventId                             UIAEvent = 20000
	UIA_Window_WindowClosedEventId                       UIAEvent = 20017
	UIA_Window_WindowOpenedEventId                       UIAEvent = 20016
)

// UIAControlType represents UI Automation Control Type Identifiers.
// For more details, see the official document on MSDN.
//
// https://docs.microsoft.com/en-us/windows/win32/winauto/uiauto-controltype-ids
type UIAControlType int

const (
	UIA_AppBarControlTypeId       UIAControlType = 50040
	UIA_ButtonControlTypeId       UIAControlType = 50000
	UIA_CalendarControlTypeId     UIAControlType = 50001
	UIA_CheckBoxControlTypeId     UIAControlType = 50002
	UIA_ComboBoxControlTypeId     UIAControlType = 50003
	UIA_CustomControlTypeId       UIAControlType = 50025
	UIA_DataGridControlTypeId     UIAControlType = 50028
	UIA_DataItemControlTypeId     UIAControlType = 50029
	UIA_DocumentControlTypeId     UIAControlType = 50030
	UIA_EditControlTypeId         UIAControlType = 50004
	UIA_GroupControlTypeId        UIAControlType = 50026
	UIA_HeaderControlTypeId       UIAControlType = 50034
	UIA_HeaderItemControlTypeId   UIAControlType = 50035
	UIA_HyperlinkControlTypeId    UIAControlType = 50005
	UIA_ImageControlTypeId        UIAControlType = 50006
	UIA_ListControlTypeId         UIAControlType = 50008
	UIA_ListItemControlTypeId     UIAControlType = 50007
	UIA_MenuBarControlTypeId      UIAControlType = 50010
	UIA_MenuControlTypeId         UIAControlType = 50009
	UIA_MenuItemControlTypeId     UIAControlType = 50011
	UIA_WindowControlTypeId       UIAControlType = 50032
	UIA_PaneControlTypeId         UIAControlType = 50033
	UIA_ProgressBarControlTypeId  UIAControlType = 50012
	UIA_RadioButtonControlTypeId  UIAControlType = 50013
	UIA_ScrollBarControlTypeId    UIAControlType = 50014
	UIA_SemanticZoomControlTypeId UIAControlType = 50039
	UIA_SeparatorControlTypeId    UIAControlType = 50038
	UIA_SliderControlTypeId       UIAControlType = 50015
	UIA_SpinnerControlTypeId      UIAControlType = 50016
	UIA_SplitButtonControlTypeId  UIAControlType = 50031
	UIA_StatusBarControlTypeId    UIAControlType = 50017
	UIA_TabControlTypeId          UIAControlType = 50018
	UIA_TabItemControlTypeId      UIAControlType = 50019
	UIA_TableControlTypeId        UIAControlType = 50036
	UIA_TextControlTypeId         UIAControlType = 50020
	UIA_ThumbControlTypeId        UIAControlType = 50027
	UIA_TitleBarControlTypeId     UIAControlType = 50037
	UIA_ToolBarControlTypeId      UIAControlType = 50021
	UIA_ToolTipControlTypeId      UIAControlType = 50022
	UIA_TreeControlTypeId         UIAControlType = 50023
	UIA_TreeItemControlTypeId     UIAControlType = 50024
)
