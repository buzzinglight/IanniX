#include <QObject>
#include <QTabletEvent>

class ExtWacomManager {
public:
    explicit ExtWacomManager();
    ~ExtWacomManager();

public:
    qreal absoluteX, absoluteY, absoluteZ, pressure, tangentialPressure, tiltX, tiltY, rotation;
    quint16 deviceID;

protected:
    quint32 mLastUsedTablet, mContextID, mTabletOfContext;

public:
    void setMouseControl(bool val);
    void setValuesFromEvent(void*);
};
