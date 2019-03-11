#include <stdlib.h> //CABECERA-BIBLIOTECA EST¡NDAR DEL LENGUAJE C
#include <GLUT/glut.h> //CABECERA-BIBLIOTECA DE GLUT
#include <math.h> //LIBRERIA PARA AGREGAR POTENCIA

typedef enum{
    NEGRO,
    AZUL,
    VERDE,
    CYAN,
    ROJO,
    MAGENTA,
    AMARILLO,
    BLANCO,
    x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19
}COLORES;

const float PaletaColor[27][3]={0,0,0,0,0,1,0,1,0,0,1,1,1,0,0,1,0,1,1,1,0,1,1,1, 0.5,0.5,0.5,   0.5,0.5,0,  0.5,0.5,1,  0.5,0,0,   0.5,0,1,  0.5,1,0,  0.5,1,1,  0,0,0.5,  0,1,0.5,
    1,0,0.5,  1,1,0.5,  0,0.5,0,  0,0.5,1, 1,0.5,0, 1,0.5,1,  0.5,0,0.5,  0.5,1,0.5, 0,0.5,0.5, 1,0.5,0.5};


typedef struct{ //ESTRUCTURA PARA DEFININIR LAS COORDENADAS DE LOS PUNTOS
    float x;
    float y;
}PUNTO;

typedef struct{ // ESTRUCTURA PARA DEFINIR LOS VERTICES DE LA LINEA
    float xi;
    float yi;
    float xf;
    float yf;
}LINEA;

typedef struct{ // ESTRUCTURA PARA DEFINIR LOS VERTICES DEL CUADRADO
    float x;
    float y;
    float lado; //LADO
}CUADRADO;

typedef struct{ // ESTRUCTURA PARA DEFINIR LOS VERTICES DEL CIRCULO
    float x0;
    float y0;
    float r;
}CIRCULO;

typedef struct{ //ESTRUCTURA PARA DEFINIR LOS VERTICES DE LA ELIPSE
    float x0;
    float a;
    float y0;
    float b;
    float th;
}ELIPSE;


//____________________________________________________________________ FUNCIONES DECLARACION


void Pantalla(void); //MANDA LLAMAR LA FUNCION PARA IMPRIMIR PANTALLA
void Linea(LINEA *L); //MANDA LLAMAR LA FUNCION PARA IMPRIMIR LINEA
void Cuadrado(CUADRADO *C); //MANDA LLAMAR LA FUNCION PARA IMPRIMIR CUADRADO
void Circulo(CIRCULO *C); //MANDA LLAMAR LA FUNCION PARA IMPRIMIR EL CIRCULO
void Elipse(ELIPSE *E); //MANDA LLAMAR LA FUNCION PARA IMPRIMIR LA ELIPSE
void AsignaColor(COLORES color); //FUNCION DE PRUEBA (PASO POR VALOR)
void Raton(int boton, int estado, int x, int y); //RATON
void RatonActivo(int x, int y);
void DibujarTexto(char *Text, float x, float y);
void DibujarTexto2(char *Text, float x, float y);
void CuadrosColores();
void Teclado(unsigned char tecla, int x, int y);


int size=1; //TAMAÑO INICIAL
int sizeCuadrado=1;
int menu; //MENU BOTON DERECHO
int menuCuadrado;
int star=0;

void TamanoPunto(int id); //TAMAÑO DE LAS FIGURAS
void BtnDerecho(int id); //ACCION BOTON DERECHO
void TamanoCuadrado(int id);

unsigned int NumDeCuadros = 0;
CUADRADO Vcuad[100];

unsigned int PrimerPunto = 1;
unsigned int NumDeLineas = 1;
LINEA Vline[100];

unsigned int PrimerPuntoCirc = 1;
unsigned int NumDeCirculos = 1;
CIRCULO Vcirc[100];

unsigned int PrimerPuntoElipse = 1;
unsigned int SegundoPuntoElipse = 0;
unsigned int NumDeElipses = 1;
ELIPSE Velipse[100];

const unsigned int TOTAL_PUNTOS = 4000; //LIMITE DE PUNTOS
unsigned int NumDePuntos = 0; //CONTADOR
PUNTO Vpuntos[TOTAL_PUNTOS]; //ARREGLO DE PUNTOS

//LINEA L1;

COLORES Color = NEGRO;

int BanderaLinea = 0;
int BanderaCuadrado = 0;
int BanderaTriangulo = 0;
int BanderaCirculo = 0;
int BanderaLapiz = 0;
int BanderaElipse = 0;


