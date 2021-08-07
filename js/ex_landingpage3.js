
//create the animation function
//this functions similarly to a main loop in a game
function animate()
{
    //immediately request another animation
    requestAnimationFrame(animate);

    //render the scene
    renderer.render(scene,camera);
    
    //update the rotation
    stars.rotation.y += 0.0005;
    stars.rotation.x += 0.0005;
}

//make one intial call to the animation function
animate();


//also handle resize events
window.addEventListener( 'resize', onWindowResize, false );

function onWindowResize()
{
    //updated the projection matrix
    camera.aspect = window.innerWidth / window.innerHeight;
    camera.updateProjectionMatrix();

    //set the size of the canvas
    renderer.setSize( window.innerWidth, window.innerHeight );

}