/*----------------------------------------------------------------------------

FILE NAME
	WacomTabletDriver.h

PURPOSE
	Apple Event access to the Wacom tablet driver.

COPYRIGHT
	Copyright WACOM Technology, Inc.  2008 - 2010.
	All rights reserved.

----------------------------------------------------------------------------*/
#import <Cocoa/Cocoa.h>
#import "TabletAEDictionary.h"

// All Apple Event indices are 1-based
#define kInvalidAppleEventIndex 0

//////////////////////////////////////////////////////////////////////////////
@interface WacomTabletDriver : NSObject
{

}

// Context Management
+ (UInt32) createContextForTablet:(UInt32)index type:(AEContextType)contextType;
+ (void) destroyContext:(UInt32)context;

// Get Data
+ (NSAppleEventDescriptor*) dataForAttribute:(DescType)attribute 
												  ofType:(DescType)dataType 
										  routingTable:(NSAppleEventDescriptor *)routingDesc;
										  
+ (UInt32) controlCountOfContext:(UInt32)context 
						forControlType:(eAETabletControlType)controlType;
						
+ (UInt32) functionCountOfControl:(UInt32)control 
								ofContext:(UInt32)context 
						 forControlType:(eAETabletControlType)controlType;

+ (UInt32) tabletCount;
+ (UInt32) transducerCountForTablet:(UInt32)tablet;

// Set Data
+ (BOOL) setBytes:(void*)bytes 
			  ofSize:(UInt32)size 
			  ofType:(DescType)dataType 
	  forAttribute:(DescType)attribute 
	  routingTable:(NSAppleEventDescriptor *)routingDesc;
	  
// Apple Event routing tables

// - Raw
+ (NSAppleEventDescriptor *) routingTableForDriver;
+ (NSAppleEventDescriptor *) routingTableForTablet:(UInt32)tablet;
+ (NSAppleEventDescriptor *) routingTableForTablet:(UInt32)context transducer:(UInt32)transducer;

// - Context-based
+ (NSAppleEventDescriptor *) routingTableForContext:(UInt32)context;
+ (NSAppleEventDescriptor *) routingTableForContext:(UInt32)context control:(UInt32)control controlType:(eAETabletControlType)controlType;
+ (NSAppleEventDescriptor *) routingTableForContext:(UInt32)context control:(UInt32)control controlType:(eAETabletControlType)controlType function:(UInt32)function;

// Utilities
+ (NSAppleEventDescriptor *)driverAppleEventTarget;
+ (DescType)descTypeFromControlType:(eAETabletControlType)controlType;
+ (void) resendLastTabletEventOfType:(DescType)tabletEventType;

@end
