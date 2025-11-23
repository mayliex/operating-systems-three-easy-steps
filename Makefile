run-process-api-1:
	clang process-api/1.c -o tmp/process-api-1 && ./tmp/process-api-1

run-process-api-2_3:
	clang process-api/2_3.c -o tmp/process-api-2_3 && ./tmp/process-api-2_3

run-process-api-4_execve:
	clang process-api/4_execve.c -o tmp/process-api-4_execve && ./tmp/process-api-4_execve

run-process-api-4_execl:
	clang process-api/4_execl.c -o tmp/process-api-4_execl && ./tmp/process-api-4_execl

run-process-api-4_execvp:
	clang process-api/4_execvp.c -o tmp/process-api-4_execvp && ./tmp/process-api-4_execvp

run-process-api-5:
	clang process-api/5.c -o tmp/process-api-5 && ./tmp/process-api-5

run-process-api-6:
	clang process-api/6.c -o tmp/process-api-6 && ./tmp/process-api-6

clean:
	rm -rf tmp/*
