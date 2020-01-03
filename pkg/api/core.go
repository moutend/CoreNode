package api

import (
	"bytes"
	"fmt"
	"io"
	"log"
	"net/http"
)

func GetCore(w http.ResponseWriter, r *http.Request) error {
	if _, err := io.Copy(w, bytes.NewBufferString(`{}`)); err != nil {
		log.Println(err)
		return fmt.Errorf("Internal error")
	}

	return nil
}
