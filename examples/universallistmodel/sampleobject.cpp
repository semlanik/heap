#include "sampleobject.h"

SampleObject::SampleObject(int aParam1, float aParam2, const QString& aName) : QObject()
  ,m_param1(aParam1)
  ,m_param2(aParam2)
  ,m_name(aName)
{

}
