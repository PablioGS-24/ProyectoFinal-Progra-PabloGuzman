#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

struct Producto {
    int codigo;
    char nombre[50];
    float precio;
    int stock;
    bool activo;
};

const char* ARCHIVO = "productos.dat";
const float PORCENTAJE_IVA = 0.12;

// FUNCIONES
void menu();
void gestionProducto();
void procesoVenta();
void registrarProducto();
void listarproducto();
void buscarProductoCodigo();
void buscarProductoNombre();
void actualizarPrecio();
void actualizarStock();
void eliminarProducto();
bool existeProducto(int codigo);

int main() {
    menu();
    return 0;
}

// MENU PRINCIPAL
void menu() {
    int opcion;
    do {
        cout << "\n===== MENU PRINCIPAL =====\n";
        cout << "1. Gestion de Productos\n";
        cout << "2. Proceso de venta\n";
        cout << "3. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                gestionProducto();
                break;
            case 2:
                procesoVenta();
                break;
            case 3:
                cout << "Saliendo del Sistema.....\n";
                break;
            default:
                cout << "Opcion Invalida.....\n";
        }
    } while (opcion != 3);
}

//SUBMENU ---> CRUD DE LOS PRODUCTOS
void gestionProducto() {
    int opcion1;
    do {
        cout << "\n===== CRUD de Productos =====\n";
        cout << "1. Registar Producto\n";
        cout << "2. Listar Productos Activos\n";
        cout << "3. Buscar Producto por Codigo\n";
        cout << "4. Buscar Producto por Nombre\n";
        cout << "5. Modificar Precio\n";
        cout << "6. Actualizar Stock\n";
        cout << "7. Eliminar / Desactivar Producto\n";
        cout << "8. Salir al Menu Principal\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion1;

        switch (opcion1) {
            case 1: registrarProducto(); break;
            case 2: listarproducto(); break;
            case 3: buscarProductoCodigo(); break;
            case 4: buscarProductoNombre(); break;
            case 5: actualizarPrecio(); break;
            case 6: actualizarStock(); break;
            case 7: eliminarProducto(); break;
            case 8: cout << "Regresando al menu principal.....\n"; break;
            default: cout << "Opcion Invalida...\n";
        }
    } while (opcion1 != 8);
}

// C - CREATE (REGISTRAR/CREAR UN PRODUCTO)
void registrarProducto() {
    Producto p;

    cout << "\n--- Registar/Crear Producto ---\n";
    cout << "Codigo: ";
    cin >> p.codigo;

    if (existeProducto(p.codigo)) {
        cout << "Ya Existe un Producto con ese Codigo...\n";
        return;
    }

    cin.ignore();
    cout << "Nombre: ";
    cin.getline(p.nombre, 50);

    cout << "Precio: ";
    cin >> p.precio;

    cout << "Stock: ";
    cin >> p.stock;

    p.activo = true;

    ofstream archivo(ARCHIVO, ios::binary | ios::app);
    if(!archivo) {
        cout << "Error al Abrir el archivo...\n";
        return;
    }

    archivo.write(reinterpret_cast<char*>(&p), sizeof(Producto));
    archivo.close();

    cout << "Producto Guardado con Exito.\n";
}

// R - READ (LISTAR PRODUCTOS)
void listarproducto() {
    Producto p;
    ifstream archivo(ARCHIVO, ios::binary);

    if(!archivo) {
        cout << "No hay Productos Registrados...\n";
        return;
    }

    cout << "\n--- Lista de Productos Activos ---\n";
    cout << left << setw(10) << "Codigo"
         << setw(25) << "Nombre"
         << setw(12) << "Precio" 
         << setw(10) << "Stock" << endl;
    cout << "------------------------------------------------------------\n";

    while (archivo.read(reinterpret_cast<char*>(&p), sizeof(Producto))) {
        if (p.activo) {
            cout << left << setw(10) << p.codigo
                 << setw(25) << p.nombre
                 << "Q" << setw(11) << p.precio
                 << setw(10) << p.stock << endl;
        }
    }
    archivo.close();
}

