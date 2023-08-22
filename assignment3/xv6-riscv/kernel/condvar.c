#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"
#include "sleeplock.h"
#include "condvar.h"

void
initcond(struct cond_t *cv, char *name)
{
  initsleeplock(&cv->lk, "cond sleep lock");
  cv->name = name;
  cv->cond = 0;
}

void cond_wait(struct cond_t *cv, struct sleeplock *lock)
{

    condsleep(cv, lock);
}

void cond_signal(struct cond_t *cv)
{
    wakeupone(cv);

}

void cond_broadcast(struct cond_t *cv)
{

    wakeup(cv);

}
