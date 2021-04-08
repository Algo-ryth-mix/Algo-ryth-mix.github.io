package main

// we need something to log and the http stuff
import (
	"log"
	"net/http"
)

func main() {

	//make a fileserver
	fileServer := http.FileServer(http.Dir("./static"))

	//route it at "/""
	http.Handle("/", fileServer)

	//start the server and log any potential errors
	if err := http.ListenAndServe(":8080", nil); err != nil {
		log.Fatalf("Could not start server! %v", err)
	}
}
