#include <stdio.h>
#include <string.h>
#include "funciones.h"

// Agregar un producto
void agregarProducto(char nombres[][LONGITUD_NOMBRE], int tiempos_fabricacion[], char nombres_recursos[][MAX_RECURSOS][LONGITUD_NOMBRE], 
                     int cantidades_recursos[][MAX_RECURSOS], int cantidades[], int cuentas_recursos[], int *cantidad_productos) {
    printf("\nIngrese los datos del producto:\n");
    printf("Nombre del producto: ");
    scanf(" %[^\n]", nombres[*cantidad_productos]);
    printf("Tiempo de fabricacion por unidad (en horas): ");
    scanf("%d", &tiempos_fabricacion[*cantidad_productos]);
    printf("Cantidad requerida: ");
    scanf("%d", &cantidades[*cantidad_productos]);

    printf("Cuantos recursos requiere este producto (maximo %d): ", MAX_RECURSOS);
    scanf("%d", &cuentas_recursos[*cantidad_productos]);

    for (int i = 0; i < cuentas_recursos[*cantidad_productos]; i++) {
        printf("Nombre del recurso %d: ", i + 1);
        scanf(" %[^\n]", nombres_recursos[*cantidad_productos][i]);
        printf("Cantidad necesaria de %s por unidad del producto: ", nombres_recursos[*cantidad_productos][i]);
        scanf("%d", &cantidades_recursos[*cantidad_productos][i]);
    }

    (*cantidad_productos)++;
    printf("\nProducto agregado correctamente.\n");
}

// Mostrar productos
void mostrarProductos(char nombres[][LONGITUD_NOMBRE], int tiempos_fabricacion[], char nombres_recursos[][MAX_RECURSOS][LONGITUD_NOMBRE], 
                      int cantidades_recursos[][MAX_RECURSOS], int cantidades[], int cuentas_recursos[], int cantidad_productos) {
    if (cantidad_productos == 0) {
        printf("\nNo hay productos registrados.\n");
        return;
    }

    printf("\nLista de productos:\n");
    for (int i = 0; i < cantidad_productos; i++) {
        printf("%d. Nombre: %s | Tiempo por unidad: %d h | Cantidad requerida: %d\n", 
               i + 1, nombres[i], tiempos_fabricacion[i], cantidades[i]);
        printf("   Recursos requeridos:\n");
        for (int j = 0; j < cuentas_recursos[i]; j++) {
            printf("      - %s: %d unidades por producto\n", nombres_recursos[i][j], cantidades_recursos[i][j]);
        }
    }
}

// Eliminar un producto
void eliminarProducto(char nombres[][LONGITUD_NOMBRE], int tiempos_fabricacion[], char nombres_recursos[][MAX_RECURSOS][LONGITUD_NOMBRE], 
                      int cantidades_recursos[][MAX_RECURSOS], int cantidades[], int cuentas_recursos[], int *cantidad_productos) {
    char nombre[LONGITUD_NOMBRE];
    printf("\nIngrese el nombre del producto a eliminar: ");
    scanf(" %[^\n]", nombre);

    for (int i = 0; i < *cantidad_productos; i++) {
        if (strcmp(nombres[i], nombre) == 0) {
            for (int j = i; j < *cantidad_productos - 1; j++) {
                strcpy(nombres[j], nombres[j + 1]);
                tiempos_fabricacion[j] = tiempos_fabricacion[j + 1];
                cantidades[j] = cantidades[j + 1];
                cuentas_recursos[j] = cuentas_recursos[j + 1];
                for (int k = 0; k < MAX_RECURSOS; k++) {
                    strcpy(nombres_recursos[j][k], nombres_recursos[j + 1][k]);
                    cantidades_recursos[j][k] = cantidades_recursos[j + 1][k];
                }
            }
            (*cantidad_productos)--;
            printf("\nProducto eliminado correctamente.\n");
            return;
        }
    }
    printf("\nProducto no encontrado.\n");
}

