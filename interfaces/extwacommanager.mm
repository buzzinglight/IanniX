#include "extwacommanager.h"

#import <Cocoa/Cocoa.h>
#import "qwacom/WacomTabletDriver.h"
#import "qwacom/TabletAEDictionary.h"

ExtWacomManager::ExtWacomManager() {
    mLastUsedTablet   = 0;
    mContextID        = 0;
    mTabletOfContext  = 0;

    absoluteX = absoluteY = absoluteZ = pressure = tangentialPressure = tiltX = tiltY = rotation = deviceID = 0;

    NSEventMask observedTypes =	 NSTabletPointMask
                                            |	NSTabletProximityMask

                                            |	NSMouseMovedMask
                                            |	NSLeftMouseDraggedMask
                                            |	NSRightMouseDraggedMask
                                            |	NSOtherMouseDraggedMask

                                            |	NSLeftMouseDownMask
                                            |	NSRightMouseDownMask
                                            |	NSOtherMouseDownMask

                                            |	NSLeftMouseUpMask
                                            |	NSRightMouseUpMask
                                            |	NSOtherMouseUpMask;

    // We will watch and log all these events as they come to us.
    [NSEvent addLocalMonitorForEventsMatchingMask:observedTypes handler:^(NSEvent* theEvent) {
                                                          setValuesFromEvent(theEvent);
                                                          return theEvent;
                                                      }];
}

ExtWacomManager::~ExtWacomManager() {
    if(mContextID)
        [WacomTabletDriver destroyContext:mContextID];
}

void ExtWacomManager::setMouseControl(bool val) {
    // If we changed tablets since creating the context, we need to start over
    if((mLastUsedTablet != mTabletOfContext) && (mContextID)) {
        [WacomTabletDriver destroyContext:mContextID];
        mContextID = 0;
    }
    // If no context, create one
    if(!mContextID) {
        mContextID        = [WacomTabletDriver createContextForTablet:mLastUsedTablet type:pContextTypeDefault];
        mTabletOfContext  = mLastUsedTablet;
    }

    NSAppleEventDescriptor  *routingDesc   = [WacomTabletDriver routingTableForContext:mContextID];
    Boolean                 newMovesCursor = val;

    [WacomTabletDriver setBytes:&newMovesCursor
                                ofSize:sizeof(Boolean)
                                ofType:typeBoolean
                                forAttribute:pContextMovesSystemCursor
                                routingTable:routingDesc];
}

