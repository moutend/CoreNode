package api

import (
	"bytes"
	"fmt"
	"io"
	"log"
	"net/http"
	"syscall"
	"unsafe"

	"github.com/moutend/CoreNode/pkg/dll"
	"github.com/moutend/CoreNode/pkg/types"
)

func GetCore(w http.ResponseWriter, r *http.Request) error {
	if _, err := io.Copy(w, bytes.NewBufferString(`{}`)); err != nil {
		log.Println(err)
		return fmt.Errorf("Internal error")
	}

	return nil
}

func GetCoreBulk(w http.ResponseWriter, r *http.Request) error {
	code := int32(0)

	dll.ProcBulkFetch.Call(uintptr(unsafe.Pointer(&code)), syscall.NewCallback(handleFunc))

	if code != 0 {
		err := fmt.Errorf("failed to continue")
		log.Println(err)
		return err
	}

	if _, err := io.Copy(w, bytes.NewBufferString(`{}`)); err != nil {
		log.Println(err)
		return err
	}

	return nil
}

func handleFunc(rawElementsPtr uintptr, rawElementsLen uintptr, rawProcessInfoPtr uintptr) int64 {
	length := int32(rawElementsLen)

	for i := 0; i < int(length); i++ {
		rawElementPtr := *(*uintptr)(unsafe.Pointer(rawElementsPtr + uintptr(8*i)))
		element := types.UintptrToElement(uintptr(rawElementPtr))
		log.Printf(
			"Name:%v\tClassName:%v\tAriaRole:%v\tControlTypeId:%v\tRole:%v\tIndex:%v\tDepth:%v\tLocation:{%v,%v,%v,%v}\n",
			element.Name,
			element.ClassName,
			element.AriaRoleName,
			element.ControlTypeId,
			element.Role,
			element.Index,
			element.Depth,
			element.Left,
			element.Top,
			element.Width,
			element.Height,
		)
	}

	return 0
}
