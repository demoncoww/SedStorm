//
//  MessageManager.cpp
//  Sedimental Storm
//
//  Created by Max Savage on 1/22/15.
//  Copyright (c) 2015 Max Savage. All rights reserved.
//

// Header Include
#include "MessageManager.h"

MessageManager::MessageManager(char const * const pName, bool setAsGlobal)
	: IEventManager(pName, setAsGlobal)
{
	m_activeQueue = 0;
}

bool MessageManager::AddListener(const EventListenerDelegate& eventDelegate, const EventType& type)
{
	EventListenerList& eventListenerList = m_eventListeners[type];
	for (auto index = eventListenerList.begin(); index != eventListenerList.end(); ++index)
	{
	if (eventDelegate == (*index))
		{
		GCC_WARNING(“Attempting to double-register a delegate“);
		return false;
		}
	}
	eventListenerList.push_back(eventDelegate);
	return true;
}

bool MessageManager::RemoveListener(const EventListenerDelegate& eventDelegate, const EventType& type)
{
	bool success = false;
	auto findIndex = m_eventListeners.find(type);
	if (findIndex != m_eventListeners.end())
	{
		EventListenerList& listeners = findIndex->second;
		for (auto index = listeners.begin(); index != listeners.end(); ++index)
		{
			if (eventDelegate == (*index))
			{
				listeners.erase(index);
				success = true;
				break;
			}
		}
	}
	return success;
}

bool MessageManager::TriggerEvent(const IEventDataPtr& pEvent) const
{
	bool processed = false;
	auto findIndex = m_eventListeners.find(pEvent->VGetEventType());
		if (findIndex != m_eventListeners.end())
		{
		const EventListenerList& eventListenerList = findIndex->second;
		for (EventListenerList::const_iterator index = eventListenerList.begin(); index != eventListenerList.end(); ++index)
		{
			EventListenerDelegate listener = (*index);
			listener(pEvent);
			processed = true;
		}
	}
	return processed;
}

bool MessageManager::QueueEvent(const IEventDataPtr& pEvent)
{
	GCC_ASSERT(m_activeQueue >= 0);
	GCC_ASSERT(m_activeQueue < EVENTMANAGER_NUM_QUEUES);
	auto findIndex = m_eventListeners.find(pEvent->VGetEventType());
	if (findIndex != m_eventListeners.end())
	{
		m_queues[m_activeQueue].push_back(pEvent);
		return true;
	}
	else
	{
		return false;
	}
}

bool MessageManager::AbortEvent(const EventType& inType, bool allOfType)
{
	GCC_ASSERT(m_activeQueue >= 0);
	GCC_ASSERT(m_activeQueue < EVENTMANAGER_NUM_QUEUES);
	bool success = false;
	EventListenerMap::iterator findIndex = m_eventListeners.find(inType);
	if (findIndex != m_eventListeners.end())
	{
		EventQueue& eventQueue = m_queues[m_activeQueue];
		auto index = eventQueue.begin();
		while (index != eventQueue.end())
		{
// Removing an item from the queue will invalidate the iterator, so
// have it point to the next member. All work inside this loop will
// be done using thisIndex.
			auto thisIndex = index;
			++index;
			if ((*thisIndex)->VGetEventType() == inType)
			{
				eventQueue.erase(thisIt);
				success = true;
				if (!allOfType)
				break;
			}
		}
	}
	return success;
}

bool MessageManager::update(unsigned long maxMillis)
{
	unsigned long currMs = GetTickCount();
	unsigned long maxMs = ((maxMillis == IEventManager::kINFINITE) ?
	(IEventManager::kINFINITE) :
	(currMs + maxMillis));
// swap active queues and clear the new queue after the swap
	int queueToProcess = m_activeQueue;
	m_activeQueue = (m_activeQueue + 1) % EVENTMANAGER_NUM_QUEUES;
	m_queues[m_activeQueue].clear();
// Process the queue
	while (!m_queues[queueToProcess].empty())
	{
// pop the front of the queue
		IEventDataPtr pEvent = m_queues[queueToProcess].front();
		m_queues[queueToProcess].pop_front();
		const EventType& eventType = pEvent->VGetEventType();
// find all the delegate functions registered for this event