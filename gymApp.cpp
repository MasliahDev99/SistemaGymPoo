#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Direccion
{ // clase abstracta
private:
    string calle;
    int numeroPuerta;
    int codPostal;

public:
    Direccion(){};
    Direccion(string calle, int num, int cod) : calle(calle), numeroPuerta(num), codPostal(cod){};
    void setCalle(string c) { calle = c; }
    void setNumeroPuerta(int numP) { numeroPuerta = numP; }
    void setCodPostal(int cp) { codPostal = cp; }

    string getCalle() const { return calle; }
    int getNumeroPuerta() const { return numeroPuerta; }
    int getCodPostal() const { return codPostal; }
};

class MembresiasGym
{
private:
    string nombre_Membresias; // una lista que contiene membresias
    float precioMembresia;
    bool Activado = false;
    vector<MembresiasGym> Planes; // vector para modelas la lista de planes
public:
    MembresiasGym(){};
    MembresiasGym(string nombre, float precio, bool activ = false) : nombre_Membresias(nombre), precioMembresia(precio), Activado(activ) {}
    void ActivarMembresia()
    {
        this->Activado = true;
    }
    void DesactivarMembresia()
    {
        this->Activado = false;
    }
    void setPrecioMembresia(float precio)
    {
        precioMembresia = precio;
    }
    void setNombreMembresia(string nombre)
    {
        nombre_Membresias = nombre;
    }

    // getters
    bool getEstadoMembresia()
    {
        return this->Activado;
    }
    string getNombre()
    {
        return this->nombre_Membresias;
    }
    float getPrecioMembresia()
    {
        return this->precioMembresia;
    }

    bool ExisteMembresia(string nombrePlan)
    {
        for (auto &plan : Planes)
        {
            if (nombrePlan == plan.getNombre())
            {
                return true;
            }
        }
        return false;
    }
    MembresiasGym *getMembresia(string nombre)
    {
        for (auto &plan : Planes)
        {
            if (nombre == plan.getNombre())
            {
                return &plan;
            }
        }
        return nullptr;
    }
};

class Cliente
{
private:
    string nombreUser;
    string apellidoUser;
    int cedula;
    int edad;
    string password;
    MembresiasGym *membresiaUsuario;
    Direccion direccionCliente;

public:
    Cliente(){};
    // Constructor
    Cliente(string _nombre, string _apellido, int _cedula, int _edad, string _pass, Direccion dc) : nombreUser(_nombre), apellidoUser(_apellido), cedula(_cedula), edad(_edad), password(_pass), membresiaUsuario(nullptr), direccionCliente(dc){};

    // Setters
    void setNombre(string nombre)
    {
        nombreUser = nombre;
    }
    void setApellido(string apellido)
    {
        apellidoUser = apellido;
    }
    void setDNI(int dni)
    {
        cedula = dni;
    }
    void setEdad(int e)
    {
        edad = e;
    }
    void setPassword(string pass)
    {
        password = pass;
    }

    // Getters
    string getNombre()
    {
        return nombreUser;
    }
    string getApellido()
    {
        return apellidoUser;
    }
    string getPassword()
    {
        return password;
    }
    int getDNI()
    {
        return cedula;
    }
    int getEdad()
    {
        return edad;
    }
    // asocio un cliente a una membresia
    // pre condicion , la membresia existe
    void AsociarMembresia(MembresiasGym *nuevaMembresia)
    {
        membresiaUsuario = nuevaMembresia;
        membresiaUsuario->ActivarMembresia();
    }
    bool UsuarioPerteneceMembresia(MembresiasGym *membresiaDada) const
    {
        return membresiaUsuario == membresiaDada;
    }

    void DarBajaMembresiaUsuario(MembresiasGym *membresiaDebaja)
    {

        membresiaDebaja->DesactivarMembresia();
        membresiaUsuario = nullptr;
    }
};

