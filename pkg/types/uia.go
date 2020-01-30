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
	UIA_ButtonControlTypeId       = 50000
	UIA_CalendarControlTypeId     = 50001
	UIA_CheckBoxControlTypeId     = 50002
	UIA_ComboBoxControlTypeId     = 50003
	UIA_EditControlTypeId         = 50004
	UIA_HyperlinkControlTypeId    = 50005
	UIA_ImageControlTypeId        = 50006
	UIA_ListItemControlTypeId     = 50007
	UIA_ListControlTypeId         = 50008
	UIA_MenuControlTypeId         = 50009
	UIA_MenuBarControlTypeId      = 50010
	UIA_MenuItemControlTypeId     = 50011
	UIA_ProgressBarControlTypeId  = 50012
	UIA_RadioButtonControlTypeId  = 50013
	UIA_ScrollBarControlTypeId    = 50014
	UIA_SliderControlTypeId       = 50015
	UIA_SpinnerControlTypeId      = 50016
	UIA_StatusBarControlTypeId    = 50017
	UIA_TabControlTypeId          = 50018
	UIA_TabItemControlTypeId      = 50019
	UIA_TextControlTypeId         = 50020
	UIA_ToolBarControlTypeId      = 50021
	UIA_ToolTipControlTypeId      = 50022
	UIA_TreeControlTypeId         = 50023
	UIA_TreeItemControlTypeId     = 50024
	UIA_CustomControlTypeId       = 50025
	UIA_GroupControlTypeId        = 50026
	UIA_ThumbControlTypeId        = 50027
	UIA_DataGridControlTypeId     = 50028
	UIA_DataItemControlTypeId     = 50029
	UIA_DocumentControlTypeId     = 50030
	UIA_SplitButtonControlTypeId  = 50031
	UIA_WindowControlTypeId       = 50032
	UIA_PaneControlTypeId         = 50033
	UIA_HeaderControlTypeId       = 50034
	UIA_HeaderItemControlTypeId   = 50035
	UIA_TableControlTypeId        = 50036
	UIA_TitleBarControlTypeId     = 50037
	UIA_SeparatorControlTypeId    = 50038
	UIA_SemanticZoomControlTypeId = 50039
	UIA_AppBarControlTypeId       = 50040
)
