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
