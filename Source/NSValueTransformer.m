/* Implementation for NSValueTransformer for GNUStep
   Copyright (C) 2006 Free Software Foundation, Inc.

   Written Dr. H. Nikolaus Schaller
   Created on Mon Mar 21 2005.
   Updated (thread safety) by Richard Frith-Macdonald
   
   This file is part of the GNUstep Base Library.

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.
   
   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.
   
   You should have received a copy of the GNU Library General Public
   License along with this library; if not, write to the Free
   Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02111 USA.
   */ 

#import "Foundation/Foundation.h"
#import "GNUstepBase/GSLock.h"

@interface NSNegateBooleanTransformer : NSValueTransformer
@end

@interface NSIsNilTransformer : NSValueTransformer
@end

@interface NSIsNotNilTransformer : NSValueTransformer
@end

@interface NSUnarchiveFromDataTransformer : NSValueTransformer
@end


@implementation NSValueTransformer

NSString * const NSNegateBooleanTransformerName
  = @"NSNegateBooleanTransformerName";
NSString * const NSIsNilTransformerName
  = @"NSIsNilTransformerName";
NSString * const NSIsNotNilTransformerName
  = @"NSIsNotNilTransformerName"; 
NSString * const NSUnarchiveFromDataTransformerName
  = @"NSUnarchiveFromDataTransformerName";

// non-abstract methods

static NSMutableDictionary *registry = nil;
static GSLazyLock *lock = nil;

+ (void) initialize
{
  if (lock == nil)
    {
      NSValueTransformer	*t;

      lock = [GSLazyLock new];
      registry = [[NSMutableDictionary alloc] init];

      t = [NSNegateBooleanTransformer new];
      [self setValueTransformer: t
		        forName: NSNegateBooleanTransformerName];
      RELEASE(t);

      t = [NSIsNilTransformer new];
      [self setValueTransformer: t
		        forName: NSIsNilTransformerName];
      RELEASE(t);

      t = [NSIsNotNilTransformer new];
      [self setValueTransformer: t
		        forName: NSIsNotNilTransformerName];
      RELEASE(t);

      t = [NSUnarchiveFromDataTransformer new];
      [self setValueTransformer: t
		        forName: NSUnarchiveFromDataTransformerName];
      RELEASE(t);
    }
}

+ (void) setValueTransformer: (NSValueTransformer *)transformer
		     forName: (NSString *)name
{
  [lock lock];
  [registry setObject: transformer forKey: name];
  [lock unlock];
}

+ (NSValueTransformer *) valueTransformerForName: (NSString *)name
{
  NSValueTransformer	*transformer;

  [lock lock];
  transformer = [registry objectForKey: name];
  RETAIN(transformer);
  [lock unlock];
  return AUTORELEASE(transformer);
}

+ (NSArray *) valueTransformerNames;
{
  NSArray	*names;

  [lock lock];
  names = [registry allKeys];
  [lock unlock];
  return names;
}

+ (BOOL) allowsReverseTransformation
{
  [self subclassResponsibility: _cmd];
  return NO;
}

+ (Class) transformedValueClass
{
  return [self subclassResponsibility: _cmd];
}

- (id) reverseTransformedValue: (id)value
{
  if ([[self class] allowsReverseTransformation] == NO)
    {
      [NSException raise: NSGenericException
      		  format: @"[%@] is not reversible",
	NSStringFromClass([self class])];
    }
  return [self transformedValue: value];
}

- (id) transformedValue: (id)value
{
  return [self subclassResponsibility: _cmd];
}

@end

// builtin transformers

@implementation NSNegateBooleanTransformer

+ (BOOL) allowsReverseTransformation
{
  return YES;
}

+ (Class) transformedValueClass
{
  return [NSNumber class];
}

- (id) reverseTransformedValue: (id) value
{
  return [NSNumber numberWithBool: [value boolValue] ? NO : YES];
}

- (id) transformedValue: (id)value
{
  return [NSNumber numberWithBool: [value boolValue] ? NO : YES];
}

@end

@implementation NSIsNilTransformer

+ (BOOL) allowsReverseTransformation
{
  return NO;
}

+ (Class) transformedValueClass
{
  return [NSNumber class];
}

- (id) transformedValue: (id)value
{
  return [NSNumber numberWithBool: (value == nil) ? YES : NO];
}

@end

@implementation NSIsNotNilTransformer

+ (BOOL) allowsReverseTransformation
{
  return NO;
}

+ (Class) transformedValueClass
{
  return [NSNumber class];
}

- (id) transformedValue: (id)value
{
  return [NSNumber numberWithBool: (value != nil) ? YES : NO];
}

@end

@implementation NSUnarchiveFromDataTransformer

+ (BOOL) allowsReverseTransformation
{
  return YES;
}

+ (Class) transformedValueClass
{
  return [NSData class];
}

- (id) reverseTransformedValue: (id)value
{
// FIXME ... should we use a keyed archive?
  return [NSKeyedArchiver archivedDataWithRootObject: value];
}

- (id) transformedValue: (id)value
{
// FIXME ... should we use a keyed archive?
  return [NSKeyedUnarchiver unarchiveObjectWithData: value];
}

@end
