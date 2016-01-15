#include "NodeSequential.h"

using namespace std;

namespace AI
{
	// -----------------------------------------------------------

	CNodeSequential::CNodeSequential()
	{
		_name = "Sequence";
		currentPosition = -1;
	}

	// -----------------------------------------------------------
	
	void CNodeSequential::init(void* agent)
	{
		currentPosition = -1;
		for (BehaviorTreeListIter iter = children.begin(); iter!= children.end(); iter++)
			(*iter)->init(agent);
	}

	// -----------------------------------------------------------
	
	BEHAVIOR_STATUS CNodeSequential::execute(void* agent)
	{
		// GGG
		//printf("%s > ", _name.c_str());
		if (currentPosition == -1) //starting out
		{
			init(agent);
			currentPosition = 0;
		}

		if (children.size() == 0)
			return BT_SUCCESS;

		BehaviorTreeNode* currentTask = children.at(currentPosition);
		BEHAVIOR_STATUS result = currentTask->execute(agent);

		while(result == BT_SUCCESS)
		{
			if (currentPosition == children.size()-1) //finished last task
			{
				currentPosition = -1; //indicate we are not running anything
				return BT_SUCCESS;
			}
			else
			{
				currentPosition++;
				currentTask = children.at(currentPosition);
				result = currentTask->execute(agent);
			}
		}
		if (result == BT_FAILURE)
			currentPosition = -1;
		return result;
	}


}	// namespace AI
