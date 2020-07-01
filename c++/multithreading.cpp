#include <iostream>
#include "core/thread_manager.hpp"

int main()
{

    //create a self-scaling thread manager, that keeps track of what is where and why the world
    //keeps rotating
	auto& mgr = pixl::core::DynamicSizeThreadManager::get_instance()
		.respect_max_threads()
		.set_percentage(1.4F)
		.orphan_buffer();


	mgr.spin_up([](auto thread_id)
	{
		std::cout << "hello world" << std::endl;
	});

	mgr.join();
}