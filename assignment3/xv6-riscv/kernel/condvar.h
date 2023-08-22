struct cond_t
{
    uint cond; // Is the lock held?
    struct sleeplock lk;
    // For debugging:
    char *name; // Name of lock.
};