// R - READ (BUSCAR POR CODIGO)
void buscarProductoCodigo() {
    Producto p;
    int codigoBuscado;
    bool encontrado = false;

    cout << "\n--- Buscar Producto por Codigo ---\n";
    cout << "Ingrese el Codigo: ";
    cin >> codigoBuscado;

    ifstream archivo(ARCHIVO, ios::binary);
    if (!archivo) {
        cout << "No hay Productos Registrados.\n";
        return;
    }

    while (archivo.read(reinterpret_cast<char*>(&p), sizeof(Producto))) {
        if (p.codigo == codigoBuscado && p.activo) {
            cout << "\n--- Producto Encontrado ---\n";
            cout << "Codigo: " << p.codigo << endl;
            cout << "Nombre: " << p.nombre << endl;
            cout << "Precio: Q" << p.precio << endl;
            cout << "Stock: " << p.stock << " unidades" << endl;
            encontrado = true;
            break;
        }
    }
    archivo.close();

    if (!encontrado) cout << "Producto no Encontrado.\n";
}

// R - READ (BUSCAR POR NOMBRE)
void buscarProductoNombre() {
    Producto p;
    string nombreBuscado;
    bool encontrado = false;

    cout << "\n--- Buscar Producto por Nombre ---\n";
    cout << "Ingrese el Nombre: ";
    cin.ignore();
    getline(cin, nombreBuscado);

    ifstream archivo(ARCHIVO, ios::binary);
    if (!archivo) {
        cout << "No hay Productos Registrados.\n";
        return;
    }

    while (archivo.read(reinterpret_cast<char*>(&p), sizeof(Producto))) {
        if (p.nombre == nombreBuscado && p.activo) {
            cout << "\n--- Producto Encontrado ---\n";
            cout << "Codigo: " << p.codigo << endl;
            cout << "Nombre: " << p.nombre << endl;
            cout << "Precio: Q" << p.precio << endl;
            cout << "Stock: " << p.stock << " unidades" << endl;
            encontrado = true;
            break;
        }
    }
    archivo.close();

    if (!encontrado) cout << "Producto no Encontrado.\n";
}

// U - UPDATE (ACTUALIZAR PRECIO)
void actualizarPrecio() {
    Producto p;
    int codigoBuscado;
    bool encontrado = false;

    cout << "\n--- Modificar Precio de Producto ---\n";
    cout << "Ingrese el Codigo: ";
    cin >> codigoBuscado;

    fstream archivo(ARCHIVO, ios::binary | ios::in | ios::out);
    if (!archivo) {
        cout << "No hay productos registrados.\n";
        return;
    }

    while (archivo.read(reinterpret_cast<char*>(&p), sizeof(Producto))) {
        if (p.codigo == codigoBuscado && p.activo) {
            cout << "Producto: " << p.nombre << " | Precio Actual: Q" << p.precio << endl;
            cout << "Ingrese el Nuevo Precio: ";
            cin >> p.precio;

            archivo.seekp(-static_cast<int>(sizeof(Producto)), ios::cur);
            archivo.write(reinterpret_cast<char*>(&p), sizeof(Producto));

            encontrado = true;
            cout << "Precio actualizado correctamente.\n";
            break;
        }
    }
    archivo.close();

    if (!encontrado) cout << "Producto no encontrado.\n";
}

// U - UPDATE (ACTUALIZAR STOCK)
void actualizarStock() {
    Producto p;
    int codigoBuscado;
    bool encontrado = false;

    cout << "\n--- Actualizar Stock de Producto ---\n";
    cout << "Ingrese el Codigo: ";
    cin >> codigoBuscado;

    fstream archivo(ARCHIVO, ios::binary | ios::in | ios::out);
    if (!archivo) {
        cout << "No hay productos registrados.\n";
        return;
    }

    while (archivo.read(reinterpret_cast<char*>(&p), sizeof(Producto))) {
        if (p.codigo == codigoBuscado && p.activo) {
            cout << "Producto: " << p.nombre << " | Stock Actual: " << p.stock << endl;
            cout << "Ingrese el Nuevo Stock: ";
            cin >> p.stock;

            archivo.seekp(-static_cast<int>(sizeof(Producto)), ios::cur);
            archivo.write(reinterpret_cast<char*>(&p), sizeof(Producto));

            encontrado = true;
            cout << "Stock actualizado correctamente.\n";
            break;
        }
    }
    archivo.close();

    if (!encontrado) cout << "Producto no encontrado.\n";
}

