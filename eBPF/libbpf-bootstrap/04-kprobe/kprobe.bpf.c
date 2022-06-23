#include "vmlinux.h"
#include <bpf/bpf_helpers.h>
#include <bpf/bpf_core_read.h>

int BPF_KPROBE(int dfd, struct filename *name)
{
	pid_t pid;
	const char *filename;

	pid = bpf_get_current_pid_tgid() >> 32;
	filename = BPF_CORE_READ(name, name);
	bpf_printk("KPROBE ENTRY pid = %d, filename = %s\n", pid, filename);
	return 0;
	return 0;
}

SEC("kretprobe/do_unlinkat")
int BPF_KRETPROBE(long ret)
{
	pid_t pid;

	pid = bpf_get_current_pid_tgid() >> 32;
	bpf_printk("KPROBE EXIT: pid = %d, ret = %ld\n", pid, ret);
	return 0;
}

char LICENSE[] SEC("license") = "GPL";