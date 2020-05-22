function nav_update(root) {


  //get the navigation
  var nav = document.getElementsByClassName("navigation")[0];


  if(root != null)
  {
    for (var j = 0; j < nav.childNodes.length; j++) {
      //check if the node is a div
      if (nav.childNodes[j].tagName == "DIV")
        //remove the active class from it
        if (nav.childNodes[j].childNodes[0].classList.contains(root))
          nav.childNodes[j].childNodes[0].classList.add("active")
        else
          nav.childNodes[j].childNodes[0].classList.remove("active");
    }
  }

  //iterate over all children of the Navigation
  for (var i = 0; i < nav.childNodes.length; i++) {
    //add a click handler to them
    nav.childNodes[i].addEventListener("click", function () {

        //handle burger-menu thing
        if(this.tagName == "I")
        {
            if(nav.classList.contains("mobile_active"))
            {
                nav.classList.remove("mobile_active")
            }
            else nav.classList.add("mobile_active")

            return
        }

      //inside the click handler iterate over all elements of the nav
      for (var j = 0; j < nav.childNodes.length; j++) {
        //check if the node is a div
        if (nav.childNodes[j].tagName == "DIV")
          //remove the active class from it
          nav.childNodes[j].childNodes[0].classList.remove("active");
      }

      //add the active class to this node only
      this.childNodes[0].classList.add("active");
    });
  }
}
