#define GL_SILENCE_DEPRECATION
#include <cstdlib>
#include <vector>
#include <GLUT/glut.h>

struct Obstacle {
    int type; // 1 for G, 2 for U, 3 for C
    int position; // X position of the obstacle
};
struct Floaters {
    int type; // 1 for Collectable, 2 for Shield, 3 for PowerUp
    int position; // X position of the floater
};
void Display();
void StandingHuman(); //done
void G();
void U();
void C();
void SlowPowerUp();
void ShieldPowerUp();
void Collectable();
void LowerBorder();
void UpperBorder();
void DrawObstacle(int obstacleType, int position);
void DrawFloater(int obstacleType, int position);
void CollisionDetection();
void Anim();

std::vector<Obstacle> obstacles; // List of obstacles
std::vector<Floaters> floaters; // List of obstacles
bool duckBool = false;
int obstacleMotion = 1000;
float movingBackground = 0;

int speed = 9;
int obstacleChoice = 0;
int lastObstacleTime = 0;
int lastFloatTime = 0;
int angle = 0;

int upAndDown = 0;
bool up = true;

void Display(){
    glClear(GL_COLOR_BUFFER_BIT);
    
    
    UpperBorder();
    
    
    //infinite lower border animation
    glPushMatrix();
    glTranslated(movingBackground, 0, 0);
    LowerBorder();
    glPopMatrix();
    glPushMatrix();
    glTranslated(movingBackground+1000, 0, 0);
    LowerBorder();
    glPopMatrix();
    
    // Draw all obstacles from the list
    for (const auto& obstacle : obstacles) {
        DrawObstacle(obstacle.type, obstacle.position);
    }




    for (const auto& floater : floaters) {
        DrawFloater(floater.type, floater.position);
    }

    
    StandingHuman();
    glutIdleFunc(Anim);
    glutPostRedisplay();
    glFlush();
}

void DrawFloater(int floaterType, int position){
    glPushMatrix();
    glTranslated(position, 600, 0);
    
    // Draw the corresponding obstacle based on its type
    switch (floaterType) {
        case 1: Collectable(); break;
        case 2:
            ShieldPowerUp();
            break;
        case 3: SlowPowerUp(); break;
    }
    glPopMatrix();
}

void DrawObstacle(int obstacleType, int position) {
    glPushMatrix();
    glTranslated(position, 0, 0);

    // Draw the corresponding obstacle based on its type
    switch (obstacleType) {
        case 1: G(); break;
        case 2:
            glPushMatrix();
            glTranslated(0, 200, 0);
            U();
            glPopMatrix();
            break;
        case 3: C(); break;
    }

    glPopMatrix();
}

void StandingHuman(){
    int duck = 0;
    if(duckBool)
        duck=40;
    //head
    glBegin(GL_QUADS);
    glColor3f(0.5, 0.5, 0.5);
    glVertex2d(125, 350-duck);
    glVertex2d(175, 350-duck);
    glVertex2d(175, 400-duck);
    glVertex2d(125, 400-duck);
    glEnd();
    //body
    glBegin(GL_TRIANGLES);
    glColor3f(0, 0, 0);
    glVertex2d(100, 250-duck);
    glVertex2d(200, 250-duck);
    glVertex2d(150, 350-duck);
    glEnd();
    //right arm
    glBegin(GL_LINES);
    glVertex2d(175, 300-duck);
    glVertex2d(210, 300-duck);
    glEnd();
    //left arm
    glBegin(GL_LINES);
    glVertex2d(125, 300-duck);
    glVertex2d(90, 300-duck);
    glEnd();
    //right leg
    glBegin(GL_LINE_STRIP);
    glVertex2d(175, 250-duck);
    glVertex2d(200, 215-duck);
    glVertex2d(175, 175);
    glEnd();
    //left leg
    glBegin(GL_LINE_STRIP);
    glVertex2d(115, 250-duck);
    glVertex2d(140, 215-duck);
    glVertex2d(115, 175);
    glEnd();
    
}

