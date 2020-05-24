#include <pixl/filesystem.hpp>
#include <pixl/graphics.hpp>
#include <pixl/net.hpp> //not actually a thing, hopefully in the future ?

//get some aliases
namespace fs = pixl::fs;
namespace net = pixl::net;
namespace gfx = pixl::graphics;

//create a bunch of registries
//note that only one of them is a normal provider that points to a directory
provider_registry::gen_provider<sandbox_provider>("./assets/sandbox/","sandbox");
provider_registry::gen_provider<virtual_provider>("./pixlfs/assets.pp.xz","virtual", fs::READONLY);
provider_registry::gen_provider<network_provider>(net::game_server->files(),"network");

//We traverse all of the providers with the same
//function, also we can traverse into archives
auto folder  = fs::view("sandbox://my_game_folder/pack1.pp");
auto archive = fs::view("virtual://assets/");
auto remote  = fs::view("network://remote_game_folder");


//get a subfolder for all of them
auto fimages = folder ["images"];
auto aimages = archive["images"];
auto rimages = remote ["images"];

//note this is an alternative form to traverse the filesystem,
//I am not sure about this one yet, personally I like it, but it
//does kinda look weird
auto something = folder/"somewhereelse";

//combining a view, allows you to merge multiple providers into
//one. a search for a file in all of them, takes the first occurence from left to right
auto finder = fs::combined_view(fimages,aimages,rimages);

//find a file in the combined view, note that we deserialize directly into
//any supported type, a type needs to define a custom loader for that
auto my_texture = finder.find("something.jpg").as<gfx::Texture2D>();
