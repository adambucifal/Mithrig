#include <maya/MPxCommand.h>
#include <maya/MArgList.h>
#include <maya/MSyntax.h>
#include <maya/MObject.h>


namespace Mithrig::Commands 
{
	class CmdDataNode : public MPxCommand 
	{
	public:

		static void* creator() { return new CmdDataNode; }
		static MSyntax syntax();

		MStatus doIt(const MArgList& args) override;
		MStatus undoIt() override;
		MStatus redoIt() override;
		bool isUndoable() const override { return true; }
		bool hasSyntax() const override { return true; }

	private:

		MStatus parse_args(const MArgList& args);
	
	private:
		MObject m_node;
		bool m_node_created = false;

		MString m_name;
		MString m_type;
	};
}
