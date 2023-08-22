#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"
#include "sleeplock.h"
#include "condvar.h"
#include "semaphore.h"  

void sem_init (struct semaphore *s, int x){
    s->s = x;
    initcond(&s->sem_cond,"sema_cond");
    initsleeplock(&s->lk,"sema_lock");
}
void sem_wait (struct semaphore *s){
    acquiresleep(&s->lk);
    while(s->s<=0){
        cond_wait(&s->sem_cond,&s->lk);
    }
    s->s = s->s -1;
    releasesleep(&s->lk);
}
void sem_post (struct semaphore *s){
    acquiresleep(&s->lk);
    s->s = s->s +1;
    cond_signal(&s->sem_cond);
    releasesleep(&s->lk);
}

