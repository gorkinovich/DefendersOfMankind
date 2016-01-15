//#include "BehaviorTree.h"
#include "NodeRepeat.h"

#include <assert.h>

using namespace std;

namespace AI
{

	// -----------------------------------------------------------

	BEHAVIOR_STATUS CNodeRepeat::execute(void* agent)
	{
		if (children.size()== 0)
			return BT_SUCCESS;
		else
		{
			BEHAVIOR_STATUS status = children.at(0)->execute(agent);
			if (status == BT_SUCCESS)
			{
				if (target!= -1) {
					count++;
					if (count == target)
					{
						init(agent);
						return BT_SUCCESS;
					}
				}
				initChildren(agent);
				return BT_RUNNING;
			}
			return status;
		}
	}

	// -----------------------------------------------------------

	void CNodeRepeat::init( void* agent )
	{
		count = 0;
		initChildren(agent);
	}

	// -----------------------------------------------------------

	void CNodeRepeat::initChildren(void * agent)
	{
		if (children.size() == 1)
			children.at(0)->init(agent);
	}

	// -----------------------------------------------------------

	BehaviorTreeInternalNode* CNodeRepeat::addChild( BehaviorTreeNode* newChild )
	{
		assert(children.size() == 0);
		BehaviorTreeInternalNode::addChild(newChild);
		return this;
	}

	// -----------------------------------------------------------

	CNodeRepeat::CNodeRepeat(int repeats)
	{
		target = repeats;
		count = 0;
	};

}	// namespace AI