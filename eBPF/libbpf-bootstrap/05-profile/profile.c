#include "profile.skel.h"
#include "profile.h"
//#include "blazesym.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/syscall.h>
#include <sys/sysinfo.h>
#include <linux/perf_event.h>
#include <bpf/libbpf.h>
#include <bpf/bpf.h>

static long perf_event_open(struct perf_event_attr *hw_event, pid_t pid, int cpu, int group_fd, unsigned long flags)
{
	int ret = syscall(__NR_perf_event_open, hw_event, pid, cpu, group_fd, flags);
	return ret;
}

static struct blazesym *symbolizer;

static void show_stack_trace(__u64 *stack, int stack_sz, pid_t pid)
{

}

int main(int argc, char **argv)
{
	return 0;
}