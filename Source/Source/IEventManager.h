#include "EventData.h"
#include "EventEnums.h"

class IEventManager
{
public:
	enum eConstants { kINFINITE = 0xffffffff };

	explicit IEventManager(const char* pName, bool setAsGlobal);
	virtual ˜IEventManager(void);

	virtual bool VAddListener(const EventListenerDelegate& eventDelegate, const EventType& type) = 0;
	virtual bool VRemoveListener(const EventListenerDelegate& eventDelegate, const EventType& type) = 0;
	virtual bool VTriggerEvent(const IEventDataPtr& pEvent) const = 0;
	virtual bool VQueueEvent(const IEventDataPtr& pEvent) = 0;
	virtual bool VAbortEvent(const EventType& type, bool allOfType = false) = 0;
	virtual bool Update(unsigned long maxMillis = kINFINITE) = 0;
	static IEventManager* Get(void);
};