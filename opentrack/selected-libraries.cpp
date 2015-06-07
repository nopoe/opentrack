#include "opentrack/selected-libraries.hpp"
#include <QDebug>

SelectedLibraries::~SelectedLibraries()
{
}

template<typename t>
static mem<t> make_instance(mem<dylib> lib)
{
    mem<t> ret;
    if (lib != nullptr && lib->Constructor)
        ret = mem<t>(reinterpret_cast<t*>(reinterpret_cast<OPENTRACK_CTOR_FUNPTR>(lib->Constructor)()));
    return ret;
}

SelectedLibraries::SelectedLibraries(QFrame* frame, dylibptr t, dylibptr p, dylibptr f) :
    pTracker(nullptr),
    pFilter(nullptr),
    pProtocol(nullptr),
    correct(false)
{
    pTracker = make_instance<ITracker>(t);
    pProtocol = make_instance<IProtocol>(p);
    pFilter = make_instance<IFilter>(f);

    if (!pTracker || !pProtocol)
    {
        qDebug() << "dylib load failure";
        return;
    }

    if(!pProtocol->correct())
    {
        qDebug() << "protocol load failure";
        return;
    }

    pTracker->start_tracker(frame);

    correct = true;
}
