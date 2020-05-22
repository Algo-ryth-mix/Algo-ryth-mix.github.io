function loadFile(filename) {
  return fetch(filename).then(function (result) {
    return {
      source: filename,
      contents: result.text(),
    };
  });
}

async function amalgamate(manifest) {
  console.log("amalgamate loaded!");

  //get entries to load
  const contents  = await loadFile("./sub/"+manifest+".txt").then(response => response.contents.then(c => c));

  const root = document.getElementById("root");

  //load entries
  const promises = await contents.split("\n").map(async line => {

    //skip comments and empty lines
    if(line.startsWith("#")) return;
    if(line.length <= 1) return;

    line = line.replace(".","");
    const content = await loadFile("./sub/"+line+".html").then(response => response.contents.then(c => c));
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
