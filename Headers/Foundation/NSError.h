/** Interface for NSError for GNUStep
   Copyright (C) 2004,2006 Free Software Foundation, Inc.

   Written by:  Richard Frith-Macdonald <rfm@gnu.org>
   Date: May 2004
   
   This file is part of the GNUstep Base Library.
   
   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 3 of the License, or (at your option) any later version.
   
   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.
   
   You should have received a copy of the GNU Lesser General Public
   License along with this library; if not, write to the Free
   Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02111 USA.

   AutogsdocSource: NSError.m
   */ 

#ifndef __NSError_h_GNUSTEP_BASE_INCLUDE
#define __NSError_h_GNUSTEP_BASE_INCLUDE
#import	<GNUstepBase/GSVersionMacros.h>

#import	<Foundation/NSObject.h>

#if	OS_API_VERSION(100300,GS_API_LATEST)

#if	defined(__cplusplus)
extern "C" {
#endif

@class NSArray, NSDictionary, NSString;

/**
 * Key for user info dictionary component which describes the error in
 * a human readable format.
 */
GS_EXPORT NSString* const NSLocalizedDescriptionKey;

/**
 * Where one error has caused another, the underlying error can be stored
 * in the user info dictionary using this key.
 */
GS_EXPORT NSString* const NSUnderlyingErrorKey;

#if	OS_API_VERSION(100400,GS_API_LATEST)
/**
 * This key can be used to store the file path of a resource involved
 * in the error (eg unreadable file).
 */
GS_EXPORT NSString* const NSFilePathErrorKey;
/**
 * Key for an [NSNumber] containing an NSStringEncoding value.
 */
GS_EXPORT NSString* const NSStringEncodingErrorKey;
/**
 * This can be used to store the URLK involved in the error.
 */
GS_EXPORT NSString* const NSURLErrorKey;
/**
 * Key to store a string describing what caused the error to occur.
 */
GS_EXPORT NSString* const NSLocalizedFailureReasonErrorKey;
/**
 * Key to store an [NSArray] of strings suitable for use as the
 * titles of buttons in an alert panel used to attempt error
 * recovery in a GUI application.
 */
GS_EXPORT NSString* const NSLocalizedRecoveryOptionsErrorKey;
/**
 * Key to store a string providing a hint on how to use the buttons
 * in an alert panel.
 */
GS_EXPORT NSString* const NSLocalizedRecoverySuggestionErrorKey;
/**
 * Key to store an object which can be used to attempt to recover from
 * the error.
 */
GS_EXPORT NSString* const NSRecoveryAttempterErrorKey;
#endif

/**
 * Domain for system errors (on MACH).
 */
GS_EXPORT NSString* const NSMACHErrorDomain;
/**
 * Domain for system errors.
 */
GS_EXPORT NSString* const NSOSStatusErrorDomain;
/**
 * Domain for system and system library errors.
 */
GS_EXPORT NSString* const NSPOSIXErrorDomain;
#if	OS_API_VERSION(100400,GS_API_LATEST)
/**
 * Domain for Foundation and AppKit (base and gui) errors.
 */
GS_EXPORT NSString* const NSCocoaErrorDomain;
#endif

/**
 * Error information class.<br />
 * NSError instances are used to pass information about runtime errors
 * from lower levels to higher levels of the program.<br />
 * These should be used instead of exceptions where an error is caused
 * by external factors (such as a resource file not being present)
 * rather than a programming error (where NSException should be used).
 */
@interface NSError : NSObject <NSCopying, NSCoding>
{
@private
  int		_code;
  NSString	*_domain;
  NSDictionary	*_userInfo;
}

/**
 * Creates and returns an autoreleased NSError instance by calling
 * -initWithDomain:code:userInfo:
 */
+ (id) errorWithDomain: (NSString*)aDomain
		  code: (int)aCode
	      userInfo: (NSDictionary*)aDictionary;

/**
 * Return the error code ... which is not globally unique, just unique for
 * a particular domain.
 */
- (int) code;

/**
 * Return the domain for this instance.
 */
- (NSString*) domain;

/** <init />
 * Initialises the receiver using the supplied domain, code, and info.<br />
 * The domain must be non-nil.
 */
- (id) initWithDomain: (NSString*)aDomain
		 code: (int)aCode
	     userInfo: (NSDictionary*)aDictionary;

/**
 * Return a human readable description for the error.<br />
 * The default implementation uses the value from the user info dictionary
 * if it is available, otherwise it generates a generic one from domain
 * and code.
 */
- (NSString *) localizedDescription;

#if	OS_API_VERSION(100400,GS_API_LATEST)
/**
 * Return a human readable explanation of the reason for the error
 * (if known).  This should normally be a more discursive explanation
 * then the short one provided by the -localizedDescription method.<br />
 * The default implementation uses the value from the user info dictionary
 * if it is available, otherwise it returns nil.
 */
- (NSString *) localizedFailureReason;

/**
 * Returns an array of strings to be used as titles of buttons in an
 * alert panel when offering the user optionbs to try to recover from
 * the error.<br />
 * The default implementation uses the value from the user info dictionary
 * if it is available, otherwise it returns nil.
 */
- (NSArray *) localizedRecoveryOptions;

/**
 * Returns a string used as the secondary text in an alert panel,
 * suggesting how the user might select an option to attempt to
 * recover from the error.<br />
 * The default implementation uses the value from the user info dictionary
 * if it is available, otherwise it returns nil.
 */
- (NSString *) localizedRecoverySuggestion;

/**
 * Not yet useful in GNUstep.<br />
 * The default implementation uses the value from the user info dictionary
 * if it is available, otherwise it returns nil.
 */
- (id) recoveryAttempter;
#endif

/**
 * Return the user info for this instance (or nil if none is set)<br />
 * The <code>NSLocalizedDescriptionKey</code> should locate a human readable
 * description in the dictionary.<br /> 
 * The <code>NSUnderlyingErrorKey</code> key should locate an
 * <code>NSError</code> instance if an error is available describing any
 * underlying problem.<br />
 */
- (NSDictionary*) userInfo;
@end

#if	defined(__cplusplus)
}
#endif

#endif

#endif	/* __NSError_h_GNUSTEP_BASE_INCLUDE*/
