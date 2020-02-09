package types

import (
	"reflect"
	"syscall"
	"unsafe"
)

// RawElement is C / C++ language representation.
type RawElement struct {
	Top                int32
	Left               int32
	Width              int32
	Height             int32
	Index              int32
	Depth              int32
	ControlTypeId      int32
	Role               int32
	NameLength         int32
	ClassNameLength    int32
	AriaRoleNameLength int32
	NameData           uintptr
	ClassNameData      uintptr
	AriaRoleNameData   uintptr
}

// Element is Go language representation.
type Element struct {
	Top           int
	Left          int
	Width         int
	Height        int
	Index         int
	Depth         int
	ControlTypeId UIAControlType
	Role          MSAARole
	Name          string
	ClassName     string
	AriaRoleName  string
}

// RawEvent is C / C++ language representation.
type RawEvent struct {
	EventId int32
	Element uintptr
}

// Event is Go language representation.
type Event struct {
	EventId int
	Element Element
}

// RawProcessInfo is C / C++ representation.
type RawProcessInfo struct {
	ProcessNameLen  int32
	ProcessNameData uintptr
}

// ProcessInfo is Go representation.
type ProcessInfo struct {
	ProcessName string
}

// UintptrToString converts NULL terminated wide char string (`wchar_t *` type) to `string`.
//
// Its length is the number of wide characters except for NULL.
// Its capacity should be equal to length or larger than the length.
func UintptrToString(dataPtr uintptr, dataLen, dataCap int) string {
	if dataPtr == 0 || dataLen <= 0 || dataCap <= 0 {
		return ""
	}

	u16header := reflect.SliceHeader{Data: dataPtr, Len: dataLen, Cap: dataCap}
	u16slice := *(*[]uint16)(unsafe.Pointer(&u16header))

	return syscall.UTF16ToString(u16slice)
}

// UintptrToElement converts pointer to `RawElement` to `Element`.
func UintptrToElement(rawElementPtr uintptr) Element {
	element := Element{}

	if rawElementPtr == 0 {
		return element
	}

	rawElement := *(*RawElement)(unsafe.Pointer(rawElementPtr))

	element.Left = int(rawElement.Left)
	element.Top = int(rawElement.Top)
	element.Width = int(rawElement.Width)
	element.Height = int(rawElement.Height)
	element.Index = int(rawElement.Index)
	element.Depth = int(rawElement.Depth)

	element.ControlTypeId = UIAControlType(rawElement.ControlTypeId)
	element.Role = MSAARole(rawElement.Role)

	element.Name = UintptrToString(rawElement.NameData, int(rawElement.NameLength), int(rawElement.NameLength))
	element.ClassName = UintptrToString(rawElement.ClassNameData, int(rawElement.ClassNameLength), int(rawElement.ClassNameLength))
	element.AriaRoleName = UintptrToString(rawElement.AriaRoleNameData, int(rawElement.AriaRoleNameLength), int(rawElement.AriaRoleNameLength))

	return element
}

// UintptrToEvent converts pointer to `RawEvent` to `Event`.
func UintptrToEvent(rawEventPtr uintptr) Event {
	event := Event{}

	if rawEventPtr == 0 {
		return event
	}

	rawEvent := *(*RawEvent)(unsafe.Pointer(rawEventPtr))

	event.EventId = int(rawEvent.EventId)
	event.Element = UintptrToElement(rawEvent.Element)

	return event
}
