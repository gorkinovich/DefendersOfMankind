#include "NodeLA.h"

#include "LatentAction.h"

namespace AI
{
	// -----------------------------------------------------------

	CNodeLA::~CNodeLA(void)
	{
		if (_action != NULL) 
			delete _action;
	}

	// -----------------------------------------------------------

	BEHAVIOR_STATUS CNodeLA::execute(void* context)
	{
		// Comprobamos si la LA ya había terminado.
		// Si hacemos la llamada sin esta comprobación y la LA ya 
		// ha terminado, se volvería a llamar al método onStop
		CLatentAction::LAStatus status = _action->getStatus();
		if (status == CLatentAction::SUCCESS) {
			return BT_SUCCESS;		
		} 
		if (status == CLatentAction::FAIL) {
			return BT_FAILURE;
		}
		// Ejecutamos la LA
		status = _action->update();
		// Transformamos el resultado en un valor que entiendan los BTs
		if (status == CLatentAction::SUCCESS) {
			return BT_SUCCESS;		
		} 
		if (status == CLatentAction::FAIL) {
			return BT_FAILURE;
		}
		return BT_RUNNING;
	}

	// -----------------------------------------------------------

	void CNodeLA::init(void* agent)
	{
		if (_action->getStatus() != CLatentAction::READY) {
			_action->reset();
		}
	}

	// -----------------------------------------------------------

	bool CNodeLA::accept(const Core::SmartMessage & message)
	{
		return _action->accept(message);
	}

	// -----------------------------------------------------------

	void CNodeLA::process(const Core::SmartMessage & message)
	{
		_action->process(message);
	}

	// -----------------------------------------------------------

	void CNodeLA::useContext(CBehaviorExecutionContext* context)
	{
		BehaviorTreeNode::useContext(context);
		_action->useContext(context);
	}

}
