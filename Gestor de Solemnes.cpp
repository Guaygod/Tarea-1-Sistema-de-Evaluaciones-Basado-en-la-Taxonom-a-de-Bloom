#include <iostream>
#include <string>
#include <limits>

using namespace std;

const int MAX_PREGUNTAS = 100;

struct Pregunta {
    string enunciado;
    string nivel;
    int tiempo;
    bool usadaAntes = false;
};

Pregunta banco[MAX_PREGUNTAS];
int cantPreg = 0;

void limpiarBuffer() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void agregarPregunta() {
    if (cantPreg >= MAX_PREGUNTAS) {
        cout << "No se pueden agregar mas preguntas.\n";
        return;
    }

    Pregunta p;
    limpiarBuffer();
    cout << "Ingrese enunciado: ";
    getline(cin, p.enunciado);
    cout << "Ingrese nivel de la taxonomia: ";
    getline(cin, p.nivel);
    cout << "Ingrese tiempo estimado (minutos): ";
    cin >> p.tiempo;

    banco[cantPreg++] = p;
    cout << "Pregunta agregada.\n";
}

void listarPreguntas() {
    if (cantPreg == 0) {
        cout << "No hay preguntas registradas.\n";
        return;
    }

    for (int i = 0; i < cantPreg; ++i) {
        cout << "[" << i + 1 << "] Enunciado: " << banco[i].enunciado << endl;
        cout << "   Nivel: " << banco[i].nivel << endl;
        cout << "   Tiempo: " << banco[i].tiempo << " min" << endl;
        cout << "   Usada antes: " << (banco[i].usadaAntes ? "Si" : "No") << endl;
        cout << "------------------------\n";
    }
}

void actualizarPregunta() {
    listarPreguntas();
    int idx;
    cout << "Ingrese numero de pregunta a actualizar: ";
    cin >> idx;

    if (idx < 1 || idx > cantPreg) {
        cout << "Indice invalido.\n";
        return;
    }

    limpiarBuffer();
    cout << "Nuevo enunciado: ";
    getline(cin, banco[idx - 1].enunciado);
    cout << "Nuevo nivel: ";
    getline(cin, banco[idx - 1].nivel);
    cout << "Nuevo tiempo (minutos): ";
    cin >> banco[idx - 1].tiempo;

    cout << "Pregunta actualizada.\n";
}

void eliminarPregunta() {
    listarPreguntas();
    int idx;
    cout << "Ingrese numero de pregunta a eliminar: ";
    cin >> idx;

    if (idx < 1 || idx > cantPreg) {
        cout << "Indice invalido.\n";
        return;
    }

    for (int i = idx - 1; i < cantPreg - 1; ++i) {
        banco[i] = banco[i + 1];
    }

    cantPreg--;
    cout << "Pregunta eliminada.\n";
}

void marcarUsada() {
    listarPreguntas();
    int idx;
    cout << "Ingrese numero de pregunta usada antes: ";
    cin >> idx;

    if (idx < 1 || idx > cantPreg) {
        cout << "Indice invalido.\n";
        return;
    }

    banco[idx - 1].usadaAntes = true;
    cout << "Pregunta marcada como usada.\n";
}

void generarEvaluacion() {
    limpiarBuffer();
    string nivelBuscado;
    int cantidad;

    cout << "Ingrese nivel para la evaluacion: ";
    getline(cin, nivelBuscado);
    cout << "Ingrese cantidad de preguntas: ";
    cin >> cantidad;

    int contador = 0;
    int tiempoTotal = 0;

    cout << "\n--- Evaluacion generada ---\n";

    for (int i = 0; i < cantPreg && contador < cantidad; ++i) {
        if (banco[i].nivel == nivelBuscado && !banco[i].usadaAntes) {
            cout << "[" << contador + 1 << "] " << banco[i].enunciado << endl;
            cout << "   Tiempo: " << banco[i].tiempo << " min\n";
            cout << "--------------------------\n";
            tiempoTotal += banco[i].tiempo;
            contador++;
        }
    }

    if (contador == 0) {
        cout << "No se encontraron preguntas con ese nivel.\n";
    } else {
        cout << "Tiempo total estimado: " << tiempoTotal << " minutos\n";
    }
}

void menu() {
    int opcion;

    do {
        cout << "\n--- Menu del Sistema de Evaluacion ---\n";
        cout << "1. Agregar pregunta\n";
        cout << "2. Listar preguntas\n";
        cout << "3. Actualizar pregunta\n";
        cout << "4. Eliminar pregunta\n";
        cout << "5. Generar evaluacion\n";
        cout << "6. Marcar como usada\n";
        cout << "0. Salir\n";
        cout << "Opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: agregarPregunta(); break;
            case 2: listarPreguntas(); break;
            case 3: actualizarPregunta(); break;
            case 4: eliminarPregunta(); break;
            case 5: generarEvaluacion(); break;
            case 6: marcarUsada(); break;
            case 0: cout << "Saliendo del programa.\n"; break;
            default: cout << "Opcion invalida.\n";
        }

    } while (opcion != 0);
}

int main() {
    menu();
    return 0;
}