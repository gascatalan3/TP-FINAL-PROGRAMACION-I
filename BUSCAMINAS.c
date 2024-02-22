/*
TP INTEGRADOR DE FINAL 
PROGRAMACION 1
UNRN - SEDE ANDINA
*/

/* BUSCAMINAS */

/* PASOS/INSTRUCCIONES:    Presento una matriz como una cuadricula con casillas que tiene filas y columnas enumeradas.                         
                            Algunas casillas van a tener minas que se generan aleatoriamente, otras casillas tienen un valor que indica la cantidad de minas adyacentes.
                            Debo tratar de despejar todas las casillas que NO tienen mina, sin pisar una mina para poder ganar.
                            Creo la matriz y genero valores aleatorios incluyendo minas, 0-> casilla vacia / 1-> minas y debo permitir ingresar coordenadas (1,1 o A,1) para el 
                            jugador para que me despeje una casilla. La logica del programa debe verificar esa coordenada si es 1 o 0.
                                    -> si es 1: el jugador acumula puntos.
                                    -> si es 0: pierde la partida y el juego revela todas las casillas del tablero, e indica con X las que el jugador acertó.
                            El juego continua hasta que se despejan todas las casillas que tienen valor de 1 o se haya comido una mina
                            Y alfinal, se enseña la puntuacion del jugador.
*/

/* Declaracion de librerias */
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
/* Declaracion de constantes */
#define CAPACIDAD 20
#define TERMINA_BIEN 0
#define TERMINA_ERROR 1



/*
    Esta funcion es de tipo "void" y lo que hace es generar e inicializar un tablero en cero, es decir el tablero original con sus correspondientes
    filas y columnas para dar inicio y visualizar el tablero con sus casillas.

    @param tablero_original ->  recibe una matriz que es el tablero original en principio.
    @param tablero_mostrar ->   recibe una matriz que tambien es el tablero, pero en este caso uso esta variable para "mostrar" las casillas del tablero.
                                Esto me va a servir para cuando tenga que revelar las casillas, en este caso me sirve para demostrar que cada casilla tiene un "-".
    @param filas ->     es la cantidad de filas que va a tener la matriz que representa la cuadricula, esto es el tablero del juego.
    @param columnas ->  es la cantidad de columnas que va a tener la matriz que representa la cuadricula con casillas, esto es el tablero del juego.

    @pre ->     recibir por un lado una matriz original y por otro una matriz que representa e identifica las casillas, y un numero que identifica a las filas y otro a las columnas.
    @post ->    en pantalla, se deberia imprimir el tablero del juego con sus respectivas filas y columnas, enumeradas y cada casilla representada con un "-" en la primer
                vista del tablero original.
*/
void tablero(int **tablero_original, int **tablero_mostrar, int filas, int columnas)
{
    int i;
    int j;

    printf("\n\tCUADRICULA CON SUS CASILLAS\n");
    printf("    ");
    for (j = 0; j < columnas; j++)
    {
        printf("%3d ", j);
    }
    printf("\n");

    for (i = 0; i < filas; i++)
    {
        printf("%3d ", i);

        for (j = 0; j < columnas; j++)
        {
            tablero_original[i][j] = ' ';
            tablero_mostrar[i][j] = '-';
            printf("%3c ", tablero_mostrar[i][j]);
        }
        printf("\n");
    }
}



/*
    Esta funcion es de tipo "void". Su funcionamiento y su objetivo es generar las minas de manera "random" (o aleatoria) para que se pongan en el tablero. De acuerdo a los 
    tres niveles de dificultad que tenemos, serán más o menos minas.

    @param tablero_original ->  matriz con el tablero original, es decir con el tablero sin descubrir ninguna casilla ni nada, ya que es en este tablero donde incorporo las minas.
    @param filas ->             es la cantidad de filas que va a tener la matriz que representa la cuadricula, esto es el tablero del juego.
    @param columnas ->          es la cantidad de columnas que va a tener la matriz que representa la cuadricula con casillas, esto es el tablero del juego.
    @param minas ->             es la cantidad de minas que voy a poner en el tablero, de acuerdo al nivel de dificultad que yo seleccioné

    @pre ->     recibo por un lado una matriz que es el tablero original de cero, sin ninguna casilla revelada ni tampoco minas
         ->     recibo numeros enteros positivos que representan la cantidad de filas del tablero, la cantidad de columnas del tablero, y la cantidad de minas que voy a poner.
    @post ->    en el tablero original, voy a "poner" determinada cantidad de minas en lugares generados "aleatoriamente".
*/
void generacion_minas(int **tablero_original, int filas, int columnas, int minas)
{
    int minas_generadas;
    int fila;
    int columna;

    minas_generadas = 0;

    while (minas_generadas < minas)
    {
        fila = rand() % filas;
        columna = rand() % columnas;

        if (tablero_original[fila][columna] != '1')
        {
            tablero_original[fila][columna] = '1';
            minas_generadas++;
        }
    }
}



