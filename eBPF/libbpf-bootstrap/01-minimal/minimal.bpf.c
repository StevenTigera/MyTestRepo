#include "vmlinux.h"
#include <bpf/bpf_helpers.h>

int my_pid = 0;

SEC("tp/syscalls/sys_enter_write")
int handle_tp(void *ctx)
{
	u64 pid_tgid = bpf_get_current_pid_tgid();
	int pid = pid_tgid >> 32;

	bpf_printk("stevepro pid_tgid %ull\n", pid_tgid);
	bpf_printk("stevepro my_pid   %d\n", my_pid);
	bpf_printk("stevepro    pid   %d\n", pid);

	if (pid != my_pid)
	{
		return 0;
	}

	bpf_printk("adriana BPF triggered from PID %d\n", pid);
	return 0;
}

//char LICENSE[] SEC("license") = "Dual BSD/GPL";
char LICENSE[] SEC("license") = "GPL";