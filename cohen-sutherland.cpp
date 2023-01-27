// Nombre:      cohen-sutherland.cpp
// Proposito:   Implementacion del algoritmo de Cohen Sutherland 
//              para clipping de rectas
// Autor:       Alex H. Pfoccori Quispe
// Compilacion: g++ cohen-sutherland.cpp -lglut -lGL -lGLU -o cohen-sutherland.exe
// Ejecucion:   ./cohen-sutherland.exe
 
// LIbrerias
#include <GL/glut.h>
#include <stdio.h>
#include <iostream>
using namespace std;

// Definicion de codigo de region
const int INSIDE = 0;   // 0000
const int LEFT = 1;     // 0001
const int RIGHT = 2;    // 0010
const int BOTTOM = 4;   // 0100
const int TOP = 8;      // 1000

// Definicion del metodo de mostrar ventana
void display();

// Definicion de xmax, ymax and xmin, ymin para
// el rectangulo de clipping.
int xmax;
int ymax;
int xmin;
int ymin;

// Definicion del puntos de inicion y final da recta
int xinicio;
int yinicio;
int xfinal;
int yfinal;

// Iniciamos nuestros parametros de color y la dimension de la ventana
void init(void)
{
    glClearColor(0.0,0,0,0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-5,30,-5,30);
}

// Funcion para dibujar un pixel
void display(double x1, double y1, double x2, double y2)
{
    glClear(GL_COLOR_BUFFER_BIT);
    // Definimos el color del viewport
    glColor3f(0.0,1.0,0.0);
    // Graficamos las rectas del viewport
    glBegin(GL_LINE_LOOP);
    glVertex2i(xmin,ymin);
    glVertex2i(xmin,ymax);
    glVertex2i(xmax,ymax);
    glVertex2i(xmax,ymin);
    glEnd();
    // Definimos el color de la recta recortada
    glColor3f(1.0,0.0,0.0);
    // Graficamos la recta recortada
    glBegin(GL_LINES);
    glVertex2i(x1,y1);
    glVertex2i(x2,y2);
    glEnd();
    glFlush();
}

// Funcion para obtener codigo de region para el punto (x,y)
int puntoCodigo(double x, double y)
{
	// Inicializamos el punto en el interior
	int code = INSIDE;

	if (x < xmin)       // para la parte izquierda del viewport
		code |= LEFT;
	else if (x > xmax)  // para la parte derecha del viewport
		code |= RIGHT;
	if (y < ymin)       // para la parte de abajo del viewport
		code |= BOTTOM;
	else if (y > ymax)  // para la parte de arriba del viewport
		code |= TOP;
	return code;
}

// Implementacion del codigo Cohen Sutherland
void cohenSutherland(double x1, double y1, double x2, double y2)
{
	// Optencion de los codigo del punto P0 y P1
	int code1 = puntoCodigo(x1, y1);
	int code2 = puntoCodigo(x2, y2);

	bool accept = false;

	while (true) {
		if ((code1 == 0) && (code2 == 0)) {
			// Si ambos puntos entran dentro del viewport
			accept = true;
			break;
		}
		else if (code1 & code2) {
			// Si ambos puntos estan fuera del viewport
			break;
		}
		else {
            // Si alguna seccion esta dentro de la region
			int cod_aux;
			double x, y;

			// Si por lo menos uno de los puntos esta fuera del viewport
			if (code1 != 0)
				cod_aux = code1;
			else
				cod_aux = code2;

			// Encontrar los puntos de interseccion
			if (cod_aux & TOP) {
				// Punto esta por encima del viewport
				x = x1 + (x2 - x1) * (ymax - y1) / (y2 - y1);
				y = ymax;
			}
			else if (cod_aux & BOTTOM) {
				// Punto esta por abajo del viewport
				x = x1 + (x2 - x1) * (ymin - y1) / (y2 - y1);
				y = ymin;
			}
			else if (cod_aux & RIGHT) {
				// Punto esta a la rederecha del viewport
				y = y1 + (y2 - y1) * (xmax - x1) / (x2 - x1);
				x = xmax;
			}
			else if (cod_aux & LEFT) {
				// Putno esta a la izquierda del viewport
				y = y1 + (y2 - y1) * (xmin - x1) / (x2 - x1);
				x = xmin;
			}

			// Los nuevos puntos fueron encontrados ahora remplazaremos
			if (cod_aux == code1) {
				x1 = x;
				y1 = y;
				code1 = puntoCodigo(x1, y1);
			}
			else {
				x2 = x;
				y2 = y;
				code2 = puntoCodigo(x2, y2);
			}
		}
	}
    // Si todos los puntos estan dentro imprimir
	if (accept) {
        display(x1, y1, x2, y2);
	}
	else
		cout << "Linea no esta dentro" << endl;
}

// Funcion que dibuja una recta
void DibujarRecta() {
    // Para dibujar la recta debemos aplicar el algoritmo de Cohen Sutherland
    cohenSutherland(xinicio, yinicio, xfinal, yfinal);
    glFlush();
}

// Main
int main(int argc,char** argv)
{
    // Ingreso de datos por consola
    printf("ALGORITMO DE COHEN SUTHERLAND\n");
    printf("=============================\n");
    printf("\nDATOS DEL VIEWPORT:\n");
    printf("==================\n");
    printf("Ingrese los datos -> xmin ymin \n");
    cin>>xmin>>ymin;
    printf("Ingrese los datos -> xmax ymax \n");
    cin>>xmax>>ymax;
    printf("\nDATOS DE LA RECTA: \n");
    printf("======================\n");
    printf("Ingrese los datos -> xinicio yinicio \n");
    cin>>xinicio>>yinicio;
    printf("Ingrese los datos -> xfinal yfinal \n");
    cin>>xfinal>>yfinal;

     // Inicializacion de la ventana
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    // Tamanio de la ventana
    glutInitWindowSize(500, 500);
    // Posiciono de inicio de la ventana
    glutInitWindowPosition(0, 0);
    // Nombre de la ventana
    glutCreateWindow("Implementacion de Cohen Sutherland");  
    glutDisplayFunc(DibujarRecta);
    init();
    glutMainLoop();
	return 0;
}
