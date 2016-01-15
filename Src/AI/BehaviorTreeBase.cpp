#include "BehaviorTreeBase.h"


namespace AI
{

	BehaviorTreeInternalNode::~BehaviorTreeInternalNode()
	{
		BehaviorTreeListIter iter;
		for (iter = children.begin(); iter!= children.end(); iter++)
		{
			delete *iter;
		}
	}

	// -----------------------------------------------------------

	BehaviorTreeInternalNode* BehaviorTreeInternalNode::addChild(BehaviorTreeNode* newChild)
	{
		children.push_back(newChild);
		return this;
	};

	// -----------------------------------------------------------

	bool BehaviorTreeInternalNode::accept(const Core::SmartMessage & message)
	{
		BehaviorTreeListIter iter;
		for (iter = children.begin(); iter!= children.end(); iter++)
		{
			if ((*iter)->accept(message))
				return true;
		}
		return false;
	};

	// -----------------------------------------------------------

	void BehaviorTreeInternalNode::process(const Core::SmartMessage & message)
	{
		BehaviorTreeListIter iter;
		for (iter = children.begin(); iter!= children.end(); iter++)
		{
			if ((*iter)->accept(message))
				(*iter)->process(message);
		}
	};

	// -----------------------------------------------------------

	void BehaviorTreeInternalNode::useContext(CBehaviorExecutionContext* context) 
	{ 
		_context = context; 
		BehaviorTreeListIter iter;
		for (iter = children.begin(); iter!= children.end(); iter++)
		{
			(*iter)->useContext(context);
		}
	};


} // namespace AI