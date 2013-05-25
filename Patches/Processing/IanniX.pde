import oscP5.*;
import netP5.*;
import java.lang.reflect.Method;

public class IanniXMessage {
  public String type;
  public IannixObject object;
  public PVector coord;
  public PVector absoluteCoord;
  public IannixObject cursor;

  public IanniXMessage(String _type, IannixObject _object, PVector _coord, PVector _absoluteCoord) {
    type          = _type;
    object        = _object;
    coord         = _coord;
    absoluteCoord = _absoluteCoord;
    cursor        = null;
  }    
  public IanniXMessage(String _type, IannixObject _object, PVector _coord, PVector _absoluteCoord, IannixObject _cursor) {
    type          = _type;
    object        = _object;
    coord         = _coord;
    absoluteCoord = _absoluteCoord;
    cursor        = _cursor;
  }
}

public class IannixObject {
  public int id;
  public String groupId;
  public IannixObject() {
    id      = 0;
    groupId = "";
  }
  public IannixObject(int _id, String _groupId) {
    id      = _id;
    groupId = _groupId;
  }
}

public class IanniX {
  private OscP5 oscManager;
  private NetAddress iannixLocation;
  private PApplet parent;
  private Method cursorsFromIanniX, triggersFromIanniX, curvesFromIanniX;
  private Method scoreStarted, scoreStopped, scoreRewinded;
  private boolean playingState, scoreHasRewinded, scoreHasStopped, scoreHasStarted;
  private ArrayList receivedCursorsMessages  = new ArrayList();
  private ArrayList receivedCurvesMessages   = new ArrayList();
  private ArrayList receivedTriggersMessages = new ArrayList();

  //Initialize a connection with IanniX
  public IanniX(PApplet _parent, String ipOfIanniX, int portInOfIannix, int portOutOfIanniX) {
    playingState     = false;
    scoreHasRewinded = true;
    scoreHasStopped  = false;
    scoreHasStarted  = false;
    parent         = _parent;
    oscManager     = new OscP5(this, portOutOfIanniX);
    iannixLocation = new NetAddress(ipOfIanniX, portInOfIannix);
    try {  
      cursorsFromIanniX  = parent.getClass().getMethod("cursorsFromIanniX", IanniXMessage.class);
    } 
    catch (Exception e) {  
      println("[IanniX interface] You may create a cursorsFromIanniX method");
    }
    try {  
      triggersFromIanniX = parent.getClass().getMethod("triggersFromIanniX", IanniXMessage.class);
    } 
    catch (Exception e) {  
      println("[IanniX interface] You may create a triggersFromIanniX method");
    }
    try {  
      curvesFromIanniX   = parent.getClass().getMethod("curvesFromIanniX", IanniXMessage.class);
    } 
    catch (Exception e) {  
      println("[IanniX interface] You may create a curvesFromIanniX method");
    }

    try {  
      scoreStarted = parent.getClass().getMethod("scoreStarted", Float.class, String.class);
    } 
    catch (Exception e) {  
      println("[IanniX interface] You may create a scoreStarted method");
    }
    try {  
      scoreStopped = parent.getClass().getMethod("scoreStopped", Float.class, String.class);
    } 
    catch (Exception e) {  
      println("[IanniX interface] You may create a scoreStopped method");
    }
    try {  
      scoreRewinded = parent.getClass().getMethod("scoreRewinded", Float.class, String.class);
    } 
    catch (Exception e) {  
      println("[IanniX interface] You may create a scoreRewinded method");
    }
  }

  //Send a message to IanniX
  public void send(String command, float... arguments) {
    OscMessage iannixMessage = new OscMessage("/iannix/" + command);
    for (int argumentsIndex = 0 ; argumentsIndex < arguments.length ; argumentsIndex++)
      iannixMessage.add(arguments[argumentsIndex]);
    oscManager.send(iannixMessage, iannixLocation);
  }

  //Event when a message is receveived from IanniX
  protected void oscEvent(OscMessage iannixMessage) {
    if ((iannixMessage.checkAddrPattern("/cursor")) && (iannixMessage.arguments().length > 7)) {
      callCursorsFromIanniX(new IanniXMessage("cursor", 
      new IannixObject((int)iannixMessage.get(0).floatValue(), iannixMessage.get(1).stringValue()), 
      new PVector(iannixMessage.get(2).floatValue(), iannixMessage.get(3).floatValue(), iannixMessage.get(4).floatValue()), 
      new PVector(iannixMessage.get(5).floatValue(), iannixMessage.get(6).floatValue(), iannixMessage.get(7).floatValue())
        ));
    }
    else if ((iannixMessage.checkAddrPattern("/curve")) && (iannixMessage.arguments().length > 7)) {
      callCurvesFromIanniX(new IanniXMessage("curve", 
      new IannixObject((int)iannixMessage.get(0).floatValue(), iannixMessage.get(1).stringValue()), 
      new PVector(iannixMessage.get(2).floatValue(), iannixMessage.get(3).floatValue(), iannixMessage.get(4).floatValue()), 
      new PVector(iannixMessage.get(5).floatValue(), iannixMessage.get(6).floatValue(), iannixMessage.get(7).floatValue())
        ));
    }
    else if ((iannixMessage.checkAddrPattern("/trigger")) && (iannixMessage.arguments().length > 9)) {
      callTriggersFromIanniX(new IanniXMessage("trigger", 
      new IannixObject((int)iannixMessage.get(0).floatValue(), iannixMessage.get(1).stringValue()), 
      new PVector(iannixMessage.get(2).floatValue(), iannixMessage.get(3).floatValue(), iannixMessage.get(4).floatValue()), 
      new PVector(iannixMessage.get(5).floatValue(), iannixMessage.get(6).floatValue(), iannixMessage.get(7).floatValue()), 
      new IannixObject((int)iannixMessage.get(8).floatValue(), iannixMessage.get(9).stringValue()) 
        ));
    }
    else if ((iannixMessage.checkAddrPattern("/transport")) && (iannixMessage.arguments().length > 2)) {
      if (iannixMessage.get(0).stringValue().equalsIgnoreCase("play"))
        callScoreStarted(iannixMessage.get(1).floatValue(), iannixMessage.get(2).stringValue());
      else if (iannixMessage.get(0).stringValue().equalsIgnoreCase("stop"))
        callScoreStopped(iannixMessage.get(1).floatValue(), iannixMessage.get(2).stringValue());
      else if (iannixMessage.get(0).stringValue().equalsIgnoreCase("fastrewind"))
        callScoreRewinded(iannixMessage.get(1).floatValue(), iannixMessage.get(2).stringValue());
    }
  }


