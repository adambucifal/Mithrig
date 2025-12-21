#include <maya/MPxCommand.h>
#include <maya/MArgList.h>
#include <maya/MSyntax.h>
#include <maya/MObject.h>


namespace Mithrig 
{

	class DataNodeCommand : public MPxCommand 
	{

	public:
		static void* creator() { return new DataNodeCommand; }
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
		MString m_name;
		MString m_type;

	};

}
