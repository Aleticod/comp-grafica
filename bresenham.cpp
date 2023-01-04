// Nombre:      bresenham.cpp
// Proposito:   Dibujar una linea pixel a pixel mediante el metodo de Bresenham
// Autor:       Alex H. Pfoccori Quispe

#include <GL/glut.h>
#include <stdio.h>

int xinicio, yinicio, xfinal, yfinal;


// Iniciamos nuestros parametros de color y la dimension de la ventana
void inicio() {
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-10, 10, -10, 10);
}

// Funcion para dibujar un pixel
void dibujarPixel(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

// Implementacion del algoritmo de Bresenham
void bresenham(int xinicio, int xfinal, int yinicio, int yfinal) {
    int dx, dy, i, p;
    int incx, incy, inc1, inc2;
    int x,y;

    // Calculo de las variaciones en X e Y
    dx = xfinal-xinicio;
    dy = yfinal-yinicio;

    if (dx < 0) dx = -dx;
    if (dy < 0) dy = -dy;
    incx = 1;
    if (xfinal < xinicio) incx = -1;
    incy = 1;
    if (yfinal < yinicio) incy = -1;
    x = xinicio;
    y = yinicio;

    // Verificacion de la pendiente
    // Caso: 0 < m < 1  o  -1 < m < 0
    if (dx > dy) {
        dibujarPixel(x, y);
        // Se define el Po (P inicial)
        p = 2 * dy-dx;
        // Se calcula los incrementos
        inc1 = 2*(dy-dx);
        inc2 = 2*dy;

        i = 0;
        // Bucle while
        while (i<dx) {
            if (p >= 0) {
                // Se incrementa la y en 1
                y += incy;
                // Se calcula el nuevo P
                p += inc1;
            }
            else
                // Se calcula el nuevo P
                p += inc2;
            // Se incrementa la x en 1
            x += incx;
            i++;
            dibujarPixel(x, y);
        }
    // Caso: m > 1  o  m < -1
    } else {
        dibujarPixel(x, y);
        // Se define el Po (P inicial)
        p = 2*dx-dy;
        // Se calcula los incrementos
        inc1 = 2*(dx-dy);
        inc2 = 2*dx;

        // Bucle while
        i = 0;
        while (i<dy) {
            if (p >= 0) {
                // Se incrementa la x en 1
                x += incx;
                // Se calcula el nuevo P
                p += inc1;
            }
            else
                // Se calcual el nuevo P
                p += inc2;
            // Se incrementa la y en 1
            y += incy;
            i++;
            dibujarPixel(x, y);
        }
    }
}


// Funcion dibujar que llama a la funcion bresenham
void Dibujar() {
    bresenham(xinicio, xfinal, yinicio, yfinal);
    glFlush();
}


// Programa principal
int main(int argc, char **argv) {
    // Lectura de los datos
    printf( "Ingresar coordenadas (xinicio yinicio xfinal yfinal), ejemplo 1 2 4 7\n");
    scanf("%d %d %d %d", &xinicio, &yinicio, &xfinal, &yfinal);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Implementacion del Bresenham");
    inicio();
    glutDisplayFunc(Dibujar);
    glutMainLoop();
    return 0;
}