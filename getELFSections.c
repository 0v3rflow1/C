#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <elf.h>

int main(int argc, char *argv[])
{
    if(argc!=2)
    {
      printf("Use: %s <path>\n\n",argv[0]);
      exit(EXIT_FAILURE);
    }
    int fd;
    Elf64_Ehdr header; // Estructura para el encabezado ELF
    Elf64_Shdr section; // Estructura para la sección ELF
    // Abrir el archivo ELF en modo lectura
    if ((fd = open(argv[1], O_RDONLY)) < 0) 
    {
        perror("open");
        exit(EXIT_FAILURE);
    }
    printf("Target: %s\n",argv[1]);
    // Leer el encabezado ELF del archivo
    if (read(fd, &header, sizeof(header)) != sizeof(header)) 
    {
        perror("read");
        close(fd);
        exit(EXIT_FAILURE);
    }
    // Mostrar el número de secciones en el archivo
    printf("El archivo tiene %d secciones.\n", header.e_shnum);
    
    // Leer la sección de cadena (contiene los nombres de las secciones)
    if (lseek(fd, header.e_shoff + header.e_shstrndx * sizeof(section), SEEK_SET) < 0) 
    {
        perror("lseek");
        close(fd);
        exit(EXIT_FAILURE);
    }
    if (read(fd, &section, sizeof(section)) != sizeof(section)) 
    {
        perror("read");
        close(fd);
        exit(EXIT_FAILURE);
    }
    char *strtab = malloc(section.sh_size);
    if (lseek(fd, section.sh_offset, SEEK_SET) < 0) 
    {
        perror("lseek");
        free(strtab);
        close(fd);
        exit(EXIT_FAILURE);
    }
    if (read(fd, strtab, section.sh_size) != section.sh_size) 
    {
        perror("read");
        free(strtab);
        close(fd);
        exit(EXIT_FAILURE);
    }
    
    // Leer la información de cada sección y mostrarla en pantalla
    int i;
    printf("Secciones: \n");
    for (i = 0; i < header.e_shnum; i++) 
    {
        if (lseek(fd, header.e_shoff + i * sizeof(section), SEEK_SET) < 0) 
        {
            perror("lseek");
            free(strtab);
            close(fd);
            exit(EXIT_FAILURE);
        }
        if (read(fd, &section, sizeof(section)) != sizeof(section)) 
        {
            perror("read");
            free(strtab);
            close(fd);
            exit(EXIT_FAILURE);
        }
        printf(" %s\n", strtab + section.sh_name);
    }
    free(strtab);
    close(fd); 
    return 0;
}
