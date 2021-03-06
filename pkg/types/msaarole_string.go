// Code generated by "stringer -type=MSAARole"; DO NOT EDIT.

package types

import "strconv"

func _() {
	// An "invalid array index" compiler error signifies that the constant values have changed.
	// Re-run the stringer command to generate them again.
	var x [1]struct{}
	_ = x[ROLE_SYSTEM_TITLEBAR-1]
	_ = x[ROLE_SYSTEM_MENUBAR-2]
	_ = x[ROLE_SYSTEM_SCROLLBAR-3]
	_ = x[ROLE_SYSTEM_GRIP-4]
	_ = x[ROLE_SYSTEM_SOUND-5]
	_ = x[ROLE_SYSTEM_CURSOR-6]
	_ = x[ROLE_SYSTEM_CARET-7]
	_ = x[ROLE_SYSTEM_ALERT-8]
	_ = x[ROLE_SYSTEM_WINDOW-9]
	_ = x[ROLE_SYSTEM_CLIENT-10]
	_ = x[ROLE_SYSTEM_MENUPOPUP-11]
	_ = x[ROLE_SYSTEM_MENUITEM-12]
	_ = x[ROLE_SYSTEM_TOOLTIP-13]
	_ = x[ROLE_SYSTEM_APPLICATION-14]
	_ = x[ROLE_SYSTEM_DOCUMENT-15]
	_ = x[ROLE_SYSTEM_PANE-16]
	_ = x[ROLE_SYSTEM_CHART-17]
	_ = x[ROLE_SYSTEM_DIALOG-18]
	_ = x[ROLE_SYSTEM_BORDER-19]
	_ = x[ROLE_SYSTEM_GROUPING-20]
	_ = x[ROLE_SYSTEM_SEPARATOR-21]
	_ = x[ROLE_SYSTEM_TOOLBAR-22]
	_ = x[ROLE_SYSTEM_STATUSBAR-23]
	_ = x[ROLE_SYSTEM_TABLE-24]
	_ = x[ROLE_SYSTEM_COLUMNHEADER-25]
	_ = x[ROLE_SYSTEM_ROWHEADER-26]
	_ = x[ROLE_SYSTEM_COLUMN-27]
	_ = x[ROLE_SYSTEM_ROW-28]
	_ = x[ROLE_SYSTEM_CELL-29]
	_ = x[ROLE_SYSTEM_LINK-30]
	_ = x[ROLE_SYSTEM_HELPBALLOON-31]
	_ = x[ROLE_SYSTEM_CHARACTER-32]
	_ = x[ROLE_SYSTEM_LIST-33]
	_ = x[ROLE_SYSTEM_LISTITEM-34]
	_ = x[ROLE_SYSTEM_OUTLINE-35]
	_ = x[ROLE_SYSTEM_OUTLINEITEM-36]
	_ = x[ROLE_SYSTEM_PAGETAB-37]
	_ = x[ROLE_SYSTEM_PROPERTYPAGE-38]
	_ = x[ROLE_SYSTEM_INDICATOR-39]
	_ = x[ROLE_SYSTEM_GRAPHIC-40]
	_ = x[ROLE_SYSTEM_STATICTEXT-41]
	_ = x[ROLE_SYSTEM_TEXT-42]
	_ = x[ROLE_SYSTEM_PUSHBUTTON-43]
	_ = x[ROLE_SYSTEM_CHECKBUTTON-44]
	_ = x[ROLE_SYSTEM_RADIOBUTTON-45]
	_ = x[ROLE_SYSTEM_COMBOBOX-46]
	_ = x[ROLE_SYSTEM_DROPLIST-47]
	_ = x[ROLE_SYSTEM_PROGRESSBAR-48]
	_ = x[ROLE_SYSTEM_DIAL-49]
	_ = x[ROLE_SYSTEM_HOTKEYFIELD-50]
	_ = x[ROLE_SYSTEM_SLIDER-51]
	_ = x[ROLE_SYSTEM_SPINBUTTON-52]
	_ = x[ROLE_SYSTEM_DIAGRAM-53]
	_ = x[ROLE_SYSTEM_ANIMATION-54]
	_ = x[ROLE_SYSTEM_EQUATION-55]
	_ = x[ROLE_SYSTEM_BUTTONDROPDOWN-56]
	_ = x[ROLE_SYSTEM_BUTTONMENU-57]
	_ = x[ROLE_SYSTEM_BUTTONDROPDOWNGRID-58]
	_ = x[ROLE_SYSTEM_WHITESPACE-59]
	_ = x[ROLE_SYSTEM_PAGETABLIST-60]
	_ = x[ROLE_SYSTEM_CLOCK-61]
	_ = x[ROLE_SYSTEM_SPLITBUTTON-62]
	_ = x[ROLE_SYSTEM_IPADDRESS-63]
	_ = x[ROLE_SYSTEM_OUTLINEBUTTON-64]
}