class Gym
{
private:
    string nombreGym;
    Direccion direccionGym;
    vector<MembresiasGym> ListaMembresias;
    vector<Cliente> ListaClientes;
    vector<Gym> ListaGymn;
    Cliente *clientes;
    MembresiasGym estadoMembresias;

public:
    Gym(){};
    Gym(string nombre, Direccion sucursal) : nombreGym(nombre), direccionGym(sucursal), clientes(nullptr){};
    ~Gym(){};

    void AgregarMembresiasGym(const string &nombre, float precio)
    {
        MembresiasGym membresias(nombre, precio, true);
        ListaMembresias.push_back(membresias);
    }
    vector<MembresiasGym> obtenerListaMembresiasDisponibles()
    {
        vector<MembresiasGym> membresiasDisponibles;
        for (auto &plan : ListaMembresias)
        {
            if (plan.getEstadoMembresia())
            {
                membresiasDisponibles.push_back(plan);
            }
        }
        return membresiasDisponibles;
    }
    void AgregarGymnasios(const string &nombre, const string &calle, int numPuerta, int codP)
    {
        Direccion direccionGym(calle, numPuerta, codP);
        Gym nuevoGymnasio(nombre, direccionGym);
        ListaGymn.push_back(nuevoGymnasio);
    }

    const string getDireccionSucursal() const
    {
        // convierto en string el numero de puerta y codigo postal ya que son int
        string numeroPuerta = to_string(direccionGym.getNumeroPuerta());
        string codPostal = to_string(direccionGym.getCodPostal());

        return "\nCalle: " + direccionGym.getCalle() + "\nNumero puerta: " + numeroPuerta + "\nCodigo postal: " + codPostal;
    }
    string getNombre() const
    {
        return nombreGym;
    }
    void MostrarListadoGymnasios()
    {
        if (ListaGymn.empty())
        {
            cout << "Error: No se encuentran gymnasios cargados..." << endl;
            return;
        }
        else
        {

            cout << "------------------------ " << endl;
            int i = 0;
            for (const Gym &gyms : ListaGymn)
            {
                cout << "Nombre: " << gyms.getNombre() << " (" << i + 1 << ")"
                     << "\nDireccion: " << gyms.getDireccionSucursal() << endl;
                cout << " ----------------------------------------------------------" << endl;
                i++;
            }
        }
    }
    void MostrarMembresias()
    {
        if (ListaMembresias.empty())
        {
            cout << "Error: Lista de membresias vacia..." << endl;
            return;
        }
        else
        {
            int i = 0;
            for (auto &membresias : ListaMembresias)
            {
                cout << "Nombre: " << membresias.getNombre() << " (" << i + 1 << ")"
                     << "\nPrecio: " << membresias.getPrecioMembresia() << " " << endl;
                cout << " ----------------------------------------------------------" << endl;
                i++;
            }
        }
    }
    // retorna un puntero al gymnasio pasado por nombre, si no lo encuentra devuelve null
    Gym *getGymnasio(string nombreGym)
    {
        for (auto &gym : ListaGymn)
        {
            if (gym.getNombre() == nombreGym)
            {
                return &gym;
            }
        }
        return nullptr;
    }
    void AltaUsuario(const Cliente &nuevoCliente)
    {
        ListaClientes.push_back(nuevoCliente);
    }
    // dada una cedula retorna el puntero del cliente del gym
    Cliente *getClienteKey(int cedula)
    {
        for (auto &cliente : ListaClientes)
        {
            if (cliente.getDNI() == cedula)
            {
                return &cliente;
            }
        }
        return nullptr;
    }
    bool ExisteCedula(int cedula)
    {
        for (auto &cliente : ListaClientes)
        {
            if (cliente.getDNI() == cedula)
            {
                return true;
            }
        }
        return false; // si no existe una cedula retorna false
    }
    bool MismaDireccionGym(const string &calle, const int numero_Puerta, const int codigo_Postal)
    {
        // arreglar, solo funciona si es el mismo gym pero si son gimnasios diferentes en la misma direccion no lo toma en cuenta
        for (auto const &gym : ListaGymn)
        {
            // si la direccion del gimnasio es igual, entonces retorna true en caso contrario false
            if (gym.direccionGym.getCalle() == calle && gym.direccionGym.getNumeroPuerta() == numero_Puerta && gym.direccionGym.getCodPostal() == codigo_Postal)
            {
                return true;
            }
        }
        return false;
    }
};
void InicializarMembresiasGym(Gym &gym)
{
    gym.AgregarMembresiasGym("Bronce", 2.50);
    gym.AgregarMembresiasGym("Plata", 3.50);
    gym.AgregarMembresiasGym("Gold", 5.50);
}
void InicializarGymnasios(Gym &gymnasio)
{
    // dado que el programa no consta de una base de datos, creo un mini base de datos con casos bases para el inicio
    gymnasio.AgregarGymnasios("FitnessPro", "Av.Italia", 2360, 11500);
    gymnasio.AgregarGymnasios("FitnessPro", "Rivera", 1400, 11500);
    gymnasio.AgregarGymnasios("Gymnasio_1", "Pocitos", 2390, 11500);
    gymnasio.AgregarGymnasios("Gymnasio_2", "Rivera", 1000, 11500);
}
void LimpiarScreen()
{
    system("clear");
}
void MenuAdmin(Gym &gymMain)
{

    string calle, nombreG, nombreM;
    int numeroP, codP;
    // float precio;
    int op;
    do
    {

        cout << "---------------------ADMIN-----------------------------" << endl;
        cout << "1-Ver Listado Gymnasios" << endl;
        cout << "2-Gestionar gymnasios" << endl;
        cout << "3-salir" << endl;
        cout << "Ingrese opcion: ";
        cin >> op;

        switch (op)
        {
        case 1:
        {
            LimpiarScreen();
            char s;
            cout << "--------------Gimnasios----------------------" << endl;
            gymMain.MostrarListadoGymnasios();
            cout << "Salir con (S): ";
            cin >> s;
            if (s == 's' || s == 'S')
            {
                LimpiarScreen();
                break;
            }
            break;
        }
        case 2:
        {
            int var;
            LimpiarScreen();
            do
            {
                cout << " ----------------------------------" << endl;
                cout << "1-Agregar nuevo gymnasio" << endl;
                cout << "2-Agregar Membresia" << endl;
                cout << "3-salir" << endl;
                cout << "Opcion: ";
                cin >> var;

                switch (var)
                {
                case 1:
                {
                    cout << "---Nuevo gimnasio---" << endl;
                    cout << "Nombre: ";
                    cin >> nombreG;
                    cout << "Direccion del gimnasio " << endl;
                    cout << "Calle: ";
                    cin >> calle;
                    cout << "Numero de puerta: ";
                    cin >> numeroP;
                    cout << "Codigo postal: ";
                    cin >> codP;
                    char r;
                    cout << "Esta seguro que los datos estan correctos? (s/n): ";
                    cin >> r;
                    if (r == 's' || r == 'S')
                    {
                        LimpiarScreen();
                        // si ya existe un gimnasio en esta direccion entonces muestro el error
                        if (gymMain.MismaDireccionGym(calle, numeroP, codP))
                        {
                            LimpiarScreen();
                            cout << "Ya existe un gimnasio registrado en esta dirección." << endl;
                            break;
                        }
                        else
                        {

                            gymMain.AgregarGymnasios(nombreG, calle, numeroP, codP);
                            cout << "Revisar que se haya registrado correctamente en la opción 1" << endl;
                        }
                    }
                    else
                    {
                        cout << "jodete" << endl;
                    }

                    break;
                }
                case 2:
                {
                    break;
                }
                case 3:
                {
                    LimpiarScreen();
                    break;
                }
                default:
                {
                    LimpiarScreen();
                    cout << "Error: opcion incorrecta..." << endl;
                    break;
                }
                };

            } while (var != 3);
            break;
        }
        case 3:
        {
            LimpiarScreen();
            break;
        }
        default:
        {
            LimpiarScreen();
            cout << "Error: opcion invalida..." << endl;
            break;
        }
        };

    } while (op != 3);
}
void MenuCliente(Gym &gymEncontrado, Cliente *cliente, Gym &gymnsioMain)
{
    int op;
    do
    {
        cout << "+++++++++" << gymEncontrado.getNombre() << ". Usuario(" << cliente->getNombre() << ") ++++" << endl;
        cout << "1-Ver planes(Membresias)" << endl;
        cout << "2-Mi cuenta" << endl;
        cout << "7-salir" << endl;
        cout << "Opcion: ";
        cin >> op;
        switch (op)
        {
        case 1:
        {
            LimpiarScreen();
            gymnsioMain.MostrarMembresias();
            break;
        }
        case 2:
        {
            break;
        }
        default:
        {
            break;
        }
        }
    } while (op != 7);
}
void Menu(Gym &gym)
{
    int opcion;
    int chances = 3;
    bool sinChances = false;
    do
    {

        cout << "********** Menú Princial **********" << endl;
        cout << "1-Ver Lista de gymnasios disponibles " << endl;
        cout << "2-Registro / Login " << endl;
        cout << "3-Sobre nosotros" << endl;
        cout << "7-Si desea salir(7)" << endl;
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion)
        {
        case 1:
        {
            LimpiarScreen();
            char n;
            string name;
            Gym *gymEncontrado = nullptr;
            cout << "******* Gymnasios Disponibles ******* " << endl;
            gym.MostrarListadoGymnasios();
            cout << "Desea ver las membresias que contiene algun gymnasio en particular?(S/n):  ";
            cin >> n;
            LimpiarScreen();
            while (n == 's' || n == 'S')
            {
                LimpiarScreen();
                cout << "Ingrese nombre del gym que esta interesado: ";
                cin >> name;
                gymEncontrado = gym.getGymnasio(name);
                if (gymEncontrado == nullptr)
                {
                    cout << "Error: El gymnasio ingresado no se encuentra en nuestra base de datos..." << endl;
                }
                else
                {
                    InicializarMembresiasGym(*gymEncontrado);
                    gymEncontrado->MostrarMembresias();
                }

                cout << "Si desea las membresias que contiene algun gymnasio en particular(S/n):  ";
                cin >> n;
            }
            delete gymEncontrado;
            gymEncontrado = nullptr;
            break;
            // las debo agregar membresias a cada objeto gym, dado que se encuentran unicamente en el objeto general asociados
        }
        // Login / registro
        case 2:
        {
            LimpiarScreen();
            string nombreGym, nombreUsuario, apellidoUser, password, calle;
            int cedula, edad, numP;
            cout << "Ingrese nombre de gymnasio donde desea logearse o registrar: ";
            cin >> nombreGym;

            Gym *gymnasioEncontrado = gym.getGymnasio(nombreGym);

            if (gymnasioEncontrado == nullptr)
            {
                cout << "Error: El nombre del gymnasio ingresado no es correcto..." << endl;
                break;
            }
            else
            {
                //  lugar de trabajo
                char op;
                LimpiarScreen();
                cout << "Gymnasio: " << gymnasioEncontrado->getNombre() << ". " << endl;
                cout << "Bienvenidos" << endl;
                cout << "Si tiene una cuenta ingrese (S/n): ";
                cin >> op;

                if (op == 'S' || op == 's')
                {
                    cout << "---Login---" << endl;
                    cout << "Cedula: ";
                    cin >> cedula;
                    cout << "password: ";
                    cin >> password;
                    // verifica la autentificacion
                    Cliente *clienteEncontrado = gymnasioEncontrado->getClienteKey(cedula);

                    if (clienteEncontrado != nullptr && clienteEncontrado->getPassword() == password)
                    {
                        // el usuario se pudo logear
                        // se redirige al menu de usuario
                        LimpiarScreen();
                        MenuCliente(*gymnasioEncontrado, clienteEncontrado, gym);
                    }
                    else
                    {
                        LimpiarScreen();
                        cout << "Error: credenciales ingresadas incorrectas.." << endl;
                        break;
                    }
                }
                else
                {
                    LimpiarScreen();

                    cout << "---Registro---" << endl;
                    cout << "Nombre: ";
                    cin >> nombreUsuario;
                    cout << "Apellido: ";
                    cin >> apellidoUser;
                    do
                    {
                        cout << "Cedula: ";
                        cin >> cedula;
                        if (gymnasioEncontrado->ExisteCedula(cedula))
                        {
                            chances--;
                            cout << "Chances disponibles: " << chances << endl;
                        }
                        if (chances == 0)
                        {
                            cout << "Error: se ha ingresado una cedula existente varias veces..." << endl;
                            sinChances = true;
                            break;
                        }
                    } while (gymnasioEncontrado->ExisteCedula(cedula) && chances > 0);
                    if (sinChances)
                        break;
                    cout << "Edad: ";
                    cin >> edad;
                    cout << "Contraseña: ";
                    cin >> password;
                    cout << "---Direccion---" << endl;
                    cout << "Calle: ";
                    cin >> calle;
                    cout << "Número: ";
                    cin >> numP;
                    Direccion dirUsuario(calle, numP, 11500);
                    Cliente nuevoUsuario(nombreUsuario, apellidoUser, cedula, edad, password, dirUsuario);
                    // crea el objeto usuario en el gym
                    gymnasioEncontrado->AltaUsuario(nuevoUsuario); // doy de alta al cliente en el gymnasio ingresado
                    // vuelve al menu
                }
            }
            break;
        }
        case 3:
        {
            LimpiarScreen();
            cout << "---------------------------------------" << endl;
            cout << "Proyecto practica de POO en c++" << endl;
            cout << "Es un sistema de gymnasios, cuenta con un simulador de registro/login y" << endl;
            cout << "ademas cuenta con una lista de gymnasios registrados donde el usuario puede visualizar y de ahi elegir cual registrarse." << endl;
            cout << "Cada gymnasio cuenta con una lista de membresias con su precio y descripcion." << endl;
            cout << "En la parte del usuario contamos con un menu simple de 'mi cuenta', el cual tiene opciones como; Cambiar contraseña," << endl;
            cout << "mi plan actual de la membresia, historial de planes y dar de baja" << endl;
            cout << "Este mini proyecto elaborado por Felipe Masliah en vacaiones de turismo " << endl;
            break;
        }
        case 7:
        {
            LimpiarScreen();
            cout << "Saliendo del programa...";

            break;
        }
        default:
        {
            LimpiarScreen();
            if (opcion == 1000)
            {
                LimpiarScreen();
                MenuAdmin(gym);
            }
            else
            {

                cout << " Ingrese opción valída... " << endl;
            }
            break;
        }
        }

    } while (opcion != 7);
}

int main()
{
    LimpiarScreen();
    Gym gymnasio;
    InicializarGymnasios(gymnasio);
    Menu(gymnasio);

    return 0;
}
/*Consideraciones
-En la funcion si existe en la misma direccion un gymnasio es incorrecta ya que solo comprueba que no se repita el mismo gym en la misma direccion,
pero si son diferentes gym lo toma valido y es un errror.

-Cuando en menu principal abro el listado de gymnasios y coloco ver sus membresias y luego salgo del menu por alguna razon da segmenation fault (prioridad 1 arreglarlo)
pasos
    *opcion 1 ver listado de gimnasios
        solicitar ver plan de membresias de un gimnasio en particular
            - muestra sus planes
        apretamos 'n' para no continuar
    *opcion 7 para salir del programa / rompe

    // arreglar los errores del menu
-------
*Hacer el menu de usuario

*/