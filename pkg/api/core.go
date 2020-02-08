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

func handleFunc(rawElementsPtr uintptr, rawElementsLen uintptr) int64 {
	log.Println("Do nothing here")
	return 0

	length := int32(rawElementsLen)

	for i := 0; i < int(length); i++ {
		rawElementPtr := unsafe.Pointer(rawElementsPtr + uintptr(i))
		element := types.UintptrToElement(uintptr(rawElementPtr))
		log.Printf("@@@ %+v\n", element)
	}

	return 0
}
