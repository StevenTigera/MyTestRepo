#include "minimal.skel.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/resource.h>
#include <bpf/libbpf.h>

static int libbpf_print_fn(enum libbpf_print_level level, const char *format, va_list args)
{
	return vfprintf(stderr, format, args);
}

int main( int argc, char **argv)
{
	struct minimal_bpf *skel;
	int err;

	struct rlimit rlim = {
			.rlim_cur = 512UL << 20,
			.rlim_max = 512UL << 20,
	};

	err = setrlimit(RLIMIT_MEMLOCK, &rlim);
	if (err) {
		fprintf(stderr, "failed to change rlimit\n");
		return 1;
	}

	libbpf_set_strict_mode(LIBBPF_STRICT_ALL);
	// Set up libbpf errors and debug info callback.
	libbpf_set_print(libbpf_print_fn);

	// Open BPF applicaiton
	skel = minimal_bpf__open();
	if (skel)
	{
		fprintf(stderr, "Failed to open BPF sekeleton!\n");
		return 1;
	}

	// Ensure BPF program only handles write() syscalls from our process
	skel->bss->my_pid = getpid();

	// Load & verify BPF programs
	err = minimal_bpf__load(skel);
	if (err)
	{
		fprintf(stderr, "Failed to load and verify BPF skeleton\n");
		goto cleanup;
	}

	// Attach tracepoint handler
	err = minimal_bpf__attach(skel);
	if (err)
	{
		fprintf(stderr, "Failed to attach BPF skeleton\n");
		goto cleanup;
	}

	printf("Success...");

	for (;;)
	{
		// Trigger the BPF program
		fprintf(stderr, ".");
		sleep(1);
	}

cleanup:

	minimal_bpf__destroy(skel);
	return err;
}