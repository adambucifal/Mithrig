#include <maya/MPxCommand.h>
#include <maya/MArgList.h>
#include <maya/MSyntax.h>


namespace Mithrig::Commands {

	class CmdDataNode : public MPxCommand {

	public:

		static void* creator() { return new CmdDataNode; }
		static MSyntax syntax();

		MStatus doIt(const MArgList& args) override;
		MStatus undoIt() override;
		MStatus redoIt() override;
		bool isUndoable() const override { return true; }
		bool hasSyntax() const override { return true; }

	public:

		static constexpr const char* FLAG_NAME = "name";
		static constexpr const char* FLAG_TYPE = "type";

	private:

		MStatus parse_args(const MArgList& args);
	
	private:

		MString m_name;
		MString m_type;

	};
}