void ExtWacomManager::setValuesFromEvent(void *event) {
    NSEvent     *theEvent            = (NSEvent*)event;
    NSEventType eventType            = [theEvent type];
    BOOL        isMouseEvent         = NO;
    BOOL        isTabletPointEvent   = NO;


    // Establish which events we may safely query for subtype
    if(eventType == NSMouseMoved
        ||	eventType == NSLeftMouseDragged
        ||	eventType == NSRightMouseDragged
        ||	eventType == NSOtherMouseDragged

        ||	eventType == NSLeftMouseDown
        ||	eventType == NSRightMouseDown
        ||	eventType == NSOtherMouseDown

        ||	eventType == NSLeftMouseUp
        ||	eventType == NSRightMouseUp
        ||	eventType == NSOtherMouseUp ) {
        isMouseEvent = YES;
    }

    // Find tablet point events (both pure and embedded)
    if(eventType == NSTabletPoint || (isMouseEvent == YES &&	[theEvent subtype] == NSTabletPointEventSubtype))
        isTabletPointEvent = YES;

    if(eventType == NSTabletProximity) {
        qDebug("%d", mLastUsedTablet);
        mLastUsedTablet = [theEvent systemTabletID];
        qDebug("%d", mLastUsedTablet);
        //penName           = [self nameOfPen:[theEvent pointingDeviceSerialNumber]];
    }

    // Mouse move
    if(eventType == NSMouseMoved) {
        /*
        [mMouseMoveLocationXField		setFloatValue:[theEvent locationInWindow].x];
        [mMouseMoveLocationYField		setFloatValue:[theEvent locationInWindow].y];
        [mMouseMoveDeltaXField			setFloatValue:[theEvent deltaX]];
        [mMouseMoveDeltaYField			setFloatValue:[theEvent deltaY]];
        [mMouseMoveModifiersField		setStringValue:modifierString];
        [mMouseMoveIsTabletEventField	setStringValue:(isTabletPointEvent ? @"Yes" : @"No")];
        */
    }

    // Mouse down
    if(eventType == NSLeftMouseDown || eventType == NSRightMouseDown || eventType == NSOtherMouseDown ) {
        /*
        [mMouseDownLocationXField		setFloatValue:[theEvent locationInWindow].x];
        [mMouseDownLocationYField		setFloatValue:[theEvent locationInWindow].y];
        [mMouseDownModifiersField		setStringValue:modifierString];
        [mMouseDownIsTabletEventField	setStringValue:(isTabletPointEvent ? @"Yes" : @"No")];
        */
    }

    // Mouse Dragged
    if(eventType == NSLeftMouseDragged ||	eventType == NSRightMouseDragged ||	eventType == NSOtherMouseDragged ) {
        /*
        [mMouseDragLocationXField		setFloatValue:[theEvent locationInWindow].x];
        [mMouseDragLocationYField		setFloatValue:[theEvent locationInWindow].y];
        [mMouseDragDeltaXField			setFloatValue:[theEvent deltaX]];
        [mMouseDragDeltaYField			setFloatValue:[theEvent deltaY]];
        [mMouseDragModifiersField		setStringValue:modifierString];
        [mMouseDragIsTabletEventField	setStringValue:(isTabletPointEvent ? @"Yes" : @"No")];

        [mMouseDragIsTabletEventField setNeedsDisplay:YES];
        */
    }

    // Mouse up
    if(eventType == NSLeftMouseUp || eventType == NSRightMouseUp || eventType == NSOtherMouseUp) {
        /*
        [mMouseUpLocationXField			setFloatValue:[theEvent locationInWindow].x];
        [mMouseUpLocationYField			setFloatValue:[theEvent locationInWindow].y];
        [mMouseUpModifiersField			setStringValue:modifierString];
        [mMouseUpIsTabletEventField	setStringValue:(isTabletPointEvent ? @"Yes" : @"No")];
        */
    }

    // Set field valid for Tablet Point events
    if(isTabletPointEvent == YES) {
        /*
        [mAbsoluteXField					setIntValue:[theEvent absoluteX]];
        [mAbsoluteYField					setIntValue:[theEvent absoluteY]];
        [mAbsoluteZField					setIntValue:[theEvent absoluteZ]];

        [mPressureField					setFloatValue:[theEvent pressure]];
        [mTangentialPressureField		setFloatValue:[theEvent tangentialPressure]];

        [mTiltXField						setFloatValue:[theEvent tilt].x];
        [mTiltYField						setFloatValue:[theEvent tilt].y];
        [mRotationField					setFloatValue:[theEvent rotation]];

        [mDeviceIDField					setIntValue:[theEvent deviceID]];
        */
        absoluteX          = [theEvent absoluteX];
        absoluteY          = [theEvent absoluteY];
        absoluteZ          = [theEvent absoluteZ];
        pressure           = [theEvent pressure];
        tangentialPressure = [theEvent tangentialPressure];
        tiltX              = [theEvent tilt].x;
        tiltY              = [theEvent tilt].y;
        rotation           = [theEvent rotation];
        deviceID           = [theEvent deviceID];
        qDebug("%d, %f %f %f => %f", deviceID, absoluteX, absoluteY, absoluteZ, pressure);
    }

    // Set Fields valid for point or proximity events
    if(isTabletPointEvent == YES || eventType == NSTabletProximity) {
        /*
        [mDeviceIDField					setIntValue:[theEvent deviceID]];
        */
    }

    if(eventType == NSTabletProximity) {
        /*
        [mTransducerNameField			setStringValue:penName];
        [mTransducerSerialNumberField	setStringValue:[NSString stringWithFormat:@"0x%X", [theEvent pointingDeviceSerialNumber]]];
        */
    }
}

