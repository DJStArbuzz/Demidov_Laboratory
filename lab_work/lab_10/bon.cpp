    if (Polygons.size() != 0) {
        for (size_t i = 0; i < Polygons.size(); i++) {
            vector<Point> list = Polygons[i].getVertices();

            for (int j = 0; j < list.size(); j++) {

                glBegin(GL_POINT);
                glColor3f(3.0, 0.0, 0.0);
                glVertex3f(list[j].x, list[j].y, 0);
                glEnd();
            }
        }
    }


class Button {
private:
    double x;
    double y;
    double width;
    double height;
    const char* text;
public:
    Button() : x(0), y(0), width(0), height(0), text(nullptr) {};
    Button(double x, double y, double width, double height,const char* text) 
        : x(x), y(y), width(width), height(height), text(text) {};
    
    vector <double> colors;
    void setColor(double first, double second, double third) {
        colors.push_back(first);
        colors.push_back(second);
        colors.push_back(third);
    }

    void drawButton() {
        
        //Отрисовка кнопки
        glBegin(GL_POLYGON);
        glColor3f(colors[0], colors[1], colors[2]); // Серый цвет
        glVertex2f(x, y);
        glVertex2f(x + width, y);
        glVertex2f(x + width, y + height);
        glVertex2f(x, y + height);
        glEnd();

        glColor3f(0.0f, 0.0f, 0.0f); // Серый цветw
        int textLength = strlen(text);
        float textX = x + 20;
        float textY = y + 25;

        glRasterPos2f(textX, textY);
        for (int i = 0; i < textLength; i++) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
        }
    }

    bool isButtonHovered(Point& najatie) {
        return najatie.x >= this->x && najatie.x <= this->x + this->width &&
            najatie.y >= this->y && najatie.y <= this->y + this ->height;
    }
   
};


vector <Polygon> Polygons;
vector <Ellipse> Ellipsoids;
int editing_number = -1;

enum MenuState
{
    MAIN,
    CREATION,
    POLYGON,
    ELLIPSE,
    CIRCLE,
    RECTANGLE,
    SQUARE,
    TRIANGLE,
    EDIT
};

MenuState currentMenuState = MAIN;
//Кнопки меню
Button bPolygon(-900, -900, 200, 75, "Polygon");
Button bEllipse(-650, -900, 200, 75, "Ellipse");
Button bCircle(-400, -900, 200, 75, "Circle");
Button bRectangle(-900, -800, 200, 75, "Rectangle");
Button bTriangle(-650, -800, 200, 75, "Triangle");
Button bSquare(-400, -800, 200, 75, "Square");
Button to_Main_Menu(700, -900, 200, 75, "To start");

Button Create(450, -900, 200, 75, "Create");
Button Edit(700, -900, 200, 75, "Edit");

