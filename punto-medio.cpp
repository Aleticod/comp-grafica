// Nombre:      punto-medio.cpp
// Proposito:   Implementacion del algoritmo de punto medio
// Autor:       Alex H. Pfoccori Quispe
// Compilacion: g++ punto-medio.cpp -lglut -lGL -lGLU -o punto-medio.exe
// Ejecucion:   ./punto-medio.exe

#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

// Variables globales
int xinicio, yinicio, xfinal, yfinal;
int h, k, r, a, b;
int opc;


// Iniciamos nuestros parametros de color y la dimension de la ventana
void inicio() {
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-15, 15, -15, 15);    // Nuestra ventana sera de 30 x 30
}

// Funcion para dibujar un pixel
void dibujarPixel(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

// RECTA
// Implementacion del algoritmo de punto medio para una recta
void puntoMedioRecta(int xinicio, int xfinal, int yinicio, int yfinal) {
    // Declaracion de variables
    int dx, dy;
    float dm;
    int x, y, xfin, yfin;

    // Calculo de las variaciones en X e Y
    dx = xfinal-xinicio;
    dy = yfinal-yinicio;

    // Verificacion de pendite de la recta
    // Caso: 0 < m < 1  o  -1 < m < 0
    if (abs(dy) < abs(dx)) {

        // Verificar que el inicio sea de izquierda a derecha
        if(xinicio > xfinal) {
            x = xfinal;
            y = yfinal;
            xfin = xinicio;
        }
        else {
            x = xinicio;
            y = yinicio;
            xfin = xfinal;
        }

        // Evaluacion del punto medio
        dm = dy - dx / 2;

        // Bucle: inicia en el punto incial x hasta el punto final x
        while(x <= xfin) {

            // Se grafica los pixel (x,y)
            dibujarPixel(x, y);

            // Se hace un incremento en x
            x = x + 1;

            // Evaluacion del punto medio
            if (dm <= 0) {
                dm = dm + dy;           // Punto medio para el siguiente punto
            }
            else {
                y = y + 1;
                dm = dm + (dy - dx);    // Punto medio para el siguiente punto

            }
        }
    }

    // Caso: m > 1  o  m < -1
    else {

        // Verificamos que el recorrido sea de abajo a arriba
        if(yinicio > yfinal) {
            x = xfinal;
            y = yfinal;
            yfin = yinicio;
        }
        else {
            x = xinicio;
            y = yinicio;
            yfin = yfinal;
        }

        // Evaluamos el punto medio para el primer punto
        dm = dx - dy / 2;

        // Bucle que va desde el inicio y hasta el final y
        while(y <= yfin) {

            // Se dibujan el pixel (x,y)
            dibujarPixel(x, y);

            // Incremento de una unidad en "y"
            y = y + 1;

            // Evaluacion del punto medio para el siguiente punto
            if (dm <= 0) {
                dm = dm + dx;
            }
            else {
                x = x + 1;
                dm = dm + (dx - dy);

            }
        }
    }
}

// CIRCUNFERENCIA
// Implementacion del algoritmo de punto medio para una circunferencia
void puntoMedioCirculo(int h, int k, int r) {
    // Definimos variables
    int x, y;
    float p;

    // Inicializamos el punto (x,y) en (0,r)
    x = 0;
    y = r;

    // Calculo del primero parametro de decision P
    p = 5/4 - r;

    // Se grafican los 4 primeros pixeles conocidos
    dibujarPixel(h + x, k + y);
    dibujarPixel(h + x, k - y);
    dibujarPixel(h + y, k + x);
    dibujarPixel(h - y, k + x);

    // Evaluamos los pixeles antes de llegar a la recta identidad
    while(x < y) { 
        // En el caso en que se grafique el punto Este
        if (p <= 0) {
            x += 1;
            p = p + 2 * x + 1; // Calculo del nuevo parametro de evaluacion
        }
        // En el caso en que se grafique el punto Sur Este
        else {
            x +=1;
            y -=1;
            p = p + (2 * x) - (2 * y) + 1; // Calculo del nuevo parametro de evaluacion
        }

        // Se grafican los 8 puntos (Esto mediante reflexion)
        dibujarPixel(h + x, k + y);
        dibujarPixel(h + y, k + x);
        dibujarPixel(h + y, k - x);
        dibujarPixel(h + x, k - y);
        dibujarPixel(h - x, k - y);
        dibujarPixel(h - y, k - x);
        dibujarPixel(h - y, k + x);
        dibujarPixel(h - x, k + y);
    }
}

// ELIPSE
// Implementacion del algoritmo de punto medio para una elipse
void puntoMedioElipse(int h, int k, int a, int b) {
    // Definicion de variables
    int x, y, a2, b2;
    float p1, p2;

    // Inicializamos el punto (x,y) en (0,b)
    x = 0;
    y = b;

    // Elevamos el parametro a y b al cuadrado
    a2 = pow(a, 2);
    b2 = pow(b, 2);

    // Graficamos los 4 pixeles conocidos al inicio
    dibujarPixel(h + a, k);
    dibujarPixel(h - a, k);
    dibujarPixel(h, k + b);
    dibujarPixel(h, k - b);

    // Calculo del primer parametro de decision
    p1 = b2 - (a2 * b) + 0.25 * a2;

    // Evaluamos para el primer y segundo cuadrante
    while ((b2 * x) < (a2 * y)) {

        // Evaluamos el parametro de decision
        if (p1 < 0) {
            x ++;
            p1 = p1 + (2 * b2 * x) + b2;
        }
        else {
            x ++;
            y --;
            p1 = p1 + (2 * b2 * x) - (2 * a2 * y) + b2;
        }

        // Graficamos los 4 pixeles (metodo de refelxion) 
        dibujarPixel(h + x, k + y);
        dibujarPixel(h - x, k + y);
        dibujarPixel(h + x, k - y);
        dibujarPixel(h - x, k - y);
    }
    
    // Calculo del segundo parameto de decision
    p2=(b2) * pow((x+0.5), 2) + (a2) * pow((y - 1), 2) - (a2 * b2);
    
    // Evaluamos para el tercer y cuarto cuadrante
    while(y>0)
      {

        // Evaluamos el segundo parametro de decision
         if (p2>0)
         {
           y --;
           p2 = p2 - (2 * a2 * y) + a2;
         }
         else
         {
           x ++; 
           y --;
           p2 = p2 + (2 * b2 * x) - (2 * a2 * y) + a2;
         }

         // Graficamos los 4 pixeles (metodo de refelxion
         dibujarPixel(h + x, k + y);
         dibujarPixel(h - x, k + y);
         dibujarPixel(h + x, k - y);
         dibujarPixel(h - x, k - y);
      }
}

// Funcion DibujarRecta que hace llamado a la funcion puntoMedioRecta
void DibujarRecta() {
    puntoMedioRecta(xinicio, xfinal, yinicio, yfinal);
    glFlush();
}

// Funcion DibujarCirculo que hace llamado a la funcion puntoMedioCirculo
void DibujarCirculo() {
    puntoMedioCirculo(h, k , r);
    glFlush();
}

// Funcion DibujarElpse que hace llamado a la funcion puntoMedioElipse
void DibujarElipse() {
    puntoMedioElipse(h, k, a, b);
    glFlush();
}

// Programa principal
int main(int argc, char **argv) {
    // Menu para elegir que algoritmo ejecutar
    printf("INGRESE UNA OPCION (1 - 3)\n");
    printf("1 -> Graficar una recta\n");
    printf("2 -> Graficar una circunferencia\n");
    printf("3 -> Graficrr una elipe\n");
    scanf("%d", &opc);

    switch (opc) {
        // Caso: Recibir datos de la recta
        case 1:
            printf( "Ingresar coordenadas (xinicio, yinicio) y (xfinal, yfinal)\n");
            printf("Ingresar x inicial: \n");
            scanf("%d", &xinicio);
            printf("Ingresar y inicial: \n");
            scanf("%d", &yinicio);
            printf("Ingresar x final: \n");
            scanf("%d", &xfinal);
            printf("Ingresar y final: \n");
            scanf("%d", &yfinal);
            break;
        // Caso: Recibir datos del Circulo
        case 2:
            printf( "Ingresar las coordenadas del centro (h, k) y el radio r\n");
            printf("Ingresar h: \n");
            scanf("%d", &h);
            printf("Ingresar k: \n");
            scanf("%d", &k);
            printf("Ingresar r (radio): \n");
            scanf("%d", &r);
            break;
        // Caso: Recibir datos de la Elpse
        case 3:
            printf( "Ingresar las coordenadas del centro (h,k) y los parametros a y b \n");
            printf("Ingresar h: \n");
            scanf("%d", &h);
            printf("Ingresar k: \n");
            scanf("%d", &k);
            printf("Ingresar el parametro a: \n");
            scanf("%d", &a);
            printf("Ingresar el parametro b: \n");
            scanf("%d", &b);
            break;
    }

    // Inicializacion de la ventana
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    // Tamanio de la ventana
    glutInitWindowSize(500, 500);
    // Posiciono de inicio de la ventana
    glutInitWindowPosition(0, 0);
    // Nombre de la ventana
    glutCreateWindow("Implementacion de Punto Medio");
    inicio();
    // Dependiendo a la opcion ingresada se hara llamada a la funcion
    // Dibujar
    switch (opc) {
        // Caso: Dibujar la Recta
        case 1:
            glutDisplayFunc(DibujarRecta);
            break;
        // Caso: Dibujar el Circulo
        case 2:
            glutDisplayFunc(DibujarCirculo);
            break;
        // Caso: Dibujar la Elipse
        case 3:
            glutDisplayFunc(DibujarElipse);
            break;
    }

    glutMainLoop();
    return 0;
}