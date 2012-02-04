import oscP5.*;
import netP5.*;
import java.awt.geom.Point2D;

OscP5 oscManager;
NetAddress iannixLocation;

PVector points[] = new PVector[60];
int previousMouseX = 0, previousMouseY = 0;


void setup() {
  //Screen size
  size(800, 600);
  noStroke();
  background(0);
  smooth();
  pointsInit();

  //Initialize connection with IanniX
  iannixInit("127.0.0.1", 1234, 57120);
}

void pointsInit() {
  //Allocate objects
  for(int pointsIndex = 0 ; pointsIndex < points.length ; pointsIndex++)
    points[pointsIndex] = new PVector(-1, -1);
}

void draw() {
  //Black background
  fill(0, 0, 0, 5);
  rect(0, 0, width, height);

  //X-Y mouse coordonates are mapped on lines colors and score speed
  if(previousMouseY != mouseY)
    iannixSend("setColorActive2 lines ", map(mouseY, 0, height, 0, 360), 255, 255, 255);
  previousMouseY = mouseY;
  if(previousMouseX != mouseX)
    iannixSend("speed", map(mouseX, 0, width, 0, 1));
  previousMouseX = mouseX;

  //Draw received points
  fill(200, 255, 80);
  for(int pointsIndex = 0 ; pointsIndex < points.length ; pointsIndex++) {
    if((points[pointsIndex].x != 0) && (points[pointsIndex].y != 0))
      ellipse(map(points[pointsIndex].x, 0, 1, 0, width), map(points[pointsIndex].y, 1, 0, 0, height), 10, 10);
  }
}


//Initialize a connection with IanniX
void iannixInit(String ip, int port, int localPort) {
  oscManager = new OscP5(this, localPort);
  iannixLocation = new NetAddress(ip, port);
}

//Send a message to IanniX
void iannixSend(String command, float... arguments) {
  OscMessage iannixMessage = new OscMessage("/iannix/" + command);
  for(int argumentsIndex = 0 ; argumentsIndex < arguments.length ; argumentsIndex++)
    iannixMessage.add(arguments[argumentsIndex]);
  oscManager.send(iannixMessage, iannixLocation);
}

//Event when a message is receveived from IanniX
void oscEvent(OscMessage iannixMessage) {
  if((iannixMessage.checkAddrPattern("/cursor")) && (iannixMessage.arguments().length > 2)) {
    int cursor_id = (int)iannixMessage.get(0).floatValue();
    float cursor_x_value = iannixMessage.get(1).floatValue();
    float cursor_y_value = iannixMessage.get(2).floatValue();

    if(cursor_id < points.length) {
      points[cursor_id].x = cursor_x_value;
      points[cursor_id].y = cursor_y_value;
    }
  }
  else if((iannixMessage.checkAddrPattern("/transport")) && (iannixMessage.arguments().length > 1)) {
    String statut = (String)iannixMessage.get(0).stringValue();
    if(statut.equals("play"))
      pointsInit();
  }
}

