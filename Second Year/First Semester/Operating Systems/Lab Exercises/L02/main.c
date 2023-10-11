#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() {
    const char mesaj[] = "Hello World!\n";
    write(STDOUT_FILENO,mesaj, 13);
}