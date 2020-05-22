#include "pixl_pack.h"
#include <vector>
#include <cstdio>

using namespace pixl::util;
using namespace std; //don't actually do this

//some pack-data you got from somewhere, possibly a file or a network descriptor, or unzipped, whatever floats your boat
vector<uint8_t> data_you_got = from_somewhere();

//intialize a c++ reader with the data
PackReader reader(data_you_got);

//get a single file-entry
auto view = reader.filter("my_file_descriptor.txt")

//write to console
printf("%s: %s\n",view.path(),view.get().data());

