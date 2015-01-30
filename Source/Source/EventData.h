//
//  EventData.h
//  Sedimental Storm
//
//  Created by Max Savage on 1/28/15.
//  Copyright (c) 2015 Max Savage. All rights reserved.
//

#include <functional>
#include <memory>

#include "EventEnums.h"


class IEventData
{
public:
	virtual const EventType& VGetEventType(void) const = 0;
	virtual float VGetTimeStamp(void) const = 0;
	virtual IEventDataPtr VCopy(void) const = 0;
	virtual const char* GetName(void) const = 0;
};

typedef std::shared_ptr<IEventData> IEventDataPtr; // smart ptr to IEventData
void Delegate(IEventDataPtr pEventData);
typedef std::function<IEventDataPtr> EventListenerDelegate;

class BaseEventData : public IEventData
{
	const float m_timeStamp;
	public:
		explicit BaseEventData(const float timeStamp = 0.0f) : m_timeStamp(timeStamp) { }
		virtual ˜BaseEventData(void) {}
// Returns the type of the event
		virtual const EventType& VGetEventType(void) const = 0;
		float VGetTimeStamp(void) const { return m_timeStamp; }
};