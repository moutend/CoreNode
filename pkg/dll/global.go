package dll

import (
	"syscall"
)

var (
	dll = syscall.NewLazyDLL("CoreNode.dll")

	ProcSetup     = dll.NewProc("Setup")
	ProcTeardown  = dll.NewProc("Teardown")
	ProcBulkFetch = dll.NewProc("BulkFetch")
)
