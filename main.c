#include <stdio.h>
#include "funciones.h"

int main() {
    char nombres[MAX_PRODUCTOS][LONGITUD_NOMBRE];
    int tiempos_fabricacion[MAX_PRODUCTOS];
    char nombres_recursos[MAX_PRODUCTOS][MAX_RECURSOS][LONGITUD_NOMBRE];
    int cantidades_recursos[MAX_PRODUCTOS][MAX_RECURSOS];
    int cantidades[MAX_PRODUCTOS];
    int cuentas_recursos[MAX_PRODUCTOS];
    int cantidad_productos = 0;

    char nombres_recursos_disponibles[MAX_RECURSOS][LONGITUD_NOMBRE];
    int cantidades_recursos_disponibles[MAX_RECURSOS];
    int cantidad_recursos;

    do {
        printf("Cuantos tipos de recursos tiene disponibles. Puede ingresar hasta %d: ", MAX_RECURSOS);
        scanf("%d", &cantidad_recursos);

        if (cantidad_recursos < 1 || cantidad_recursos > MAX_RECURSOS) {
            printf("Error: el numero de recursos debe estar entre 1 y %d. Intentelo de nuevo.\n", MAX_RECURSOS);
        }
    } while (cantidad_recursos < 1 || cantidad_recursos > MAX_RECURSOS);

    for (int i = 0; i < cantidad_recursos; i++) {
        printf("Nombre del recurso %d: ", i + 1);
        scanf(" %[^\n]", nombres_recursos_disponibles[i]);
        printf("Cantidad disponible de %s: ", nombres_recursos_disponibles[i]);
        scanf("%d", &cantidades_recursos_disponibles[i]);
    }

    int opcion;

    do {
        printf("\n===== Menu Principal =====\n");
        printf("1. Agregar producto\n");
        printf("2. Mostrar productos\n");
        printf("3. Eliminar producto\n");
        printf("4. Editar producto\n");
        printf("5. Verificar factibilidad de produccion por producto\n");
        printf("6. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                if (cantidad_productos >= MAX_PRODUCTOS) {
                    printf("\nError: No se pueden agregar mas productos. Limite alcanzado (%d).\n", MAX_PRODUCTOS);
                } else {
                    agregarProducto(nombres, tiempos_fabricacion, nombres_recursos, cantidades_recursos, cantidades, cuentas_recursos, &cantidad_productos);
                }
                break;
            case 2:
                mostrarProductos(nombres, tiempos_fabricacion, nombres_recursos, cantidades_recursos, cantidades, cuentas_recursos, cantidad_productos);
                break;
            case 3:
                eliminarProducto(nombres, tiempos_fabricacion, nombres_recursos, cantidades_recursos, cantidades, cuentas_recursos, &cantidad_productos);
                break;
            case 4:
                editarProducto(nombres, tiempos_fabricacion, cantidades, cantidad_productos);
                break;
            case 5:
                verificarFactibilidadPorProducto(nombres, tiempos_fabricacion, nombres_recursos, cantidades_recursos, 
                                                 cantidades, cuentas_recursos, cantidad_productos, nombres_recursos_disponibles, 
                                                 cantidades_recursos_disponibles, cantidad_recursos);
                break;
            case 6:
                printf("\nSaliendo del programa. ¡Hasta luego!\n");
                break;
            default:
                printf("\nOpcion no valida. Inténtelo de nuevo.\n");
        }
    } while (opcion != 6);

    return 0;
}