  private void callCursorsFromIanniX(IanniXMessage message) {
    addToReceivedCursorsMessages(message);
    if (cursorsFromIanniX != null) {
      try {
        cursorsFromIanniX.invoke(parent, message);
      }  
      catch (Exception e) {
      }
    }
  }
  private void callTriggersFromIanniX(IanniXMessage message) {
    addToReceivedTriggersMessages(message);
    if (triggersFromIanniX != null) {
      try {
        triggersFromIanniX.invoke(parent, message);
      } 
      catch (Exception e) {
      }
    }
  }
  private void callCurvesFromIanniX(IanniXMessage message) {
    addToReceivedCurvesMessages(message);
    if (curvesFromIanniX != null) {
      try {
        curvesFromIanniX.invoke(parent, message);
      } 
      catch (Exception e) {
      }
    }
  }


  private void callScoreStarted(Float time, String timeStr) {
    playingState    = true;
    scoreHasStarted = true;
    if (scoreStarted != null) {
      try {
        scoreStarted.invoke(parent, time, timeStr);
      } 
      catch (Exception e) {
      }
    }
  }
  private void callScoreStopped(Float time, String timeStr) {
    playingState    = false;
    scoreHasStopped = true;
    if (scoreStopped != null) {
      try {
        scoreStopped.invoke(parent, time, timeStr);
      } 
      catch (Exception e) {
      }
    }
  }
  private void callScoreRewinded(Float time, String timeStr) {
    scoreHasRewinded = true;
    receivedCursorsMessages.clear();
    receivedTriggersMessages.clear();
    receivedCurvesMessages.clear();
    if (scoreRewinded != null) {
      try {
        scoreRewinded.invoke(parent, time, timeStr);
      } 
      catch (Exception e) {
      }
    }
  }

  private void addToReceivedCursorsMessages(IanniXMessage message) {
    receivedCursorsMessages.add(message);
    while (receivedCursorsMessages.size () > 500)
      receivedCursorsMessages.remove(0);
  }
  private void addToReceivedCurvesMessages(IanniXMessage message) {
    receivedCurvesMessages.add(message);
    while (receivedCurvesMessages.size () > 500)
      receivedCurvesMessages.remove(0);
  }
  private void addToReceivedTriggersMessages(IanniXMessage message) {
    receivedTriggersMessages.add(message);
    while (receivedTriggersMessages.size () > 500)
      receivedTriggersMessages.remove(0);
  }

  public boolean isPlaying() {
    return playingState;
  }

  public void scoreStart() {
    iannix.send("play");
  }
  public void scoreStop() {
    iannix.send("stop");
  }
  public void scoreRewind() {
    iannix.send("fastrewind");
  }

  public boolean hasReceivedCursorsMessages() {
    return (receivedCursorsMessages.size() > 0);
  }
  public boolean hasReceivedCurvesMessages() {
    return (receivedCurvesMessages.size() > 0);
  }
  public boolean hasReceivedTriggersMessages() {
    return (receivedTriggersMessages.size() > 0);
  }

  public int receivedCursorsMessagesCount() {
    return receivedCursorsMessages.size();
  }
  public int receivedTriggersMessagesCount() {
    return receivedTriggersMessages.size();
  }
  public int receivedCurvesMessagesCount() {
    return receivedCurvesMessages.size();
  }

  public IanniXMessage getReceivedCursorsMessages() {
    if (hasReceivedCursorsMessages()) {
      IanniXMessage retour = (IanniXMessage)receivedCursorsMessages.get(0);
      receivedCursorsMessages.remove(0);
      return retour;
    }
    else
      return null;
  }
  public IanniXMessage getReceivedTriggersMessages() {
    if (hasReceivedTriggersMessages()) {
      IanniXMessage retour = (IanniXMessage)receivedTriggersMessages.get(0);
      receivedTriggersMessages.remove(0);
      return retour;
    }
    else
      return null;
  }
  public IanniXMessage getReceivedCurvesMessages() {
    if (hasReceivedCurvesMessages()) {
      IanniXMessage retour = (IanniXMessage)receivedCurvesMessages.get(0);
      receivedCurvesMessages.remove(0);
      return retour;
    }
    else
      return null;
  }

  public boolean hasScoreStarted() {
    if (scoreHasStarted) {
      scoreHasStarted = false;
      return true;
    }
    else
      return false;
  }
  public boolean hasScoreStopped() {
    if (scoreHasStopped) {
      scoreHasStopped = false;
      return true;
    }
    else
      return false;
  }
  public boolean hasScoreRewinded() {
    if (scoreHasRewinded) {
      scoreHasRewinded = false;
      return true;
    }
    else
      return false;
  }
}