//____________________________________________________________________ FUNCION MAIN


int main(int argc, char** argv)
{
    //______________________________________CONFIGURACIONES INICIALES
    glutInit(&argc, argv);                  //Inicializa la libreria GLUT
    glutInitWindowPosition(100,100);         //Posicion de la venta:
    glutInitWindowSize(400,400);            //Tamaño de la venta
    glutCreateWindow("Primitivas de Dibujo en OpenGL");       //Se crea la ventana a mostrar
    
    //______________________________________DIBUJAR MENU BTN DERECHO
    menuCuadrado=glutCreateMenu(TamanoCuadrado);
    glutAddMenuEntry("Aumentar", 1);
    glutAddMenuEntry("Disminuir", 2);
    
    
    menu=glutCreateMenu(TamanoPunto);
    glutAddMenuEntry("Aumentar", 1);
    glutAddMenuEntry("Disminuir", 2);
    
    glutCreateMenu(BtnDerecho);
    glutAddSubMenu("Grosor", menu);
    glutAddSubMenu("Tamaño Cuadrado", menuCuadrado);
    
    glutAddMenuEntry("Salir",2);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    
    
    glClearColor(1,1,1,1);                  // Definir el color //Ultimo cero para otras configuraciones diferentes a RGB
    glMatrixMode(GL_PROJECTION); //Activar matriz de transformación
    gluOrtho2D(-10, 10, -10, 10); // (xmin,Xmax,Ymin,Ymax) eje coordenado
    
    //_____________________________________ASIGNACION DE CALLBACKS (FUNCIONES DE SERVICIO A EVENTOS)
    
    glutDisplayFunc(&Pantalla);
    glutMouseFunc(&Raton);
    glutMotionFunc(&RatonActivo);
    glutKeyboardFunc(&Teclado);
    AsignaColor(Color);
    
    
    //_____________________________________ESTADO DE ESPERA DE EVENTOS
    glutMainLoop();     //Procesamiento de eventos GLUT
    return 0; //
}


//____________________________________________________________________ FUNCION PANTALLA

