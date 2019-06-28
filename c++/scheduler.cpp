//Pool Runner
void Scheduler::schedulerPoolRunner()
{
  using namespace std::literals;

  while(m_keepPoolAlive) {
    //pre check if there is any work
    if(!m_poolTasks.empty())
    {
      //prime the task with 0 work
      runnable task =  runnable::create<&no_task>();
      {
        std::unique_lock<std::mutex> lock(poolTaskMutex);

        //check again (maybe a different runner already snacked the task)
        if(!m_poolTasks.empty())
        {
          //run the task in the back
          task = m_poolTasks.back();
          m_poolTasks.pop_back();
        } // else continue;// (not needed as we prime with 0-work)
      }
      //execute the task
      task();
    } else {
      //if there isn't, sleep for a bit
      std::this_thread::sleep_for(1ms);
    }
  }
}
