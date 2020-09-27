function loadFile(filename) {
  return fetch(filename).then(function (result) {
    return {
      source: filename,
      contents: result.text(),
    };
  });
}

function findGetParameter(parameterName) {
  var result = null,
      tmp = [];
  location.search
      .substr(1)
      .split("&")
      .forEach(function (item) {
        tmp = item.split("=");
        if (tmp[0] === parameterName) result = decodeURIComponent(tmp[1]);
      });
  return result;
}

function make_manifest(content)
{
  return "#autogen-manifest\neaster-egg\nnav\n" + content
}

function make_blog_entry(content,location)
{
  if(content.startsWith("<!-- Blog -->")){
    console.log("find:" + content.search("<!-- Jumplink -->").toString());
    const title = content.substr(content.search("<!--Title")+10,content.search("Title-->") - content.search("<!--Title") - 11); 
    return content.substr(0,content.search("<!-- Jumplink -->")) + `<br><a href='article.html?x=${location}&t=${title}'> Keep Reading </a></article>`
  }
  else return content
}

async function amalgamate(manifest,blogify = false,manifest_is_contents = false) {
  console.log("amalgamate loaded!");
  var contents = "";

  //get entries to load
  if(!manifest_is_contents)
    contents  = await loadFile("./sub/"+manifest+".txt").then(response => response.contents.then(c => c));
  else
    contents = manifest

  const root = document.getElementById("root");

  //load entries
  const promises = await contents.split("\n").map(async line => {

    //skip comments and empty lines
    if(line.startsWith("#")) return;
    if(line.length <= 1) return;

    line = line.replace(".","");
    const content = await loadFile("./sub/"+line+".html").then(response => response.contents.then(c => c));
    if(blogify)
    {
      return make_blog_entry(content,line);
    }
    //root.innerHTML+= content;
    return content;
  })

  //assemble and await entries
  fullHtml = (await Promise.all(promises)).join("\n");
  //set entries
  root.innerHTML = fullHtml;
  if(document.getElementById("amalgamate-after") != null)
  {
      amalgamate_after();
  }
}
