#ifndef FUNCIONES_H
#define FUNCIONES_H

#define MAX_PRODUCTOS 50
#define MAX_RECURSOS 50
#define LONGITUD_NOMBRE 50

void agregarProducto(char nombres[][LONGITUD_NOMBRE], int tiempos_fabricacion[], char nombres_recursos[][MAX_RECURSOS][LONGITUD_NOMBRE], 
                     int cantidades_recursos[][MAX_RECURSOS], int cantidades[], int cuentas_recursos[], int *cantidad_productos);

void mostrarProductos(char nombres[][LONGITUD_NOMBRE], int tiempos_fabricacion[], char nombres_recursos[][MAX_RECURSOS][LONGITUD_NOMBRE], 
                      int cantidades_recursos[][MAX_RECURSOS], int cantidades[], int cuentas_recursos[], int cantidad_productos);

void eliminarProducto(char nombres[][LONGITUD_NOMBRE], int tiempos_fabricacion[], char nombres_recursos[][MAX_RECURSOS][LONGITUD_NOMBRE], 
                      int cantidades_recursos[][MAX_RECURSOS], int cantidades[], int cuentas_recursos[], int *cantidad_productos);

void editarProducto(char nombres[][LONGITUD_NOMBRE], int tiempos_fabricacion[], int cantidades[], int cantidad_productos);

void verificarFactibilidadPorProducto(char nombres[][LONGITUD_NOMBRE], int tiempos_fabricacion[], char nombres_recursos[][MAX_RECURSOS][LONGITUD_NOMBRE], 
                                      int cantidades_recursos[][MAX_RECURSOS], int cantidades[], int cuentas_recursos[], int cantidad_productos, 
                                      char nombres_recursos_disponibles[][LONGITUD_NOMBRE], int cantidades_recursos_disponibles[], int cantidad_recursos);

#endif
