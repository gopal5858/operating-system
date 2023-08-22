struct semaphore {
    int s;
    struct cond_t sem_cond;
    struct sleeplock lk;
};