package app

import (
	"context"
	"fmt"
	"log"
	"net/http"
	"sync"
	"syscall"
	"unsafe"

	"github.com/moutend/CoreNode/pkg/api"
	"github.com/moutend/CoreNode/pkg/dll"
	"github.com/moutend/CoreNode/pkg/mux"
	"github.com/moutend/CoreNode/pkg/types"
)

func handleFunc(rawEventPtr uintptr) int64 {
	event := types.UintptrToEvent(rawEventPtr)

	log.Printf(
		"Name:%v\tClassName:%v\tAriaRole:%v\tProcessName:%v\tControlTypeId:%v\tRole:%v\tEventId:%v\tLocation:{%v,%v,%v,%v}\n",
		event.Element.Name,
		event.Element.ClassName,
		event.Element.AriaRoleName,
		event.Element.ProcessName,
		event.Element.ControlTypeId,
		event.Element.Role,
		event.EventId,
		event.Element.Left,
		event.Element.Top,
		event.Element.Width,
		event.Element.Height,
	)

	return 0
}

type app struct {
	m         *sync.Mutex
	wg        *sync.WaitGroup
	server    *http.Server
	isRunning bool
}

func (a *app) setup() error {
	var code int32

	dll.ProcSetup.Call(uintptr(unsafe.Pointer(&code)), 0, syscall.NewCallback(handleFunc))

	if code != 0 {
		return fmt.Errorf("Failed to call dll.ProcSetup.Call()")
	}

	mux := mux.New()

	mux.Get("/v1/core", api.GetCore)
	mux.Get("/v1/core/bulk", api.GetCoreBulk)

	a.server = &http.Server{
		Addr:    ":7903",
		Handler: mux,
	}

	a.wg.Add(1)

	go func() {
		if err := a.server.ListenAndServe(); err != http.ErrServerClosed {
			panic(err)
		}
		a.wg.Done()
	}()

	return nil
}

func (a *app) Setup() error {
	a.m.Lock()
	defer a.m.Unlock()

	if a.isRunning {
		fmt.Errorf("Setup is already done")
	}
	if err := a.setup(); err != nil {
		return err
	}

	a.isRunning = true

	return nil
}

func (a *app) teardown() error {
	var code int32

	dll.ProcTeardown.Call(uintptr(unsafe.Pointer(&code)))

	if code != 0 {
		return fmt.Errorf("Failed to call dll.ProcTeardown.Call()")
	}

	if err := a.server.Shutdown(context.TODO()); err != nil {
		return err
	}

	a.wg.Wait()

	return nil
}

func (a *app) Teardown() error {
	a.m.Lock()
	defer a.m.Unlock()

	if !a.isRunning {
		return fmt.Errorf("Teardown is already done")
	}
	if err := a.teardown(); err != nil {
		return err
	}

	a.isRunning = false

	return nil
}

func New() *app {
	return &app{
		m:  &sync.Mutex{},
		wg: &sync.WaitGroup{},
	}
}
