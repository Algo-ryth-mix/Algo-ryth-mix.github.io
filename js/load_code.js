function loadFile(filename)
{
  return fetch(filename).then(function(result){
    return {
      source: filename,
      contents: result.text()
    }
  })
}

function match_loader(loader,language,meta)
{
  var files = document.getElementsByClassName(loader)
  for (var j = 0; j < files.length; j++) {
    loadFile(files[j].id).then(
      function(response){
        response.contents.then(
           source => document.getElementById(response.source).innerHTML =  Prism.highlight(source,language,meta)
         )
      }
    )
  }
}


function loadcode() {
  match_loader('loadjs',Prism.languages.js,'js')
  match_loader('loadcpp',Prism.languages.cpp,'cpp')
  match_loader('loadyml',Prism.languages.yaml,'yaml')
  match_loader('loadbash',Prism.languages.bash,'bash')
  match_loader('loadlua',Prism.languages.lua,'lua')
  match_loader('loadpy',Prism.languages.lua,'py')
}