void G(){
    glColor3f(1, 0.8, 0);
    
    glPushMatrix();
    glTranslated(-250, 0, 0);
    
    glBegin(GL_QUADS);
    glVertex2d(250, 175);
    glVertex2d(325, 175);
    glVertex2d(325, 200);
    glVertex2d(275, 200);
        
    glVertex2d(250, 175);
    glVertex2d(250, 275);
    glVertex2d(275, 250);
    glVertex2d(275, 200);
    
    
    glVertex2d(275, 250);
    glVertex2d(250, 275);
    glVertex2d(325, 275);
    glVertex2d(325, 260);
    
    glVertex2d(325, 200);
    glVertex2d(315, 200);
    glVertex2d(315, 215);
    glVertex2d(325, 215);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
    glVertex2d(300, 215);
    glVertex2d(340, 215);
    glVertex2d(340, 230);
    glVertex2d(300, 230);
    glEnd();
    
    glPopMatrix();
}

void C(){
    
    glPushMatrix();
    
    glTranslated(-250, 0, 0);
    
    glColor3f(1, 0, 0);
    glBegin(GL_QUADS);
    glVertex2d(250, 175);
    glVertex2d(325, 175);
    glVertex2d(325, 200);
    glVertex2d(275, 200);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex2d(250, 175);
    glVertex2d(250, 275);
    glVertex2d(275, 250);
    glVertex2d(275, 200);
    glEnd();
    
    glBegin(GL_POLYGON);
    glVertex2d(275, 250);
    glVertex2d(250, 275);
    glVertex2d(325, 275);
    glVertex2d(325, 260);
    glEnd();
    
    glPopMatrix();
}

void U(){
    glColor3f(0, 0, 0);
    
    glBegin(GL_QUADS);
    glVertex2d(0, 175);
    glVertex2d(0, 275);
    glVertex2d(25, 250);
    glVertex2d(25, 200);
    glEnd();
    
    // Now draw the object
    glBegin(GL_LINE_LOOP);
    glVertex2d(0, 175);
    glVertex2d(75, 175);
    glVertex2d(50, 200);
    glVertex2d(25, 200);
    glEnd();
    
    glBegin(GL_POLYGON);
    glVertex2d(50, 200);
    glVertex2d(75, 175);
    glVertex2d(75, 275);
    glVertex2d(50, 250);
    glEnd();
    
}


void SlowPowerUp(){
    glColor3f(0, 1, 0);
    
    glPushMatrix();
    glTranslated(0, upAndDown, 0);
    
    glBegin(GL_POLYGON);
    glVertex2d(0, 0);
    glVertex2d(20, 10);
    glVertex2d(25, 20);
    glVertex2d(10, 23);
    glVertex2d(8, 18);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glVertex2d(25, 20);
    glVertex2d(10, 33);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex2d(10, 33);
    glVertex2d(25, 40);
    glVertex2d(10, 43);
    glVertex2d(0, 33);
    glEnd();
    glBegin(GL_LINES);
    glVertex2d(0, 33);
    glVertex2d(10, 23);
    glEnd();
    
    glPopMatrix();
    

}

void ShieldPowerUp(){
    glPointSize(5);
    glColor3f(0, 0, 1);
    
    glPushMatrix();
    glTranslated(0, upAndDown, 0);
    
    glBegin(GL_QUADS);
    glVertex2d(0, 0);
    glVertex2d(30, 0);
    glVertex2d(30, 20);
    glVertex2d(0, 20);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex2d(0, 20);
    glVertex2d(15, 20);
    glVertex2d(7, 40);
    glEnd();
    glBegin(GL_POINTS);
    glColor3f(0, 1, 1);
    glVertex2d(30, 20);
    glVertex2d(30, 40);
    glEnd();
    glColor3f(0, 0, 0);
    glBegin(GL_LINES);
    glVertex2d(30, 20);
    glVertex2d(30, 40);
    glEnd();
    
    glPopMatrix();
}