const _MSAARole_name = "ROLE_SYSTEM_TITLEBARROLE_SYSTEM_MENUBARROLE_SYSTEM_SCROLLBARROLE_SYSTEM_GRIPROLE_SYSTEM_SOUNDROLE_SYSTEM_CURSORROLE_SYSTEM_CARETROLE_SYSTEM_ALERTROLE_SYSTEM_WINDOWROLE_SYSTEM_CLIENTROLE_SYSTEM_MENUPOPUPROLE_SYSTEM_MENUITEMROLE_SYSTEM_TOOLTIPROLE_SYSTEM_APPLICATIONROLE_SYSTEM_DOCUMENTROLE_SYSTEM_PANEROLE_SYSTEM_CHARTROLE_SYSTEM_DIALOGROLE_SYSTEM_BORDERROLE_SYSTEM_GROUPINGROLE_SYSTEM_SEPARATORROLE_SYSTEM_TOOLBARROLE_SYSTEM_STATUSBARROLE_SYSTEM_TABLEROLE_SYSTEM_COLUMNHEADERROLE_SYSTEM_ROWHEADERROLE_SYSTEM_COLUMNROLE_SYSTEM_ROWROLE_SYSTEM_CELLROLE_SYSTEM_LINKROLE_SYSTEM_HELPBALLOONROLE_SYSTEM_CHARACTERROLE_SYSTEM_LISTROLE_SYSTEM_LISTITEMROLE_SYSTEM_OUTLINEROLE_SYSTEM_OUTLINEITEMROLE_SYSTEM_PAGETABROLE_SYSTEM_PROPERTYPAGEROLE_SYSTEM_INDICATORROLE_SYSTEM_GRAPHICROLE_SYSTEM_STATICTEXTROLE_SYSTEM_TEXTROLE_SYSTEM_PUSHBUTTONROLE_SYSTEM_CHECKBUTTONROLE_SYSTEM_RADIOBUTTONROLE_SYSTEM_COMBOBOXROLE_SYSTEM_DROPLISTROLE_SYSTEM_PROGRESSBARROLE_SYSTEM_DIALROLE_SYSTEM_HOTKEYFIELDROLE_SYSTEM_SLIDERROLE_SYSTEM_SPINBUTTONROLE_SYSTEM_DIAGRAMROLE_SYSTEM_ANIMATIONROLE_SYSTEM_EQUATIONROLE_SYSTEM_BUTTONDROPDOWNROLE_SYSTEM_BUTTONMENUROLE_SYSTEM_BUTTONDROPDOWNGRIDROLE_SYSTEM_WHITESPACEROLE_SYSTEM_PAGETABLISTROLE_SYSTEM_CLOCKROLE_SYSTEM_SPLITBUTTONROLE_SYSTEM_IPADDRESSROLE_SYSTEM_OUTLINEBUTTON"

var _MSAARole_index = [...]uint16{0, 20, 39, 60, 76, 93, 111, 128, 145, 163, 181, 202, 222, 241, 264, 284, 300, 317, 335, 353, 373, 394, 413, 434, 451, 475, 496, 514, 529, 545, 561, 584, 605, 621, 641, 660, 683, 702, 726, 747, 766, 788, 804, 826, 849, 872, 892, 912, 935, 951, 974, 992, 1014, 1033, 1054, 1074, 1100, 1122, 1152, 1174, 1197, 1214, 1237, 1258, 1283}

func (i MSAARole) String() string {
	i -= 1
	if i < 0 || i >= MSAARole(len(_MSAARole_index)-1) {
		return "MSAARole(" + strconv.FormatInt(int64(i+1), 10) + ")"
	}
	return _MSAARole_name[_MSAARole_index[i]:_MSAARole_index[i+1]]
}
