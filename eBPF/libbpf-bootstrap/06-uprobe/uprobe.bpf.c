#include "vmlinux.h"
#include <bpf/bpf_helpers.h>

SEC("uprobe/func")
int BPF_KPROBE(int a, int b)
{
	bpf_printk("UPROBE ENTRY: a=%d b=%d\n", a, b);
	return 0;
}

SEC("uretprobe/func")
int BPF_KRETPROBE(int ret)
{
	bpf_printk("UPROBE EXIT: return %d\n", ret);
	return 0;
}