void mouseClickHandler(int button, int state, int x, int y) {
    // Проверка нажатия левой кнопки мыши
    setlocale(LC_ALL, "rus");
    double X = (x - 500) * 2, Y = 1000 - (y * 2);
    
    Point najatie(X, Y);
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        switch (currentMenuState)
        {
        case MAIN:
            // Проверяем, на какую кнопку основного меню был сделан щелчок
            if (Create.isButtonHovered(najatie))
            {
                currentMenuState = CREATION;
                glutPostRedisplay();
            }
            if (Edit.isButtonHovered(najatie))
            {
                currentMenuState = EDIT;
                glutPostRedisplay();
            }

            break;
        case CREATION:
            if (bPolygon.isButtonHovered(najatie))
            {
                currentMenuState = POLYGON;
                glutPostRedisplay();
            }
            if (bRectangle.isButtonHovered(najatie))
            {
                currentMenuState = RECTANGLE;
                glutPostRedisplay();
            }
            if (bSquare.isButtonHovered(najatie))
            {
                currentMenuState = SQUARE;
                glutPostRedisplay();
            }
            if (bEllipse.isButtonHovered(najatie))
            {
                currentMenuState = ELLIPSE;
                glutPostRedisplay();
            }
            if (bCircle.isButtonHovered(najatie))
            {
                currentMenuState = CIRCLE;
                glutPostRedisplay();
            }
            if (bTriangle.isButtonHovered(najatie))
            {
                currentMenuState = TRIANGLE;
                glutPostRedisplay();
            }
            if (to_Main_Menu.isButtonHovered(najatie))
            {
                currentMenuState = MAIN;
                glutPostRedisplay();
            }
            break;
        case EDIT:
            if (to_Main_Menu.isButtonHovered(najatie))
            {
                currentMenuState = MAIN;
                glutPostRedisplay();
            }
            else if (true) {
                if (Polygons.size() == 0) {
                    cout << "Изменять нечего, вектор полигонов пустой!" << endl;
                    cout << "Переход к созданию многоугольника" << endl;
                    currentMenuState = MAIN;
                    glutPostRedisplay();
                }
                else if(true){
                    cout << "Введите номер изменяемого элемента от 1 до " << Polygons.size() << endl;
                    cin >> editing_number;//ввод порядкового номера для удобста счета от 1
                    editing_number--; // последующее изменение n под номер данного елемента
                    int n = Polygons[editing_number].verticesCount();
                    if (n == 3) {
                        currentMenuState = TRIANGLE;
                        glutPostRedisplay();
                    }
                    else if (n == 4) {
                        vector<Point> Verts = Polygons[editing_number].getVertices();
                        double a = dist(Verts[0], Verts[1]), b = dist(Verts[1], Verts[2]), c = dist(Verts[2], Verts[3]), d = dist(Verts[3], Verts[0]);
                        if (equal(a, b) && equal(b,c) && equal(c,d) && equal(a,d)) {
                            currentMenuState = SQUARE;
                            glutPostRedisplay();
                        }
                        else if (equal(a, c) && equal(b, d)) {
                            currentMenuState = RECTANGLE;
                            glutPostRedisplay();
                        }
                        else if(true){
                            currentMenuState = POLYGON;
                            glutPostRedisplay();
                        }
                    }
                    else if(n > 4){
                        currentMenuState = POLYGON;
                        glutPostRedisplay();
                    }
                }
            }
            break;
        case POLYGON:

            if (to_Main_Menu.isButtonHovered(najatie))
            {
                // Переключаем состояние меню на MAIN
                currentMenuState = MAIN;
                // Обновляем сцену
                glutPostRedisplay();
            }
            else if (true) {
                cout << "Введите колличество вершин многоугольника" << endl;
                int n;
                cin >> n;
                vector <Point> dots;
                for (int i = 0; i < n; i++) {
                    double x, y;
                    cin >> x >> y;
                    dots.push_back(Point(x, y));
                }
                if (editing_number == -1) {
                    Polygons.push_back(Polygon(dots));
                }
                else {
                    Polygons[editing_number] = Polygon(dots);
                }
                currentMenuState = MAIN;
                glutPostRedisplay();
            }
            

            break;
        case RECTANGLE:
            if (to_Main_Menu.isButtonHovered(najatie))
            {
                // Переключаем состояние меню на MAIN
                currentMenuState = MAIN;
                // Обновляем сцену
                glutPostRedisplay();
            }
            else if (true) {
                cout << "Введите 2 вершины и коэффициент отнощения сторон прямоугольника" << endl;
                double x1, y1, x2, y2, k;
                cin >> x1 >> y1 >> x2 >> y2 >> k;
                if (editing_number == -1) {
                    Polygons.push_back(Rectangle(Point(x1, y1), Point(x2, y2), k));
                }
                else {
                    Polygons[editing_number] = Rectangle(Point(x1, y1), Point(x2, y2), k);
                }
                
                currentMenuState = MAIN;
                glutPostRedisplay();
            }
            break;
        case SQUARE:
            if (to_Main_Menu.isButtonHovered(najatie))
            {
                // Переключаем состояние меню на MAIN
                currentMenuState = MAIN;
                // Обновляем сцену
                glutPostRedisplay();
            }
            else if (true) {
                cout << "Введите 2 вершины квадрата" << endl;
                double x1, y1, x2, y2;
                cin >> x1 >> y1 >> x2 >> y2;
                if (editing_number == -1) {
                    Polygons.push_back(Square(Point(x1, y1), Point(x2, y2)));
                }
                else {
                    Polygons[editing_number] = Square(Point(x1, y1), Point(x2, y2));
                }
                
                currentMenuState = MAIN;
                glutPostRedisplay();
            }
            break;
        case TRIANGLE:
            
            if (to_Main_Menu.isButtonHovered(najatie))
            {
                currentMenuState = MAIN;
                // Обновляем сцену
                glutPostRedisplay();
            }
            else if (true) {
                cout << "Введите 3 вершины треуголька" << endl;
                double x1, y1, x2, y2, x3, y3;
                cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
                vector <Point> dots;
                dots.push_back(Point(x1, y1));
                dots.push_back(Point(x2, y2));
                dots.push_back(Point(x3, y3));
                if (editing_number == -1) {
                    Polygons.push_back(Triangle(dots));
                }
                else {
                    Polygons[editing_number] = Triangle(dots);
                }
                
                currentMenuState = MAIN;
                glutPostRedisplay();
            }
            break;

        case ELLIPSE:
            
            if (to_Main_Menu.isButtonHovered(najatie))
            {
                currentMenuState = MAIN;
                glutPostRedisplay();
            }
            else if (true) {
                cout << "Введите 2 вершины фокусов и расстояние" << endl;
                double x1, y1, x2, y2, r;
                cin >> x1 >> y1 >> x2 >> y2 >> r;
                Ellipsoids.push_back(Ellipse(Point(x1, y1), Point(x2, y2), r));
                
                currentMenuState = MAIN;
                glutPostRedisplay();
            }
            break;
        
        case CIRCLE:
            if (to_Main_Menu.isButtonHovered(najatie))
            {
                currentMenuState = MAIN;
                glutPostRedisplay();
            }
            else if (true) {
                cout << "Введите центр круга и радиус" << endl;
                double x1, y1,  r;
                cin >> x1 >> y1 >> r;
                Ellipsoids.push_back(Ellipse(Point(x1, y1), Point(x1 + 1, y1), r * 2));
                
                currentMenuState = MAIN;
                glutPostRedisplay();
            }
            break;
        }
    }
}