/*
    Esta funcion es de tipo "int". Lo que hace es contar el número de minas más cercanas (adyacentes) a la casilla especifica del tablero que yo marqué.

    @param tablero_original ->  matriz con el tablero original, es decir con el tablero sin descubrir ninguna casilla ni nada, ya que es en este tablero donde incorporo las minas.
    @param filas ->             es la cantidad de filas que va a tener la matriz que representa la cuadricula, esto es el tablero del juego.
    @param columnas ->          es la cantidad de columnas que va a tener la matriz que representa la cuadricula con casillas, esto es el tablero del juego.
    @param fila ->              es la coordenada de la fila que yo ingreso para la casilla que quiero revelar o marcar.
    @param columna ->           es la coordenada de la columna que yo ingreso par la casilla que quiero revelar o marcar.

    @pre ->     recibo el tablero original, dos valores que son la cantidad de filas y columnas que tiene, y otros dos valores que es la fila y columna que yo ingresé como coordenada
    @post ->    obtener la cantidad de minas en las casillas más cercanas a la que yo seleccioné
    @return ->  un contador con un valor positivo indicandome la cantidad de minas
*/
int contar_minas_cercanas(int **tablero_original, int filas, int columnas, int fila, int columna)
{
    int contador = 0;
    int fila_nueva;;
    int columna_nueva;
    int i;
    int j;

    for (i = -1; i <= 1; i++)
    {
        for (j = -1; j <= 1; j++)
        {
            fila_nueva = fila + i;
            columna_nueva = columna + j;

            if (fila_nueva >= 0 && fila_nueva < filas && columna_nueva >= 0 && columna_nueva < columnas)
            {
                if (tablero_original[fila_nueva][columna_nueva] == '1')
                {
                    contador++;
                }
            }
        }
    }

    return contador;
}



/*
    Esta funcion es de tipo "void". Su funcion es revelar el tablero con todas las minas en él mostrando en pantalla, el tablero en si y donde estaban las minas con una 'X'.
    Esto pasa cuando el jugador pisa la mina y pierde, entonces asi se le muestran todas las minas en donde estaban.

    @param tablero_original ->  recibe una matriz que es el tablero original en principio.
    @param tablero_mostrar ->   recibe una matriz que tambien es el tablero, pero en este caso uso esta variable para "mostrar" las casillas del tablero.
    @param filas ->             es la cantidad de filas que va a tener la matriz que representa la cuadricula, esto es el tablero del juego.
    @param columnas ->          es la cantidad de columnas que va a tener la matriz que representa la cuadricula con casillas, esto es el tablero del juego.

    @pre ->     recibir la matriz del tablero, y sus dimensiones correspondientes.
    @post ->    en pantalla, se debe imprimir el tablero revelando donde estaban las minas.
*/
void mostrar_tablero_minas(int **tablero_original, int **tablero_mostrar, int filas, int columnas)
{
    for (int i = 0; i < filas; i++)
    {
        for (int j = 0; j < columnas; j++)
        {
            if (tablero_original[i][j] == '1')
            {
                tablero_mostrar[i][j] = 'X';
            }
        }
    }
}



