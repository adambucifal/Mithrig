#include "config.h"
#include "cmd_dataNode.h"

#include <maya/MFnPlugin.h>
#include <maya/MFnDependencyNode.h>
#include <maya/MGlobal.h>
#include <maya/MString.h>

using namespace Mithrig::Commands;

const MString kDataNodeCommand = "mithrigDataNode";


MStatus initializePlugin(MObject obj) 
{
	MFnPlugin plugin(obj);

	plugin.registerCommand(kDataNodeCommand, CmdDataNode::creator, CmdDataNode::syntax);

	return MS::kSuccess;
}


MStatus uninitializePlugin(MObject obj) 
{
	MFnPlugin plugin(obj);

	plugin.deregisterCommand(kDataNodeCommand);

	return MS::kSuccess;
}
