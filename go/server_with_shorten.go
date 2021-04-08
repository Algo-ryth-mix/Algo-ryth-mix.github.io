// The next examples have some code ommitted for brevity, 
// as always you can find the whole code on github
// https://github.com/Algo-ryth-mix/learning-go

...//server.go

//make a fileserver
fileServer := http.FileServer(http.Dir("./static"))

//route it at "/""
http.Handle("/", fileServer)

//we add a route to /shorten
http.HandleFunc("/shorten", shortenHandler)

...//shorten.go

func shortenHandler(w http.ResponseWriter, r *http.Request) {

	//parsing the POST form
	if err := r.ParseForm(); err != nil {
		fmt.Fprintf(w, "ParseForm() err: %v", err)
		return
	}

	//get the unshortened url
	long := r.FormValue("long")

	//get a new code
	counter++
	short := intToLetters(counter)

	//insert the code into the map (note that there is no checking here)
	urlStore[short] = long

	//craft a little bit of a resonse
	fmt.Fprint(w, "<!DOCTYPE html><html lang=\"en\"><body>")
	fmt.Fprintf(w, "New Short Url <a href=http://localhost:8080/r?s=%v>http://localhost:8080/r?s=%v</a>", short, short)
	fmt.Fprint(w, "</body></html>")

}

...//global.go

var urlStore map[string]string = make(map[string]string)
var counter int = 0