/*
    Esta funcion es de tipo "bool". Su funcion es que verifica si el jugador ganó el juego al despejar todas las casillas que no contenían minas

    @param tablero_mostrar ->   recibe una matriz que tambien es el tablero, pero en este caso uso esta variable para "mostrar" las casillas del tablero.
    @param filas ->             es la cantidad de filas que va a tener la matriz que representa la cuadricula, esto es el tablero del juego.
    @param columnas ->          es la cantidad de columnas que va a tener la matriz que representa la cuadricula con casillas, esto es el tablero del juego.

    @pre ->     recibir la matriz del tablero, y sus dimensiones correspondientes.
    @post ->    tendrá que corrobar si se ganó el juego o no de acuerdo a las verificaciones de las casillas en el tablero.
    @return ->  ganar, que podrá ser de tipo true o false, de acuerdo a si el jugador ganó o no.
*/
bool ganar_juego(int **tablero_mostrar, int filas, int columnas)
{
    bool ganar;

    ganar = true;

    for (int i = 0; i < filas; i++)
    {
        for (int j = 0; j < columnas; j++)
        {
            if (tablero_mostrar[i][j] == '-')
            {
                ganar = false;
            }
        }
    }

    return ganar;
}



/*
    Esta funcion es de tipo "void". Su funcion es ir mostrando el tablero ACTUALIZADO al jugador en la pantalla, a medida que se revelan casillas o se marcan.

    @param tablero_mostrar ->   recibe una matriz que tambien es el tablero, pero en este caso uso esta variable para "mostrar" las casillas del tablero.
    @param filas ->             es la cantidad de filas que va a tener la matriz que representa la cuadricula, esto es el tablero del juego.
    @param columnas ->          es la cantidad de columnas que va a tener la matriz que representa la cuadricula con casillas, esto es el tablero del juego.

    @pre ->     recibir la matriz del tablero que se está mostrando, y las dimensiones correspondientes.
    @post ->    imprimir en pantalla el tablero actualizado de acuerdo a los movimientos realizados.
*/
void mostrar_tablero_actualizado(int **tablero_mostrar, int filas, int columnas)
{
    int j;
    int i;

    printf("\n\tTABLERO ACTUAL\n");
    printf("    ");
    for (j = 0; j < columnas; j++)
    {
        printf("%3d ", j);
    }

    printf("\n");

    for (i = 0; i < filas; i++)
    {
        printf("%3d ", i);

        for (int j = 0; j < columnas; j++)
        {
            printf("%3c ", tablero_mostrar[i][j]);
        }
        printf("\n");
    }
}



/*
    Esta funcion es de tipo "void". Su funcion es la de marcar una casilla y verificar si realmente era una mina o no.

    @param tablero_mostrar ->   recibe una matriz que tambien es el tablero, pero en este caso uso esta variable para "mostrar" las casillas del tablero.
    @param fila ->              es la coordenada de la fila que yo ingresé para la casilla.
    @param columna ->           es la coordenada de la columna que yo ingresé para la casilla.
    @param tablero_original ->  recibe una matriz que es el tablero original en principio.
    @param puntuacion ->        es un puntero, en el cual voy a ir almacenando una puntuacion de acuerdo a si acierto a donde estaba la mina o no.
    @param minas_marcadas ->    es un puntero de tipo int que me indica la cantidad de minas que puedo marcar.
    @param minas ->             es la cantidad de minas totales que hay en el juego, segun la dificultad que seleccioné.

    @pre ->     recibir las matrices del tablero original y el tablero que voy a mostrar, sus dimensiones correspondientes y una puntuación que arranca en 0.  
    @post ->    la casilla quede marcada (y pueda sumar puntuacion o no), que ya esté marcada o que directamente esa casilla ya fue revelada antes.          
*/
void marcar_casilla(int **tablero_mostrar, int fila, int columna, int **tablero_original, int *puntuacion, int *minas_marcadas, int minas)
{
    if (tablero_mostrar[fila][columna] == '-')
    {
        if (*minas_marcadas < minas)
        {
            tablero_mostrar[fila][columna] = 'M';
            (*minas_marcadas)++;
            if (tablero_original[fila][columna] == '1')
            {
                (*puntuacion)++;
                printf("BIEN. Encontraste una mina. \nPuntuación: %d\n", *puntuacion);
            }
        }
        else
        {
            printf("Ya marcaste el maximo de minas posibles\n");

        }
    }
    else if (tablero_mostrar[fila][columna] == 'M')
    {
        tablero_mostrar[fila][columna] = '-';
        (*minas_marcadas)--;
        printf("La casilla fue desmarcada\n");
    }
    else
    {
        printf("Esta casilla ya fue revelada\n");
    }
}



