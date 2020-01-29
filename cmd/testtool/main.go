package main

import (
	"encoding/hex"
	"fmt"
	"log"
	"math/rand"
	"os"
	"os/signal"
	"os/user"
	"path/filepath"
	"syscall"
	"time"
	"unsafe"

	"github.com/moutend/CoreNode/pkg/dll"
	"github.com/moutend/CoreNode/pkg/types"
)

func main() {
	if err := run(os.Args); err != nil {
		log.New(os.Stderr, "", 0).Fatal(err)
	}
}

func run(args []string) error {
	rand.Seed(time.Now().Unix())
	p := make([]byte, 16)

	if _, err := rand.Read(p); err != nil {
		return err
	}

	u, err := user.Current()

	if err != nil {
		return err
	}

	fileName := fmt.Sprintf("CoreNode-%s.txt", hex.EncodeToString(p))
	outputPath := filepath.Join(u.HomeDir, "AppData", "Roaming", "ScreenReaderX", "SystemLog", fileName)
	os.MkdirAll(filepath.Dir(outputPath), 0755)

	output := types.NewBackgroundWriter(outputPath)
	defer output.Close()

	log.SetFlags(log.Ldate | log.Ltime | log.LUTC | log.Llongfile)
	log.SetOutput(output)

	var code int32

	dll.ProcSetup.Call(uintptr(unsafe.Pointer(&code)), 0, syscall.NewCallback(handleFunc))

	if code != 0 {
		log.Println("Failed to call Setup")
		return nil
	}

	log.Println("Setup is completed")

	interrupt := make(chan os.Signal, 1)
	signal.Notify(interrupt, os.Interrupt)

	<-interrupt

	log.Println("Teardown is completed")

	return nil
}

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
