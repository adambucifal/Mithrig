#pragma once
#include <maya/MString.h>


namespace Mithrig::Config 
{

	// Plugin
	constexpr const char kName[] = "Mithrig";
	constexpr const char kVersion[] = "1.0.0";
	constexpr const char kDeveloperFullName[] = "Adam Bucifal";

	// Commands
	constexpr const char kCommandPrefix[] = "mithrig";

	// Commands Flags
	static constexpr const char kFlagNameShort[] = "n";
	static constexpr const char kFlagNameLong[] = "name";

	static constexpr const char kFlagTypeShort[] = "t";
	static constexpr const char kFlagTypeLong[] = "type";

	// Naming
	constexpr const char kNamingIncrementChar = '#';
	constexpr const char kNamingIncrement[] = "###";
	const MString kNamingIncrementString = kNamingIncrement;
	
	// DataNode
	constexpr const char kDataNodeAffix[] = "datanode";
	constexpr const char kDataNodeAttributeType[] = "type";

}