/*
    Esta funcion es de tipo "void". Su funcion es la de revelar las casillas más cercanas indicando con un número entero positivo la cantidad de minas cercanas que hay.
    Dentro de esta funcion se hace uso de otras funciones.

    @param tablero_original ->  recibe una matriz que es el tablero original en principio.
    @param tablero_mostrar ->   recibe una matriz que tambien es el tablero, pero en este caso uso esta variable para "mostrar" las casillas del tablero.
    @param filas ->             es la cantidad de filas que va a tener la matriz que representa la cuadricula, esto es el tablero del juego.
    @param columnas ->          es la cantidad de columnas que va a tener la matriz que representa la cuadricula con casillas, esto es el tablero del juego.
    @param fila ->              es la coordenada de la fila que yo ingresé para la casilla.
    @param columna ->           es la coordenada de la columna que yo ingresé para la casilla.

    @pre ->     se recibe el tablero original y el tablero que se está mostrando, sus dimensiones correspondientes, y la coordenada (fila y columna) que se acaba de ingresar.
    @post ->    si tengo minas cercanas, la casilla se revela con un número de acuerdo a cuantas minas cercanas tiene. Si NO tiene minas cercanas, se revela indicando un 0.
                Y en el caso de que una casilla tenga un 0, se llamár recursivamente para explorar las casillas cercanas hasta obtener un número.
*/
// Función para revelar casillas adyacentes
void mostrar_casillas(int **tablero_original, int **tablero_mostrar, int filas, int columnas, int fila, int columna)
{
    int minas_cercanas;
    int i;
    int j;

    if (fila < 0 || fila >= filas || columna < 0 || columna >= columnas || tablero_mostrar[fila][columna] != '-')
    {
        return;
    }

    minas_cercanas = contar_minas_cercanas(tablero_original, filas, columnas, fila, columna);

    if (minas_cercanas > 0)
    {
        /* Si hay minas cercanas, revelo la casilla */
        tablero_mostrar[fila][columna] = '0' + minas_cercanas;
    }
    else
    {
        /* Si la casilla está vacía, se revela y se exploran las mas cercanas */
        tablero_mostrar[fila][columna] = ' ';
        for (i = -1; i <= 1; i++)
        {
            for (j = -1; j <= 1; j++)
            {
                mostrar_casillas(tablero_original, tablero_mostrar, filas, columnas, fila + i, columna + j);
            }
        }
    }
}