void Pantalla()
{
    glClearColor (1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    
   
    //MENU DE INSTRUCCIONES
    if(star==0||star==1)
     {
         glClearColor (0.9, 0.9, 0.9, 1.0);
         glClear(GL_COLOR_BUFFER_BIT);
         glColor3f(0, 0, 0);
         DibujarTexto2("INSTRUCCIONES", -4, 8);
         DibujarTexto2("Tecla  +  : Aumenta grosor de dibujado", -8.5, 6);
         DibujarTexto2("Tecla  -  : Disminuye grosor de dibujado", -8.5, 5);
         DibujarTexto2("Tecla  c  : Aumenta tamano del cuadrado", -8.5, 4);
         DibujarTexto2("Tecla  x  : Disminuye tamano del cuadrado", -8.5, 3);
         DibujarTexto2("Tecla  a  : Eleccion rapida color azul", -8.5, 2);
         DibujarTexto2("Tecla  n  : Eleccion rapida color negro", -8.5, 1);
         DibujarTexto2("Click derecho/Tecla e: Salir", -8.5, 0);
         DibujarTexto2("Click izquierdo para continuar", -6, -7);
         
         star=1;
     
         glFlush();
         glClearColor (1.0, 1.0, 1.0, 1.0);
         glClear(GL_COLOR_BUFFER_BIT);
     }
    
    if(star==2)
    {
    unsigned int i;
        
        
    //________________________________________________________ DIBUJO DE FIGURAS
        
    glBegin(GL_POINTS);
    for(i = 0; i < NumDePuntos; i++)
    {
        glVertex2f(Vpuntos[i].x, Vpuntos[i].y);
    }
    glEnd();
        
    for(i = 0; i < NumDeCuadros; i++)
    {
        Cuadrado(&Vcuad[i]);
    }
    
    for(i = 0; i < NumDeCirculos; i++)
    {
        Circulo(&Vcirc[i]);
    }

    for(i = 0; i < NumDeLineas; i++)
    {
        Linea(&Vline[i]);
    }
        
    for(i = 0; i < NumDeElipses; i++)
    {
        Elipse(&Velipse[i]);
    }
    
    
    glColor3f(0.9, 0.9, 0.9);
    glRectf(-10, -7.7, 10,-10);
    
    glBegin(GL_LINES);
    glColor3f(0, 0, 0);
    glLineWidth(3);
    glVertex2f(-10, -7.7);
    glVertex2f(10, -7.7);
    glEnd();
    
    
    //LINEA EN HERRAMIENTAS
    glBegin(GL_LINES);
    glColor3f(0, 0, 0);
    glVertex2f(0, -8.8);
    glVertex2f(1, -7.9);
    glEnd();
    
    //CUADRADO EN HERRAMIENTAS
    glBegin(GL_LINE_LOOP);
    glVertex2f(0.2, -9);
    glVertex2f(1, -9);
    glVertex2f(1, -9.9);
    glVertex2f(0.2, -9.9);
    glEnd();
    
    
    //CIRCULO EN HERRAMIENTAS
    CIRCULO *Circ; //PUNTERO CIRCULO
    Circ=(CIRCULO *)malloc(sizeof(CIRCULO));
    Circ->x0=1.93;
    Circ->y0=-9.4;
    Circ->r=.5;
    glColor3f(0, 0 , 0);
    Circulo(Circ); //Mandamos los valores de Circ a la funcion Circulo
    free(Circ);
    

    //ELIPSE
    ELIPSE *E;
    E=(ELIPSE *)malloc(sizeof(ELIPSE)); //Tamaño del puntero
    //Valores para el puntero de la elipse
    E->x0=3.5; //0.0
    E->a=.7;
    E->y0= -9.5; //0.0
    E->b=.2;
    E->th=45.0;
    Elipse(E);
    free(E);
    
    
    CuadrosColores();
    
    //LAPIZ EN HERRAMIENTAS
    glBegin(GL_LINES);
    glColor3f(0, 0, 0);
    glLineWidth(2);
    glVertex2f(2, -7.9);
    glVertex2f(2, -8.6);
    glEnd();
        
    glBegin(GL_LINE_STRIP);
    glColor3f(0, 0, 0);
    glVertex2f(2.7, -7.7);
    glVertex2f(2.7, -10);
    glEnd();
    
    //LINEA LATERAL
    glBegin(GL_LINE_STRIP);
    glColor3f(0, 0, 0);
    glVertex2f(2.7, -7.7);
    glVertex2f(2.7, -10);
    glEnd();
    
    //LINEA CENTRAL
    glBegin(GL_LINES);
    glVertex2f(1.2, -7.7);
    glVertex2f(1.2, -10);
    glEnd();
    
    //LINEA HORIZONTAL
    glBegin(GL_LINES);
    glVertex2f(0, -8.8);
    glVertex2f(4.2, -8.8);
    glEnd();
        
        
    glBegin(GL_LINE_STRIP);
    glColor3f(0, 0, 0);
    glVertex2f(4.2, -8.8);
    glVertex2f(4.2, -10);
    glEnd();
        
    
    
    glRectf(10,10,8,9);
    
    glColor3f(0,0, 0);
    DibujarTexto("Usa el click derecho", 4.5, -9);
    DibujarTexto("para ver mas opciones", 4.5, -9.5);
    glColor3f(1, 1, 1);
    DibujarTexto("Teclas", 8.4, 9.3);
    

    
    CuadrosColores();
    glFlush();
    }

}



//____________________________________________________________________ DIBUJAR TEXTO

void DibujarTexto(char *Text, float x, float y)
{
    char *c;
    glRasterPos2f(x, y);
    
    for(c = Text; *c != '\0'; c++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, *c);
}

void DibujarTexto2(char *Text, float x, float y)
{
    char *c;
    glRasterPos2f(x, y);
    
    for(c = Text; *c != '\0'; c++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
}



//____________________________________________________________________ RATON ACTIVO
void RatonActivo(int x, int y)
{
    if(BanderaLapiz == 1)
    {
        glPointSize(size);
        if (NumDePuntos < TOTAL_PUNTOS) //El contador va aumentando hasta que la condicion no se cumpla
        {
            Vpuntos[NumDePuntos].x = ((float)x - 200)/20; //Asigna el valor de x del punto
            Vpuntos[NumDePuntos].y = -1 * ((float)y - 200)/20; //Asigna el valor y del punto
            NumDePuntos++; //Aumenta el contador
            glutPostRedisplay(); //Redibuja la pantalla
        }
    }
}


//____________________________________________________________________ USO DE RATON


void Raton(int boton, int estado, int x, int y)
{
    float xc, yc;
    
    
    if ((boton == GLUT_LEFT_BUTTON) && (estado == GLUT_DOWN))
    {
       
        if(star==1)
        {
            star=2;
            Pantalla();
        }
        
        
        xc = ((float)x - 200) / 20;
        yc = ((float)(400 - y) - 200) / 20;
        
        if ((xc >= -10) && (xc <= -9) && (yc >= -10) && (yc <= -9))
            Color = NEGRO;
        else if ((xc >= -10) && (xc <= -9) && (yc >= -9) && (yc <= -8))
            Color = AZUL;
        else if ((xc >= -9) && (xc <= -8) && (yc >= -10) && (yc <= -9))
            Color = VERDE;
        else if ((xc >= -9) && (xc <= -8) && (yc >= -9) && (yc <= -8))
            Color = CYAN;
        else if ((xc >= -8) && (xc <= -7) && (yc >= -10) && (yc <= -9))
            Color = ROJO;
        else if ((xc >= -8) && (xc <= -7) && (yc >= -9) && (yc <= -8))
            Color = MAGENTA;
        else if ((xc >= -7) && (xc <= -6) && (yc >= -10) && (yc <= -9))
            Color = AMARILLO;
        else if ((xc >= -7) && (xc <= -6) && (yc >= -9) && (yc <= -8))
            Color = BLANCO;
        else if ((xc >= -6) && (xc <= -5) && (yc >= -10) && (yc <= -9))
            Color = x1;
        else if ((xc >= -6) && (xc <= -5) && (yc >= -9) && (yc <= -8))
            Color = x2;
        else if ((xc >= -5) && (xc <= -4) && (yc >= -10) && (yc <= -9))
            Color = x3;
        else if ((xc >= -5) && (xc <= -4) && (yc >= -9) && (yc <= -8))
            Color = x4;
        else if ((xc >= -4) && (xc <= -3) && (yc >= -10) && (yc <= -9))
            Color = x5;
        else if ((xc >= -4) && (xc <= -3) && (yc >= -9) && (yc <= -8))
            Color = x6;
        else if ((xc >= -3) && (xc <= -2) && (yc >= -10) && (yc <= -9))
            Color = x7;
        else if ((xc >= -3) && (xc <= -2) && (yc >= -9) && (yc <= -8))
            Color = x8;
        else if ((xc >= -2) && (xc <= -1) && (yc >= -10) && (yc <= -9))
            Color = x9;
        else if ((xc >= -2) && (xc <= -1) && (yc >= -9) && (yc <= -8))
            Color = x10;
        else if ((xc >= -1) && (xc <= 0) && (yc >= -10) && (yc <= -9))
            Color = x11;
        else if ((xc >= -1) && (xc <= 0) && (yc >= -9) && (yc <= -8))
            Color = x12;
        else if ((xc >= 0) && (xc <= 1) && (yc >= -10) && (yc <= -9))
        {
            BanderaCuadrado = 1;
            BanderaLinea = 0;
            BanderaCirculo = 0;
            BanderaLapiz = 0;
            BanderaElipse = 0;
        }
        else if ((xc >= 0) && (xc <= 1) && (yc >= -9) && (yc <= -8))
        {
            BanderaLinea = 1;
            BanderaCuadrado = 0;
            BanderaCirculo = 0;
            BanderaLapiz = 0;
            BanderaElipse = 0;
        }
        else if ((xc >= 1) && (xc <= 3) && (yc >= -10) && (yc <= -9))
        {
            BanderaCirculo = 1;
            BanderaCuadrado = 0;
            BanderaLinea = 0;
            BanderaLapiz = 0;
            BanderaElipse = 0;
        }
        else if ((xc >= 1) && (xc <= 3) && (yc >= -9) && (yc <= -8))
        {
            BanderaLapiz = 1;
            BanderaCirculo = 0;
            BanderaCuadrado = 0;
            BanderaLinea = 0;
            BanderaElipse = 0;
        }
        else if ((xc >= 3) && (xc <= 4) && (yc >= -10) && (yc <= -9))
        {
            BanderaElipse = 1;
            BanderaLapiz = 0;
            BanderaCirculo = 0;
            BanderaCuadrado = 0;
            BanderaLinea = 0;
        }
        else if (BanderaCuadrado == 1)          //DIBUJO DE CUADRADOS
        {
            glLineWidth(size);
            NumDeCuadros++;
            Vcuad[NumDeCuadros - 1].x = ((float)x - 200) / 20;
            Vcuad[NumDeCuadros - 1].y = ((float)(400 - y) - 200) / 20;
            Vcuad[NumDeCuadros - 1].lado = sizeCuadrado;
        }
        else if (BanderaCirculo == 1)       //DIBUJO DE CIRCULO
        {
            if(PrimerPuntoCirc == 1)
            {
                glLineWidth(size);
                Vcirc[NumDeCirculos - 1].x0 = xc;
                Vcirc[NumDeCirculos - 1].y0 = yc;
                Vcirc[NumDeCirculos - 1].r = 0;
                PrimerPuntoCirc = 0;
            }
            else
            {
                glLineWidth(size);
                Vcirc[NumDeCirculos - 1].r = sqrt(pow(xc - Vcirc[NumDeCirculos - 1].x0, 2) + pow(yc - Vcirc[NumDeCirculos - 1].y0, 2));
                NumDeCirculos++;
                PrimerPuntoCirc = 1;
            }
        }
        else if (BanderaLinea == 1)         //DIBUJO DE LINEA
        {
            
            if(PrimerPunto == 1)
            {
                
                glLineWidth(size);
                Vline[NumDeLineas - 1].xi = xc;
                Vline[NumDeLineas - 1].yi = yc;
                Vline[NumDeLineas - 1].xf = xc;
                Vline[NumDeLineas - 1].yf = yc;
                PrimerPunto = 0;
            }
            else
            {
                glLineWidth(size);
                Vline[NumDeLineas - 1].xf = xc;
                Vline[NumDeLineas - 1].yf = yc;
                NumDeLineas++;
                PrimerPunto = 1;
            }
        }
        else if (BanderaElipse == 1)            //DIBUJO DE ELIPSE
        {
            
            if(PrimerPuntoElipse == 1)
            {
                
                glLineWidth(size);
                Velipse[NumDeElipses - 1].x0 = xc;
                Velipse[NumDeElipses - 1].y0 = yc;
                PrimerPuntoElipse = 0;
                SegundoPuntoElipse = 1;
            }
            else if(SegundoPuntoElipse == 1)
            {
                Velipse[NumDeElipses - 1].a = xc - Velipse[NumDeElipses - 1].x0;
                Velipse[NumDeElipses - 1].b = yc - Velipse[NumDeElipses - 1].y0;
                Velipse[NumDeElipses - 1].th = atan(Velipse[NumDeElipses - 1].b / Velipse[NumDeElipses - 1].b);
                SegundoPuntoElipse = 0;
                PrimerPuntoElipse = 1;
                NumDeElipses++;
            }
        }
        else if ((xc >= 8) && (xc <= 10) && (yc >= 8) && (yc <= 10))
        {

            BanderaLapiz = 0;
            BanderaCirculo = 0;
            BanderaCuadrado = 0;
            BanderaLinea = 0;
            star=0;
            Pantalla();
        }

        glutPostRedisplay();
    }
    

    
}



//____________________________________________________________________ ASIGNAR COLOR


void AsignaColor(COLORES color)
{
    glColor3f(PaletaColor[color][0], PaletaColor[color][1], PaletaColor[color][2]);
}


//____________________________________________________________________ PRIMITIVAS FUNCIONES DESARRROLLO


void Linea(LINEA *L) //FUNCION QUE RECIBE EL PUNTERO LINEA
{
    
    glBegin(GL_LINE_LOOP);
    glVertex2f(L->xi,L->yi);
    glVertex2f(L->xf,L->yf);
    glEnd();
}

void Cuadrado(CUADRADO *C) //FUNCION QUE RECIBE EL PUNTERO CUADRADO
{
    
    glBegin(GL_LINE_LOOP);
    glPointSize(size);
    glVertex2f(C->x , C->y); //Posicion del Vertice 1
    glVertex2f(C->x + C->lado , C->y); //Posicion del Vertice 2
    glVertex2f(C->x + C->lado , C->y - C->lado); //Posicion del Vertice 3
    glVertex2f(C->x , C->y - C->lado); //Posicion del Vertice 4
    glEnd();
}




void Circulo(CIRCULO *C) //FUNCION QUE RECIBE EL PUNTERO CIRCULO
{
    
    float th,x,y;
    
    //CON COORDENADAS POLARES
    
    glBegin(GL_LINE_LOOP);
    for(th=0;th<360;th+=1)
    {
        x=C->r*cos((th/180)*3.1416) + C->x0;
        y=C->r*sin((th/180)*3.1416) +C->y0;
        glVertex2f(x, y); //Para dibujar el circulo
    }
    glEnd();
}

void Elipse(ELIPSE *E) //FUNCION QUE RECIBE EL PUNTERO ELIPSE
{
    float x,y,th, xr, yr;
    
    glBegin(GL_LINE_LOOP);
    for(th=0; th<360; th+=10)
    {
        x=E->a*cos((th/180)*3.141596);
        y=E->b*sin((th/180)*3.141596);
        xr = x * cos((E->th/180) * 3.141596) - y * sin((E->th/180) * 3.141596) + E->x0;
        yr = x * sin((E->th/180) * 3.141596) + y * cos((E->th/180) * 3.141596) + E->y0;
        glVertex2f(xr, yr);
    }
    glEnd();
}


//____________________________________________________________________________ PALETA DE COLORES

void CuadrosColores()
{
    AsignaColor(NEGRO);
    glRectf(-10,-10,-9,-9);
    AsignaColor(AZUL);
    glRectf(-10,-9,-9,-8);
    AsignaColor(VERDE);
    glRectf(-9,-10,-8,-9);
    AsignaColor(CYAN);
    glRectf(-9,-9,-8,-8);
    AsignaColor(ROJO);
    glRectf(-8,-10,-7,-9);
    AsignaColor(MAGENTA);
    glRectf(-8,-9,-7,-8);
    AsignaColor(AMARILLO);
    glRectf(-7,-10,-6,-9);
    AsignaColor(BLANCO);
    glRectf(-7,-9,-6,-8);
    AsignaColor(x1);
    glRectf(-6,-10,-5,-9);
    AsignaColor(x2);
    glRectf(-6,-9,-5,-8);
    AsignaColor(x3);
    glRectf(-5,-10,-4,-9);
    AsignaColor(x4);
    glRectf(-5,-9,-4,-8);
    AsignaColor(x5);
    glRectf(-4,-10,-3,-9);
    AsignaColor(x6);
    glRectf(-4,-9,-3,-8);
    AsignaColor(x7);
    glRectf(-3,-10,-2,-9);
    AsignaColor(x8);
    glRectf(-3,-9,-2,-8);
    AsignaColor(x9);
    glRectf(-2,-10,-1,-9);
    AsignaColor(x10);
    glRectf(-2,-9,-1,-8);
    AsignaColor(x11);
    glRectf(-1,-10,0,-9);
    AsignaColor(x12);
    glRectf(-1,-9,0,-8);
    if(Color == NEGRO)
        AsignaColor(NEGRO);
    if(Color == AZUL)
        AsignaColor(AZUL);
    if(Color == VERDE)
        AsignaColor(VERDE);
    if(Color == CYAN)
        AsignaColor(CYAN);
    if(Color == ROJO)
        AsignaColor(ROJO);
    if(Color == MAGENTA)
        AsignaColor(MAGENTA);
    if(Color == AMARILLO)
        AsignaColor(AMARILLO);
    if(Color == BLANCO)
        AsignaColor(BLANCO);
    if(Color == x1)
        AsignaColor(x1);
    if(Color == x2)
        AsignaColor(x2);
    if(Color == x3)
        AsignaColor(x3);
    if(Color == x4)
        AsignaColor(x4);
    if(Color == x5)
        AsignaColor(x5);
    if(Color == x6)
        AsignaColor(x6);
    if(Color == x7)
        AsignaColor(x7);
    if(Color == x8)
        AsignaColor(x8);
    if(Color == x9)
        AsignaColor(x9);
    if(Color == x10)
        AsignaColor(x10);
    if(Color == x11)
        AsignaColor(x11);
    if(Color == x12)
        AsignaColor(x12);
}



void TamanoPunto(int id)
{
    switch(id)
    {
        case 1:size++;
            break;
            
        case 2:if(size>1)
            size--;
            break;
    }
    
}

void TamanoCuadrado(int id)
{
    switch(id)
    {
        case 1:sizeCuadrado++;
            break;
            
        case 2:if(sizeCuadrado>1)
            sizeCuadrado--;
            break;
    }
}

void BtnDerecho(int id)
{
    
    if(id==2)
        exit(0);
    
}

void Teclado(unsigned char tecla, int x, int y)
{
    if(tecla == '+')
        size++;
    if(tecla == '-')
        size--;
    
    if(tecla=='c')
        sizeCuadrado++;
    if(tecla=='x')
        sizeCuadrado--;
    
    if(tecla=='n')
        Color=NEGRO;
    
    if(tecla=='a')
        Color=AZUL;
    
    if(tecla=='e')
        exit(0);
    
    
    glutPostRedisplay();
}






