#include "..\ftnoir_tracker_base\ftnoir_tracker_base.h"
#include "ui_FTNoIR_SMClientcontrols.h"

#include <sm_api_qt.h>
#include <QMessageBox>
#include <QSettings>
#include "Windows.h"
#include "math.h"

using namespace sm::faceapi;
using namespace sm::faceapi::qt;

class FTNoIR_Tracker_SM : public ITracker
{
public:
	FTNoIR_Tracker_SM();
	~FTNoIR_Tracker_SM();

	void Release();
    void Initialize();
    void StartTracker();
	void GiveHeadPoseData(THeadPoseData *data);
	void loadSettings();

	bool setParameterValue(const int index, const float newvalue);

private:
	/** face api variables **/
	APIScope *faceapi_scope;
    QSharedPointer<EngineBase> _engine;
	smEngineHandle _engine_handle;

	THeadPoseData newHeadPose;								// Structure with new headpose

	//parameter list for the filter-function(s)
	enum
	{
		kPortAddress=0,										// Index in QList
		kNumFilterParameters								// Indicate number of parameters used
	};
	QList<std::pair<float,float>>	parameterRange;
	QList<float>					parameterValueAsFloat;

};
