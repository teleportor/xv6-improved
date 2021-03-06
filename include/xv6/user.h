struct stat;
struct rtcdate;

// system calls
int fork(void);
int exit(void) __attribute__((noreturn));
int wait(void);
int pipe(int*);
int write(int, void*, int);
int read(int, void*, int);
int close(int);
int kill(int);
int exec(char*, char**);
int open(char*, int);
int mknod(char*, short, short);
int unlink(char*);
int fstat(int fd, struct stat*);
int link(char*, char*);
int mkdir(char*);
int chdir(char*);
int dup(int);
int getpid(void);
char* sbrk(int);
int sleep(int);
int uptime(void);

// thread api
int thread_create(void);
int thread_exit(void) __attribute__((noreturn));
int thread_wait(void);

// synchronization api
//// sleep lock
userlock lock_create(void);
void lock_acquire(userlock);
void lock_release(userlock);
int lock_holding(userlock);
void lock_free(userlock);

//// semaphore
usersem semaphore_create(int);
void semaphore_acquire(usersem);
void semaphore_release(usersem);
int semaphore_getcounter(usersem);
void semaphore_free(usersem);

//// read-write lock
userrwlock rwlock_create(void);
void rwlock_acquire_read(userrwlock);
void rwlock_acquire_write(userrwlock);
void rwlock_release_read(userrwlock);
void rwlock_release_write(userrwlock);
int rwlock_holding_read(userrwlock);
int rwlock_holding_write(userrwlock);
void rwlock_free(userrwlock);

// ulib.c
int stat(char*, struct stat*);
char* strcpy(char*, char*);
void *memmove(void*, void*, int);
char* strchr(const char*, char c);
int strcmp(const char*, const char*);
void printf(int, char*, ...);
char* gets(char*, int max);
uint strlen(char*);
void* memset(void*, int, uint);
void* malloc(uint);
void free(void*);
int atoi(const char*);
