//
//  MessageManager.h
//  Sedimental Storm
//
//  Created by Max Savage on 1/22/15.
//  Copyright (c) 2015 Max Savage. All rights reserved.
//

#include <map>
#include <list>
#include <queue>
#include <string>

#include "IEventManager.h"
#include "EventEnums.h"

// Setup stuff, create instance of map, queues, list
const unsigned int EVENTMANAGER_NUM_QUEUES = 2;

class MessageManager : public IEventManager
{
	typedef std::list<EventListenerDelegate> EventListenerList;
	typedef std::map<EventType, EventListenerList> EventListenerMap;
	typedef std::list<IEventDataPtr> EventQueue;
	EventListenerMap m_eventListeners;
	EventQueue m_queues[EVENTMANAGER_NUM_QUEUES];
	int m_activeQueue; 

	public:

		explicit MessageManager(const char* pName, bool setAsGlobal);
		virtual ˜MessageManager(void) { }

		// Good stuff down here


		// Matches a delegate function with an event type, so anytime the event type is sent, the delegate will be called.
		// Use to add new delegate to the list, do not double register delegates.
		virtual bool VAddListener(const EventListenerDelegate& eventDelegate, const EventType& type); 
		

		// Removes a delegate. 
		// Use to edit list of delegates. Remove components upon object destruction, etc.
		virtual bool VRemoveListener(const EventListenerDelegate& eventDelegate, const EventType& type);
	

		// Immediately fires an event to listeners that care about it.
		// Subvert queue to immediately trigger event passed. Use sparingly.
		virtual bool VTriggerEvent(const IEventDataPtr& pEvent) const;


		// Puts an event in a queue to be fired later.
		// Standard event trigger call. Use a bunch.
		virtual bool VQueueEvent(const IEventDataPtr& pEvent); 


		// Removes first queued event.
		virtual bool VAbortEvent(const EventType& type, bool allOfType = false); 


		// Processes the events in the queue. This is called every game loop.
		// Updates all of the above stuff.
		virtual bool Update(unsigned long maxMillis = kINFINITE); 

};
