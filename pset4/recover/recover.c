#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>


typedef uint8_t byte;

bool is_jpeg(byte *block) {
    // Verifica se o bloco corresponde ao cabeçalho de um arquivo JPEG
    return (block[0] == 0xff && block[1] == 0xd8 && block[2] == 0xff && (block[3] & 0xf0) == 0xe0);
}

int main(int argc, char *argv[]) {
    // Verifica se o número correto de argumentos foi fornecido
    if (argc != 2) {
        fprintf(stderr, "Uso: %s arquivo_forense.raw\n", argv[0]);
        return 1;
    }

    // Abre o arquivo forense
    FILE *forensic_file = fopen(argv[1], "r");
    if (forensic_file == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo forense.\n");
        return 2;
    }

    // Variáveis para controle
    byte block[512];
    int jpeg_count = 0;
    FILE *jpeg_file = NULL;

    // Lê blocos de 512 bytes do arquivo forense
    while (fread(block, sizeof(byte), 512, forensic_file) == 512) {
        if (is_jpeg(block)) {
            // Fecha o arquivo JPEG anterior (se existir)
            if (jpeg_file != NULL) {
                fclose(jpeg_file);
            }

            // Cria um novo arquivo JPEG
            char filename[8];
            sprintf(filename, "%03i.jpg", jpeg_count);
            jpeg_file = fopen(filename, "w");
            jpeg_count++;
        }

        // Escreve o bloco no arquivo JPEG atual
        if (jpeg_file != NULL) {
            fwrite(block, sizeof(byte), 512, jpeg_file);
        }
    }

    // Fecha o último arquivo JPEG
    if (jpeg_file != NULL) {
        fclose(jpeg_file);
    }

    // Fecha o arquivo forense
    fclose(forensic_file);

    return 0;
}