// D - DELETE (BORRADO LOGICO)
void eliminarProducto() {
    Producto p;
    int codigoBuscado;
    bool encontrado = false;

    cout << "\n--- Eliminar/Desactivar Producto ---\n";
    cout << "Ingrese el Codigo: ";
    cin >> codigoBuscado;

    fstream archivo(ARCHIVO, ios::binary | ios::in | ios::out);
    if (!archivo) {
        cout << "No hay productos registrados.\n";
        return;
    }

    while (archivo.read(reinterpret_cast<char*>(&p), sizeof(Producto))) {
        if (p.codigo == codigoBuscado && p.activo) {
            p.activo = false; 

            archivo.seekp(-static_cast<int>(sizeof(Producto)), ios::cur);
            archivo.write(reinterpret_cast<char*>(&p), sizeof(Producto));

            encontrado = true;
            cout << "Producto eliminado (desactivado) correctamente.\n";
            break;
        }
    }
    archivo.close();

    if (!encontrado) cout << "Producto no encontrado.\n";
}

// FUNCION DE VALIDACION DE EXISTENCIAS
bool existeProducto(int codigo) {
    Producto p;
    ifstream archivo(ARCHIVO, ios::binary);
    if (!archivo) return false;

    while (archivo.read(reinterpret_cast<char*>(&p), sizeof(Producto))) {
        if (p.codigo == codigo && p.activo) {
            archivo.close();
            return true;
        }
    }
    archivo.close();
    return false;
}

// PROCESO DE VENTA
void procesoVenta() {
    Producto p;
    int codigoBuscado, cantidad;
    bool encontrado = false;

    cout << "\n===== PROCESO DE VENTA =====\n";
    cout << "Ingrese el Codigo del Producto: ";
    cin >> codigoBuscado;

    fstream archivo(ARCHIVO, ios::binary | ios::in | ios::out);
    if (!archivo) {
        cout << "No hay Productos Registrados en el Sistema.\n";
        return;
    }

    while (archivo.read(reinterpret_cast<char*>(&p), sizeof(Producto))) {
        if (p.codigo == codigoBuscado && p.activo) {
            encontrado = true;

            cout << "\n--- Informacion del Producto ---\n";
            cout << "Nombre: " << p.nombre << "\n";
            cout << "Precio Unitario: Q" << p.precio << "\n";
            cout << "Stock Disponible: " << p.stock << " Unidades" << "\n";
            cout << "--------------------------" << "\n";

            cout << "Ingrese la Cantidad a Comprar: ";
            cin >> cantidad;

            if (cantidad <= 0) {
                cout << "Cantidad Invalidad...\n";
                break;
            }

            if (cantidad > p.stock) {
                cout << "Error: No hay Suficiente Stock Disponible para cubrir la venta.\n";

            } else {
                float subtotal = cantidad *p.precio;    //CALCULO DE SUBTOTAL
                float iva = subtotal * PORCENTAJE_IVA;  //CALCULO DEL IVA
                float total = subtotal + iva;

                cout << "\n===== TICKET DE VENTA =====\n";
                cout << "Subtotal: Q" << subtotal << "\n";
                cout << "IVA (" << (PORCENTAJE_IVA *100) << "%): Q" << iva << "\n";
                cout << "TOTAL A PAGAR: Q" << total << "\n";
                cout << "--------------------------" << "\n";

                p.stock -= cantidad;

                archivo.seekp(-static_cast<int>(sizeof(Producto)), ios::cur);
                archivo.write(reinterpret_cast<char*>(&p), sizeof(Producto));

                cout << "Venta Procesada e Inventario Actualizado con Exito.\n";
            }
            break;
        }
    }
    archivo.close();

    if (!encontrado) {
        cout << "Producto no Encontado.\n";
    }
}