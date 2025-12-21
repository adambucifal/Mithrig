#include "config.h"
#include "cmd_dataNode.h"

#include <maya/MFnPlugin.h>
#include <maya/MFnDependencyNode.h>
#include <maya/MGlobal.h>
#include <maya/MString.h>


const MString kDataNodeCommand = "mithrigDataNode";


MStatus initializePlugin(MObject obj) 
{
	MFnPlugin plugin(obj);

	plugin.registerCommand(kDataNodeCommand, Mithrig::DataNodeCommand::creator, Mithrig::DataNodeCommand::syntax);

	return MS::kSuccess;
}


MStatus uninitializePlugin(MObject obj) 
{
	MFnPlugin plugin(obj);

	plugin.deregisterCommand(kDataNodeCommand);

	return MS::kSuccess;
}
