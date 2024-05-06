#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Tarea
{
    int TareaID;       // Numérico autoincremental comenzando en 1000
    char *Descripcion; //
    int Duracion;      // entre 10 – 100
} Tarea;

typedef struct TNodo
{
    struct Tarea T;
    struct TNodo *Siguiente;
} TNodo;

TNodo *crearlistaVacia();
TNodo *CrearTarea(int *id);
void cargaTareas(TNodo **tareasPendientes, TNodo *nuevoNodo);
void cargarTareaPendiente(TNodo **tareaspendientes, int *pid);
void mostrarTareas(TNodo *Lista);
void cargarRealizadas(TNodo **tareasPendientes, TNodo **tareasRealizadas);
void consultarTareas(TNodo *tareasPendientes, TNodo *tareasRealizadas);

int main()
{
    int id = 999;
    int *pid;
    pid = &id;
    TNodo *tareasPendientes = crearlistaVacia();
    TNodo *tareasRealizadas = crearlistaVacia();

    cargarTareaPendiente(&tareasPendientes, pid);
    cargarRealizadas(&tareasPendientes, &tareasRealizadas);
    puts("Tareas Pendientes");
    mostrarTareas(tareasPendientes);
    puts("Tareas Realizadas");
    mostrarTareas(tareasRealizadas);
    consultarTareas(tareasPendientes,tareasRealizadas);
}

TNodo *crearlistaVacia()
{
    return NULL;
}
TNodo *CrearTarea(int *id)
{
    TNodo *NNodo = (TNodo *)malloc(sizeof(TNodo));
    // cargamos dinamicamente la descripcion
    char *buff;
    fflush(stdin);
    buff = (char *)malloc(100 * sizeof(char));
    puts("Ingrese una descripcion: ");
    gets(buff);
    // obtenido en el buff la descripcion vemos su tamaño y hacemos la descripcion de esa longitud
    NNodo->T.Descripcion = (char *)malloc((strlen(buff) + 1) * sizeof(char));
    strcpy(NNodo->T.Descripcion, buff);
    // generamos el resto
    NNodo->T.Duracion = rand() % 91 + 10;//rand()%(Mayor-Menor+1)+Menor
    (*id)++;
    NNodo->T.TareaID = *id;
    NNodo->Siguiente = NULL;
    free(buff);
    return NNodo;
}
void cargaTareas(TNodo **tareasPendientes, TNodo *nuevoNodo)
{
    nuevoNodo->Siguiente = *tareasPendientes;
    *tareasPendientes = nuevoNodo;
}
void cargarTareaPendiente(TNodo **tareaspendientes, int *pid)
{
    int respuesta;
    puts("Desea cargar tarea? 1.SI 2.NO");
    scanf("%d", &respuesta);

    while (respuesta == 1)
    {
        TNodo *nuevaTarea = CrearTarea(pid);
        cargaTareas(tareaspendientes, nuevaTarea);
        puts("Desea cargar tarea? 1.SI 2.NO");
        scanf("%d", &respuesta);
    }
}
void mostrarTareas(TNodo *Lista)
{
    while (Lista != NULL)
    {
        puts("-----------------------------------------------\n");
        printf("Id de la tarea: %d\n", Lista->T.TareaID);
        printf("Descripcion: %s\n", Lista->T.Descripcion);
        printf("Duracion: %d\n", Lista->T.Duracion);
        Lista = Lista->Siguiente;
    }
}

void cargarRealizadas(TNodo **tareasPendientes, TNodo **tareasRealizadas)
{
    // hago un puntero que apunte al inicio de mi lista enlazada
    TNodo **aux = tareasPendientes;
    int id;
    mostrarTareas(*tareasPendientes);
    puts("indicar id de la tarea que se realizo:");
    scanf("%d", &id);
    // Busco el ID en la lista si no lo encuentro sigo recorriendola
    while ((*aux)->Siguiente != NULL && (*aux)->T.TareaID != id)
    {
        // haciendo el siguiente codigo obtengo la direccion del puntero que apunta a *aux->Siguiente
        aux = &(*aux)->Siguiente;
    }
    // Si encontramos el nodo con el dato especificado, lo eliminamos.
    if (*aux)
    {
        // creo un puntero que apuntara al nodo que quiero mover
        TNodo *tareaRealizada = *aux;
        // desvinculo el nodo de tareasPendientes
        *aux = (*aux)->Siguiente;
        // agrego el nodo a la tareas realizadas
        cargaTareas(tareasRealizadas, tareaRealizada);
    }
}

void consultarTareas(TNodo *tareasPendientes, TNodo *tareasRealizadas)
{
    int respuesta, id;
    char *palabra, *buff,*estaPalabra;
    puts("Buscara por ID o por palabra clave? 1.id 2.palabra");
    scanf("%d", &respuesta);
    if (respuesta == 1)
    {
        while (tareasRealizadas != NULL)
        {
            if (tareasRealizadas->T.TareaID == id)
            {
                puts("---------------------Tarea realizada--------------------------\n");
                printf("Id de la tarea: %d\n", tareasRealizadas->T.TareaID);
                printf("Descripcion: %s\n", tareasRealizadas->T.Descripcion);
                printf("Duracion: %d\n", tareasRealizadas->T.Duracion);
            }
            tareasRealizadas = tareasRealizadas->Siguiente;
        }
        while (tareasPendientes != NULL)
        {
            if (tareasPendientes->T.TareaID == id)
            {
                puts("----------------------Tarea Pendiente-------------------------\n");
                printf("Id de la tarea: %d\n", tareasPendientes->T.TareaID);
                printf("Descripcion: %s\n", tareasPendientes->T.Descripcion);
                printf("Duracion: %d\n", tareasPendientes->T.Duracion);
            }
            tareasPendientes = tareasPendientes->Siguiente;
        }
    }
    if (respuesta == 2)
    {
        buff = (char *)malloc(100 * sizeof(char));
        fflush(stdin);
        printf("Ingrese palabra clave: ");
        gets(buff);
        palabra = (char *)malloc((strlen(buff) + 1) * sizeof(char));
        strcpy(palabra, buff);
        while (tareasRealizadas != NULL)
        {
            estaPalabra = strstr(tareasRealizadas->T.Descripcion/*string1*/,palabra/*sting2*/);
            // busca la primera aparición de string2 en string1
            if (estaPalabra)
            {
                puts("---------------------Tarea Realizada--------------------------\n");
                printf("Id de la tarea: %d\n", tareasRealizadas->T.TareaID);
                printf("Descripcion: %s\n", tareasRealizadas->T.Descripcion);
                printf("Duracion: %d\n", tareasRealizadas->T.Duracion);
            }
            tareasRealizadas = tareasRealizadas->Siguiente;
        }
        while (tareasPendientes != NULL)
        {
            estaPalabra = strstr(tareasPendientes->T.Descripcion/*string1*/,palabra/*sting2*/);
            // busca la primera aparición de string2 en string1
            if (estaPalabra)
            {
                puts("----------------------Tarea Realizada-------------------------\n");
                printf("Id de la tarea: %d\n", tareasPendientes->T.TareaID);
                printf("Descripcion: %s\n", tareasPendientes->T.Descripcion);
                printf("Duracion: %d\n", tareasPendientes->T.Duracion);
            }
            tareasPendientes = tareasPendientes->Siguiente;
        }
        free(buff);
    }
}
