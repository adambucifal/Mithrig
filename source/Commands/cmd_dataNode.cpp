#include "cmd_dataNode.h"
#include "datanode.h"
#include "names.h"
#include "config.h"

#include <maya/MArgParser.h>
#include <maya/MStatus.h>
#include <maya/MFnDependencyNode.h>
#include <maya/MGlobal.h>
#include <maya/MDGModifier.h>


MStatus Mithrig::Commands::CmdDataNode::doIt(const MArgList& args) 
{
	CHECK_MSTATUS_AND_RETURN_IT(parse_args(args));
	return redoIt();
}


MStatus Mithrig::Commands::CmdDataNode::undoIt() 
{
	if (m_node_created)
	{
		MDGModifier dgmod;
		dgmod.deleteNode(m_node);

		return dgmod.doIt();
	}

	return MS::kSuccess;
}


MStatus Mithrig::Commands::CmdDataNode::redoIt() 
{

	MStatus status;

	m_node = Mithrig::DataNode::create(m_name, m_type);
	m_node_created = true;

	MFnDependencyNode dep_fn(m_node, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);

	setResult(dep_fn.name());

	return status;
}


MSyntax Mithrig::Commands::CmdDataNode::syntax() 
{
	MSyntax syntax;

	syntax.addFlag(Config::kFlagNameShort, Config::kFlagNameLong, MSyntax::kString);
	syntax.addFlag(Config::kFlagTypeShort, Config::kFlagTypeLong, MSyntax::kString);

	return syntax;
}


MStatus Mithrig::Commands::CmdDataNode::parse_args(const MArgList& args) 
{
	MArgParser parsed(syntax(), args);

	m_name = parsed.flagArgumentString(Config::kFlagNameLong, 0);
	m_type = parsed.flagArgumentString(Config::kFlagTypeLong, 0);

	return MS::kSuccess;
}
