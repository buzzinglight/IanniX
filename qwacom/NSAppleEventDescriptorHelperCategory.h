/*----------------------------------------------------------------------------

NAME

NSAppleEventDescriptorHelperCategory.h


COPYRIGHT

Copyright WACOM Technologies, Inc. 2008
All rights reserved.

-----------------------------------------------------------------------------*/
#pragma once

#include <Cocoa/Cocoa.h>



///////////////////////////////////////////////////////////////////////////////
@interface NSAppleEventDescriptor (WacomExtension)


+ (NSAppleEventDescriptor *)descriptorWithUInt32:(UInt32)unsignedInt;

+ (NSAppleEventDescriptor *)descriptorForObjectOfType:(DescType)objType
                                withKey:(NSAppleEventDescriptor *)keyDesc
											ofForm:(DescType)keyForm;

+ (NSAppleEventDescriptor *)descriptorForObjectOfType:(DescType)objType
										  withKey:(NSAppleEventDescriptor *)keyDesc
                                 ofForm:(DescType)keyForm
                                   from:(NSAppleEventDescriptor *)fromDesc;

- (OSErr)sendWithPriority:(UInt32)priority andTimeout:(UInt32)timeout;

- (NSAppleEventDescriptor*)sendExpectingReplyWithPriority:(UInt32)priority 
									  andTimeout:(UInt32)timeout;
@end



///////////////////////////////////////////////////////////////////////////////
