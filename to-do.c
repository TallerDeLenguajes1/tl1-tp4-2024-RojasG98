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
void cargarTareaPendiente(TNodo **tareaspendientes,int *pid);
void mostrarTareas(TNodo *Lista);
void cargarRealizadas(TNodo **tareasPendientes, TNodo **tareasRealizadas);

int main()
{
    int id = 999;
    int *pid;
    pid = &id;
    TNodo *tareasPendientes = crearlistaVacia();
    TNodo *tareasRealizadas = crearlistaVacia();

    cargarTareaPendiente(&tareasPendientes,pid);
    cargarRealizadas(&tareasPendientes,&tareasRealizadas);
    puts("Tareas Pendientes");
    mostrarTareas(tareasPendientes);
    puts("Tareas Realizadas");
    mostrarTareas(tareasRealizadas);
    
}

TNodo *crearlistaVacia()
{
    return NULL;
}
TNodo *CrearTarea(int *id)
{
    TNodo *NNodo = (TNodo *)malloc(sizeof(TNodo));
    //cargamos dinamicamente la descripcion
    char *buff;
    fflush(stdin);
    buff = (char *)malloc(100 * sizeof(char));
    puts("Ingrese una descripcion: ");
    gets(buff);
    //obtenido en el buff la descripcion vemos su tamaño y hacemos la descripcion de esa longitud
    NNodo->T.Descripcion = (char *)malloc((strlen(buff) + 1) * sizeof(char));
    strcpy(NNodo->T.Descripcion, buff);
    //generamos el resto
    NNodo->T.Duracion = rand() % 91 + 10;
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
    TNodo **aux = tareasPendientes;
    int id;
    mostrarTareas(*tareasPendientes);
    puts("indicar id de la tarea que se realizo:");
    scanf("%d",&id);
    //Busco el ID en la lista
    while ((*aux)->Siguiente!= NULL && (*aux)->T.TareaID != id)
    {
        aux = &(*aux)->Siguiente;
    }
     // Si encontramos el nodo con el dato especificado, lo eliminamos.
    if (*aux){
        TNodo *tareaRealizada = *aux;
        *aux = (*aux)->Siguiente;
        cargaTareas(tareasRealizadas,tareaRealizada);
    }
    
}