// Editar un producto
void editarProducto(char nombres[][LONGITUD_NOMBRE], int tiempos_fabricacion[], int cantidades[], int cantidad_productos) {
    char nombre[LONGITUD_NOMBRE];
    printf("\nIngrese el nombre del producto a editar: ");
    scanf(" %[^\n]", nombre);

    for (int i = 0; i < cantidad_productos; i++) {
        if (strcmp(nombres[i], nombre) == 0) {
            printf("\nProducto encontrado: %s\n", nombres[i]);
            printf("1. Editar nombre\n");
            printf("2. Editar tiempo de fabricacion\n");
            printf("3. Editar cantidad requerida\n");
            printf("Seleccione una opcion: ");
            int opcion;
            scanf("%d", &opcion);

            switch (opcion) {
                case 1:
                    printf("Ingrese el nuevo nombre: ");
                    scanf(" %[^\n]", nombres[i]);
                    printf("Nombre actualizado correctamente.\n");
                    break;
                case 2:
                    printf("Ingrese el nuevo tiempo de fabricacion: ");
                    scanf("%d", &tiempos_fabricacion[i]);
                    printf("Tiempo de fabricacion actualizado correctamente.\n");
                    break;
                case 3:
                    printf("Ingrese la nueva cantidad requerida: ");
                    scanf("%d", &cantidades[i]);
                    printf("Cantidad requerida actualizada correctamente.\n");
                    break;
                default:
                    printf("Opcion no valida. No se realizaron cambios.\n");
            }
            return;
        }
    }

    printf("\nProducto no encontrado.\n");
}

// Verificar factibilidad por producto
void verificarFactibilidadPorProducto(char nombres[][LONGITUD_NOMBRE], int tiempos_fabricacion[], char nombres_recursos[][MAX_RECURSOS][LONGITUD_NOMBRE], 
                                      int cantidades_recursos[][MAX_RECURSOS], int cantidades[], int cuentas_recursos[], int cantidad_productos, 
                                      char nombres_recursos_disponibles[][LONGITUD_NOMBRE], int cantidades_recursos_disponibles[], int cantidad_recursos) {
    if (cantidad_productos == 0) {
        printf("\nNo hay productos registrados para verificar.\n");
        return;
    }

    printf("\n==== Verificacion de Factibilidad por Producto ====\n");

    for (int i = 0; i < cantidad_productos; i++) {
        printf("\nProducto: %s\n", nombres[i]);
        int factible = 1;  // Asumimos que el producto es factible inicialmente.

        for (int j = 0; j < cuentas_recursos[i]; j++) {
            int total_requerido = cantidades_recursos[i][j] * cantidades[i];

            int indice_disponible = -1;
            for (int k = 0; k < cantidad_recursos; k++) {
                if (strcmp(nombres_recursos[i][j], nombres_recursos_disponibles[k]) == 0) {
                    indice_disponible = k;
                    break;
                }
            }

            if (indice_disponible != -1) {
                printf("   - Recurso: %s | Requerido: %d | Disponible: %d\n", nombres_recursos[i][j], total_requerido, 
                       cantidades_recursos_disponibles[indice_disponible]);
                if (total_requerido > cantidades_recursos_disponibles[indice_disponible]) {
                    printf("     ¡No hay suficientes recursos disponibles!\n");
                    factible = 0;  // El producto no es factible si falta un recurso.
                }
            } else {
                printf("   - Recurso: %s | Requerido: %d | No disponible\n", nombres_recursos[i][j], total_requerido);
                factible = 0;  // El producto no es factible si el recurso no está disponible.
            }
        }

        if (factible) {
            printf("   => Este producto **se puede fabricar** con los recursos disponibles.\n");
        } else {
            printf("   => Este producto **no se puede fabricar** debido a la falta de recursos.\n");
        }
    }
}