/*
    Esta funcion es de tipo "bool". Su funcion es la de determinar QUE HACER cuando el jugador selecciona una casilla, se le solicita y se le pide que quiere hacer.
    Puede revelarla o marcar/desmarcar esa casilla

    @param tablero_original ->  recibe una matriz que es el tablero original en principio.
    @param tablero_mostrar ->   recibe una matriz que tambien es el tablero, pero en este caso uso esta variable para "mostrar" las casillas del tablero.
    @param fila ->              es la coordenada de la fila que yo ingresé para la casilla.
    @param columna ->           es la coordenada de la columna que yo ingresé para la casilla.
    @param filas ->             es la cantidad de filas que va a tener la matriz que representa la cuadricula, esto es el tablero del juego.
    @param columnas ->          es la cantidad de columnas que va a tener la matriz que representa la cuadricula con casillas, esto es el tablero del juego.
    @param puntuacion ->        es un puntero, en el cual voy a ir almacenando una puntuacion de acuerdo a si acierto a donde estaba la mina o no.
    @param nivel_minas ->       es la cantidad de minas que hay, segun la dificultad seleccionada.
    @param minas_marcadas ->    es un puntero de tipo int, que me indicará la cantidad de minas que puedo marcar. 

    @pre ->     tenemos las matrices de los tableros, sus dimensiones correspondientes, la coordenada que se ingresó para jugar y el contador de la puntuación hasta este momento.
    @post ->    voy a poder revelar la casilla que ingresé, perder porque pisé una mina, o si metí mal la opcion, volver a intentar y meter una opcion correcta. 
    @return ->  retorno, de tipo bool, siendo false o true. Si es TRUE puedo seguir jugando / Si es FALSE perdí porque pisé una mina.
*/
bool verificar_casilla(int **tablero_original, int **tablero_mostrar, int fila, int columna, int filas, int columnas, int *puntuacion, int nivel_minas, int *minas_marcadas)
{
    int opcion;
    int minas_cercanas;
    bool retorno;
    printf("1. Revelar la casilla\n");
    printf("2. Marcar/Desmarcar casilla (como la bandera)\n");
    printf("Seleccione una opción: ");
    scanf("%d", &opcion);

    if (opcion == 1)
    {
        if (tablero_original[fila][columna] == '1')
        {
            /* Hay una mina, se revelan todas y se muestra el tablero */ 
            mostrar_tablero_minas(tablero_original, tablero_mostrar, filas, columnas);
            retorno = false;
        }
        else if (tablero_original[fila][columna] == 'M')
        {
            printf("NO se puede");
            retorno = false;
        }
        else
        {
            minas_cercanas = contar_minas_cercanas(tablero_original, filas, columnas, fila, columna);

            /* Actualizo el tablero con la cantidad de minas cercanas que hay */
            if (minas_cercanas > 0)
            {
                tablero_mostrar[fila][columna] = '0' + minas_cercanas;
            }
            else
            {
                /* Si la casilla no tiene nada, revelo las casillas proximas */
                mostrar_casillas(tablero_original, tablero_mostrar, filas, columnas, fila, columna);
            }
            retorno = true;
        }
    }
    else if (opcion == 2)
    {
        marcar_casilla(tablero_mostrar, fila, columna, tablero_original, puntuacion, minas_marcadas, nivel_minas);
        retorno = true;
        //return true; // El juego continúa después de marcar/desmarcar una casilla
    }
    else
    {
        retorno = true;
    }

    return retorno;
}



/*
    Esta funcion es de tipo "bool". Su funcion es la de verificar si las coordenadas que se ingresaron son VALIDAS, es decir son dos numeros enteros positivos ingresados de manera
    correcta. NO pueden ser caracteres no validos, o caracteres como "a a".

    @param fila ->      es un puntero, que es la coordenada de la fila que yo ingresé para la casilla.
    @param columna ->   es un puntero, que es la coordenada de la columna que yo ingresé para la casilla.
    @param nivel_filas ->       es la cantidad de filas que va a tener la matriz que representa la cuadricula, esto es el tablero del juego.
    @param nivel_ columnas ->   es la cantidad de columnas que va a tener la matriz que representa la cuadricula con casillas, esto es el tablero del juego. 

    @pre ->     recibimos un puntero de fila y columna porque se modifican sus valores y las dimensiones correspondientes para hacer la comprobacion.
    @post ->    las coordenadas ingresadas serán validas o seran invalidas.
    @return ->  valido, será de tipo bool y puede ser false o true. Si es TRUE -> las coordenadas son validas. Si es FALSE -> las coordenadas NO son validas.
*/
bool verificar_coordenadas(int *fila, int *columna, int nivel_filas, int nivel_columnas) 
{
    bool valido;

    if (scanf("%d %d", fila, columna) != 2) 
    {
        /* Limpia el búfer de entrada en caso de una entrada inválida */
        while (getchar() != '\n') 
        {
            continue;
        }

        valido = false;
    }
    else
    {
        if (*fila >= 0 && *fila < nivel_filas && *columna >= 0 && *columna < nivel_columnas) 
        {
            valido = true;
        } 
        else 
        {
            valido = false;
        }
    }

    return valido;
}



