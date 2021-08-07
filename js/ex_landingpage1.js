
//Create the scene to render to
const scene = new THREE.Scene();

//Create the camera, this is required to render the scene later
const camera = new THREE.PerspectiveCamera(75,window.innerWidth/window.innerHeight,0.1,1000);

//Get the DOM element to render to, this must be <canvas>
const renderer = new THREE.WebGLRenderer({
     canvas : document.querySelector('#bg'),
});

//Set dpi and size of the canvas
renderer.setPixelRatio(window.devicePixelRatio);
renderer.setSize(window.innerWidth,window.innerHeight);