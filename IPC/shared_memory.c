#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>

#define SIZE 1000

int main(int argc, char * argv[]) {
	if (argc != 3) {
		return 1;
	}

	int reg1, reg2;
	sscanf(argv[1], "%d", &reg1);
	sscanf(argv[2], "%d", &reg2);
	key_t mem_key = ftok("./shared_memory.c", 1);
	printf("%d", (int)mem_key);

	int mem1_id = shmget(reg1, SIZE, IPC_CREAT);
	int mem2_id = shmget(reg2, SIZE, IPC_CREAT);
	int mem3_id = shmget(mem_key, SIZE, IPC_CREAT | IPC_EXCL | 0666);

	int * mem1 = shmat(mem1_id, NULL, SHM_RDONLY);
	int * mem2 = shmat(mem2_id, NULL, SHM_RDONLY);
	int * mem3 = shmat(mem3_id, NULL, 0);

	for (int i = 0; i < 100; ++i) {
		mem3[i] = mem1[i] + mem2[i];
	}

	shmdt(mem1);
	shmdt(mem2);
	shmdt(mem3);
	return 0;
}
