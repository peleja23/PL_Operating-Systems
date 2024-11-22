#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    int size = 10;
    char buf[size];
    int bytes_read;
    int status;

    int fd_in = open("./etc/passwd.txt", O_RDONLY, 0666);
    if (fd_in == -1) {
        perror("open");
        return 1;
    }

    int fd_out = open("saida.txt", O_WRONLY | O_CREAT, 0666);
    if (fd_out == -1) {
        perror("open");
        return 1;
    }

    int fd_err = open("erros.txt", O_WRONLY | O_CREAT, 0666);
    if (fd_err == -1) {
        perror("open");
        return 1;
    }
	int fd_ecra = dup(1);
	
    dup2(fd_in, 0); //este é para o STDIN_FILENO
    close(fd_in);
	dup2(fd_out, 1); //este é para o STDOUT_FILENO
    close(fd_out);
	dup2(fd_err, 2); //este é para o STDERR_FILENO
    close(fd_err);

    while ((bytes_read = read(0, &buf, size)) > 0) {
        write(1, &buf, bytes_read);
    }
    
	snprintf(buf, 10, "terminei\n");
	write(1, &buf, 10);
	write(fd_ecra, &buf, 10);// ao inves de escrever com o fd_ecra podiamos restaurar o 1 com dup2(fd_ecra,1); e depois podiamos fazer write(1, &buf, 10); outra vez
	if(fork() == 0){
		
		//o filho mantem copia todos os file descriptors do pai
	
	}
	wait(&status);
	if(WIFEXITED(status)){
		return 0;
	}
    return 0;
}