/* Funcion principal main del programa */
int main()
{
    char nombre[CAPACIDAD];
    int **tablero_original;
    int **tablero_mostrar;
    int puntuacion;
    int minas_marcadas;
    int dificultad;
    int nivel_filas;
    int nivel_columnas;
    int nivel_minas;
    int fila;
    int columna;
    int i;

    puntuacion = 0;
    minas_marcadas = 0;
    srand(time(NULL));

    printf("\n-----BUSCAMINAS------\n");
    printf("Por favor, para su identificación ingrese su nombre: ");
    fgets(nombre, sizeof(nombre), stdin);
    printf("Bienvenido al BUSCAMINAS, jugador %s", nombre);

    printf("\nLos niveles son:\n");
    printf("Opcion 1 -> Principiante, 8x8 casillas con 10 minas\n");
    printf("Opcion 2 -> Intermedio, 16x16 casillas y 40 minas\n");
    printf("Opcion 3 -> Experto, 16x30 casillas y 99 minas\n");
    printf("Opcion 4 -> Personalizado, seleccione usted las casillas y las minas\n");
    printf("Opcion: ");
    scanf("%d", &dificultad);

    if (dificultad == 1)
    {
        nivel_filas = 8;
        nivel_columnas = 8;
        nivel_minas = 10;
    }
    else if (dificultad == 2)
    {
        nivel_filas = 16;
        nivel_columnas = 16;
        nivel_minas = 40;
    }
    else if (dificultad == 3)
    {
        nivel_filas = 16;
        nivel_columnas = 30;
        nivel_minas = 99;
    }
    else if (dificultad == 4)
    {
        printf("\nFilas: ");
        scanf("%d", &nivel_filas);
        printf("Columnas: ");
        scanf("%d", &nivel_columnas);
        printf("Minas: ");
        scanf("%d", &nivel_minas);
    }
    else 
    {
        printf("\nOpción no válida. Vuelva a intentar jugar\n");
        return TERMINA_ERROR;
    }

    /* Memoria dinamica para las matrices */
    tablero_original = (int **)malloc(nivel_filas * sizeof(int *));
    tablero_mostrar = (int **)malloc(nivel_filas * sizeof(int *));
    for (i = 0; i < nivel_filas; i++) 
    {
        tablero_original[i] = (int *)malloc(nivel_columnas * sizeof(int));
        tablero_mostrar[i] = (int *)malloc(nivel_columnas * sizeof(int));
    }

    /* Inicializo el tablero y muestro el tablero original 'base' desde cero */
    tablero(tablero_original, tablero_mostrar, nivel_filas, nivel_columnas);

    /* Genero las minas de manera aleatoria dentro del tablero */
    generacion_minas(tablero_original, nivel_filas, nivel_columnas, nivel_minas);

    while (1)
    {
        printf("Ingrese las coordenadas (fila columna, ejemplo 1 0): ");

        /* Verifico mediante funcion y este if, si las coordenadas que ingresé son correctas o no */
        if (!verificar_coordenadas(&fila, &columna, nivel_filas, nivel_columnas)) 
        {
            printf("ERROR en las coordenadas, NO son validas. Porfavor, intente de nuevo\n");
        }

        else
        {
            /* Verifico la casilla que seleccione y actualizo el tablero, en este caso revelando las minas porque en rama del if es porque perdí */
            if (!verificar_casilla(tablero_original, tablero_mostrar, fila, columna, nivel_filas, nivel_columnas, &puntuacion, nivel_minas, &minas_marcadas))
            {
                mostrar_tablero_actualizado(tablero_mostrar, nivel_filas, nivel_columnas);
                printf("Derrota. Acabas de pisar una mina y explotaste.\nTu puntuación final fue de: %d\nPuedes tomarte revancha e intentarlo de nuevo.\n", puntuacion);
                return TERMINA_BIEN;
            }

            /* Muestro y actualizo el tablero luego de cada movimiento */
            mostrar_tablero_actualizado(tablero_mostrar, nivel_filas, nivel_columnas);

            /* Compruebo si todas las casillas que NO tienen minas las despejé, y si es así entonces es porque gané */
            if (ganar_juego(tablero_mostrar, nivel_filas, nivel_columnas))
            {
                printf("VICTORIA MAGISTRAL! Evitastes todas las minas posibles.\nTu puntuación final fue de: %d\n", puntuacion);
                return TERMINA_BIEN;
            }
        }
    }
    /* Liberacion de memoria dinamica */
    for (int i = 0; i < nivel_filas; i++) 
    {
        free(tablero_original[i]);
        free(tablero_mostrar[i]);
    }
    free(tablero_original);
    free(tablero_mostrar);
}


