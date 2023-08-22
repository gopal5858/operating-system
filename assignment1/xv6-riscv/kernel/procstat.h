
struct procstat {
  int pid;     // Process ID
  int ppid;    // Parent ID
  char state[8];  // Process state
  char command[16]; // Process name
  int ctime;    // Creation time
  int stime;    // Start time
  int etime;    // Execution time
  unsigned long size;  // Process size
};