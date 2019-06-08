function loadFile(filename)
{
  return fetch(filename).then(function(result){
    return {
      source: filename,
      contents: result.text()
    }
  })
}

function PrettyPrintCppFile(str)
{
  str = str.replace(/&/g, "&amp;");
  str = str.replace(/>/g, "&gt;");
  str = str.replace(/</g, "&lt;");
  str = str.replace(/"/g, "&quot;");
  str = str.replace(/'/g, "&#039;");
  return  PR.prettyPrintOne(str,"c++");
}

function loadcode() {
  var files = document.getElementsByClassName('loadcpp')
  for (var j = 0; j < files.length; j++) {
    loadFile(files[j].id).then(
      function(response){
        response.contents.then(
           source => document.getElementById(response.source).innerHTML = PrettyPrintCppFile(source)
         )
      }
    )
  }
}
