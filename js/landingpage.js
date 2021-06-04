const scene = new THREE.Scene();

const camera = new THREE.PerspectiveCamera(75,window.innerWidth/window.innerHeight,0.1,1000);

const renderer = new THREE.WebGLRenderer({
     canvas : document.querySelector('#bg'),
});

renderer.setPixelRatio(window.devicePixelRatio);
renderer.setSize(window.innerWidth,window.innerHeight);

camera.position.setZ(45);

const star_material = new THREE.MeshBasicMaterial({color:0xFFFFFF});

function make_star() {
    const geometry = new THREE.SphereGeometry(0.25,24,24);
    const star = new THREE.Mesh(geometry,star_material);
    const [x,y,z] = Array(3).fill().map(() => Math.random() * 200 - 100)

    star.position.set(x,y,z);
    return star
}

scene.background = new THREE.Color(0x1E2C39)

stars = new THREE.Group()

for (var i = 0; i < 200; i++)
{
    stars.add(make_star())
}
scene.add(stars)

radians = 0;

function animate()
{
    radians += 10;
    requestAnimationFrame(animate);
    renderer.render(scene,camera);
    stars.rotation.y += 0.0005;
    stars.rotation.x += 0.0005;
}
animate();