//**********************************************************
// Рисование сцены
void RenderScene(void) {
	setlocale(LC_ALL, "rus");
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f); // Цвет фона окна
	glClear(GL_COLOR_BUFFER_BIT);
	DrawOs();
    bPolygon.setColor(0.9,0.0,0.5);
    bEllipse.setColor(1.0, 0.5,0.3);
    bCircle.setColor(0.2,1.0,1.0);
    bRectangle.setColor(0.6,1.0,0.1);
    bSquare.setColor(0.0, 0.2,1.0);
    bTriangle.setColor(0.8, 0.8, 0.2);
    to_Main_Menu.setColor(1.0, 0.0, 0.0);
    Create.setColor(0.0,1.0,0.0);
    Edit.setColor(1.0,1.0,0.0);
    
    switch (currentMenuState)
    {
    case MAIN:
        
        Create.drawButton();
        Edit.drawButton();
        break;
    case CREATION:
        bPolygon.drawButton();
        bEllipse.drawButton();
        bCircle.drawButton();
        bRectangle.drawButton();
        bSquare.drawButton();
        bTriangle.drawButton();
        to_Main_Menu.drawButton();
    case EDIT:
        to_Main_Menu.drawButton();
        break;
    case POLYGON:
        to_Main_Menu.drawButton();
        break;
    case ELLIPSE:
        to_Main_Menu.drawButton();
        break;
    case CIRCLE:
        to_Main_Menu.drawButton();
        break;
    case RECTANGLE:
        to_Main_Menu.drawButton();
        break;
    case SQUARE:
        to_Main_Menu.drawButton();
        break;
    case TRIANGLE:
        to_Main_Menu.drawButton();
        break;
    }
    
    if (Polygons.size() != 0) {
        for (size_t i = 0; i < Polygons.size(); i++) {
            Polygons[i].draw();
        }
    }

    if (Ellipsoids.size() != 0) {
        for (size_t i = 0; i < Ellipsoids.size(); i++) {
            Ellipsoids[i].draw();
        }
    }

	glutSwapBuffers();

}


int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(1000, 1000); // Размер окна
	glutCreateWindow("Template"); // Создание окна, его название
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
    glutMouseFunc(mouseClickHandler);
	srand(time(NULL));

	SetupRC();
	glutMainLoop();

}

