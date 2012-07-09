/*----------------------------------------------------------------------------

NAME

NSAppleEventDescriptorHelperCategory.m


COPYRIGHT

Copyright WACOM Technologies, Inc. 2008
All rights reserved.

-----------------------------------------------------------------------------*/

#import "NSAppleEventDescriptorHelperCategory.h"

#import <Carbon/Carbon.h>


///////////////////////////////////////////////////////////////////////////////
@implementation NSAppleEventDescriptor (WacomExtension)



//////////////////////////////////////////////////////////////////////////////
// descriptorForObjectOfType:withKey:ofForm:
//
//	Purpose:
//		Create an autoreleased NSAppleEventDescriptor instance for an Apple Event 
//		object from type objType, key keyDesc, and form key.
//
//	Parameters:
//		objType - The object class of the desired Apple event objects.
//		keyDesc - The key data for the object specifier.
//		keyForm - The key form for the object specifier.
//
//	Return:
//		An NSAppleEventDescriptor instance or nil in case of error.
//
//	Notes:
//		This is used to create descriptor for an object that has no container.
//
+ (NSAppleEventDescriptor *) descriptorForObjectOfType:(DescType)objType
															  withKey:(NSAppleEventDescriptor *)keyDesc
																ofForm:(DescType)keyForm
{
	NSAppleEventDescriptor *result = nil;
	AEDesc resultDesc;
	OSErr err = CreateObjSpecifier(objType,
											(AEDesc*)[[NSAppleEventDescriptor nullDescriptor] aeDesc], // null descriptor means no container
											keyForm,
											(AEDesc*)[keyDesc aeDesc],
											NO,
											&resultDesc);
	if (err == noErr)
	{
		result = [[[NSAppleEventDescriptor alloc] initWithAEDescNoCopy:&resultDesc] autorelease];
	}
	return result;
}



//////////////////////////////////////////////////////////////////////////////
// descriptorForObjectOfType:withKey:ofForm:from:
//
//	Purpose:
//		Create an autoreleased NSAppleEventDescriptor instance for an Apple Event 
//		object from type objType, key keyDesc, and form key.
//
//	Parameters:
//		objType	- The object class of the desired Apple event objects.
//		keyDesc	- The key data for the object specifier record.
//		keyForm	- The key form for the object specifier record.
//		fromDesc	- The container object of the requested Apple Event object.
//
//	Return:
//		An NSAppleEventDescriptor instance or nil in case of error.
//
+ (NSAppleEventDescriptor *) descriptorForObjectOfType:(DescType)objType
															  withKey:(NSAppleEventDescriptor *)keyDesc
																ofForm:(DescType)keyForm
																  from:(NSAppleEventDescriptor *)fromDesc
{
	NSAppleEventDescriptor  *result     = nil;
	AEDesc                  resultDesc;
	
	OSErr err = CreateObjSpecifier(objType,
											(AEDesc*)[fromDesc aeDesc],
											keyForm,
											(AEDesc*)[keyDesc aeDesc],
											NO,
											&resultDesc);
	if (err == noErr)
	{
		result = [[[NSAppleEventDescriptor alloc] initWithAEDescNoCopy:&resultDesc] autorelease];
	}
	return result;
}



//////////////////////////////////////////////////////////////////////////////
// descriptorWithUInt32:
//
//	Purpose:
//		Create and return an autoreleased NSAppleEventDescriptor that contains 
//		an UIInt32 value.
//
//	Parameters:
//		unsignedInt - The UInt32 value to place into the Apple Event descriptor.
//
//	Return:
//		An NSAppleEventDescriptor instance that represents an UIInt32 value.
//
+ (NSAppleEventDescriptor *)descriptorWithUInt32:(UInt32)unsignedInt
{
	return [NSAppleEventDescriptor descriptorWithDescriptorType:typeUInt32
						bytes:&unsignedInt length:sizeof(unsignedInt)];
}



//////////////////////////////////////////////////////////////////////////////
// sendWithPriority:andTimeout:
//
//	Purpose:
//		Send the Apple Event represented by this NSAppleEventDescriptor
//		without waiting for a reply from the target.
//
//	Parameters:
//		priority - Priority for the delivery of the Apple Event.
//		timeout - Timeout in ticks.
//
//	Return:
//		An OSErr code.
//
- (OSErr) sendWithPriority:(UInt32)priority andTimeout:(UInt32)timeout
{
	// send the apple event without waiting for a reply
	return AESend([self aeDesc], NULL, kAENoReply, priority, timeout, NULL, NULL);
}



//////////////////////////////////////////////////////////////////////////////
// sendExpectingReplyWithPriority:andTimeout:
//
//	Purpose:
//		Send the Apple Event represented by this NSAppleEventDescriptor.
//		This method waits for a reply from the target and returns the reply
//		as an NSAppleEventDescriptor.
//
//	Parameters:
//		priority - Priority for the delivery of the Apple Event.
//		timeout - Timeout in ticks.
//
//	Return:
//		An autoreleased NSAppleEventDescriptor that contains the reply or
//		nil if error occurs.
//
- (NSAppleEventDescriptor*) sendExpectingReplyWithPriority:(UInt32)priority 
																andTimeout:(UInt32)timeout
{
	NSAppleEventDescriptor *result = nil;
	AppleEvent resultDesc;
	
	// send the apple event
	OSErr err = AESend([self aeDesc], &resultDesc, kAEWaitReply, priority, timeout, NULL, NULL);
	
	// get the reply
	if (err == noErr)
	{
		result = [[[NSAppleEventDescriptor alloc] initWithAEDescNoCopy:&resultDesc] autorelease];
	}

	return result;
}



///////////////////////////////////////////////////////////////////////////////
@end



///////////////////////////////////////////////////////////////////////////////
