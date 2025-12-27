#pragma once
#include "component.h"
#include <nlohmann/json.hpp>



namespace Mithrig {

	class IkChain : public System
	{

	public:
		//IkChain(const MString& name, const nlohmann::json& params) : System(name, params) {}

		using System::System;
		MStatus creator() override;

	};

}

