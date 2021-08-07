
//set camera position and background color
camera.position.setZ(45);
scene.background = new THREE.Color(0x1E2C39)

//setup materials
const star_material = new THREE.MeshBasicMaterial({color:0xFFFFFF});
const green_material = new THREE.MeshBasicMaterial({color:0x6ead3a})

function make_star() {
    const geometry = new THREE.SphereGeometry(0.25,24,24);
    //choose a random color and creaste the star mesh
    const star = new THREE.Mesh(geometry,Math.random() < 0.9 ? star_material : green_material);
   
    //set random position for the star mesh
    const [x,y,z] = Array(3).fill().map(() => Math.random() * 200 - 100)
    star.position.set(x,y,z);

    return star
}


//container for all stars
stars = new THREE.Group()

//add 200 stars to the container
for (var i = 0; i < 200; i++)
{
    stars.add(make_star())
}

//add container to scene
scene.add(stars)