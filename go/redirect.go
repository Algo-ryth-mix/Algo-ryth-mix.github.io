//in server.go we add another HandleFunc with "/r" as the route


... //shorten.go
func redirectHandler(w http.ResponseWriter, r *http.Request) {

	//parse the from (GET this time)
	if err := r.ParseForm(); err != nil {
		fmt.Fprintf(w, "ParseForm() err: %v", err)
		return
	}

	//get the key to the map
	key := r.FormValue("s")

	//check if the key exists in the map
	if val, ok := urlStore[key]; ok {

		//if it does redirect the user, using moved permanently
		http.Redirect(w, r, val, http.StatusMovedPermanently)
		return
	}

	//otherwise print that this is an invalid url
	http.Error(w, "Invalid Short URL", http.StatusMisdirectedRequest)
}