void Collectable(){
    glColor3b(0, 0, 0);
    glPushMatrix();
    glRotated(angle, 0, 0, 1);
    glBegin(GL_TRIANGLES);
    glVertex2d(0, 0);
    glVertex2d(15, 0);
    glVertex2d(7, 15);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glVertex2d(7, 15);
    glVertex2d(7, 30);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex2d(0, 30);
    glVertex2d(0, 35);
    glVertex2d(15, 35);
    glVertex2d(15, 30);
    glEnd();
    glPopMatrix();
}

void LowerBorder()
{
    glPointSize(5);
    glBegin(GL_LINES);
    glVertex2d(0, 175);
    glVertex2d(1080, 175);
    glEnd();
    glBegin(GL_POINTS);
    for (int i = 0; i<55; i++) {
        glVertex2d(10+i*20, 110);
    }
    glEnd();
    glBegin(GL_QUADS);
    for (int i = 0; i<28; i++) {
        glVertex2d(0+i*40, 0);
        glVertex2d(20+i*40, 0);
        glVertex2d(20+i*40, 50);
        glVertex2d(0+i*40, 50);
    }
    glEnd();
    
    glBegin(GL_TRIANGLES);
    for (int i = 0; i<28; i++) {
        glVertex2d(20+i*40, 0);
        glVertex2d(40+i*40, 0);
        glVertex2d(30+i*40, 50);
    }
    glEnd();
}

void UpperBorder(){
    glBegin(GL_LINES);
    glVertex2d(0, 1000 - 175);
    glVertex2d(1000, 1000 - 175);
    glEnd();
}

void Anim(){
    
    int currentTime = glutGet(GLUT_ELAPSED_TIME);
    int timeInterval = 1000 * (10-speed);
    int randomTimeInterval = rand()%2500 * 100;
    if (currentTime - lastObstacleTime >= timeInterval || lastObstacleTime == 0) {
        lastObstacleTime = currentTime;
        int randomType = 1 + (rand() % 3);
        
        obstacles.push_back({randomType, 1000});
    }

    if (currentTime - lastFloatTime >= randomTimeInterval || lastFloatTime == 0) {
        lastFloatTime = currentTime;
        int randomValue = rand() % 100;  // Generate a number between 0 and 99
        int randomFloatType;

        if (randomValue < 70) {
            randomFloatType = 1;  // 70% chance
        } else if (randomValue < 85) {
            randomFloatType = 2;  // 15% chance
        } else {
            randomFloatType = 3;  // 15% chance
        }
        
        floaters.push_back({randomFloatType, 1000});
    }
    
    // Update obstacle positions and remove those that have moved off the screen
    for (auto it = obstacles.begin(); it != obstacles.end(); ) {
        it->position -= speed; // Move the obstacle to the left

        // Remove the obstacle if it goes off the screen
        if (it->position < -1000) {
            it = obstacles.erase(it);
        } else {
            ++it;
        }
    }
    
    for(auto it = floaters.begin(); it != floaters.end(); ){
        it->position -= speed;
        
        if (it->position < -1000) {
            it = floaters.erase(it);
        } else {
            ++it;
        }
    }
    
    movingBackground-=speed;
    obstacleMotion-=speed;
    angle-=5;
    if(upAndDown==0){
        up = true;
    }
    if(upAndDown == 100){
        up = false;
    }
    
    if(up){
        upAndDown+=1;
    }
    else{
        upAndDown-=1;
    }
    
    if(movingBackground<=-1080){
        movingBackground=0;
    }
    glutPostRedisplay();
}

int main(int argc, char** argr){
    glutInit(&argc, argr);
    glutInitWindowSize(1000, 700);
    glutInitWindowPosition(150, 150);

    glutCreateWindow("Infinite Runner");
    glutDisplayFunc(Display);
    glClearColor(1, 1, 1, 0);
    gluOrtho2D(0, 1000, 0, 1000);
    glutMainLoop();
    return 0;
}




