#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

#include "draw.c"

int main(){
    
    printf("\n\n");
    
    // Introduzco las 2 listas de palabras.
    
    // Primera listas son de palabras bastante comunes (dificultad estandar)
    char lista1[50][15] = {"casa", "jardin", "coche", "armario", "mesa", "baul", "telefono", "silla", "lampara", 
                           "leon", "pajaro", "hermana", "libro", "puerta", "pantalon", "galleta", "desayuno", "ventana",
                           "arroz", "suelo", "cuaderno", "nevera", "estuche", "canada", "cable", "pantalla", "barro",
                           "papel", "capucha", "siete", "cintura", "gente", "callejon", "alto", "jirafa", "balcon", "integral",
                           "rueda", "molestar", "jabon", "hospital", "gato", "ciervo", "doctor", "portatil", "correr", "vidrio", 
                           "artista", "compas", "marcador"};
    // Segunda contiene palabras algo más raras (dificultad alta)
    char lista2[50][15] = {"reuma", "tropel", "alguacil", "cerner", "caserio", "abominar", "atosigar", "gaznate", "acemila", "elucidar",
                           "albedo", "gutural", "alfeizar", "alicuota", "amojamar", "analogo", "cachaza", "canicula", "fuero", "galbana",
                           "pachorra", "hediondo", "icono", "insomnio", "ilicito", "tremula", "imprenta", "prefacio", "apendice", "alumco",
                           "silex", "cuarcita", "elipse", "bujia", "inefable", "ademan", "atisbar", "anodina", "jofaina", "labil", "mejunje",
                           "alfajor", "miasma", "omnivoro", "patena", "chacal", "sibilino", "sublime", "desidia", "prosodia"};
    
    // Muestro por pantalla al usuario las instrucciones del juego
    printf("Instrucciones de juego\n");
    printf("----------------------");
    printf("\n\n");
    printf("- El jugador tiene 7 oportunidades por palabra.\n");
    printf("- Solo los fallos restan oportunidades.\n");
    printf("- Si acierta letra suma 2 puntos.\n");
    printf("- Si falla letra resta 1 punto.\n");
    printf("- Si resuelve antes de gastar las 7 oportunidades suma 10 puntos.\n");
    printf("- Las letras deben ser introducidas en minúsculas.\n");
    printf("- Debe evitarse introducir la letra \"ñ\".\n");
    printf("\n                            A jugar!!!\n\n");
    
    int juego = 0;
    
    while (juego == 0){
        
        char *palabra = NULL, resolver, nuevo_juego;
        int dif, x1, i, puntuacion = 0, oportunidades = 7, indicador, contador = 0, contador2 = 0;
        
        // Pido al usuario que escoja la dificultad del juego
        salto1:
        printf("Escoja la dificultad del juego (1 -> estándar; 2 -> difícil): ");
        scanf("%i", &dif);
        setbuf(stdin, NULL);
        
        if (dif != 1 && dif != 2){
            printf("\nError! Introduzca números 1 o 2 para escoger dificultad.\n\n");
            goto salto1;
        }
        
        // Genero el numero aleatorio que dara la palabra de una de las dos listas
        srand(time(NULL));
        x1 = rand()%(50);
        
        // Palabra aleatoria
        if (dif == 1){
            palabra = lista1[x1];
        } else if (dif == 2){
            palabra = lista2[x1];
        }
        
        char solucion[strlen(palabra) + 1];
        char letra[strlen(palabra) + 7 + 1];
        
        printf("\n\n");
        
        // ========================================= COMIENZA EL JUEGO =========================================
        
        char pista[strlen(palabra) + 1];
        for (i=0; i<strlen(palabra); i++)
            pista[i] = '_';
        
        pista[strlen(palabra) + 1] = '\0';
        
        for (i=0; i<strlen(pista)-1; i++)
            printf("%c ", pista[i]);
        
        while (oportunidades != 0){
            salto2:
            printf("\n\nIntroduzca una letra: ");
            scanf("%c", &letra[contador]);
            setbuf(stdin, NULL);
            fgetc(stdin);
            /* Compruebo si la letra introducida ya se ha introducido antes */
            if (contador > 0){
                for (i=0; i<contador; i++){
                    if (letra[contador] == letra[i]){
                        printf("Letra repetida. Por favor, introduzca otra letra.");
                        goto salto2;
                    }
                }
            }
            /* Indicador para ver si se ha acertado la letra o no */
            indicador = 0;
            for (i=0; i<strlen(palabra); i++){
                if (letra[contador] == palabra[i]){
                    puntuacion += 2;
                    indicador++;
                    pista[i] = letra[contador];
                    contador2++;
                }
            }
            if (contador2 == strlen(palabra)){
                printf("\n                     Correcto!\n\n");
                puntuacion += 10;
                printf("Puntuacion final = %i", puntuacion);
                printf("\n¿Desea jugar otra vez? (s/n): ");
                scanf("%c", &nuevo_juego);
                setbuf(stdin, NULL);
                fgetc(stdin);
                if (nuevo_juego == 'n')
                    juego = 1;
                goto salto3;
            }
            if (indicador == 0){
                if (puntuacion > 0)
                    puntuacion--;
                oportunidades--;
                if (oportunidades == 6)
                    cuerda();
                if (oportunidades == 5)
                    cabeza();
                if (oportunidades == 4)
                    tronco();
                if (oportunidades == 3)
                    brazo_der();
                if (oportunidades == 2)
                    brazo_izq();
                if (oportunidades == 1)
                    pie_der();
                if (oportunidades == 0){
                    pie_izq();
                    printf("\nFin del juego\n");
                    printf("¿Desea jugar otra vez? (s/n): ");
                    scanf("%c", &nuevo_juego);
                    setbuf(stdin, NULL);
                    fgetc(stdin);
                    if (nuevo_juego == 'n')
                        juego = 1;
                    goto salto3;
                }
            }
            printf("\n\nPuntuación = %i", puntuacion);
            printf("\nOportunidades = %i", oportunidades);
            printf("\n\n");
            resolver = 'n';
            if (oportunidades!=0){
                for (i=0; i<strlen(pista); i++)
                    printf("%c ", pista[i]);
                printf("\n\n¿Desea resolver? (s/n): ");
                scanf("%c", &resolver);
                setbuf(stdin, NULL);
                fgetc(stdin);
                if (resolver == 's'){
                    printf("Introduzca la palabra: ");
                    scanf("%s", solucion);
                    setbuf(stdin, NULL);
                    if (strcmp(solucion, palabra) == 0){
                        printf("\n                     Correcto!\n\n");
                        puntuacion += 10;
                    } else {
                        printf("La palabra no es correcta. Fin del juego!");
                    }
                    printf("\nPuntuacion final = %i", puntuacion);
                    printf("\n¿Desea jugar otra vez? (s/n): ");
                    scanf("%c", &nuevo_juego);
                    setbuf(stdin, NULL);
                    fgetc(stdin);
                    if (nuevo_juego == 'n')
                        juego = 1;
                    goto salto3;
                }
            }
            contador++;
            printf("\n");
        }
        salto3:
        printf("\n\n");
    }
    printf("                           ¡Gracias por jugar!");
    printf("\n\n");
    
    return 0;
}
