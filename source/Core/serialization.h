#pragma once
#include <maya/MObject.h>
#include <cstdint>
#include <string>


namespace Mithrig
{ 
	namespace Serialize
	{

		std::string obj(const MObject& obj);


	}

	namespace Deserialize
	{

		MObject obj(const std::string& uuid);

	}

}