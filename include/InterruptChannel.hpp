#ifndef MESOS_INTERRUPT_CHANNEL_
#define MESOS_INTERRUPT_CHANNEL_
#include <MesosChannel.hpp>
#include <mutex>

namespace mesos        {
namespace perl         {

class InterruptChannel : public MesosChannel
{
public:
    std::queue<MesosCommand>* pending_;

    typedef void (*interrupt_cb_t) (void *, int);

    InterruptChannel(interrupt_cb_t interrupt_cb = NULL, void* interrupt_arg = NULL);
    ~InterruptChannel();
    void send(const MesosCommand& command);
    const MesosCommand recv();
    MesosChannel* share();
    size_t size();
    int fd (){ return -1; };

private:
    int* count_;
    std::mutex* mutex_;
    interrupt_cb_t interrupt_cb_;
    void* interrupt_arg_;
};

} // namespace perl         {
} // namespace mesos        {


#endif // MESOS_INTERRUPT_CHANNEL_
